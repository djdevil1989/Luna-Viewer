/* Copyright (c) 2010
 *
 * Modular Systems All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *   3. Neither the name Modular Systems nor the names of its contributors
 *      may be used to endorse or promote products derived from this
 *      software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY MODULAR SYSTEMS AND CONTRIBUTORS �AS IS�
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MODULAR SYSTEMS OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "llviewerprecompiledheaders.h"

#include "jc_lslviewerbridge.h"
#include "llchatbar.h"
#include "llagent.h"
#include "llappviewer.h"
#include "stdtypes.h"
#include "llviewerregion.h"
#include "llworld.h"
#include "lluuid.h"
#include "llfilepicker.h"
#include "llassetstorage.h"
#include "llviewerobjectlist.h"

#include "importtracker.h"

#include "llviewerobject.h"

#include "llvoavatar.h"

#include "llinventorymodel.h"

#include "lltooldraganddrop.h"

#include "llmd5.h"

#include "llstartup.h"

#include "llcontrol.h"

#include "llviewercontrol.h"

#include "llviewergenericmessage.h"

#include "llviewerwindow.h"

#include "floaterao.h"


#define phoenix_point (LLAssetType::EType)127
#define phoenix_bridge_name "#LSL<->Client Bridge v0.09"

void cmdline_printchat(std::string message);

U8 JCLSLBridge::sBridgeStatus;
JCLSLBridge* JCLSLBridge::sInstance;
BOOL JCLSLBridge::sBuildBridge;

LLViewerObject* JCLSLBridge::sBridgeObject;

U32 JCLSLBridge::lastcall;

std::map<U32,JCBridgeCallback*> JCLSLBridge::callback_map;

S32 JCLSLBridge::l2c;
bool JCLSLBridge::l2c_inuse;

JCLSLBridge::JCLSLBridge() : LLEventTimer( (F32)1.0 )
{
	if(sInstance)
	{
		////cmdline_printchat("duplicate bridge?");
		delete this;
	}else
	{
		////cmdline_printchat("instanciated bridge");
		sInstance = this;
		lastcall = 0;
		l2c = 0;
		l2c_inuse = false;
		gSavedSettings.getControl("PhoenixBuildBridge")->getSignal()->connect(boost::bind(&updateBuildBridge, _1));
		sBuildBridge = gSavedSettings.getBOOL("PhoenixBuildBridge");
		//getPermissions();
	}
}

void JCLSLBridge::updateBuildBridge(const LLSD& data)
{
	BOOL newvalue = data.asBoolean();
	if(sBuildBridge != newvalue)
	{
		if(newvalue)
		{
			cmdline_printchat("LSLBridge reinitializing.");
			sBridgeStatus = UNINITIALIZED;
		}else
		{
			cmdline_printchat("LSLBridge process terminated.");
			sBridgeStatus = FAILED;
		}
		sBuildBridge = newvalue;
	}

}


JCLSLBridge::~JCLSLBridge()
{
}

void JCLSLBridge::send_chat_to_object(std::string& chat, S32 channel, LLUUID target)
{
	if(target.isNull())target = gAgent.getID();
	LLMessageSystem* msg = gMessageSystem;
	msg->newMessage(_PREHASH_ScriptDialogReply);
	msg->nextBlock(_PREHASH_AgentData);
	msg->addUUID(_PREHASH_AgentID, gAgent.getID());
	msg->addUUID(_PREHASH_SessionID, gAgent.getSessionID());
	msg->nextBlock(_PREHASH_Data);
	msg->addUUID(_PREHASH_ObjectID, target);
	msg->addS32(_PREHASH_ChatChannel, channel);
	msg->addS32(_PREHASH_ButtonIndex, 0);
	msg->addString(_PREHASH_ButtonLabel, chat);
	gAgent.sendReliableMessage();
}
struct n2kdat
{
	LLUUID source;
	S32 channel;
	std::string reply;
};
void callbackname2key(const LLUUID& id, const std::string& first, const std::string& last, BOOL is_group, void* data)
{
	n2kdat* dat = (n2kdat*)data; 
	std::string send = dat->reply + first+" "+last;
	JCLSLBridge::send_chat_to_object(send, dat->channel, dat->source);
	delete dat;
	//if(id == subjectA.owner_id)sInstance->childSetValue("owner_a_name", first + " " + last);
	//else if(id == subjectB.owner_id)sInstance->childSetValue("owner_b_name", first + " " + last);
}

bool JCLSLBridge::lsltobridge(std::string message, std::string from_name, LLUUID source_id, LLUUID owner_id)
{
	if(message == "someshit")
	{
		////cmdline_printchat("got someshit from "+source_id.asString());
		
		return true;
	}else
	{
		std::string clip = message.substr(0,5);
		if(clip == "#@#@#")
		{
			std::string rest = message.substr(5);
			LLSD arguments = JCLSLBridge::parse_string_to_list(rest, '|');
			////cmdline_printchat(std::string(LLSD::dumpXML(arguments)));
			U32 call = atoi(arguments[0].asString().c_str());
			if(call)
			{
				arguments.erase(0);
				////cmdline_printchat(std::string(LLSD::dumpXML(arguments)));
				callback_fire(call, arguments);
				return true;
			}
		}else if(clip == "#@#@!")
		{
			std::string rest = message.substr(5);
			LLSD args = JCLSLBridge::parse_string_to_list(rest, '|');
			std::string cmd = args[0].asString();
			//std::string uniq = args[1].asString();
			if(cmd == "getsex")
			{
				std::string uniq = args[1].asString();
				LLUUID target = LLUUID(args[2].asString());
				S32	channel = atoi(args[3].asString().c_str());
				LLViewerObject* obj = gObjectList.findObject(target);
				if(obj && obj->isAvatar())
				{
					LLVOAvatar* av = (LLVOAvatar*)obj;
					std::string msg = llformat("getsexreply|%s|%d",uniq.c_str(),av->getVisualParamWeight("male"));
					send_chat_to_object(msg, channel, source_id);
				}else
				{
					std::string msg = llformat("getsexreply|%s|-1",uniq.c_str());
					send_chat_to_object(msg, channel, source_id);
				}
				return true;
			}else if(cmd == "preloadanim")
			{
				//logically, this is no worse than lltriggersoundlimited used on you, 
				//and its enherently restricted to owner due to ownersay
				//therefore, I don't think a permission is necessitated
				LLUUID anim = LLUUID(args[1].asString());
				gAssetStorage->getAssetData(anim,
						LLAssetType::AT_ANIMATION,
						(LLGetAssetCallback)NULL,
						NULL,
						TRUE);
				//maybe add completion callback later?
				return true;
			}else if(cmd == "getwindowsize")
			{
				std::string uniq = args[1].asString();
				S32	channel = atoi(args[2].asString().c_str());
				const U32 height = gViewerWindow->getWindowDisplayHeight();
				const U32 width = gViewerWindow->getWindowDisplayWidth();
				std::string msg = llformat("getwindowsizereply|%s|%d|%d",uniq.c_str(),height,width);
				send_chat_to_object(msg, channel, source_id);
				return true;
			}else if(cmd == "key2name")
			{
				//same rational as preload impactwise
				std::string uniq = args[1].asString();
				n2kdat* data = new n2kdat;
				data->channel = atoi(args[3].asString().c_str());
				bool group = (bool)atoi(args[4].asString().c_str());
				data->reply = llformat("key2namereply|%s|",uniq.c_str());
				data->source = source_id;
				gCacheName->get(LLUUID(args[2].asString()), group, callbackname2key, data);
				return true;
			}
			else if(cmd == "emao")
			{
				std::istringstream i(args[1].asString());
				i >> cmd;
				if (args[1].asString() == "on")
				{
					gSavedPerAccountSettings.setBOOL("PhoenixAOEnabled",TRUE);
					LLFloaterAO::run();
				}
				else if (args[1].asString() == "off")
				{
					gSavedPerAccountSettings.setBOOL("PhoenixAOEnabled",FALSE);
					LLFloaterAO::run();
				}
				else if (cmd == "state")
				{
					S32 chan = atoi(args[2].asString().c_str());
					std::string tmp="off";
					if(gSavedPerAccountSettings.getBOOL("PhoenixAOEnabled"))tmp="on";
					send_chat_to_object(tmp,chan,gAgent.getID());
				}
				return true;
			}
			else if(cmd == "emdd")
			{
				S32 chan = atoi(args[2].asString().c_str());
				std::string tmp = llformat("%f",gSavedSettings.getF32("RenderFarClip"));
				send_chat_to_object(tmp,chan,gAgent.getID());
				return true;
			}
			/*else if(cmd == "gettext")
			{
				S32	channel = atoi(args[2].asString().c_str());
				LLUUID target = LLUUID(args[1].asString());
				std::string floating_text;
				LLViewerObject *obj = gObjectList.findObject(target);
				if(obj)
				{
					llinfos << "gettext got obj" << llendl;
					LLHUDText *hud_text = (LLHUDText *)obj->mText.get();
					if(hud_text)
					{
						llinfos << "gettext got hud_text" << llendl;
						floating_text = hud_text->getString();
					}
				}
				llinfos << "gettext returning: " << floating_text << llendl;
				send_chat_to_object(floating_text,channel,source_id);
				return true;
			}*/ //rendered obsolete by llGetLinkPrimitiveParams and/or PRIM_TEXT in 1.38+
		}else if(message.substr(0,3) == "l2c")
		{
			std::string lolnum = message.substr(3);
			//cmdline_printchat("num="+lolnum);
			l2c = atoi(lolnum.c_str());
			//cmdline_printchat("rnum="+llformat("%d",l2c));
			l2c_inuse = true;
			return true;
		}
	}
	return false;
}
//void send_chat_from_viewer(const std::string& utf8_out_text, EChatType type, S32 channel);
// [RLVa:KB] - Checked: 2009-07-07 (RLVa-1.0.0d) | Modified: RLVa-0.2.2a
void send_chat_from_viewer(std::string utf8_out_text, EChatType type, S32 channel);
// [/RLVa:KB]
void JCLSLBridge::bridgetolsl(std::string cmd, JCBridgeCallback* cb)
{
	if(sBridgeStatus == ACTIVE)
	{
		std::string chat = llformat("%d",registerCB(cb)) + "|"+cmd;
		send_chat_from_viewer(chat, CHAT_TYPE_WHISPER, l2c_inuse ? l2c : JCLSLBridge::bridge_channel(gAgent.getID()));
	}else
	{
		////cmdline_printchat("bridge not RECHANNEL");
		delete cb;
	}
}

std::string md5hash(const std::string &text, U32 thing)
{
	char temp[MD5HEX_STR_SIZE];
	LLMD5 toast((const U8*)text.c_str(), thing);
	toast.hex_digest(temp);
	return std::string(temp);
}

/*LLUUID md5hash(const std::string &text, U32 thing)
{
 LLUUID temp;
 LLMD5 toast((const U8*)text.c_str(), thing);
 toast.raw_digest(temp.mData);
 return temp;
}*/

S32 JCLSLBridge::bridge_channel(LLUUID user)
{
	std::string tmps = md5hash(user.asString(),1);
	int i = (int)strtol((tmps.substr(0, 7) + "\n").c_str(),(char **)NULL,16);
	return (S32)i;
}

class ObjectBNameMatches : public LLInventoryCollectFunctor
{
public:
	ObjectBNameMatches(std::string name)
	{
		sName = name;
	}
	virtual ~ObjectBNameMatches() {}
	virtual bool operator()(LLInventoryCategory* cat,
							LLInventoryItem* item)
	{
		if(item)
		{
			//LLViewerInventoryCategory* folderp = gInventory.getCategory((item->getParentUUID());
			return (item->getName() == sName);// && cat->getName() == "#v");
		}
		return false;
	}
private:
	std::string sName;
};


LLUUID JCLSLBridge::findCategoryByNameOrCreate(std::string name)
{
	LLUUID phoenix_category;
	phoenix_category = gInventory.findCategoryByName(phoenix_category_name);
	if(phoenix_category.isNull())
	{
		phoenix_category = gInventory.createNewCategory(gAgent.getInventoryRootID(), LLAssetType::AT_NONE, phoenix_category_name);
	}
	return phoenix_category;
}


const LLUUID& JCLSLBridge::findInventoryByName(const std::string& object_name, std::string catname)
{
	LLViewerInventoryCategory::cat_array_t cats;
	LLViewerInventoryItem::item_array_t items;
	ObjectBNameMatches objectnamematches(object_name);
	LLUUID category;
	if(catname.length() > 0)
	{
		category = findCategoryByNameOrCreate(catname);
	}else
	{
		category = gAgent.getInventoryRootID();
	}

	gInventory.collectDescendentsIf(category,cats,items,FALSE,objectnamematches);

	if (items.count())
	{
		return items[0]->getUUID();
	}
	return LLUUID::null;
}

bool isworn(LLUUID item)
{
	LLVOAvatar* avatar = gAgent.getAvatarObject();
	if(avatar && avatar->isWearingAttachment(item) )
	{
		return true;
	}
	return false;
}

static const std::string bridgeprefix = std::string("#LSL<->Client Bridge v");
static const U32 bridgeprefix_length = U32(bridgeprefix.length());

void callbackBridgeCleanup(const LLSD &notification, const LLSD &response, LLViewerInventoryItem::item_array_t items)
{
	gSavedSettings.setWarning("PhoenixOldBridgeCleanup", FALSE);

	S32 option = LLNotification::getSelectedOption(notification, response);
	
	if ( option == 0 )
	{
		if(items.count())
		{
			cmdline_printchat("Moving out-of-date bridge objects to your trash folder.");
			//delete
			LLUUID trash_cat = gInventory.findCategoryUUIDForType(LLAssetType::AT_TRASH);
			for(LLDynamicArray<LLPointer<LLViewerInventoryItem> >::iterator itr = items.begin(); itr != items.end(); ++itr)
			{
				LLViewerInventoryItem* item = *itr;
				if(item)
				{
					move_inventory_item(gAgent.getID(),gAgent.getSessionID(),item->getUUID(),trash_cat,item->getName(), NULL);
					//cmdline_printchat("Moved item "+item->getName());
				}
			}
			//cmdline_printchat("Items moved.");
		}
	}
}
class BridgeCleanupMatches : public LLInventoryCollectFunctor
{
public:
	BridgeCleanupMatches()
	{
		trash_cat = gInventory.findCategoryUUIDForType(LLAssetType::AT_TRASH);
	}
	virtual ~BridgeCleanupMatches() {}
	virtual bool operator()(LLInventoryCategory* cat,
							LLInventoryItem* item)
	{
		if(item)
		{
			if(item->getName().substr(0,bridgeprefix_length) == bridgeprefix)
			{
				LLUUID parent_id = item->getParentUUID();
				BOOL in_trash = (parent_id == trash_cat);
				if(in_trash == FALSE)
				{
					LLViewerInventoryCategory* parent = gInventory.getCategory(parent_id);
					while(parent)
					{
						parent_id = parent->getParentUUID();
						if(parent_id == trash_cat)
						{
							in_trash = TRUE;
							break;
						}else if(parent_id.isNull())break;

						parent = gInventory.getCategory(parent_id);
					}
					if(in_trash == FALSE)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
private:
	LLUUID trash_cat;
};

void bridge_trash_check()
{
	if(gSavedSettings.getWarning("PhoenixOldBridgeCleanup"))
	{
		//cmdline_printchat("doing cleaner scan");
		BridgeCleanupMatches prefixmatcher;
		LLViewerInventoryCategory::cat_array_t cats;
		LLViewerInventoryItem::item_array_t items;

		gInventory.collectDescendentsIf(gAgent.getInventoryRootID(),cats,items,FALSE,prefixmatcher);

		LLViewerInventoryItem::item_array_t delete_queue;

		if(items.count())
		{
			//cmdline_printchat("items.count()");
			for(LLDynamicArray<LLPointer<LLViewerInventoryItem> >::iterator itr = items.begin(); itr != items.end(); ++itr)
			{
				LLViewerInventoryItem* item = *itr;
				//cmdline_printchat("item");
				if(item)
				{
					/*cmdline_printchat("item exists");
					if(
						(item->getPermissions().allowCopyBy(gAgent.getID()) == TRUE) &&
						(item->getPermissions().allowModifyBy(gAgent.getID()) == TRUE) &&
						(item->getPermissions().allowTransferTo(LLUUID::null) == TRUE)
						)*/
					{
						//cmdline_printchat("full perm");
						std::string name = item->getName();
						//cmdline_printchat("name="+name);
						if(name.length() > bridgeprefix_length)
						{
							std::string version_str = name.substr(bridgeprefix_length); // use rest of string
							std::istringstream vstream(version_str);
							F32 version_float;
							if(vstream >> version_float)
							{
								if(version_float < 0.06f)
								{
									llinfos << "bridge older than 0.06f found (" << version_float << ")[" << version_str << "] in inv but not in trash" << llendl;
									delete_queue.push_back(item);
								}else
								{
									llinfos << "bridge >= 0.06f found (" << version_float << ")[" << version_str << "] in inv but not in trash" << llendl;
								}
							}else
							{
								llinfos << "bridge object " << name << " [" << version_str << "] failed decoding version" << llendl;
							}
						}else
						{
							llinfos << "bridge object name " << name << " is less than bridgeprefix_length?" << llendl;	
						}
					}
				}
			}
			int dqlen = delete_queue.count();
			if(dqlen > 0)
			{
				//cmdline_printchat("dqlen > 0");
				std::string bridges = llformat("%d",delete_queue.count())+" older Phoenix LSL Bridge object";
				if(dqlen > 1)bridges += "s";
				LLSD args;
				args["BRIDGES"] = bridges;
				LLNotifications::instance().add("QueryBridgeCleanup", args,LLSD(), boost::bind(callbackBridgeCleanup, _1, _2, delete_queue));
			}
		}
	}
}



BOOL JCLSLBridge::tick()
{
	static BOOL firstsim = TRUE;
	if(LLStartUp::getStartupState() >= STATE_INVENTORY_SEND)
	{
		if(firstsim == TRUE && gInventory.isInventoryUsable())
		{
			//cmdline_printchat("firstsim fetching #Phoenix");
			firstsim = FALSE;
			LLUUID phoenix_category = findCategoryByNameOrCreate(phoenix_category_name);
			gInventory.fetchDescendentsOf(phoenix_category);
		}
		static BOOL first_full_load = TRUE;
		if(first_full_load)
		{
			if(gInventory.isEverythingFetched())
			{
				//cmdline_printchat("first full inv load");
				first_full_load = FALSE;
				bridge_trash_check();
			}
		}
		switch(sBridgeStatus)
		{
		case UNINITIALIZED:
			{
				if(!sBuildBridge)
				{
					//cmdline_printchat("PhoenixBuildBridge is false");
					sBridgeStatus = FAILED;
					break;
				}
				//cmdline_printchat("initializing");//<< llendl;
				LLUUID phoenix_category = findCategoryByNameOrCreate(phoenix_category_name);
				LLUUID item_id = findInventoryByName(phoenix_bridge_name);
				if(gInventory.isCategoryComplete(phoenix_category))// || (item_id.notNull() && isworn(item_id)))
				{
					//cmdline_printchat("#Phoenix is fetched");//<< llendl;
					
					if(item_id.notNull())
					{
						//cmdline_printchat("item not null");
						//cmdline_printchat("id="+item_id.asString());
						LLViewerInventoryItem* bridge = gInventory.getItem(item_id);
						if(bridge)
						{
							//cmdline_printchat("bridge there");
							//cmdline_printchat("bridge is ready to attach");//<< llendl;
							if(isworn(bridge->getUUID()))
							{
								//cmdline_printchat("worn; rechannelling");
								//cmdline_printchat("bridge is already worn");//<< llendl;
								sBridgeStatus = RECHANNEL;
							}else// if(bridge->isComplete())
							{
								//cmdline_printchat("attaching");
								//cmdline_printchat("bridge is complete, attaching");//<< llendl;
								LLMessageSystem* msg = gMessageSystem;
								msg->newMessageFast(_PREHASH_RezSingleAttachmentFromInv);
								msg->nextBlockFast(_PREHASH_AgentData);
								msg->addUUIDFast(_PREHASH_AgentID, gAgent.getID());
								msg->addUUIDFast(_PREHASH_SessionID, gAgent.getSessionID());
								msg->nextBlockFast(_PREHASH_ObjectData);
								msg->addUUIDFast(_PREHASH_ItemID, bridge->getUUID());
								msg->addUUIDFast(_PREHASH_OwnerID, bridge->getPermissions().getOwner());
								msg->addU8Fast(_PREHASH_AttachmentPt, phoenix_point);
								pack_permissions_slam(msg, bridge->getFlags(), bridge->getPermissions());
								msg->addStringFast(_PREHASH_Name, bridge->getName());
								msg->addStringFast(_PREHASH_Description, bridge->getDescription());
								msg->sendReliable(gAgent.getRegionHost());
								sBridgeStatus = RECHANNEL;
							}
						}/*else
						{
							cmdline_printchat("bridge* null");
						}*/
					}else
					{
						//cmdline_printchat("itemid is null");
						//cmdline_printchat("no bridge");//<< llendl;
						//sBridgeStatus = BUILDING;
						std::string directory = gDirUtilp->getExpandedFilename(LL_PATH_APP_SETTINGS,"bridge.xml");
						if(!LLFile::isfile(directory.c_str()))
						{
							//cmdline_printchat("bridge failed");
							//cmdline_printchat("file not there o.o");//<< llendl;
							sBridgeStatus = FAILED;
						}else
						{
							
							if(LLStartUp::getStartupState() >= STATE_STARTED)
							{
								
								//cmdline_printchat("building bridge");
								//cmdline_printchat("bridge.xml located. importing..");//<< llendl;
								gImportTracker.importer(directory,&setBridgeObject);
								sBridgeStatus = BUILDING;
							}/*else
							{
								cmdline_printchat("state is not quite ready");
							}*/
						}
					}
				}/*else
				{
					cmdline_printchat("#Phoenix is not fetched");
				}*/
			}
			break;
		case RENAMING:
			{
				//cmdline_printchat("renaming");
				////cmdline_printchat("renaming");
				LLMessageSystem* msg = gMessageSystem;
				msg->newMessageFast(_PREHASH_ObjectAttach);
				msg->nextBlockFast(_PREHASH_AgentData);
				msg->addUUIDFast(_PREHASH_AgentID, gAgent.getID() );
				msg->addUUIDFast(_PREHASH_SessionID, gAgent.getSessionID());
				msg->addU8Fast(_PREHASH_AttachmentPoint, phoenix_point);
				
				msg->nextBlockFast(_PREHASH_ObjectData);
				msg->addU32Fast(_PREHASH_ObjectLocalID, sBridgeObject->getLocalID());
				msg->addQuatFast(_PREHASH_Rotation, LLQuaternion(0.0f, 0.0f, 0.0f, 1.0f));
				
				msg->sendReliable(gAgent.getRegion()->getHost());
				sBridgeStatus = FOLDERING;
			}
			break;
		case FOLDERING:
			{
				//cmdline_printchat("foldering");
				////cmdline_printchat("foldering");
				LLUUID phoenix_category = findCategoryByNameOrCreate(phoenix_category_name);

				LLUUID bridge_id = findInventoryByName(phoenix_bridge_name);
				//cmdline_printchat("bridge_id="+bridge_id.asString());
				//cmdline_printchat("id="+bridge_id.asString());
				LLViewerInventoryItem* bridge = gInventory.getItem(bridge_id);
				if(bridge)
				{
					//cmdline_printchat("bridge exists, moving to #Phoenix.");
					move_inventory_item(gAgent.getID(),gAgent.getSessionID(),bridge->getUUID(),phoenix_category,phoenix_bridge_name, NULL);
					sBridgeStatus = RECHANNEL;
					////cmdline_printchat("moving to folder");
				}
			}
			break;
		case RECHANNEL:
			{
				{
					//cmdline_printchat("sending rechannel cmd");
					send_chat_from_viewer(std::string("0|l2c"), CHAT_TYPE_WHISPER, JCLSLBridge::bridge_channel(gAgent.getID()));
					sBridgeStatus = ACTIVE;
				}
			}
			break;
		case ACTIVE:
			{
				LLUUID bridge = findInventoryByName(phoenix_bridge_name,phoenix_category_name);
				//if(bridge)
				//LLVOAvatar* avatar = gAgent.getAvatarObject();
				if(bridge.isNull() || !isworn(bridge))
				{
					//cmdline_printchat("bridge="+bridge.asString()+" || "+(!isworn(bridge) ? "1" : "0"));
					l2c = 0;
					l2c_inuse = false;
					////cmdline_printchat("reattaching");
					sBridgeStatus = UNINITIALIZED;
				}
			}
		}
	}
	return FALSE;
}
void JCLSLBridge::setBridgeObject(LLViewerObject* obj)
{
	if(obj)
	{
		sBridgeObject = obj;
		////cmdline_printchat("callback reached");
		sBridgeStatus = RENAMING;
		LLMessageSystem* msg = gMessageSystem;
		msg->newMessageFast(_PREHASH_ObjectName);
		msg->nextBlockFast(_PREHASH_AgentData);
		msg->addUUIDFast(_PREHASH_AgentID,gAgent.getID());
		msg->addUUIDFast(_PREHASH_SessionID,gAgent.getSessionID());
		msg->nextBlockFast(_PREHASH_ObjectData);
		msg->addU32Fast(_PREHASH_LocalID,obj->getLocalID());
		msg->addStringFast(_PREHASH_Name,phoenix_bridge_name);
		gAgent.sendReliableMessage();
	}
}

void JCLSLBridge::callback_fire(U32 callback_id, LLSD data)
{
	if (!callback_id)
		return;

	std::map<U32, JCBridgeCallback*>::iterator i;

	i = callback_map.find(callback_id);
	if (i != callback_map.end())
	{
		(*i).second->fire(data);
		callback_map.erase(i);
	}
}

U32 JCLSLBridge::registerCB(JCBridgeCallback* cb)
{
	if (!cb)
		return 0;

	lastcall++;
	if (!lastcall)
		lastcall++;

	callback_map[lastcall] = cb;
	//no while(callback_map.size() > 100)callback_map.erase(0);
	return lastcall;
}

LLSD JCLSLBridge::parse_string_to_list(std::string list, char sep)
{
	LLSD newlist;
	U32 count = 0;
	std::string token;
	std::istringstream iss(list);
	while ( getline(iss, token, sep) )
	{
		newlist[count] = token;
		count += 1;
	}
	return newlist;
}


void JCLSLBridge::processSoundTrigger(LLMessageSystem* msg,void**)
{
	LLUUID	sound_id,owner_id,object_id;
	msg->getUUIDFast(_PREHASH_SoundData, _PREHASH_SoundID, sound_id);
	msg->getUUIDFast(_PREHASH_SoundData, _PREHASH_OwnerID, owner_id);
	msg->getUUIDFast(_PREHASH_SoundData, _PREHASH_ObjectID, object_id);
	if(owner_id == gAgent.getID())
	{
		
		if(sound_id == LLUUID("420d76ad-c82b-349d-7b81-f00d0ca0f38f"))
		{
			if(sBridgeStatus == ACTIVE)
			{
                std::string mess = "phoenix_bridge_rdy";
				send_chat_to_object(mess, JCLSLBridge::bridge_channel(gAgent.getID()), object_id);
			}else if(sBridgeStatus == FAILED)
			{
                std::string mess = "phoenix_bridge_failed";
				send_chat_to_object(mess, JCLSLBridge::bridge_channel(gAgent.getID()), object_id);
			}else
			{
                std::string mess = "phoenix_bridge_working";
				send_chat_to_object(mess, JCLSLBridge::bridge_channel(gAgent.getID()), object_id);
			}
		}
		
	}
}
/*
LLUUID BridgePermissions_Phoenix("c78f9f3f-56ac-4442-a0b9-8b41dad455ae");

void JCLSLBridge::loadPermissions()
{
	std::vector<std::string> strings;
	strings.push_back( BridgePermissions_Phoenix.asString() );//BridgePermissions Phoenix
	send_generic_message("avatarnotesrequest", strings);
}

void JCLSLBridge::storePermissions()
{
	LLMessageSystem *msg = gMessageSystem;
	msg->newMessage("AvatarNotesUpdate");
	msg->nextBlock("AgentData");
	msg->addUUID("AgentID", gAgent.getID());
	msg->addUUIDFast(_PREHASH_SessionID, gAgent.getSessionID());
	msg->nextBlock("Data");
	msg->addUUID("TargetID", BridgePermissions_Phoenix);
	msg->addString("Notes", "");//RECHANNEL_permissions);
	gAgent.sendReliableMessage();
}
*/
void JCLSLBridge::processAvatarNotesReply(LLMessageSystem *msg, void**)
{
	// extract the agent id
	LLUUID agent_id;
	msg->getUUID("AgentData", "AgentID", agent_id);
	LLUUID target_id;
	msg->getUUID("Data", "TargetID", target_id);

	/*if(target_id == BridgePermissions_Phoenix)
	{
		std::string text;
		msg->getString("Data", "Notes", text);
		//LLSD arguments = JCLSLBridge::parse_string_to_list(text, '|');
		//RECHANNEL_permissions = text;//arguments;
	}*/
}

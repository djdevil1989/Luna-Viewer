// <edit>
/* DOUBLE EDIT REACH AROUND
Rewritten by Hg Beeks

*/

#include "llviewerprecompiledheaders.h"

#include "llagent.h"
#include "llanimstatelabels.h"
#include "llao.h"
#include "llfilepicker.h"
#include "llinventorymodel.h"
#include "llscrolllistctrl.h"
#include "llsdserialize.h"
#include "lluictrlfactory.h"
#include "llviewercontrol.h"
#include "llvoavatar.h"
//this is for debugging ;D
//#define AO_DEBUG

//static variables
std::list<std::string>	LLAO::mStandOverrides;
LLSD					LLAO::mAnimationOverrides;
S32						LLAO::mAnimationIndex;
LLUUID					LLAO::mLastAnimation;

std::map<LLUUID,LLUUID> LLAO::mOverrides;
LLFloaterAO* LLFloaterAO::sInstance;
BOOL LLAO::mEnabled = FALSE;
F32 LLAO::mPeriod;
LLAOStandTimer* LLAO::mTimer = NULL;

class ObjectNameMatches : public LLInventoryCollectFunctor
{
public:
	ObjectNameMatches(std::string name)
	{
		sName = name;
	}
	virtual ~ObjectNameMatches() {}
	virtual bool operator()(LLInventoryCategory* cat,
							LLInventoryItem* item)
	{
		if(item)
		{
			return (item->getName() == sName);
		}
		return false;
	}
private:
	std::string sName;
};

const LLUUID& LLAO::getAssetIDByName(const std::string& name)
{
	if (name.empty()) return LLUUID::null;

	LLViewerInventoryCategory::cat_array_t cats;
	LLViewerInventoryItem::item_array_t items;
	ObjectNameMatches objectnamematches(name);
	gInventory.collectDescendentsIf(LLUUID::null,cats,items,FALSE,objectnamematches);

	if (items.count())
	{
		return items[0]->getAssetUUID();
	}
	return LLUUID::null;
};

LLUUID LLAO::getFrontUUID()
{
	if (!LLAO::mStandOverrides.empty())
		return LLUUID(LLAO::getAssetIDByName(LLAO::mStandOverrides.front()));
	else
		return LLUUID::null;
}

LLUUID LLAO::getBackUUID()
{
	if (!LLAO::mStandOverrides.empty())
		return LLUUID(LLAO::getAssetIDByName(LLAO::mStandOverrides.back()));
	else
		return LLUUID::null;
}

LLAOStandTimer::LLAOStandTimer(F32 period) : LLEventTimer(period)
{
}
BOOL LLAOStandTimer::tick()
{
	return TRUE;
}

void LLAOStandTimer::pause()
{
	//mPaused=TRUE;
}

void LLAOStandTimer::resume()
{
	//mPaused=FALSE;
}

// Used for sorting
struct SortItemPtrsByName
{
	bool operator()(const LLInventoryItem* i1, const LLInventoryItem* i2)
	{
		return (LLStringUtil::compareDict(i1->getName(), i2->getName()) < 0);
	}
};


void LLAOStandTimer::reset()
{
	mEventTimer.reset();
}

//static
void LLAO::setup()
{
	mEnabled = gSavedSettings.getBOOL("AO.Enabled");
	
	std::string ao_enabled_cmd="AO.Disabled=";
	ao_enabled_cmd.append((mEnabled) ? "false" : "true"); // NOT
	FLLua::callCommand(ao_enabled_cmd);

	gSavedSettings.getControl("AO.Period")->getSignal()->connect(boost::bind(&handleAOPeriodChanged, _1));
}
//static
void LLAO::runAnims(BOOL enabled)
{
}
//static
bool LLAO::handleAOPeriodChanged(const LLSD& newvalue)
{
	return true;
}
//static
bool LLAO::handleAOEnabledChanged(const LLSD& newvalue)
{
	BOOL value = newvalue.asBoolean();
	std::string ao_enabled_cmd="AO.Disabled=";
	ao_enabled_cmd.append((value) ? "false" : "true"); // NOT
	FLLua::callCommand(ao_enabled_cmd);
	return true;
}
//static
BOOL LLAO::isStand(LLUUID _id)
{
	std::string id = _id.asString();
	//ALL KNOWN STANDS
	if(id == "2408fe9e-df1d-1d7d-f4ff-1384fa7b350f") return TRUE;
	if(id == "15468e00-3400-bb66-cecc-646d7c14458e") return TRUE;
	if(id == "370f3a20-6ca6-9971-848c-9a01bc42ae3c") return TRUE;
	if(id == "42b46214-4b44-79ae-deb8-0df61424ff4b") return TRUE;
	if(id == "f22fed8b-a5ed-2c93-64d5-bdd8b93c889f") return TRUE;
	return FALSE;
}

BOOL LLAO::isVoice(LLUUID _id)
{
	std::string id = _id.asString();
	//ALL KNOWN VOICE ANIMS
	if(id == "3557510a-5eb4-d0ce-0b91-67c72aa75312") return TRUE;
    if(id == "a71890f1-0dab-8744-fd47-7defaf411dbf") return TRUE;
    if(id == "c1802201-5f4e-366f-7f78-2d08ec6ea54a") return TRUE;
    if(id == "68db359f-4c9c-0932-5f1e-e95e3a0b19bc") return TRUE;
    if(id == "7ef0d5c0-3346-06e4-5cfc-f081db108baa") return TRUE;
    if(id == "28a3f544-268d-da71-7da6-82c8dd522cb9") return TRUE;
    if(id == "cc340155-3e9d-60fe-d8e3-9e9abc7062d1") return TRUE;
    if(id == "55fe6788-8a16-d998-2f63-3c1eab2b6009") return TRUE;
    if(id == "69d5a8ed-9ec6-6dac-842f-d92d82e69428") return TRUE;
    if(id == "9a7f3201-7bbd-4f75-b762-24270536e4e3") return TRUE;
    if(id == "37694185-3107-d418-3a20-0181424e542d") return TRUE;
    if(id == "cb1139b6-e7c3-fdc7-a9c1-e21673d7a50e") return TRUE;
    if(id == "bbf194d1-a118-1312-998b-8145cec6eaff") return TRUE;
    if(id == "593e9a3d-58d8-c594-d6dd-f4b98965202e") return TRUE;
    if(id == "2b78c24a-2451-6135-fc49-ad274552bb68") return TRUE;
    if(id == "0f645c60-3151-2805-b6f7-28e710ed22ac") return TRUE;
	return FALSE;
}

//static
void LLAO::refresh()
{
	mOverrides.clear();
	mAnimationOverrides.clear();
	LLSD settings = gSavedPerAccountSettings.getLLSD("AO.Settings");

	mAnimationOverrides = settings["overrides"];

	std::string ffff="";
	for(
		LLSD::map_iterator stateIter = mAnimationOverrides.beginMap();
		stateIter!=mAnimationOverrides.endMap();
		++stateIter)
	{
		std::string state = stateIter->first;
		int n = stateIter->second.size();
		int i;
		for(i=0;i<n;i++)
		{
			std::string anim = mAnimationOverrides[state][i].asString();
			ffff.append(llformat("AO:AddOverride(\"%s\",\"%s\")\n",state.c_str(),anim.c_str()));
		}
	}
	FLLua::callCommand(ffff);
}

//static ------------- Floater
void LLFloaterAO::show()
{
	if(sInstance)
		sInstance->open();
	else
		(new LLFloaterAO())->open();
}

LLFloaterAO::LLFloaterAO()
:	LLFloater()
{
	sInstance = this;
	LLUICtrlFactory::getInstance()->buildFloater(this, "floater_ao.xml");
}

LLFloaterAO::~LLFloaterAO()
{
	sInstance = NULL;
}

BOOL LLFloaterAO::postBuild(void)
{
	LLComboBox*			combo;
	LLScrollListCtrl*	list;

	childSetAction("btn_save", onClickSave, this);
	childSetAction("btn_load", onClickLoad, this);

	combo = getChild<LLComboBox>( "combo_anim_type");
	combo->setCommitCallback(onCommitType);
	combo->setCallbackUserData(this);
	combo->selectFirstItem();
	mAnimTypeCombo = combo;
	mCurrentAnimType = mAnimTypeCombo->getValue().asString();
	
	combo = getChild<LLComboBox>( "combo_anim_list");
	mAnimListCombo = combo;
	childSetAction("combo_anim_add", onClickAnimAdd, this);
	childSetAction("combo_anim_delete", onClickAnimRemove, this);

	list = getChild<LLScrollListCtrl>("active_anim_list");
	mAnimationList = list;

	addAnimations();

	refresh();
	
	return TRUE;
}

void LLFloaterAO::refresh()
{
	mAnimationList->deleteAllItems();
	S32 count = LLAO::mAnimationOverrides[mCurrentAnimType].size();
	llinfos << "Refreshed, building animation list for " << mCurrentAnimType << ", Count:" << count << llendl;
	int i;
	for(i = 0; i < count; i++)
	{
		std::string name = LLAO::mAnimationOverrides[mCurrentAnimType][i].asString();
		llinfos << "Adding " << name << llendl;
		mAnimationList->addSimpleElement(name, ADD_BOTTOM);
	}
}
// static
void LLFloaterAO::onCommitType(LLUICtrl* ctrl, void* user_data)
{
	LLFloaterAO* floater = (LLFloaterAO*)user_data;
	floater->mCurrentAnimType = floater->mAnimTypeCombo->getValue().asString();
	floater->refresh();
}

void LLFloaterAO::addAnimations()
{
	mAnimListCombo->removeall();
	
	std::string none_text = getString("none_text");
	mAnimListCombo->add(none_text, LLUUID::null);

	// Add all the default (legacy) animations
	S32 i;

	// Get all inventory items that are animations
	LLViewerInventoryCategory::cat_array_t cats;
	LLViewerInventoryItem::item_array_t items;
	LLIsTypeWithPermissions is_copyable_animation(LLAssetType::AT_ANIMATION,
													PERM_NONE,
													gAgent.getID(),
													gAgent.getGroupID());
	gInventory.collectDescendentsIf(gAgent.getInventoryRootID(),
									cats,
									items,
									LLInventoryModel::EXCLUDE_TRASH,
									is_copyable_animation);

	// Copy into something we can sort
	std::vector<LLInventoryItem*> animations;

	S32 count = items.count();
	for(i = 0; i < count; ++i)
	{
		animations.push_back( items.get(i) );
	}

	// Do the sort
	std::sort(animations.begin(), animations.end(), SortItemPtrsByName());

	// And load up the combobox
	std::vector<LLInventoryItem*>::iterator it;
	for (it = animations.begin(); it != animations.end(); ++it)
	{
		LLInventoryItem* item = *it;
		mAnimListCombo->add(item->getName(), item->getAssetUUID(), ADD_BOTTOM);
	}
}

// static
void LLFloaterAO::onCommitAnim(LLUICtrl* ctrl, void* user_data)
{

}


//static
void LLFloaterAO::onClickAnimRemove(void* user_data)
{
	LLFloaterAO* floater = (LLFloaterAO*)user_data;
	std::vector<LLScrollListItem*> items = floater->mAnimationList->getAllSelected();
	for (std::vector<LLScrollListItem*>::iterator iter = items.begin(); iter != items.end(); ++iter)
	{
		LLScrollListItem* item = *iter;
		if (item->getValue().asString() != "")
		{
			std::string anim_name = item->getValue().asString();
			FLLua::callCommand(llformat("AO:RemoveOverride(\"%s\",\"%s\")",floater->mCurrentAnimType,anim_name));
		}
	}
	onCommitAnim(NULL,user_data);
}
//static
void LLFloaterAO::onClickAnimAdd(void* user_data)
{
	LLFloaterAO* floater = (LLFloaterAO*)user_data;
	std::string anim_name = floater->mAnimListCombo->getSimple();
	if (anim_name == "")
		return;
	LLUUID id(LLAO::getAssetIDByName(anim_name));
	if(id.notNull() && !LLAO::mAnimationOverrides[floater->mCurrentAnimType].has(anim_name))
	{
		LLAO::mAnimationOverrides[floater->mCurrentAnimType].append(anim_name);
		FLLua::callCommand("AO:AddOverride(\""+floater->mCurrentAnimType+"\",\""+id.asString()+"\")");
	}
	onCommitAnim(NULL,user_data);
}

BOOL LLFloaterAO::handleDragAndDrop(S32 x, S32 y, MASK mask, BOOL drop,
										 EDragAndDropType cargo_type,
										 void* cargo_data,
										 EAcceptance* accept,
										 std::string& tooltip_msg)
{
	BOOL handled = TRUE;
	switch(cargo_type)
	{
	case DAD_NOTECARD:
		{
			// Pop off to Lua
			LLInventoryItem* item = (LLInventoryItem*)cargo_data;
			if (item && gInventory.getItem(item->getAssetUUID()))
			{
				// @hook OnAONotecard(asset_id)
				LUA_CALL("OnAONotecard") << item->getAssetUUID() << LUA_END;
			}
			*accept = ACCEPT_YES_COPY_MULTI;
			break;
		}
	case DAD_ANIMATION:
		{
			LLInventoryItem* item = (LLInventoryItem*)cargo_data;
			if (item
				&& gInventory.getItem(item->getUUID()))
			{
				if (drop)
				{
					if (cargo_type == DAD_ANIMATION)
					{
						std::string anim_name = item->getName();
						if (anim_name == "")
							return true;
						LLUUID id(LLAO::getAssetIDByName(anim_name));
#ifdef AO_DEBUG
						llinfos << "Actually adding animation, this should be refreshed. Count:" << LLAO::mAnimationOverrides[mCurrentAnimType].size() << llendl;
#endif
						LLAO::mAnimationOverrides[mCurrentAnimType].append(anim_name);
#ifdef AO_DEBUG
						llinfos << "Added animation. Count:" << LLAO::mAnimationOverrides[mCurrentAnimType].size() << llendl;
#endif
						//LLAO::mTimer->reset();
						onCommitAnim(NULL,this);
					}
					refresh();
				}
				*accept = ACCEPT_YES_COPY_MULTI;
			}
			else
			{
				// Not in user's inventory means it was in object inventory
				*accept = ACCEPT_NO;
			}
			break;
		}
	default:
		*accept = ACCEPT_NO;
		if (tooltip_msg.empty())
		{
			tooltip_msg.assign("Only animations can be added to the AO.");
		}
		break;
	}
	return handled;
}


//static
void LLFloaterAO::onClickSave(void* user_data)
{
	LLFilePicker& file_picker = LLFilePicker::instance();
	if(file_picker.getSaveFile( LLFilePicker::FFSAVE_AO, LLDir::getScrubbedFileName("untitled.ao")))
	{
		std::string file_name = file_picker.getFirstFile();
		llofstream export_file(file_name);
		LLSDSerialize::toXML(gSavedPerAccountSettings.getLLSD("AO.Settings"), export_file);
		export_file.close();
	}
}

//static
void LLFloaterAO::onClickLoad(void* user_data)
{
	LLFloaterAO* floater = (LLFloaterAO*)user_data;

	LLFilePicker& file_picker = LLFilePicker::instance();
	if(file_picker.getOpenFile(LLFilePicker::FFLOAD_AO))
	{
		std::string file_name = file_picker.getFirstFile();
		llifstream xml_file(file_name);
		if(!xml_file.is_open()) return;
		LLSD data;
		if(LLSDSerialize::fromXML(data, xml_file) >= 1)
		{
			if(LLAO::isEnabled())
				LLAO::runAnims(FALSE);

			gSavedPerAccountSettings.setLLSD("AO.Settings", data);
			LLAO::refresh();

			if(LLAO::isEnabled())
				LLAO::runAnims(TRUE);

			floater->refresh();
		}
		xml_file.close();
	}
}
// </edit>
#include "llviewerprecompiledheaders.h"

#include "LuaBase_f.h"
#include "LuaAvatar_f.h"

#include "llagent.h"
#include "llvoavatar.h"
#include "llviewerobjectlist.h"
#include "llwearable.h"
#include "llwearablelist.h"
#include "llcharacter.h"
#include "llfloatercustomize.h"

void LuaDumpVisualParams()
{

	LLViewerInventoryItem* item;
	item = (LLViewerInventoryItem*)gAgent.getWearableInventoryItem(WT_SHAPE);
	if(!HasPermissions(item))
	{
		LuaError("LuaDumpVisualParams():  You do not have permission to edit this shape.");
		return;
	}

	LLVOAvatar *av=gAgent.getAvatarObject();
	std::string  param_msg("Params for avatar ");
	param_msg.append(av->getFullname().c_str());
	param_msg.append(": ");
	LuaSendChat(param_msg.c_str());
	param_msg.clear();
	for (LLVisualParam *param = av->getFirstVisualParam(); 
		param;
		param = av->getNextVisualParam())
	{
		param_msg.assign(param->getName().c_str());
		param_msg.append(" (");
		param_msg.append(toLuaString(param->getDefaultWeight()));
		param_msg.append("): ");
		param_msg.append(toLuaString(param->getCurrentWeight()));
		LuaSendChat(param_msg.c_str());
	}

	std::map<LLUUID,LLWearable *>::const_iterator i;
	for(i = gWearableList.mList.begin();i!=gWearableList.mList.end();++i)
	{
		LLWearable *wear=(LLWearable *)i->second;
		LLFILE *file = LLFile::fopen(gDirUtilp->getExpandedFilename(FL_PATH_MACROS,"data"+gDirUtilp->getDirDelimiter()+"wearables",wear->getID().asString()).c_str(),"wb");
		if(file && wear->exportFile(file))
			delete file;

		std::stringstream s;
		s << "Wearable ID: ";
		s << wear->getID().asString();
		LuaSendChat(s.str().c_str());
	}
}

std::string  LuaDumpVisualParamsToLuaCode()
{
	LLVOAvatar *av=gAgent.getAvatarObject();
	
	LLViewerInventoryItem* item;
	item = (LLViewerInventoryItem*)gAgent.getWearableInventoryItem(WT_SHAPE);
	if(!HasPermissions(item))
	{
		LuaError("LuaDumpVisualParamsToLuaCode():  You do not have permission to edit this shape.");
		return std::string();
	}
	std::string  param_msg("");
	param_msg.assign("--[[ Autogenerated by FlexLife Viewer ]]--\n");
	for (LLVisualParam *param = av->getFirstVisualParam(); 
		param;
		param = av->getNextVisualParam())
	{
		param_msg.append("setParamOnSelf(\"");
		param_msg.append(param->getName().c_str());
		param_msg.append("\",");
		param_msg.append(toLuaString(param->getCurrentWeight()));
		param_msg.append(")\n");
	}

	param_msg.append("\n\n--[[Wearables]]--\nRemoveAllWearables()\n");
	
	std::map<LLUUID,LLWearable *>::const_iterator i;
	for(i = gWearableList.mList.begin();i!=gWearableList.mList.end();++i)
	{
		LLWearable *wear=(LLWearable *)i->second;
		if(!LuaSaveWearable(wear)) break;

		std::stringstream s;
		s << "wear(\"" << wear->getID().asString() << "\")\n";
		param_msg.append(s.str());
	}
/*
	for( S32 i = 0; i < BAKED_NUM_INDICES; i++ )
	{
		S32 tex_index=LLmBakedTextureData[i].mTextureIndex
		//S32 tex_index = LLVOAvatar::sBakedTextureIndices[i];
		std::stringstream s;
		s << "setTEImage(" << tex_index <<",\""<< av->getTEImage(tex_index)->getID() << "\")\n";
		param_msg.append(s.str());
	}
*/
	param_msg.append("UpdateAppearance()\n");
	return param_msg;
}

double getParamDefaultWeight(const char* avid,const char* paramname)
{
	LLUUID uuid(avid);
	LLViewerObject *o=gObjectList.findObject(uuid);
	if(!o->isAvatar())
	{
		LuaError("Object is not an avatar.");
		return 0;
	}
	LLVOAvatar *av=(LLVOAvatar *)o;
	LLVisualParam *p=av->getVisualParam(paramname);
	if(!p)
	{
		std::string out("Invalid visual parameter: ");
		out.append(paramname);
		LuaError(out.c_str());
		return 0;
	}
	return (double)p->getDefaultWeight();
}

double getParamCurrentWeight(const char* avid,const char* paramname)
{
	LLUUID uuid(avid);
	LLViewerObject *o=gObjectList.findObject(uuid);
	if(!o->isAvatar())
	{
		LuaError("Object is not an avatar.");
		return 0;
	}
	LLVOAvatar *av=(LLVOAvatar *)o;
	LLVisualParam *p=av->getVisualParam(paramname);
	if(!p)
	{
		std::string out("Invalid visual parameter: ");
		out.append(paramname);
		LuaError(out.c_str());
		return 0;
	}
	return (double)p->getCurrentWeight();
}

double getParamMax(const char* avid,const char* paramname)
{
	LLUUID uuid(avid);
	LLViewerObject *o=gObjectList.findObject(uuid);
	if(!o->isAvatar())
	{
		LuaError("Object is not an avatar.");
		return 0;
	}
	LLVOAvatar *av=(LLVOAvatar *)o;
	LLVisualParam *p=av->getVisualParam(paramname);
	if(!p)
	{		gAgent.saveWearable(WT_SHAPE,TRUE);
		std::string out("Invalid visual parameter: ");
		out.append(paramname);
		LuaError(out.c_str());
		return 0;
	}
	return (double)p->getMaxWeight();
}

double getParamMin(const char* avid,const char* paramname)
{
	LLUUID uuid(avid);
	LLViewerObject *o=gObjectList.findObject(uuid);
	if(!o->isAvatar())
	{
		LuaError("Object is not an avatar.");
		return 0;
	}
	LLVOAvatar *av=(LLVOAvatar *)o;
	LLVisualParam *p=av->getVisualParam(paramname);
	if(!p)
	{
		std::string out("Invalid visual parameter: ");
		out.append(paramname);
		LuaError(out.c_str());
		return 0;
	}
	return (double)p->getMinWeight();
}

//------------------------------------------------------------------------
// Set
//------------------------------------------------------------------------

void setParams_Event(/*std::string &target,*/ std::string &name, double &weight)
{
	LLVOAvatar *av=gAgent.getAvatarObject();//(LLVOAvatar *)gObjectList.findObject(LLUUID(target));
	if(!av)
		return;
//	This fails on a lot of parameters, don't know why
//	av->setVisualParamWeightNoClamp(name.c_str(),weight);
	av->setVisualParamWeight(name.c_str(),weight);
}

void setParamOnTarget(const char* target,const char* paramname,double weight)
{
	// Why the hell is this not working?
	/*
/root/FlexLife/trunk/indra/newview/FLLua.h: In constructor ‘CB_Args3<T1, T2, T3>::CB_Args3(void (*)(T1&, T2&, T3&), const T1&, const T2&, const T3&) [with T1 = std::basic_string<char, std::char_traits<char>, std::allocator<char> >, T2 = std::basic_string<char, std::char_traits<char>, std::allocator<char> >, T3 = double]’:
/root/FlexLife/trunk/indra/newview/LuaAvatar_f.cpp:206:   instantiated from here
/root/FlexLife/trunk/indra/newview/FLLua.h:200: error: no matching function for call to ‘std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(const double&)’
/usr/include/c++/4.3/bits/basic_string.tcc:226: note: candidates are: std::basic_string<_CharT, _Traits, _Alloc>::basic_string(typename _Alloc::rebind<_CharT>::other::size_type, _CharT, const _Alloc&) [with _CharT = char, _Traits = std::char_traits<char>, _Alloc = std::allocator<char>]
/usr/include/c++/4.3/bits/basic_string.tcc:219: note:                 std::basic_string<_CharT, _Traits, _Alloc>::basic_string(const _CharT*, const _Alloc&) [with _CharT = char, _Traits = std::char_traits<char>, _Alloc = std::allocator<char>]
/usr/include/c++/4.3/bits/basic_string.tcc:212: note:                 std::basic_string<_CharT, _Traits, _Alloc>::basic_string(const _CharT*, typename _Alloc::rebind<_CharT>::other::size_type, const _Alloc&) [with _CharT = char, _Traits = std::char_traits<char>, _Alloc = std::allocator<char>]
/usr/include/c++/4.3/bits/basic_string.tcc:201: note:                 std::basic_string<_CharT, _Traits, _Alloc>::basic_string(const std::basic_string<_CharT, _Traits, _Alloc>&, typename _Alloc::rebind<_CharT>::other::size_type, typename _Alloc::rebind<_CharT>::other::size_type, const _Alloc&) [with _CharT = char, _Traits = std::char_traits<char>, _Alloc = std::allocator<char>]
/usr/include/c++/4.3/bits/basic_string.tcc:190: note:                 std::basic_string<_CharT, _Traits, _Alloc>::basic_string(const std::basic_string<_CharT, _Traits, _Alloc>&, typename _Alloc::rebind<_CharT>::other::size_type, typename _Alloc::rebind<_CharT>::other::size_type) [with _CharT = char, _Traits = std::char_traits<char>, _Alloc = std::allocator<char>]
/usr/include/c++/4.3/bits/basic_string.tcc:176: note:                 std::basic_string<_CharT, _Traits, _Alloc>::basic_string(const std::basic_string<_CharT, _Traits, _Alloc>&) [with _CharT = char, _Traits = std::char_traits<char>, _Alloc = std::allocator<char>]
/usr/include/c++/4.3/bits/basic_string.tcc:184: note:                 std::basic_string<_CharT, _Traits, _Alloc>::basic_string(const _Alloc&) [with _CharT = char, _Traits = std::char_traits<char>, _Alloc = std::allocator<char>]
/usr/include/c++/4.3/bits/basic_string.h:2067: note:                 std::basic_string<_CharT, _Traits, _Alloc>::basic_string() [with _CharT = char, _Traits = std::char_traits<char>, _Alloc = std::allocator<char>]
	*/

	//new CB_Args3<std::string,std::string,double>(&setParams_Event,target,paramname,weight); //add to client event queue
}

void setParamOnSelf(const char* paramname,double weight)
{
	LLVOAvatar *me=gAgent.getAvatarObject();
	if(!me)
	{
		LuaError("No Agent Avatar");
		return;
	}

	//new CB_Args3<std::string,std::string,double>(&setParams_Event,me->getID().asString(),paramname,weight); //add to client event queue
	new CB_Args2<std::string,double>(&setParams_Event,paramname,weight); //add to client event queue
}
void LuaWear_Event(const LLUUID& assetid)
{
	LLWearable *wear=LuaLoadWearable(assetid);
	if(!wear)
		LuaError("No Wearable found");
	else if((wear=gWearableList.createCopy(wear))==NULL)
		LuaError("Failed creation of new wearable");
	else
	{
		wear->saveNewAsset();
		wear->writeToAvatar(false);
	}
}
void LuaWear(const LLUUID& assetid)
{
	new CB_Args1<const LLUUID>(&LuaWear_Event,assetid);
	/*LLWearable *wear=LuaLoadWearable(assetid);
	if(!wear)
	{
		LuaError("No Wearable found");
		return;
	}
	LLWearable *newwear=gWearableList.createCopy(wear);
	if(!wear)
	{
		LuaError("Failed creation of new wearable");
		return;
	}
	newwear->saveNewAsset();
	newwear->writeToAvatar(false);*/
}
void LuaRemoveAllWearables_Event()
{
	LLAgent::userRemoveAllClothesStep2(TRUE,NULL);
}
void LuaRemoveAllWearables() // calls glGenTextures
{
	new CB_Args0(LuaRemoveAllWearables_Event);
	//LLAgent::userRemoveAllClothesStep2(TRUE,NULL);
}

bool LuaSaveWearable(LLWearable *w)
{
	if(!w)
		return false;
	//Buffer to hold the char[] version of the LLUUID
	char new_asset_id_string[UUID_STR_LENGTH];

	// Filename itself.
	char filename[LL_MAX_PATH];

	// Get ID and convert to char[]
	w->getID().toString(new_asset_id_string);
	
	// Turn ID into useful filename + path
	snprintf(filename, LL_MAX_PATH, "%s.wbl", gDirUtilp->getExpandedFilename(FL_PATH_LUA,"data",new_asset_id_string).c_str());

	// Open file handle for writing/creation
	LLFILE* fp = LLFile::fopen(filename, "wb");

	// Successful save flag
	BOOL successful_save = FALSE;

	// Did nothing fucking explode?
	if(fp && w->exportFile(fp))
	{
		//Then GREAT SUCCESS
		successful_save = TRUE;
	}

	// File handle still there?
	if(fp)
	{
		// Close it
		fclose(fp);
		fp = NULL;
	}

	// Did shit blow up?
	if(!successful_save)
	{
		// Make a char[] 2 times larger than max std::string  (?)
		char buffer[2*MAX_STRING];

		// Format error message
		snprintf(buffer,		/* Flawfinder: ignore */
				sizeof(buffer),
				"Unable to save '%s' to wearable file.",
				new_asset_id_string);

		// Stuff in warning log
		llwarns << buffer << llendl;
		
		std::stringstream s;

		// Red errors
		s << "Could not save wearable \"" << w->getName() << "\", possibly out of space.";
		LuaError(s.str().c_str());

		// Report back that shit did, indeed, blow up
		return false;
	}

	//Everything went fine, so report that
	return true;
}

LLWearable * LuaLoadWearable(const LLUUID& uuid)
{
	char filename[LL_MAX_PATH];		/* Flawfinder: ignore */
	snprintf(filename, LL_MAX_PATH, "%s.wbl", gDirUtilp->getExpandedFilename(FL_PATH_LUA,"data",uuid.asString()).c_str());		/* Flawfinder: ignore */
	LLFILE* fp = LLFile::fopen(filename, "r");		/* Flawfinder: ignore */
	
	if(!fp)
	{
		LuaError("Cannot open wearable asset file.  Make sure lua/data exists and that it is readable (CHMOD).");
		return NULL;
	}

	LLWearable *w=new LLWearable(uuid);
	if(!w->importFile(fp))
	{
		LuaError("Cannot open wearable asset file.  Make sure lua/data exists and that it is readable (CHMOD).");
		return NULL;
	}
	fclose(fp);

	return w;
}

void LuaSetTEImage(int index,const LLUUID& id)
{
	LLVOAvatar *a=gAgent.getAvatarObject();
	if(!a)
	{
		LuaError("No Agent Avatar");
		return;
	}
	a->setTEImage((U8)index,new LLViewerImage(id));
}
void LuaUpdateAppearance_Event()
{
	gAgent.saveAllWearables();

	// May fix llFloaterCustomize crash due to WT_SHAPE becoming dirty.
	LLVOAvatar* avatar = gAgent.getAvatarObject();
	if ( avatar )
	{
		avatar->invalidateAll();
		avatar->requestLayerSetUploads();
		gAgent.sendAgentSetAppearance();
		// Thanks to Zwagoth
		gAgent.saveWearable(WT_SHAPE,	TRUE);
		gAgent.saveWearable(WT_SKIN,	TRUE);
	}
}
void LuaUpdateAppearance()
{
	new CB_Args0(&LuaUpdateAppearance_Event);
	//gAgent.saveAllWearables();
}

bool HasPermissions(LLViewerInventoryItem* item)
{
	U32 perm_mask = 0x0;
	BOOL is_complete = FALSE;
	if(item)
	{
		perm_mask = item->getPermissions().getMaskOwner();
		is_complete = item->isComplete();
	}
	return((perm_mask & PERM_MODIFY) && is_complete);
}

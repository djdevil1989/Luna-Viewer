#include "llviewerprecompiledheaders.h"
#include "LuaAvatar_f.h"
#include "LuaBase_f.h"
#include "llagent.h"
#include "llvoavatar.h"
#include "llviewerobjectlist.h"
#include "llwearable.h"
#include "llwearablelist.h"
#include "llcharacter.h"

void LuaDumpVisualParams()
{

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
		LLFILE *file = LLFile::fopen(gDirUtilp->getExpandedFilename(SHL_PATH_MACROS,"data"+gDirUtilp->getDirDelimiter()+"wearables",wear->getID().asString()).c_str(),"wb");
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
	std::string  param_msg("");
	param_msg.assign("--[[ Autogenerated by ShoopedLife ]]--\n");
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
	for( S32 i = 0; i < BAKED_TEXTURE_COUNT; i++ )
	{
		S32 tex_index = LLVOAvatar::sBakedTextureIndices[i];
		std::stringstream s;
		s << "setTEImage(" << tex_index <<",\""<< av->getTEImage(tex_index)->getID() << "\")\n";
		param_msg.append(s.str());
	}
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
	return (double)p->getMinWeight();
}

//------------------------------------------------------------------------
// Set
//------------------------------------------------------------------------

void setParamOnSelf(const char* paramname,double weight)
{
	LLVOAvatar *me=gAgent.getAvatarObject();
	LLVisualParam *p=me->getVisualParam(paramname);
	p->setWeight((F32)weight,FALSE);
	me->setVisualParamWeight(p,p->getCurrentWeight());
	gAgent.setAvatarObject(me);
}

void LuaWear(const char* assetid)
{
	LLWearable *wear=LuaLoadWearable(assetid);
	
	LLWearable *newwear=gWearableList.createCopy(wear);
	newwear->saveNewAsset();
	newwear->writeToAvatar(false);
}

void LuaRemoveAllWearables()
{
	LLAgent::userRemoveAllClothesStep2(TRUE,NULL);
}

bool LuaSaveWearable(LLWearable *w)
{
	//Buffer to hold the char[] version of the LLUUID
	char new_asset_id_string[UUID_STR_LENGTH];

	// Filename itself.
	char filename[LL_MAX_PATH];

	// Get ID and convert to char[]
	w->getID().toString(new_asset_id_string);
	
	// Turn ID into useful filename + path
	snprintf(filename, LL_MAX_PATH, "%s.wbl", gDirUtilp->getExpandedFilename(SHL_PATH_LUA,"data",new_asset_id_string).c_str());

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

LLWearable * LuaLoadWearable(const char* uuid)
{
	char filename[LL_MAX_PATH];		/* Flawfinder: ignore */
	snprintf(filename, LL_MAX_PATH, "%s.wbl", gDirUtilp->getExpandedFilename(SHL_PATH_LUA,"data",uuid).c_str());		/* Flawfinder: ignore */
	LLFILE* fp = LLFile::fopen(filename, "r");		/* Flawfinder: ignore */
	
	if(!fp)
	{
		LuaError("Cannot open wearable asset file.  Make sure lua/data exists and that it is readable (CHMOD).");
		return NULL;
	}

	LLUUID id(uuid);
	LLWearable *w=new LLWearable(id);
	if(!w->importFile(fp))
	{
		LuaError("Cannot open wearable asset file.  Make sure lua/data exists and that it is readable (CHMOD).");
		return NULL;
	}
	fclose(fp);

	return w;
}

void LuaSetTEImage(int index,const char *UUID)
{
	LLVOAvatar *a=gAgent.getAvatarObject();
	LLUUID imid;
	imid.set(UUID);
	a->setTEImage((U8)index,new LLViewerImage(imid));
}

void LuaUpdateAppearance()
{
	
}
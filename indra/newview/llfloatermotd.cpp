/** 
 * @file llfloaterlagmeter.cpp
 * @brief The "Lag-o-Meter" floater used to tell users what is causing lag.
 *
 * $LicenseInfo:firstyear=2007&license=viewergpl$
 * 
 * Copyright (c) 2007-2009, Linden Research, Inc.
 * 
 * Second Life Viewer Source Code
 * The source code in this file ("Source Code") is provided by Linden Lab
 * to you under the terms of the GNU General Public License, version 2.0
 * ("GPL"), unless you have obtained a separate licensing agreement
 * ("Other License"), formally executed by you and Linden Lab.  Terms of
 * the GPL can be found in doc/GPL-license.txt in this distribution, or
 * online at http://secondlifegrid.net/programs/open_source/licensing/gplv2
 * 
 * There are special exceptions to the terms and conditions of the GPL as
 * it is applied to this Source Code. View the full text of the exception
 * in the file doc/FLOSS-exception.txt in this software distribution, or
 * online at
 * http://secondlifegrid.net/programs/open_source/licensing/flossexception
 * 
 * By copying, modifying or distributing this software, you acknowledge
 * that you have read and understood your obligations described above,
 * and agree to abide by those obligations.
 * 
 * ALL LINDEN LAB SOURCE CODE IS PROVIDED "AS IS." LINDEN LAB MAKES NO
 * WARRANTIES, EXPRESS, IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY,
 * COMPLETENESS OR PERFORMANCE.
 * $/LicenseInfo$
 */

#include "llviewerprecompiledheaders.h"
#include "llfloatermotd.h"
#include "lluictrlfactory.h"
#include "lltextbox.h"
#include "llagent.h"

LLFloaterMOTD::LLFloaterMOTD(const LLSD& key)
	:	LLFloater(std::string("floater_motd"))
{
	LLUICtrlFactory::getInstance()->buildFloater(this, "floater_motd.xml");

	mMOTDText = getChild<LLTextBox>("motd_text");
}

LLFloaterMOTD::~LLFloaterMOTD()
{
}

BOOL LLFloaterMOTD::postBuild()
{
	childSetAction("OK", onBtnOK, this);
	return TRUE;
}

void LLFloaterMOTD::draw()
{
	mMOTDText->setText( gAgent.mMOTD );
	LLFloater::draw();
}

void LLFloaterMOTD::onBtnOK( void* userdata )
{
	LLFloaterMOTD *fp =(LLFloaterMOTD *)userdata;
	fp->close(false);
}
/** 
 * @file llviewerlayer.h
 * @brief LLViewerLayer class header file
 *
 * $LicenseInfo:firstyear=2001&license=viewergpl$
 * 
 * Copyright (c) 2001-2009, Linden Research, Inc.
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
 * online at http://secondlifegrid.net/programs/open_source/licensing/flossexception
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

#ifndef LL_LLVIEWERLAYER_H
#define LL_LLVIEWERLAYER_H

// Viewer-side representation of a layer...

class LLViewerLayer
{
public:
	LLViewerLayer(const S32 width, const F32 scale = 1.f);
	virtual ~LLViewerLayer();

	F32 getValueScaled(const F32 x, const F32 y) const;
protected:
	F32 getValue(const S32 x, const S32 y) const;
protected:
	S32 mWidth;
	F32 mScale;
	F32 mScaleInv;
	F32 *mDatap;
};

#endif // LL_LLVIEWERLAYER_H

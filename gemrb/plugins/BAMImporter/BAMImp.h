/* GemRB - Infinity Engine Emulator
 * Copyright (C) 2003 The GemRB Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header: /data/gemrb/cvs2svn/gemrb/gemrb/gemrb/plugins/BAMImporter/BAMImp.h,v 1.5 2003/11/25 13:48:04 balrog994 Exp $
 *
 */

#ifndef BAMIMP_H
#define BAMIMP_H

#include "../Core/AnimationMgr.h"
#include "../../includes/globals.h"
#include "../../includes/RGBAColor.h"

typedef struct FrameEntry {
	unsigned short	Width;
	unsigned short	Height;
	short	XPos;
	short	YPos;
	unsigned long	FrameData;
} FrameEntry;

class BAMImp : public AnimationMgr
{
private:
	DataStream * str;
	bool autoFree;
	std::vector<FrameEntry> frames;
	std::vector<CycleEntry> cycles;
	Color Palette[256];
	unsigned char	CompressedColorIndex;
	unsigned long	FramesOffset, PaletteOffset, FLTOffset;
public:
	BAMImp(void);
	~BAMImp(void);
	bool Open(DataStream * stream, bool autoFree = true);
	Sprite2D * GetFrameFromCycle(unsigned char Cycle, unsigned short frame);
	Animation * GetAnimation(unsigned char Cycle, int x, int y, unsigned char mode = IE_NORMAL);
	AnimationFactory * GetAnimationFactory(const char * ResRef, unsigned char mode = IE_NORMAL);
	Sprite2D * GetFrame(unsigned short findex, unsigned char mode = IE_NORMAL);
	void * GetFramePixels(unsigned short findex, unsigned char mode = IE_NORMAL);
	/** This function will load the Animation as a Font */
	Font * GetFont();
	/** Debug Function: Returns the Global Animation Palette as a Sprite2D Object.
	If the Global Animation Palette is NULL, returns NULL. */
	Sprite2D * GetPalette();
public:
	void release(void)
	{
		delete this;
	}
};

#endif

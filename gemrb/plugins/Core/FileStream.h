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
 * $Header: /data/gemrb/cvs2svn/gemrb/gemrb/gemrb/plugins/Core/FileStream.h,v 1.3 2003/11/25 13:48:02 balrog994 Exp $
 *
 */

#ifndef FILESTREAM_H
#define FILESTREAM_H

#include "../../includes/globals.h"

#ifdef WIN32

#ifdef GEM_BUILD_DLL
#define GEM_EXPORT __declspec(dllexport)
#else
#define GEM_EXPORT __declspec(dllimport)
#endif

#else
#define GEM_EXPORT
#endif

class GEM_EXPORT FileStream : public DataStream
{
private:
	FILE * str;
	ulong startpos;
	bool autoFree;
	bool opened;
	unsigned long size;
public:
	FileStream(void);
	~FileStream(void);

	bool Open(const char * filename, bool autoFree = true);
	bool Open(FILE * stream, int startpos, int size, bool autoFree = false);
	int Read(void * dest, int length);
	int Seek(int pos, int startpos);
	unsigned long Size();
  /** No descriptions */
  int ReadLine(void * buf, int maxlen);
};

#endif

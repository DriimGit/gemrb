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
 * $Header: /data/gemrb/cvs2svn/gemrb/gemrb/gemrb/plugins/Core/ClassDesc.cpp,v 1.3 2003/11/25 13:48:02 balrog994 Exp $
 *
 */

#include "../../includes/win32def.h"
#include "ClassDesc.h"

ClassDesc::ClassDesc(void)
{
}

ClassDesc::~ClassDesc(void)
{
}

int ClassDesc::BeginCreate()
{
	return 0;
}

int ClassDesc::EndCreate()
{
	return 0;
}

Class_ID ClassDesc::SubClassID(void)
{
	return Class_ID();
}

const char* ClassDesc::InternalName(void)
{
	return 0;
}

/* GemRB - Infinity Engine Emulator
 * Copyright (C) 2003 The GemRB Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header: /data/gemrb/cvs2svn/gemrb/gemrb/gemrb/plugins/Core/WindowMgr.h,v 1.2 2003/11/25 13:48:03 balrog994 Exp $
 *
 */

#ifndef WINDOWMGR_H
#define WINDOWMGR_H

#include "Plugin.h"
#include "Window.h"
#include "DataStream.h"

/**This Class Defines basic Methods for the implementation of a GUI Window Manager.
  *@author GemRB Developement Team
  */

#ifdef WIN32

#ifdef GEM_BUILD_DLL
#define GEM_EXPORT __declspec(dllexport)
#else
#define GEM_EXPORT __declspec(dllimport)
#endif

#else
#define GEM_EXPORT
#endif

class GEM_EXPORT WindowMgr : public Plugin  {
public: 
	WindowMgr();
	virtual ~WindowMgr();
  /** This function loads all available windows from the 'stream' parameter. */
  virtual bool Open(DataStream * stream, bool autoFree = true) = 0;
  /** Returns the i-th window in the Previously Loaded Stream */
  virtual Window * GetWindow(unsigned long i) = 0;
  /** Returns the number of available windows */
  virtual unsigned long GetWindowsCount() = 0;
};

#endif

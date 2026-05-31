/*
 * This file is part of sc4-dll-utilities, a set of utilities for
 * SimCity 4 DLL Plugins.
 *
 * Copyright (C) 2026 Nicholas Hayes
 *
 * sc4-dll-utilities is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * sc4-dll-utilities is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with sc4-dll-utilities.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include <cstdint>

class cIGZWin;

namespace GZWinUtil
{
	bool GetButtonToggleState(cIGZWin* pWin, uint32_t buttonID);
	bool SetButtonToggleState(cIGZWin* pWin, uint32_t buttonID, bool toggleState);

	bool GetChildWindowEnabled(cIGZWin* pWin, uint32_t childID);
	bool SetChildWindowEnabled(cIGZWin* pWin, uint32_t childID, bool enabled);

	bool GetWindowEnabled(cIGZWin* pWin);
	bool SetWindowEnabled(cIGZWin* pWin, bool enabled);

	bool GetWindowVisible(cIGZWin* pWin);
	bool SetWindowVisible(cIGZWin* pWin, bool visible);
}
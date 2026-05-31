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

#include "GZWinUtil.h"
#include "cIGZWin.h"
#include "cIGZWinBtn.h"
#include "cRZAutoRefCount.h"

bool GZWinUtil::GetButtonToggleState(cIGZWin* pWin, uint32_t buttonID)
{
	bool result = false;

	if (pWin)
	{
		cRZAutoRefCount<cIGZWinBtn> button;

		if (pWin->GetChildAsRecursive(buttonID, GZIID_cIGZWinBtn, button.AsPPVoid()))
		{
			result = button->IsOn();
		}
	}

	return result;
}

bool GZWinUtil::SetButtonToggleState(cIGZWin* pWin, uint32_t buttonID, bool toggleState)
{
	if (pWin)
	{
		cRZAutoRefCount<cIGZWinBtn> button;

		if (pWin->GetChildAsRecursive(buttonID, GZIID_cIGZWinBtn, button.AsPPVoid()))
		{
			if (toggleState)
			{
				button->ToggleOn();
			}
			else
			{
				button->ToggleOff();
			}

			return true;
		}
	}

	return false;
}

bool GZWinUtil::GetChildWindowEnabled(cIGZWin* pWin, uint32_t childID)
{
	return pWin && GetWindowEnabled(pWin->GetChildWindowFromIDRecursive(childID));
}

bool GZWinUtil::SetChildWindowEnabled(cIGZWin* pWin, uint32_t childID, bool enabled)
{
	return pWin && SetWindowEnabled(pWin->GetChildWindowFromIDRecursive(childID), enabled);
}

bool GZWinUtil::GetWindowEnabled(cIGZWin* pWin)
{
	return pWin && pWin->GetFlag(cIGZWin::WinFlag_Enabled);
}

bool GZWinUtil::SetWindowEnabled(cIGZWin* pWin, bool enabled)
{
	if (pWin)
	{
		pWin->SetFlag(cIGZWin::WinFlag_Enabled, enabled);

		return true;
	}

	return false;
}

bool GZWinUtil::GetWindowVisible(cIGZWin* pWin)
{
	return pWin && pWin->GetFlag(cIGZWin::WinFlag_Visible);
}

bool GZWinUtil::SetWindowVisible(cIGZWin* pWin, bool visible)
{
	if (pWin)
	{
		if (visible != pWin->GetFlag(cIGZWin::WinFlag_Visible))
		{
			pWin->SetFlag(cIGZWin::WinFlag_Visible, visible);
		}

		return true;
	}

	return false;
}

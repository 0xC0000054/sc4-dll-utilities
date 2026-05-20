/*
 * This file is part of sc4-dll-utilities, a set of helper classes for
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

#include "OccupantUtil.h"
#include "cISCPropertyHolder.h"
#include "cISC4City.h"
#include "cISC4LotManager.h"
#include "cISC4Occupant.h"
#include "PropertyUtil.h"

bool OccupantUtil::GetDisplayName(cISC4Occupant* pOccupant, cIGZString& name)
{
	bool result = false;

	if (pOccupant)
	{
		result = PropertyUtil::GetDisplayName(pOccupant->AsPropertyHolder(), name);
	}

	return result;
}

bool OccupantUtil::GetExemplarName(cISC4Occupant* pOccupant, cIGZString& name)
{
	bool result = false;

	if (pOccupant)
	{
		result = PropertyUtil::GetExemplarName(pOccupant->AsPropertyHolder(), name);
	}

	return result;
}

bool OccupantUtil::GetUserVisibleName(cISC4Occupant* pOccupant, cIGZString& name)
{
	bool result = false;

	if (pOccupant)
	{
		result = PropertyUtil::GetUserVisibleName(pOccupant->AsPropertyHolder(), name);
	}

	return result;
}

bool OccupantUtil::GetUserVisibleName(cISC4Occupant* pOccupant, cRZAutoRefCount<cIGZString>& name)
{
	bool result = false;

	if (pOccupant)
	{
		result = PropertyUtil::GetUserVisibleName(pOccupant->AsPropertyHolder(), name);
	}

	return result;
}

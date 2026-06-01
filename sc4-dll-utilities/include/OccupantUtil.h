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
#include "cIGZString.h"
#include "cRZAutoRefCount.h"

class cISC4City;
class cISC4Lot;
class cISC4Occupant;

namespace OccupantUtil
{
	bool GetDisplayName(cISC4Occupant* pOccupant, cIGZString& name);

	bool GetExemplarName(cISC4Occupant* pOccupant, cIGZString& name);

	bool GetUserVisibleName(cISC4Occupant* pOccupant, cIGZString& name);
	bool GetUserVisibleName(cISC4Occupant* pOccupant, cRZAutoRefCount<cIGZString>& name);

	/**
	 * @brief Attempts to get the occupant's lot.
	 * @param pOccupant A pointer to the occupant.
	 * @return The occupant's lot or a null pointer.

	 */
	cISC4Lot* GetLot(cISC4Occupant* pOccupant);

	/**
	 * @brief Attempts to get the occupant's lot.
	 * @param pOccupant A pointer to the occupant.
	 * @param pCity An pointer to the city.
	 * This is an optimization for callers that already have
	 * a city pointer available.
	 * @return The occupant's lot or a null pointer.
	 */
	cISC4Lot* GetLot(cISC4Occupant* pOccupant, cISC4City* pCity);
}
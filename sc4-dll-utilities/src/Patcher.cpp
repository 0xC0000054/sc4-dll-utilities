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

#include "Patcher.h"

void Patcher::InstallJump(uintptr_t targetAddress, uintptr_t destination)
{
	// Allow the memory to be written to, the original page
	// protection will be restored after we write to it.
	AutoVirtualProtect avp(
		reinterpret_cast<LPVOID>(targetAddress),
		5,
		PAGE_EXECUTE_READWRITE);

	// Patch the memory at the specified address.
	*((uint8_t*)targetAddress) = 0xE9;
	*((uintptr_t*)(targetAddress + 1)) = destination - targetAddress - 5;
}

void Patcher::InstallHook(uintptr_t targetAddress, void(*pfnFunc)())
{
	InstallJump(targetAddress, reinterpret_cast<uintptr_t>(pfnFunc));
}

void Patcher::InstallCallHook(uintptr_t targetAddress, void* pfnFunc)
{
	// Allow the memory to be written to, the original page
	// protection will be restored after we write to it.
	AutoVirtualProtect avp(
		reinterpret_cast<LPVOID>(targetAddress),
		5,
		PAGE_EXECUTE_READWRITE);

	// Patch the memory at the specified address.
	*((uint8_t*)targetAddress) = 0xE8;
	*((uintptr_t*)(targetAddress + 1)) = reinterpret_cast<uintptr_t>(pfnFunc) - targetAddress - 5;
}

void Patcher::InstallJumpTableHook(uintptr_t targetAddress, void* pfnFunc)
{
	OverwriteMemory(targetAddress, reinterpret_cast<uintptr_t>(pfnFunc));
}

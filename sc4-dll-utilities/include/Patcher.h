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
#include <Windows.h>
#include <wil/result.h>

// This attribute is used for defining assembly patch hook functions.
// It makes the compiler declare the function without prolog and epilog code.
#ifdef __clang__
#define NAKED_FUN __attribute__((naked))
#else
#define NAKED_FUN __declspec(naked)
#endif

// Provides various methods for patching data in the game's memory.
// All methods throw wil::ResultException on error.

namespace Patcher
{
	// A RAII wrapper around the VirtualProtect function that restores
	// the original page protection when the destructor runs.
	class AutoVirtualProtect
	{
	public:
		AutoVirtualProtect(LPVOID address, SIZE_T size, DWORD newProtect)
			: address(address), size(size), dwOldProtect(PAGE_EXECUTE_READ)
		{
			THROW_IF_WIN32_BOOL_FALSE(VirtualProtect(
				address,
				size,
				newProtect,
				&dwOldProtect));
		}

		~AutoVirtualProtect()
		{
			// Restore the original page protection.
			VirtualProtect(
				address,
				size,
				dwOldProtect,
				&dwOldProtect);
		}

		// Disable copy and move.

		AutoVirtualProtect(const AutoVirtualProtect&) = delete;
		AutoVirtualProtect(AutoVirtualProtect&&) = delete;

		AutoVirtualProtect& operator=(const AutoVirtualProtect&) = delete;
		AutoVirtualProtect& operator=(AutoVirtualProtect&&) = delete;

	private:
		LPVOID address;
		SIZE_T size;
		DWORD dwOldProtect;
	};

	/**
	 * @brief Overwrite memory at the specified address.
	 * @tparam T The value type, must be bool, integer, or floating point.
	 * @tparam
	 * @param address The target address.
	 * @param value The value to write.
	 */
	template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	void OverwriteMemory(uintptr_t address, T value)
	{
		static_assert(std::is_arithmetic_v<T>, "T has an unsupported type.");

		// Allow the memory to be written to, the original page
		// protection will be restored after we write to it.
		AutoVirtualProtect avp(
			reinterpret_cast<LPVOID>(address),
			sizeof(value),
			PAGE_EXECUTE_READWRITE);

		// Patch the memory at the specified address.
		*((T*)address) = value;
	}

	/**
	 * @brief Installs a jump at the specified address.
	 * @param targetAddress The address to install the jump.
	 * @param destination The destination address of the jump.
	 */
	void InstallJump(uintptr_t targetAddress, uintptr_t destination);

	/**
	 * @brief Installs a jump to the specified hook function.
	 * @param targetAddress The target address.
	 * @param pfnFunc A pointer to the hook function.
	 * @remarks The hook function must be declared as follows:
	 *
	 * void NAKED_FUN HookFunctionName()
	 * The function body should contain only assembly.
	 */
	void InstallHook(uintptr_t targetAddress, void (*pfnFunc)());

	/**
	 * @brief Replaces an existing function call instruction.
	 * @param targetAddress The target address of the call instruction to update.
	 * @param pfnFunc A pointer to the replacement function address.
	 */
	void InstallCallHook(uintptr_t targetAddress, void* pfnFunc);

	/**
	 * @brief Replaces a function address in a jump table.
	 * @param targetAddress The jump table address to update.
	 * @param pfnFunc A pointer to the replacement function address.
	 */
	void InstallJumpTableHook(uintptr_t targetAddress, void* pfnFunc);
}
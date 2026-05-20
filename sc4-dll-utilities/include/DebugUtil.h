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
#include <stdarg.h>

// Provides wrappers around the Windows OutputDebugString APIs
namespace DebugUtil
{
	void PrintToDebugOutput(const char* const line);
	void PrintToDebugOutput(const wchar_t* const line);

	void PrintToDebugOutputUtf8(const char* const line);

	void PrintToDebugOutputFormatted(const char* const format, ...);
	void PrintToDebugOutputFormatted(const char* const format, va_list args);

	void PrintToDebugOutputFormattedUtf8(const char* const format, ...);
	void PrintToDebugOutputFormattedUtf8(const char* const format, va_list args);

	void PrintLineToDebugOutput(const char* const line);
	void PrintLineToDebugOutput(const wchar_t* const line);

	void PrintLineToDebugOutputUtf8(const char* const line);

	void PrintLineToDebugOutputFormatted(const char* const format, ...);
	void PrintLineToDebugOutputFormatted(const char* const format, va_list args);

	void PrintLineToDebugOutputFormattedUtf8(const char* const format, ...);
	void PrintLineToDebugOutputFormattedUtf8(const char* const format, va_list args);
}
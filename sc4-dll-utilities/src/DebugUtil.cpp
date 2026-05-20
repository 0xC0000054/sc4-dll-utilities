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

#include "DebugUtil.h"
#include "StringConversion.h"
#include <memory>
#include <string>
#include <Windows.h>

namespace
{
	typedef void (*PrintFn)(const char* const);

	void PrintToDebugOutputFormattedCore(
		PrintFn printFn,
		const char* const format,
		va_list args)
	{
		va_list argsCopy;
		va_copy(argsCopy, args);

		int formattedStringLength = std::vsnprintf(nullptr, 0, format, argsCopy);

		va_end(argsCopy);

		if (formattedStringLength > 0)
		{
			size_t formattedStringLengthWithNull = static_cast<size_t>(formattedStringLength) + 1;

			constexpr size_t stackBufferSize = 1024;

			if (formattedStringLengthWithNull >= stackBufferSize)
			{
				std::unique_ptr<char[]> buffer = std::make_unique_for_overwrite<char[]>(formattedStringLengthWithNull);

				std::vsnprintf(buffer.get(), formattedStringLengthWithNull, format, args);

				printFn(buffer.get());
			}
			else
			{
				char buffer[stackBufferSize]{};

				std::vsnprintf(buffer, stackBufferSize, format, args);

				printFn(buffer);
			}
		}
	}
}

void DebugUtil::PrintToDebugOutput(const char* const line)
{
	OutputDebugStringA(line);
}

void DebugUtil::PrintToDebugOutput(const wchar_t* const line)
{
	OutputDebugStringW(line);
}

void DebugUtil::PrintToDebugOutputUtf8(const char* const line)
{
	const int utf8Length = strlen(line);

	if (utf8Length > 0)
	{
		const int utf16Length = StringConversion::GetUtf16StringLengthFromUtf8(line, utf8Length);

		const int stackBufferSize = 1024;

		if (utf16Length >= stackBufferSize)
		{
			std::wstring utf16Str = StringConversion::Utf8ToUtf16(line, utf8Length);

			PrintToDebugOutput(utf16Str.c_str());
		}
		else
		{
			wchar_t buffer[stackBufferSize]{};

			StringConversion::Utf8ToUtf16(line, utf8Length, buffer, utf16Length);

			PrintToDebugOutput(buffer);
		}
	}
}

void DebugUtil::PrintToDebugOutputFormatted(const char* const format, ...)
{
	va_list args;
	va_start(args, format);

	PrintToDebugOutputFormatted(format, args);

	va_end(args);
}

void DebugUtil::PrintToDebugOutputFormatted(const char* const format, va_list args)
{
	PrintToDebugOutputFormattedCore(PrintToDebugOutput, format, args);
}

void DebugUtil::PrintToDebugOutputFormattedUtf8(const char* const format, ...)
{
	va_list args;
	va_start(args, format);

	PrintToDebugOutputFormattedUtf8(format, args);

	va_end(args);
}

void DebugUtil::PrintToDebugOutputFormattedUtf8(const char* const format, va_list args)
{
	PrintToDebugOutputFormattedCore(PrintToDebugOutputUtf8, format, args);
}

void DebugUtil::PrintLineToDebugOutput(const char* const line)
{
	PrintToDebugOutput(line);
	PrintToDebugOutput("\n");
}

void DebugUtil::PrintLineToDebugOutput(const wchar_t* const line)
{
	PrintToDebugOutput(line);
	PrintToDebugOutput("\n");
}

void DebugUtil::PrintLineToDebugOutputUtf8(const char* const line)
{
	PrintToDebugOutputUtf8(line);
	PrintToDebugOutput("\n");
}

void DebugUtil::PrintLineToDebugOutputFormatted(const char* const format, ...)
{
	va_list args;
	va_start(args, format);

	PrintLineToDebugOutputFormatted(format, args);

	va_end(args);
}

void DebugUtil::PrintLineToDebugOutputFormatted(const char* const format, va_list args)
{
	PrintToDebugOutputFormattedCore(PrintLineToDebugOutput, format, args);
}

void DebugUtil::PrintLineToDebugOutputFormattedUtf8(const char* const format, ...)
{
	va_list args;
	va_start(args, format);

	PrintToDebugOutputFormattedUtf8(format, args);

	va_end(args);
}

void DebugUtil::PrintLineToDebugOutputFormattedUtf8(const char* const format, va_list args)
{
	PrintToDebugOutputFormattedCore(PrintLineToDebugOutputUtf8, format, args);
}

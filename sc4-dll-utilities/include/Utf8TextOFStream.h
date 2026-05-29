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
#include <filesystem>
#include <fstream>
#include <stdarg.h>

// An output text stream that writes UTF-8 strings as binary data.
// The strings used with this class are assumed to be UTF-8, no
// character set conversion is performed when writing them.
class Utf8TextOFStream
{
public:
	Utf8TextOFStream(const std::filesystem::path& path);

	void Flush();

	void Write(const char* text);

	void Write(const cIGZString& text);

	void WriteFormatted(const char* format, ...);

	void WriteFormatted(const char* format, va_list args);

	void WriteLine(const char* line);

	void WriteLine(const cIGZString& line);

	void WriteLineFormatted(const char* format, ...);

	void WriteLineFormatted(const char* format, va_list args);

	explicit operator bool() const
	{
		return (bool)file;
	}

private:
	typedef void (Utf8TextOFStream::* WriteFormattedCallback)(const char*);

	void WriteFormattedCore(WriteFormattedCallback callback, const char* format, va_list args);

	std::ofstream file;
};


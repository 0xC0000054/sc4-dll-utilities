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

#include "Utf8TextOFStream.h"

Utf8TextOFStream::Utf8TextOFStream(const std::filesystem::path& path)
	// Open the file in binary mode to allow UTF-8 text to be written without modification.
	// UTF-8 is the native encoding of SC4.
	: file(path.c_str(), std::ofstream::out | std::ofstream::trunc | std::ofstream::binary)
{
}

void Utf8TextOFStream::Flush()
{
	if (file)
	{
		file.flush();
	}
}

void Utf8TextOFStream::Write(const char* text)
{
	if (file)
	{
		file << text;
	}
}

void Utf8TextOFStream::Write(const cIGZString& text)
{
	Write(text.ToChar());
}

void Utf8TextOFStream::WriteFormatted(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	WriteFormatted(format, args);

	va_end(args);
}

void Utf8TextOFStream::WriteFormatted(const char* format, va_list args)
{
	WriteFormattedCore(&Utf8TextOFStream::Write, format, args);
}

void Utf8TextOFStream::WriteLine(const char* text)
{
	if (file)
	{
		file << text << '\n';
	}
}

void Utf8TextOFStream::WriteLine(const cIGZString& line)
{
	WriteLine(line.ToChar());
}

void Utf8TextOFStream::WriteLineFormatted(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	WriteLineFormatted(format, args);

	va_end(args);
}

void Utf8TextOFStream::WriteLineFormatted(const char* format, va_list args)
{
	WriteFormattedCore(&Utf8TextOFStream::WriteLine, format, args);
}

void Utf8TextOFStream::WriteFormattedCore(
	WriteFormattedCallback callback,
	const char* format,
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

			std::invoke(callback, this, buffer.get());
		}
		else
		{
			char buffer[stackBufferSize]{};

			std::vsnprintf(buffer, stackBufferSize, format, args);

			std::invoke(callback, this, buffer);
		}
	}
}
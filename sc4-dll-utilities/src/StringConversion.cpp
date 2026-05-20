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

#include "StringConversion.h"
#include "cIGZString.h"
#include <Windows.h>
#include <stdexcept>
#include <memory>

int StringConversion::GetConvertedStringLength(const wchar_t* source, int sourceLength, uint32_t destinationCodePage)
{
	int length = WideCharToMultiByte(destinationCodePage, 0, source, sourceLength, nullptr, 0, nullptr, nullptr);

	THROW_LAST_ERROR_IF(length == 0);

	return length;
}

int StringConversion::GetConvertedStringLength(const std::wstring& source, uint32_t destinationCodePage)
{
	return GetConvertedStringLength(source.c_str(), static_cast<int>(source.size()), destinationCodePage);
}

int StringConversion::GetUtf16StringLength(const char* source, int sourceLength, uint32_t sourceCodePage)
{
	int length = MultiByteToWideChar(sourceCodePage, 0, source, sourceLength, nullptr, 0);

	THROW_LAST_ERROR_IF(length == 0);

	return length;
}

int StringConversion::GetUtf16StringLengthFromUtf8(const char* utf8, int utf8Length)
{
	return GetUtf16StringLength(utf8, utf8Length, CP_UTF8);
}

int StringConversion::GetUtf8StringLengthFromUtf16(const wchar_t* source, int sourceLength)
{
	return GetConvertedStringLength(source, sourceLength, CP_UTF8);
}

int StringConversion::GetUtf8StringLengthFromUtf16(const std::wstring& source)
{
	return GetConvertedStringLength(source, CP_UTF8);
}

void StringConversion::ToUtf16(const char* source, int sourceLength, uint32_t sourceCodePage, wchar_t* utf16Buffer, int utf16BufferLength)
{
	int length = MultiByteToWideChar(sourceCodePage, 0, source, sourceLength, utf16Buffer, utf16BufferLength);

	THROW_LAST_ERROR_IF(length == 0);
}

std::wstring StringConversion::ToUtf16(const char* source, int sourceLength, uint32_t sourceCodePage)
{
	std::wstring destination;

	const int utf16Length = GetUtf16StringLength(source, sourceLength, sourceCodePage);

	destination.resize(static_cast<size_t>(utf16Length));

	ToUtf16(source, sourceLength, sourceCodePage, destination.data(), utf16Length);

	return destination;
}

std::wstring StringConversion::ToUtf16(const cIGZString& source)
{
	return ToUtf16(source.ToChar(), static_cast<int>(source.Strlen()), CP_UTF8);
}

void StringConversion::FromUtf16(const wchar_t* source, int sourceLength, char* destinationBuffer, int destinationBufferLength, uint32_t destinationCodePage)
{
	int length = WideCharToMultiByte(destinationCodePage, 0, source, sourceLength, destinationBuffer, destinationBufferLength, nullptr, nullptr);

	THROW_LAST_ERROR_IF(length == 0);
}

void StringConversion::FromUtf16(const std::wstring& source, char* destinationBuffer, int destinationBufferLength, uint32_t destinationCodePage)
{
	FromUtf16(source.c_str(), static_cast<int>(source.size()), destinationBuffer, destinationBufferLength, destinationCodePage);
}

void StringConversion::FromUtf16(const wchar_t* source, int sourceLength, cIGZString& destination)
{
	const int utf8Length = GetUtf8StringLengthFromUtf16(source, sourceLength);

	const int stackBufferSize = 1024;

	if (utf8Length >= stackBufferSize)
	{
		std::unique_ptr<char[]> buffer = std::make_unique_for_overwrite<char[]>(utf8Length);

		Utf16ToUtf8(source, sourceLength, buffer.get(), utf8Length);

		destination.FromChar(buffer.get(), utf8Length);
	}
	else
	{
		char buffer[stackBufferSize]{};

		Utf16ToUtf8(source, sourceLength, buffer, utf8Length);

		destination.FromChar(buffer, utf8Length);
	}
}

void StringConversion::FromUtf16(const std::wstring& source, cIGZString& destination)
{
	const int utf8Length = GetUtf8StringLengthFromUtf16(source);

	const int stackBufferSize = 1024;

	if (utf8Length >= stackBufferSize)
	{
		std::unique_ptr<char[]> buffer = std::make_unique_for_overwrite<char[]>(utf8Length);

		Utf16ToUtf8(source, buffer.get(), utf8Length);

		destination.FromChar(buffer.get(), utf8Length);
	}
	else
	{
		char buffer[stackBufferSize]{};

		Utf16ToUtf8(source, buffer, utf8Length);

		destination.FromChar(buffer, utf8Length);
	}
}

void StringConversion::Utf8ToUtf16(const char* utf8Buffer, int utf8BufferLength, wchar_t* utf16Buffer, int utf16BufferLength)
{
	ToUtf16(utf8Buffer, utf8BufferLength, CP_UTF8, utf16Buffer, utf16BufferLength);
}

std::wstring StringConversion::Utf8ToUtf16(const char* utf8Buffer, int utf8BufferLength)
{
	return ToUtf16(utf8Buffer, utf8BufferLength, CP_UTF8);
}

void StringConversion::Utf16ToUtf8(const wchar_t* source, int sourceLength, char* destinationBuffer, int destinationBufferLength)
{
	FromUtf16(source, sourceLength, destinationBuffer, destinationBufferLength, CP_UTF8);
}

void StringConversion::Utf16ToUtf8(const std::wstring& source, char* destinationBuffer, int destinationBufferLength)
{
	FromUtf16(source, destinationBuffer, destinationBufferLength, CP_UTF8);
}

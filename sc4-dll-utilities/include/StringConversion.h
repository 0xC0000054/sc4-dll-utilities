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
#include <string>
#include <wil/result.h>

class cIGZString;

// String character set/code page conversion functions that are thin wrappers
// over the Windows WideCharToMultiByte and MultiByteToWideChar APIs.
//
// SC4 uses UTF-8 as its native format, while Windows XP and later use UTF-16LE
// as their native format.
// The UTF8 <--> UTF-16 cases have dedicated helper methods for convenience.
//
// Other Windows code pages can also be used, see the following MSDN page
// for a list of Windows code page identifiers:
// https://learn.microsoft.com/en-us/windows/win32/intl/code-page-identifiers
//
// Possible exceptions types include wil::ResultException, std::bad_alloc, etc.
namespace StringConversion
{
	int GetConvertedStringLength(const wchar_t* source, int sourceLength, uint32_t destinationCodePage);
	int GetConvertedStringLength(const std::wstring& source, uint32_t destinationCodePage);

	int GetUtf16StringLength(const char* source, int sourceLength, uint32_t sourceCodePage);

	int GetUtf16StringLengthFromUtf8(const char* utf8, int utf8Length);

	int GetUtf8StringLengthFromUtf16(const wchar_t* source, int sourceLength);
	int GetUtf8StringLengthFromUtf16(const std::wstring& source);

	void ToUtf16(const char* source, int sourceLength, uint32_t sourceCodePage, wchar_t* utf16Buffer, int utf16BufferLength);
	std::wstring ToUtf16(const char* source, int sourceLength, uint32_t sourceCodePage);

	std::wstring ToUtf16(const cIGZString& source);

	void FromUtf16(const wchar_t* source, int sourceLength, char* destinationBuffer, int destinationBufferLength, uint32_t destinationCodePage);
	void FromUtf16(const std::wstring& source, char* destinationBuffer, int destinationBufferLength, uint32_t destinationCodePage);

	void FromUtf16(const wchar_t* source, int sourceLength, cIGZString& destination);
	void FromUtf16(const std::wstring& source, cIGZString& destination);

	void Utf8ToUtf16(const char* utf8Buffer, int utf8BufferLength, wchar_t* utf16Buffer, int utf16BufferLength);
	std::wstring Utf8ToUtf16(const char* utf8Buffer, int utf8BufferLength);

	void Utf16ToUtf8(const wchar_t* source, int sourceLength, char* destinationBuffer, int destinationBufferLength);
	void Utf16ToUtf8(const std::wstring& source, char* destinationBuffer, int destinationBufferLength);
}
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
#include "cRZBaseString.h"
#include <string>
#include "wil/result.h"

namespace PathUtil
{
	// The extended path functions are used to allow various Windows APIs
	// to work with file/directory paths that exceed 260 characters in length.

	std::wstring AddExtendedPathPrefix(const std::wstring& path);
	std::wstring RemoveExtendedPathPrefix(const std::wstring& path);
	bool MustAddExtendedPathPrefix(const std::wstring& path) noexcept;
	// This function is used to normalize extended paths, as the
	// OS won't automatically do it.
	// Throws wil::ResultException on error.
	std::wstring Normalize(const std::wstring& path);

	cRZBaseString Combine(cIGZString const& path, const std::string_view& segment);
	void Combine(cIGZString const& path, const std::string_view& segment, cIGZString& destination);
	std::string Combine(const std::string& root, const std::string_view& segment);
	std::wstring Combine(const std::wstring& root, const std::wstring_view& segment);

	std::string_view GetFileName(const cIGZString& path);
	std::string_view GetFileName(const std::string_view& path);
	std::wstring_view GetFileName(const std::wstring_view& path);

	std::string_view GetExtension(const cIGZString& path);
	std::string_view GetExtension(const std::string_view& path);
	std::wstring_view GetExtension(const std::wstring_view& path);

	bool IsDirectorySeparator(char value) noexcept;
	bool IsDirectorySeparator(wchar_t value) noexcept;
}

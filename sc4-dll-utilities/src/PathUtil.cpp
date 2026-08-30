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

#include "PathUtil.h"
#include <Windows.h>

static const std::wstring_view extendedPathPrefix = L"\\\\?\\";
static const std::wstring_view extendedUncPathPrefix = L"\\\\?\\UNC\\";
static const std::wstring_view networkPathPrefix = L"\\\\";

static const char directorySeparator = '\\';
static const std::string_view directorySeparatorAsString = "\\";
static const char altDirectorySeparator = '/';
static const char volumeSeparator = ':';

static const wchar_t directorySeparatorWide = L'\\';
static const wchar_t altDirectorySeparatorWide = L'/';
static const wchar_t volumeSeparatorWide = L':';

std::wstring PathUtil::AddExtendedPathPrefix(const std::wstring& path)
{
	if (path.starts_with(extendedPathPrefix))
	{
		return path;
	}
	else
	{
		if (path.starts_with(networkPathPrefix))
		{
			std::wstring result(extendedUncPathPrefix);
			result.append(path.substr(2));

			return result;
		}
		else
		{
			std::wstring result(extendedPathPrefix);
			result.append(path);

			return result;
		}
	}
}

std::wstring PathUtil::RemoveExtendedPathPrefix(const std::wstring& path)
{
	if (path.starts_with(extendedUncPathPrefix))
	{
		std::wstring result(networkPathPrefix);

		result.append(std::wstring_view(path).substr(extendedUncPathPrefix.size()));
	}
	else if (path.starts_with(extendedPathPrefix))
	{
		std::wstring result(std::wstring_view(path).substr(extendedPathPrefix.size()));

		return result;
	}

	return path;
}

bool PathUtil::MustAddExtendedPathPrefix(const std::wstring& path) noexcept
{
	return path.size() >= MAX_PATH && !path.starts_with(extendedPathPrefix);
}

std::wstring PathUtil::Normalize(const std::wstring& path)
{
	// With the extended path format, we have to make the OS normalize the path.
	// It will not do so when opening the file.

	DWORD normalizedPathLengthWithNull = GetFullPathNameW(path.c_str(), 0, nullptr, nullptr);

	THROW_LAST_ERROR_IF(normalizedPathLengthWithNull == 0);

	std::wstring normalizedPath;
	normalizedPath.resize(normalizedPathLengthWithNull);

	DWORD normalizedPathLength2 = GetFullPathNameW(
		path.c_str(),
		normalizedPathLengthWithNull,
		normalizedPath.data(),
		nullptr);

	THROW_LAST_ERROR_IF(normalizedPathLength2 == 0);

	// Strip the null terminator.
	normalizedPath.resize(normalizedPathLength2);

	return normalizedPath;
}

cRZBaseString PathUtil::Combine(cIGZString const& root, const std::string_view& segment)
{
	cRZBaseString result;

	Combine(root, segment, result);

	return result;
}

void PathUtil::Combine(cIGZString const& root, const std::string_view& segment, cIGZString& destination)
{
	const uint32_t rootLength = root.Strlen();

	if (rootLength > 0)
	{
		const char* const rootChars = root.ToChar();
		destination.FromChar(rootChars, rootLength);

		if (!segment.empty())
		{
			if (!IsDirectorySeparator(rootChars[rootLength - 1]))
			{
				destination.Append(directorySeparatorAsString.data(), directorySeparatorAsString.size());
			}

			destination.Append(segment.data(), segment.size());
		}
	}
	else
	{
		destination.Erase(0, UINT_MAX);
	}
}

std::string PathUtil::Combine(const std::string& root, const std::string_view& segment)
{
	if (!root.empty() && !segment.empty())
	{
		std::string result(root);

		if (!IsDirectorySeparator(root[root.size() - 1]))
		{
			result.append(1, directorySeparatorWide);
		}

		result.append(segment);

		return result;
	}

	return root;
}

std::wstring PathUtil::Combine(const std::wstring& root, const std::wstring_view& segment)
{
	if (!root.empty() && !segment.empty())
	{
		std::wstring result(root);

		if (!IsDirectorySeparator(root[root.size() - 1]))
		{
			result.append(1, directorySeparatorWide);
		}

		result.append(segment);

		return result;
	}

	return root;
}

std::string_view PathUtil::GetExtension(const cIGZString& path)
{
	return GetExtension(std::string_view(path.ToChar(), path.Strlen()));
}

std::string_view PathUtil::GetExtension(const std::string_view& path)
{
	std::string_view extension;

	if (path.size() > 0)
	{
		const size_t length = path.size();
		const size_t lastCharacterIndex = length - 1;

		// This loop will exclude file names that start with a period, but that
		// is the desired behavior.

		for (size_t i = lastCharacterIndex; i != 0; i--)
		{
			const wchar_t c = path[i];

			if (c == '.')
			{
				// Treat a file name ending in a period as having no file extension.
				if (i != lastCharacterIndex)
				{
					extension = path.substr(i, length - i);
				}
				break;
			}
			else if (IsDirectorySeparator(c))
			{
				break;
			}
		}
	}

	return extension;
}

std::wstring_view PathUtil::GetExtension(const std::wstring_view& path)
{
	std::wstring_view extension;

	if (path.size() > 0)
	{
		const size_t length = path.size();
		const size_t lastCharacterIndex = length - 1;

		// This loop will exclude file names that start with a period, but that
		// is the desired behavior.

		for (size_t i = lastCharacterIndex; i != 0; i--)
		{
			const wchar_t c = path[i];

			if (c == L'.')
			{
				// Treat a file name ending in a period as having no file extension.
				if (i != lastCharacterIndex)
				{
					extension = path.substr(i, length - i);
				}
				break;
			}
			else if (IsDirectorySeparator(c))
			{
				break;
			}
		}
	}

	return extension;
}

std::string_view PathUtil::GetFileName(const cIGZString& path)
{
	return GetFileName(std::string_view(path.ToChar(), path.Strlen()));
}

std::string_view PathUtil::GetFileName(const std::string_view& path)
{
	std::string_view fileName;

	if (path.size() > 0)
	{
		const size_t length = path.size();

		// This loop will exclude file names that start with a period, but that
		// is the desired behavior.

		for (size_t i = length - 1; i != 0; i--)
		{
			const char c = path[i];

			if (IsDirectorySeparator(c) || c == volumeSeparator)
			{
				fileName = path.substr(i + 1, length - i - 1);
				break;
			}
		}
	}

	return fileName;
}

std::wstring_view PathUtil::GetFileName(const std::wstring_view& path)
{
	std::wstring_view fileName;

	if (path.size() > 0)
	{
		const size_t length = path.size();

		// This loop will exclude file names that start with a period, but that
		// is the desired behavior.

		for (size_t i = length - 1; i != 0; i--)
		{
			const wchar_t c = path[i];

			if (IsDirectorySeparator(c) || c == volumeSeparatorWide)
			{
				fileName = path.substr(i + 1, length - i - 1);
				break;
			}
		}
	}

	return fileName;
}

bool PathUtil::IsDirectorySeparator(char value) noexcept
{
	return value == directorySeparator || value == altDirectorySeparator;
}

bool PathUtil::IsDirectorySeparator(wchar_t value) noexcept
{
	return value == directorySeparatorWide || value == altDirectorySeparatorWide;
}

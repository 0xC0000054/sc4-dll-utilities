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

#include "FileSystem.h"
#include "wil/resource.h"
#include "wil/win32_helpers.h"

std::filesystem::path FileSystem::GetDllModulePath()
{
	auto buffer = wil::GetModuleFileNameW(wil::GetModuleInstanceHandle());

	std::filesystem::path path(buffer.get());

	return path;
}

std::filesystem::path FileSystem::GetDllIniFilePath()
{
	std::filesystem::path path(GetDllModulePath());

	path.replace_extension(L".ini");

	return path;
}

std::filesystem::path FileSystem::GetDllLogFilePath()
{
	std::filesystem::path path(GetDllModulePath());

	path.replace_extension(L".log");

	return path;
}

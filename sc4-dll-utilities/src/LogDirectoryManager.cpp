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

#include "LogDirectoryManager.h"
#include "cISC4App.h"
#include "GZServPtrs.h"
#include "StringConversion.h"
#include <stdexcept>

LogDirectoryManager::LogDirectoryManager() : initialized(false)
{
}

void LogDirectoryManager::Init()
{
	if (!initialized)
	{
		cISC4AppPtr sc4App;

		cRZBaseString userDataDir;

		sc4App->GetUserDataDirectory(userDataDir);

		std::filesystem::path path = StringConversion::ToUtf16(userDataDir);

		path /= "Logs";

		std::filesystem::create_directory(path);

		logDirectoryRoot = std::move(path);
		initialized = true;
	}
}

std::filesystem::path LogDirectoryManager::GetLogFilePath(const std::string_view& fileName) const
{
	if (!initialized)
	{
		throw std::runtime_error("Failed to initialize the log directory.");
	}

	std::filesystem::path path = logDirectoryRoot;

	path /= fileName;

	return path;
}

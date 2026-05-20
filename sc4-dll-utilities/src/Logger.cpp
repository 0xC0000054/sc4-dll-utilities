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

#include "Logger.h"
#include "DebugUtil.h"
#include "wil/resource.h"
#include "wil/win32_helpers.h"

namespace
{
	std::filesystem::path GetLogFilePath()
	{
		// The global log file is located next to the DLL, using the same file name with
		// a .log file extension.
		//
		// This path format is used so that the global logger instance can be used before
		// the DLL is given access to the GZCOM framework.

		auto buffer = wil::GetModuleFileNameW(wil::GetModuleInstanceHandle());

		std::filesystem::path path(buffer.get());

		path.replace_extension(".log");

		return path;
	}
}

Logger& Logger::GetInstance()
{
	static Logger logger(GetLogFilePath());

	return logger;
}

bool Logger::IsEnabled(LogLevel level) const
{
	return logLevel >= level;
}

void Logger::SetLogLevel(LogLevel level)
{
	logLevel = level;
}

Logger::Logger(const std::filesystem::path& path)
	: file(path),
	  logLevel(LogLevel::Error)
{
}

void Logger::WriteLogFileHeader(const char* const text)
{
	file.WriteLine(text);
}

void Logger::WriteLine(LogLevel level, const char* const message)
{
	if (!IsEnabled(level))
	{
		return;
	}

	WriteLineCore(message);
}

void Logger::WriteLineFormatted(LogLevel level, const char* const format, ...)
{
	if (!IsEnabled(level))
	{
		return;
	}

	va_list args;
	va_start(args, format);

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

			WriteLineCore(buffer.get());
		}
		else
		{
			char buffer[stackBufferSize]{};

			std::vsnprintf(buffer, stackBufferSize, format, args);

			WriteLineCore(buffer);
		}
	}

	va_end(args);
}

void Logger::WriteLineCore(const char* const message)
{
	if (file)
	{
#ifndef NDEBUG
		DebugUtil::PrintLineToDebugOutput(message);
#endif // !NDEBUG

		file.WriteLine(message);
	}
}
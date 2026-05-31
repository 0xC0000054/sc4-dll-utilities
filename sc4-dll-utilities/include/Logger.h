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
#include "Utf8TextOFStream.h"

// The information levels the logger supports.
// The logger will write output for the specified level
// and all lower levels.
enum class LogLevel : int32_t
{
	Info = 0,
	Error = 1,
	Debug = 2,
	Trace = 3
};

// Implements a global singleton logger.
// The output file will be located next to the DLL, using
// the same file name with a .log file extension.
class Logger
{
public:
	static Logger& GetInstance();

	void Flush();

	bool IsEnabled(LogLevel level) const;

	void SetLogLevel(LogLevel level);

	void WriteLogFileHeader(const char* const message);

	void Write(LogLevel level, const char* const message);

	void WriteFormatted(LogLevel level, const char* const format, ...);

	void WriteLine(LogLevel level, const char* const message);

	void WriteLineFormatted(LogLevel level, const char* const format, ...);

private:
	Logger(const std::filesystem::path& logFilePath);

	void WriteCore(const char* const message);
	void WriteLineCore(const char* const message);

	typedef void (Logger::* WriteFormattedCallback)(const char*);

	void WriteFormattedCore(WriteFormattedCallback callback, const char* format, va_list args);

	LogLevel logLevel;
	Utf8TextOFStream file;
};


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
#include "cIGZFile.h"
#include "cRZAutoRefCount.h"
#include <iosfwd>
#include <limits>
#include <streambuf>
#include <vector>
#include <utility>

// An adapter to allow types that use std::istream to work with SC4's cIGZFile interface.
// For example, reading from a DBPF record loaded with ResourceUtil::GetRecordAsIGZFile.
// See IniReader::load(const cGZPersistResourceKey& key) for the usage pattern.
class GZFileStreamBufAdapter final : public std::streambuf
{
public:
	GZFileStreamBufAdapter() = default;
	GZFileStreamBufAdapter(cIGZFile*);
	GZFileStreamBufAdapter(const GZFileStreamBufAdapter&) = delete;
	GZFileStreamBufAdapter(GZFileStreamBufAdapter&&) noexcept;

	GZFileStreamBufAdapter& operator=(const GZFileStreamBufAdapter&) = delete;
	GZFileStreamBufAdapter& operator=(GZFileStreamBufAdapter&&) noexcept;

	void set_file(cIGZFile*);

private:
	std::streambuf::int_type underflow() override;

	cRZAutoRefCount<cIGZFile> file;
	std::vector<char> buffer;
};


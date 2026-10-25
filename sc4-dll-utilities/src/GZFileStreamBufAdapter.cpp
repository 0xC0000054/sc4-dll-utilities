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

#include "GZFileStreamBufAdapter.h"
#include "cIGZDBSerialRecordAsIGZFile.h"

constexpr size_t MaxBufferSize = 4096;
constexpr size_t PutBack = 1;

namespace
{
	size_t GetBufferLength(cIGZFile& file)
	{
		return PutBack + std::min(static_cast<size_t>(file.Length()), MaxBufferSize);
	}
}

GZFileStreamBufAdapter::GZFileStreamBufAdapter(cIGZFile* pFile)
{
	set_file(pFile);
}

GZFileStreamBufAdapter::GZFileStreamBufAdapter(GZFileStreamBufAdapter&& other) noexcept
	: file(std::move(other.file)),
	  buffer(std::move(other.buffer))
{
	char* end = buffer.data() + buffer.size();
	setg(end, end, end);
}

GZFileStreamBufAdapter& GZFileStreamBufAdapter::operator=(GZFileStreamBufAdapter&& other) noexcept
{
	file = std::move(other.file);
	buffer = std::move(other.buffer);

	char* end = buffer.data() + buffer.size();
	setg(end, end, end);

	return *this;
}

void GZFileStreamBufAdapter::set_file(cIGZFile* pFile)
{
	this->file.Reset();
	this->buffer.resize(PutBack);
	this->buffer.clear();

	if (pFile)
	{
		this->file = pFile;
		this->buffer.resize(GetBufferLength(*pFile));
	}

	char* end = buffer.data() + buffer.size();
	setg(end, end, end);
}

std::streambuf::int_type GZFileStreamBufAdapter::underflow()
{
	// This code is adapted from Example 1 at:
	// https://web.archive.org/web/20150711115652/http://www.mr-edd.co.uk/blog/beginners_guide_streambuf

	if (gptr() < egptr()) // buffer not exhausted
	{
		return traits_type::to_int_type(*gptr());
	}

	if (!file || !file->IsOpen())
	{
		return traits_type::eof();
	}

	char* base = buffer.data();
	char* start = base;

	if (eback() == base) // true when this isn't the first fill
	{
		// Make arrangements for putback characters
		std::memmove(base, egptr() - PutBack, PutBack);
		start += PutBack;
	}

	// Start is now the start of the buffer, proper.
	// Read from the file in to the provided buffer
	uint32_t byteCount = std::min(
		buffer.size() - (start - base),
		file->Length() - file->Position());

	if (!file->ReadWithCount(start, byteCount) || byteCount == 0)
	{
		return traits_type::eof();
	}

	// Set buffer pointers
	setg(base, start, start + byteCount);

	return traits_type::to_int_type(*gptr());
}

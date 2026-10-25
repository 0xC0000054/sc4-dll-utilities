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

#include "ResourceUtil.h"
#include "cGZPersistResourceKey.h"
#include "cIGZCOM.h"
#include "cIGZDBSerialRecordAsIGZFile.h"
#include "cIGZPersistDBRecord.h"
#include "cIGZPersistDBSerialRecord.h"
#include "cIGZPersistResourceManager.h"
#include "cIGZPersistDBSegment.h"
#include "cIGZPersistDBSegmentMultiPackedFiles.h"
#include "cRZCOMDllDirector.h"
#include "cRZAutoRefCount.h"
#include "GZServPtrs.h"

bool ResourceUtil::GetRecordAsIGZFile(const cGZPersistResourceKey& key, cRZAutoRefCount<cIGZFile>& file)
{
	bool result = false;

	cIGZCOM* const pCOM = RZGetCOMDllDirector()->GZCOM();
	cIGZPersistResourceManagerPtr resMan;

	if (pCOM && resMan)
	{
		cRZAutoRefCount<cIGZPersistDBRecord> record;

		if (resMan->OpenDBRecord(key, record.AsPPObj(), false))
		{
			cRZAutoRefCount<cIGZPersistDBSerialRecord> serialRecord;

			if (record->QueryInterface(GZIID_cIGZPersistDBSerialRecord, serialRecord.AsPPVoid()))
			{
				cRZAutoRefCount<cIGZDBSerialRecordAsIGZFile> serialRecordAsIGZFile;

				if (pCOM->GetClassObject(
					GZCLSID_cIGZDBSerialRecordAsIGZFile,
					GZIID_cIGZDBSerialRecordAsIGZFile,
					serialRecordAsIGZFile.AsPPVoid()))
				{
					if (serialRecordAsIGZFile->SetDBSerialRecord(serialRecord))
					{
						// Assigning to the output cRZAutoRefCount<cIGZFile> parameter
						// will AddRef the cIGZDBSerialRecordAsIGZFile instance.

						file = serialRecordAsIGZFile->AsIGZFile();
						result = true;
					}
				}
			}
		}
	}

	return result;
}

bool ResourceUtil::GetResourceFilePath(const cGZPersistResourceKey& key, cIGZString& path)
{
	bool result = false;

	cIGZPersistResourceManagerPtr resMan;

	if (resMan)
	{
		cRZAutoRefCount<cIGZPersistDBSegment> segment;

		if (resMan->FindDBSegment(key, segment.AsPPObj()))
		{
			cRZAutoRefCount<cIGZPersistDBSegmentMultiPackedFiles> multiPackedFile;

			if (segment->QueryInterface(GZIID_cIGZPersistDBSegmentMultiPackedFiles, multiPackedFile.AsPPVoid()))
			{
				// cIGZPersistDBSegmentMultiPackedFiles is a collection of DAT files in a specific folder
				// and its sub-folders.
				// Call its FindDBSegment method to get the actual file.

				cRZAutoRefCount<cIGZPersistDBSegment> multiPackedSegment;

				if (multiPackedFile->FindDBSegment(key, multiPackedSegment.AsPPObj()))
				{
					multiPackedSegment->GetPath(path);
					result = true;
				}
			}
			else
			{
				segment->GetPath(path);
				result = true;
			}
		}
	}

	return result;
}

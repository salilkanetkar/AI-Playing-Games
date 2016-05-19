/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
// Original file Copyright Crytek GMBH or its affiliates, used under license.

#ifndef __DATAPATCHDOWNLOADER_H__
#define __DATAPATCHDOWNLOADER_H__

#if defined(WIN32) && !defined(_RELEASE)
#define DATA_PATCH_DEBUG	1
#else
#define DATA_PATCH_DEBUG	0
#endif

#include "DownloadMgr.h"

struct IDataPatcherListener
{
	virtual void DataPatchAvailable()=0;
	virtual void DataPatchNotAvailable()=0;
	virtual ~IDataPatcherListener() {}
};

class CDataPatchDownloader : public IDataListener
{
	protected:
		IDataPatcherListener				*m_pListener;
		uint32											m_patchCRC;
		int													m_patchId;								// 0 for no id supplied or no patch present
		XmlNodeRef									m_patchXML;
		const char									*m_pFileBeingPatched;
		bool												m_patchingEnabled;
		bool												m_bNeedWeaponSystemReload;

		void												PatchFail(
																	const char									*pInReason);
		void												AssertPatchDownloaded();

		virtual void								DataDownloaded(
																	CDownloadableResourcePtr		inResource);
		virtual void								DataFailedToDownload(
																	CDownloadableResourcePtr		inResource);

	public:
																CDataPatchDownloader();
		virtual											~CDataPatchDownloader();

		CDownloadableResourcePtr		GetDownloadableResource();

		void												SetPatchingEnabled(
																	bool												inEnable);
		bool												IsPatchingEnabled() const												{ return m_patchingEnabled; }

		void												AddListener(
																	IDataPatcherListener				*pInListener);
		void												RemoveListener(
																	IDataPatcherListener				*pInListener);

		int													GetPatchId()																		{ return m_patchId; } 
		uint32											GetDataPatchHash()															{ return m_patchCRC; }

		bool												NeedsWeaponSystemReload() { return m_bNeedWeaponSystemReload; }
		void												DoneWeaponSystemReload() { m_bNeedWeaponSystemReload=false; }

		void												ApplyCVarPatch();

		void												CancelDownload();

#if DATA_PATCH_DEBUG
		void												LoadPatchFromFile(
			const char *szFilename);
#endif //DATA_PATCH_DEBUG
};

#endif // __DATAPATCHDOWNLOADER_H__


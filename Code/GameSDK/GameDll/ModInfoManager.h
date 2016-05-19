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

#ifndef __MODINFOMANAGER_H__
#define __MODINFOMANAGER_H__

#include "ModInfo.h"

// a small utility to list available Mods and SP levels.
class CModInfoManager
{
public:
	CModInfoManager();

	void Refresh(); 
	void Free();

	size_t GetModCount() const;
	const ModInfo* GetModByIndex(size_t index) const;
	const ModInfo * FindModByDisplayName(const char *pName) const;

	// lists levels for active Mod
	size_t GetLevelCount() const;
	const ModInfo* GetLevelByIndex(size_t index) const;

	// returns NULL when no Mod is active
	const ModInfo* GetActiveMod() const; 
	const char* GetActiveModName() const;
	const char* GetActiveModDisplayName() const;
	ILINE bool IsRunningMod() const { return m_bRunningMod; }
	ILINE uint32 GetModCheckSum() const { return m_modCheckSum; }

	bool LoadMod(const char* modName);
	bool UnloadMod();

	static uint32 GetDirectoryHash( const char *pPath );

private:
	typedef std::vector<ModInfo> Mods;
	Mods m_mods;
	Mods m_modLevels;
	uint32 m_modCheckSum;
	bool m_bRunningMod;
};

#endif

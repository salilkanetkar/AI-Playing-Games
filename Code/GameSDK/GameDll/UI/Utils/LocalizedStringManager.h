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

// Description : Header for CLocalizedStringManager class
//               Shared by G02 and G04

#ifndef __LocalizedStringManager_h__
#define __LocalizedStringManager_h__

//-----------------------------------------------------------------------------------------------------

#include <map>

//-----------------------------------------------------------------------------------------------------

class CLocalizedStringManager
{

public:

	static int s_maxAge;

	CLocalizedStringManager();

	// Adds a generated localized string and it's generation parameters to the cache managed by this class.
	// Only pointers are copied, not whole string content.
	// Returns a pointer to the internally allocated string.
	const wchar_t* add(const wchar_t* finalStr, const char* label, bool bAdjustActions, bool bPreferXI, const char* param1, const char* param2, const char* param3, const char* param4);
	
	// Finds and returns an already generated localized string given it's generation parameters.
	// Returns NULL if no match was found.
	// Uses strcmp for internal comparison (which does initial pointer comparison, afaik).
	const wchar_t* find(const char* label, bool bAdjustActions, bool bPreferXI, const char* param1, const char* param2, const char* param3, const char* param4);

	// Increases the age of cached strings and remove/delete strings older than s_maxAge.
	// Should be called once per frame.
	// NOTE: Current implementation does NOT remove old/unreferenced strings (due to problem with wstring refcount).
	// Cache is invalidated when language changes.
	void tick();

	// Explicitly reset the cache. Should be called on change of map, gamerules, serialization, etc.
	void clear();

private:

	struct SLocalizedString
	{
		int m_refTick;
		bool m_bAdjustActions;
		bool m_bPreferXI;
		wstring m_finalStr;
		const char* m_label;
		const char* m_param1;
		const char* m_param2;
		const char* m_param3;
		const char* m_param4;
	};

	typedef unsigned int Key;
	typedef std::map<Key, SLocalizedString> Map;
	typedef std::pair<Key, SLocalizedString> Pair;

	Map m_cache;

	int m_curTick;

	const char* m_language;

	Key generateKey(const char* label, bool bAdjustActions, bool bPreferXI,
									const char* param1, const char* param2, 
									const char* param3, const char* param4);

};

//-----------------------------------------------------------------------------------------------------

#endif // __LocalizedStringManager_h__

//-----------------------------------------------------------------------------------------------------

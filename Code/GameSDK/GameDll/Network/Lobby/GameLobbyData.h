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

#ifndef __GAMELOBBYDATA_H__
#define __GAMELOBBYDATA_H__

#include "AutoEnum.h"
#include "SessionNames.h"

//------------
// LOBBY DATA
//------------


// Ids
enum ELOBBYIDS
{
	LID_MATCHDATA_GAMEMODE = 0,
	LID_MATCHDATA_MAP,
	LID_MATCHDATA_ACTIVE,
	LID_MATCHDATA_VERSION,
	LID_MATCHDATA_REQUIRED_DLCS,
	LID_MATCHDATA_PLAYLIST,
	LID_MATCHDATA_VARIANT,
	LID_MATCHDATA_SKILL,
	LID_MATCHDATA_LANGUAGE,
};

#define REQUIRED_SESSIONS_QUERY	0
#define FIND_GAME_SESSION_QUERY 0
#define REQUIRED_SESSIONS_SEARCH_PARAM	0

// Rich presence string
#define RICHPRESENCE_ID					0

// Types of rich presence we can have
#define RICHPRESENCE_GAMEPLAY		0        
#define RICHPRESENCE_LOBBY			1
#define RICHPRESENCE_FRONTEND		2
#define RICHPRESENCE_SINGLEPLAYER	3
#define RICHPRESENCE_IDLE			4

// Rich presence string params
#define RICHPRESENCE_GAMEMODES	0
#define RICHPRESENCE_MAPS				1


#define INVALID_SESSION_FAVOURITE_ID 0	// For eLDI_FavouriteID/LID_MATCHDATA_FAVOURITE_ID

#define GAMELOBBY_USE_COUNTRY_FILTERING 0

enum ELobbyDataIndex
{
	eLDI_Gamemode = 0,
	eLDI_Version = 1,
	eLDI_Playlist = 2,
	eLDI_Variant = 3,
	eLDI_RequiredDLCs = 4,
#if GAMELOBBY_USE_COUNTRY_FILTERING
	eLDI_Country = 5,
#endif
	eLDI_Language,
	eLDI_Map,
	eLDI_Skill,
	eLDI_Active,

	eLDI_Num
};

namespace GameLobbyData
{
	extern char const * const g_sUnknown;

	const uint32 ConvertGameRulesToHash(const char* gameRules);
	const char* GetGameRulesFromHash(uint32 hash, const char* unknownStr=g_sUnknown);

	const uint32 ConvertMapToHash(const char* mapName);
	const char* GetMapFromHash(uint32 hash, const char *pUnknownStr = g_sUnknown);

	const uint32 GetVersion();
	const bool IsCompatibleVersion(uint32 version);

	const uint32 GetPlaylistId();
	const uint32 GetVariantId();
	const uint32 GetGameDataPatchCRC();

	const int32 GetSearchResultsData(SCrySessionSearchResult* session, CryLobbyUserDataID id);
	const bool IsValidServer(SCrySessionSearchResult* session);
};

#endif // __GAMELOBBYDATA_H__

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

#ifndef ___GAME_BROWSER_H___
#define ___GAME_BROWSER_H___

#include "CheatProtection.h"
#include "ICryLobby.h"
#include "ICryMatchMaking.h"
#include "GameMechanismManager/GameMechanismBase.h"

#if IMPLEMENT_PC_BLADES
#include "Network/Lobby/GameServerLists.h"
#endif

#if defined( DEDICATED_SERVER )
#define DEDI_VERSION	( 1 )
#endif

#define MAX_PRESENCE_STRING_SIZE 63
#define MATCHMAKING_SESSION_PASSWORD_MAX_LENGTH (32)

#if ! defined(RELEASE)
#define USE_SESSION_SEARCH_SIMULATOR
#endif

//////////////////////////////////////////////////////////////////////////
//Pre-declarations
class CSessionSearchSimulator;


class CGameBrowser
{
public :
	CGameBrowser();
	~CGameBrowser();
	void Init( void );
	void StartSearchingForServers(CryMatchmakingSessionSearchCallback cb = CGameBrowser::MatchmakingSessionSearchCallback);
	ECryLobbyError StartSearchingForServers(SCrySessionSearchParam* param, CryMatchmakingSessionSearchCallback cb, void* cbArg, const bool bFavouriteIdSearch);
	void CancelSearching(bool feedback = true);
	void FinishedSearch(bool feedback, bool finishedSearch);

	void Update(const float dt);

	const ENatType GetNatType() const;
	const char * GetNatTypeString() const;

	// Callback (public as also used by CGame in SP)
	static void ConfigurationCallback(ECryLobbyService service, SConfigurationParams *requestedParams, uint32 paramCount);
	CHEAT_PROTECTION_EXPORT static void InitialiseCallback(ECryLobbyService service, ECryLobbyError error, void* arg);

	static void InitLobbyServiceType();

#if IMPLEMENT_PC_BLADES
	void StartFavouriteIdSearch( const CGameServerLists::EGameServerLists serverList, uint32 *pFavouriteIds, uint32 numFavouriteIds );
#endif

protected:
	enum EDelayedSearchType
	{
		eDST_None = 0,
		eDST_Full,
		eDST_FavouriteId
	};

	bool DoFavouriteIdSearch();
	bool CanStartSearch();

#if defined(USE_SESSION_SEARCH_SIMULATOR)
	CSessionSearchSimulator* m_pSessionSearchSimulator;
#endif //defined(USE_SESSION_SEARCH_SIMULATOR)

	ENatType m_NatType;
	CryLobbyTaskID m_searchingTask;
	EDelayedSearchType m_delayedSearchType;
	
#if IMPLEMENT_PC_BLADES
	uint32 m_searchFavouriteIds[CGameServerLists::k_maxServersStoredInList];
	uint32 m_currentSearchFavouriteIdIndex;
	uint32 m_numSearchFavouriteIds;

	CGameServerLists::EGameServerLists m_currentFavouriteIdSearchType;
#endif

	float m_lastSearchTime;

	bool m_bFavouriteIdSearch;

	void SetNatType(ENatType natType) { m_NatType = natType; }

	// Callbacks
	static void GetNatTypeCallback(UCryLobbyEventData eventData, void *userParam);
	static void MatchmakingSessionSearchCallback(CryLobbyTaskID taskID, ECryLobbyError error, SCrySessionSearchResult* session, void* arg);

private:

};

#endif // ___GAME_LOBBY_H___

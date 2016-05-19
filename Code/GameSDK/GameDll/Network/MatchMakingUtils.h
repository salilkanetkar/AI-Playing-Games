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

// Description : Encapsulates Matchmaking functionality for main menu.


#pragma once

#ifndef __MATCHMAKINGTILS_H__
#define __MATCHMAKINGTILS_H__

#define ENABLE_MATCH_DEBUG_CODE 0

typedef int HRESULT;



namespace Live
{
	namespace State
	{
		class User;
		class Party;
	}
}

namespace Concurrency
{
	template< typename T >
	class task;
}

namespace MatchmakingUtils
{
	

	void OnPostUpdate( float deltaTime );

	// Networking helper functions

	enum EPartyValidationResult
	{
		ePVR_NoError,
		ePVR_PartyTooLarge,
		ePVR_TooManyLocalUsers,
	};

	EPartyValidationResult IsPartyValid();
	void ShowAchievementsUI();
	void ShowPartyUI( );

	HRESULT InitiateSession( const string& gameModeId, const string& playlistId, int mpRank );

	void AssignLocalUserToGroup( const int groupNumber );

	HRESULT PartySessionReady( );
	void QuitMatchmaking(bool nonBlocking = true);
	void OnMatchFoundPopupDeclined();
	void ShouldShowMatchFoundPopup();
	void AwardComicGold();
	void EverythingIsLoadedNow();
	int GetAverageMatchTime();
	wstring GetGamertag( const unsigned long long xuid );
	unsigned long long GetLocalXuid( );
	bool IsInvitePending();
	bool IsMemberReady( unsigned long long xuid );
	void ShowGamercard( unsigned long long xuid );
	string GetPlaylistId();
	wstring GetHopperName();
	bool IsHostForFoundMatch();
	void SetLaunching();
	HRESULT SetReadyState( const bool isReady );
}

#endif

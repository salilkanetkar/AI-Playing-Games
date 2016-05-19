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

#include "StdAfx.h"

#include "GameCVars.h"

#include "MatchMakingUtils.h"
#include "Lobby/GameLobbyData.h"
#include "UnicodeFunctions.h"
#include <StringUtils.h>

#define ROUND_TO_ROUND_HOPPER_NAME "RoundToRound"
#define ROUND_TO_ROUND_PLAYLIST_ID L"00000000-0000-0000-0000-00000000001F"

#pragma warning ( disable:4717 ) // stupid warning in vccorlib.h


namespace MatchmakingUtils
{

	void OnPostUpdate( float )
	{
	}

	void ShowAchievementsUI()
	{
	}

#define MAX_PARTY 3
	EPartyValidationResult IsPartyValid()
	{
		EPartyValidationResult errorCode = ePVR_NoError;
		return errorCode;
	}

	void ShowPartyUI()
	{
	}
	


	void QuitMatchmaking(bool nonBlocking /*= true*/)
	{
	}

	void OnMatchFoundPopupDeclined()
	{
	}

	void ShouldShowMatchFoundPopup()
	{
	}

	void EverythingIsLoadedNow()
	{
	}

	int GetAverageMatchTime()
	{
		int wait = -1;
		return wait;
	}

	void AssignLocalUserToGroup( const int groupNumber )
	{
	}

	wstring GetGamertag( const unsigned long long xuid )
	{
		// Standard default gamertag.  If nothing else, at least it lets you make sure that real ones will fit.
		wstring gt = L"WWWWWWWWWWWWW";


		return gt;
	}

	unsigned long long GetLocalXuid( )
	{
		return 0;
	}

	bool IsInvitePending()
	{
		bool invitePending = false;


		return invitePending;
	}

	bool IsMemberReady( unsigned long long xuid )
	{
		return false;
	}

	void ShowGamercard( unsigned long long xuid )
	{
	}

	string GetPlaylistId()
	{
		return "";
	}

	wstring GetHopperName()
	{
		return L"";
	}

	bool IsHostForFoundMatch()
	{
		return false;
	}

	void SetLaunching()
	{
	}

}

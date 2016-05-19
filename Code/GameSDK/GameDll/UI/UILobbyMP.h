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

#ifndef __UILOBBYMP_H_
#define __UILOBBYMP_H_

#include "IUIGameEventSystem.h"
#include <IFlashUI.h>
#include "ICryStats.h"
#include "ICryLobby.h"
#include "Network/Lobby/GameLobbyData.h"
#include "ICryFriends.h"

class CUILobbyMP 
	: public IUIGameEventSystem
	, public IUIModule
{
public:
	CUILobbyMP();

	// IUIGameEventSystem
	UIEVENTSYSTEM( "UILobbyMP" );
	virtual void InitEventSystem();
	virtual void UnloadEventSystem();

	// IUIModule
	virtual void Reset();
	// ~IUIModule

	// UI functions
	void InviteAccepted();
	void SearchCompleted();
	void SearchStarted();
	void UpdateNatType();
	void ServerFound(SCrySessionSearchResult session, string sServerName);
	void PlayerListReturn(const SUIArguments& players, const SUIArguments& playerids);
	void ReadLeaderBoard(int leaderboardIdx, int mode, int nrOfEntries);
	void WriteLeaderBoard(int leaderboardIdx, const char* values);
	void RegisterLeaderBoard(string leaderboardName, int leaderBoardIdx, int nrOfColumns);
	void ShowLoadingDialog(const  char* sLoadingDialog);
	void HideLoadingDialog(const  char* sLoadingDialog);
	void LeaderboardEntryReturn(const SUIArguments& customColumns);
	void InviteFriends(int containerIdx, int friendIdx);
	void SendUserStat(SUIArguments& arg);

	//Callback when session is found
	static void MatchmakingSessionSearchCallback(CryLobbyTaskID taskID, ECryLobbyError error, SCrySessionSearchResult* session, void* arg);
	static void ReadLeaderBoardCB(CryLobbyTaskID TaskID, ECryLobbyError Error, SCryStatsLeaderBoardReadResult *Result, void *Arg);
	static void RegisterLeaderboardCB(CryLobbyTaskID TaskID, ECryLobbyError Error, void *Arg);
	static void WriteLeaderboardCallback(CryLobbyTaskID TaskID, ECryLobbyError Error, void *Arg);

	static void ReadUserDataCallback(CryLobbyTaskID taskID, ECryLobbyError error, SCryLobbyUserData* pData, uint32 numData, void* pArg);

	static void GetFriendsCB(CryLobbyTaskID taskID, ECryLobbyError error, SFriendInfo* pFriendInfo, uint32 numFriends, void* pArg);
	static void InviteFriendsCB(CryLobbyTaskID taskID, ECryLobbyError error, void* pArg);

private:
	// UI events
	void GetUserStats();
	void SearchGames(bool bLan);
	void AwardTrophy(int trophy);
	void JoinGame(unsigned int sessionID);
	void HostGame(bool bLan, string sMapPath, string sGameRules);
	void SetMultiplayer(bool bIsMultiplayer);
	void LockController( bool bLock );
	void LeaveGame();
	void GetPlayerList();
	void MutePlayer(int playerId, bool mute);
	void GetFriends(int containerIdx);

private:
	enum EUIEvent
	{
		eUIE_ServerFound = 0,
		eUIE_PlayerListReturn,
		eUIE_PlayerIdListReturn,
		eUIE_InviteAccepted,
		eUIE_SearchStarted,
		eUIE_SearchCompleted,
		eUIE_NatTypeUpdated,
		eUIE_ShowLoadingDialog,
		eUIE_HideLoadingDialog,
		eUIE_LeaderboardEntryReturn,
		eUIE_GetFriendsCompleted,
		eUIE_UserStatRead,
	};

	SUIEventReceiverDispatcher<CUILobbyMP> m_eventDispatcher;
	SUIEventSenderDispatcher<EUIEvent> m_eventSender;
	IUIEventSystem* m_pUIEvents;
	IUIEventSystem* m_pUIFunctions;
	std::vector<SCrySessionSearchResult> m_FoundServers;
};


#endif // __UILOBBYMP_H_

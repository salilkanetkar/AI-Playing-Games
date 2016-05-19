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

#ifndef __UIMultiPlayer_H__
#define __UIMultiPlayer_H__

#include "IUIGameEventSystem.h"
#include <IFlashUI.h>
#include "GameRulesModules/IGameRulesKillListener.h"

class CUIMultiPlayer 
	: public IUIGameEventSystem
	, public IUIModule
	, public IGameRulesKillListener
{
public:
	CUIMultiPlayer();

	// IUIGameEventSystem
	UIEVENTSYSTEM( "UIMultiPlayer" );
	virtual void InitEventSystem();
	virtual void UnloadEventSystem();
	virtual void LoadProfile( IPlayerProfile* pProfile );
	virtual void SaveProfile( IPlayerProfile* pProfile ) const;

	// IUIModule
	virtual void Reset();
	// ~IUIModule

	// IGameRulesKillListener
	virtual void OnEntityKilledEarly(const HitInfo &hitInfo) {};
	virtual void OnEntityKilled(const HitInfo &hitInfo);
	// ~IGameRulesKillListener

	// UI functions
	void EnteredGame();
	void PlayerJoined(EntityId playerid, const string& name);
	void UpdateScoreBoardItem(EntityId playerid, const string& name, int kills, int deaths, const string& team);
	void PlayerLeft(EntityId playerid, const string& name);
	void PlayerKilled(EntityId playerid, EntityId shooterid);
	void PlayerRenamed(EntityId playerid, const string& newName);
	void OnChatReceived(EntityId senderId, int teamFaction, const char* message);

private:
	// UI events
	void RequestPlayers();
	void GetPlayerName();
	void RequestUpdatedScores();
	void SetPlayerName( const string& newname );
	void ConnectToServer( const string& server );
	void GetServerName();
	void OnSendChatMessage( const string& message );


	void SubmitNewName();
	string GetPlayerNameById( EntityId playerid );
	string GetPlayerTeamById( EntityId playerid );

private:
	enum EUIEvent
	{
		eUIE_EnteredGame,
		eUIE_PlayerJoined,
		eUIE_ScoreBoardItemWasUpdated,
		eUIE_PlayerLeft,
		eUIE_PlayerKilled,
		eUIE_PlayerRenamed,
		eUIE_SendName,
		eUIE_SendServer,
		eUIE_ChatMsgReceived,
	};

	SUIEventReceiverDispatcher<CUIMultiPlayer> m_eventDispatcher;
	SUIEventSenderDispatcher<EUIEvent> m_eventSender;
	IUIEventSystem* m_pUIEvents;
	IUIEventSystem* m_pUIFunctions;

	struct SPlayerInfo
	{
		SPlayerInfo() : name("<UNDEFINED>") {}

		string name;
	};
	typedef std::map<EntityId, SPlayerInfo> TPlayers;
	TPlayers m_Players;

	string m_LocalPlayerName;
	string m_ServerName;
};


#endif // __UIMultiPlayer_H__

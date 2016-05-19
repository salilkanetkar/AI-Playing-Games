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

// Description : Standard game rules module to handle victory conditions for all vs
//               all games


#ifndef _GAME_RULES_STANDARD_VICTORY_CONDITIONS_PLAYER_H_
#define _GAME_RULES_STANDARD_VICTORY_CONDITIONS_PLAYER_H_

#if _MSC_VER > 1000
# pragma once
#endif

#include "GameRulesStandardVictoryConditionsTeam.h"

class CGameRules;

class CGameRulesStandardVictoryConditionsPlayer : public CGameRulesStandardVictoryConditionsTeam
{
public:
	typedef CGameRulesStandardVictoryConditionsTeam  inherited;

public:
	CGameRulesStandardVictoryConditionsPlayer();
	~CGameRulesStandardVictoryConditionsPlayer();

	virtual void  Init(XmlNodeRef xml);
	virtual void	Update(float frameTime);

	// IGameRulesVictoryConditionsModule
	virtual void ClVictoryTeam(int teamId, EGameOverReason reason, ESVC_DrawResolution drawWinningResolution, const SDrawResolutionData& level1, const SDrawResolutionData& level2, const EntityId killedEntity, const EntityId shooterEntity) {};
	virtual void ClVictoryPlayer(int playerId, EGameOverReason reason, const EntityId killedEntity, const EntityId shooterEntity);
	virtual void TeamCompletedAnObjective(int teamId) {};
	virtual bool ScoreLimitReached();
	virtual void SvOnEndGame();
	virtual void SendVictoryMessage(ChannelId channelId);
	virtual void OnNewPlayerJoined(ChannelId channelId);
	// ~IGameRulesVictoryConditionsModule

protected:
	struct SPlayerScoreResult
	{
		SPlayerScoreResult() : m_maxScore(0), m_maxScorePlayerId(0) { };

		int m_maxScore;
		EntityId m_maxScorePlayerId;
	};

	typedef CryFixedStringT<32> TFixedString;

	void	GetMaxPlayerScore(SPlayerScoreResult &result);

	// CGameRulesStandardVictoryConditionsTeam
	virtual bool SvGameStillHasOpponentPlayers();
	virtual void SvOpponentsCheckFailed();
	virtual void CheckScoreLimit();
	virtual void CheckTimeLimit();
	virtual void TimeLimitExpired();
	// ~CGameRulesStandardVictoryConditionsTeam

	void	OnEndGamePlayer(EntityId playerId, EGameOverReason reason, EntityId killedEntity=0, EntityId shooterEntity=0, bool roundsGameActuallyEnded=false);

	void	CallLuaFunc(TFixedString* funcName);

	TFixedString  m_luaFuncStartSuddenDeathSv;
	TFixedString  m_luaFuncEndSuddenDeathSv;

	TFixedString  m_tmpSuddenDeathMsg;

	bool	m_bKillsAsScore;	// Use kills instead of score when checking victory conditions.

	CGameRules::VictoryPlayerParams m_playerVictoryParams;
};

#endif // _GAME_RULES_STANDARD_VICTORY_CONDITIONS_PLAYER_H_

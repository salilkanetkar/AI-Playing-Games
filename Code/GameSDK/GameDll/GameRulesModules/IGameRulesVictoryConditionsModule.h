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

// Description : Interface for the game rule module to handle victory conditions


#ifndef _IGAME_RULES_VICTORY_CONDITIONS_MODULE_H_
#define _IGAME_RULES_VICTORY_CONDITIONS_MODULE_H_

#if _MSC_VER > 1000
# pragma once
#endif

#include <IGameRulesSystem.h>
#include "GameRulesTypes.h"

class IGameRulesVictoryConditionsModule
{
public:
	virtual ~IGameRulesVictoryConditionsModule() {}

	virtual void	Init(XmlNodeRef xml) = 0;
	virtual void	Update(float frameTime) = 0;

	virtual void OnStartGame() = 0;
	virtual void OnRestart() = 0;
	virtual void SvOnEndGame() = 0;
	virtual void SvForceEndGame(int winnerTeam, EGameOverReason eGameOverReason) = 0;

	// TODO: Need a way to let the victory have different parameters.
	virtual void	ClVictoryTeam(int teamId, EGameOverReason reason, ESVC_DrawResolution drawWinningResolution, const SDrawResolutionData& level1, const SDrawResolutionData& level2, const EntityId killedEntity, const EntityId shooterEntity) = 0;
	virtual void	ClVictoryPlayer(int playerId, EGameOverReason reason, const EntityId killedEntity, const EntityId shooterEntity) = 0;

	// needed for extraction to tell its victory module whenever a tick is extracted
	virtual void  TeamCompletedAnObjective(int teamId) = 0;

	//For sound system when time limit has been updated mid game
	virtual void ClUpdatedTimeLimit() = 0;

	// Check if the score limit has been reached
	virtual bool  ScoreLimitReached() = 0;

	virtual void  OnHostMigrationPromoteToServer() = 0;

	virtual const SDrawResolutionData* GetDrawResolutionData(ESVC_DrawResolution resolution) = 0;

  virtual void  SetWinningKillVictimShooter(EntityId victim, EntityId shooter) = 0;

	virtual void AddIntsToDrawResolutionData(ESVC_DrawResolution inResolutionLevel, const int inTeam1Data, const int inTeam2Data) = 0;
	virtual void SetFloatsInDrawResolutionData(ESVC_DrawResolution inResolutionLevel, const float inTeam1Data, const float inTeam2Data) = 0;

	virtual void SetCanPlayMusicMoods(bool bEnable) = 0;

	virtual void SendVictoryMessage(ChannelId channelId) = 0;
	virtual void OnNewPlayerJoined(ChannelId channelId) = 0;
};

#endif // _IGAME_RULES_VICTORY_CONDITIONS_MODULE_H_

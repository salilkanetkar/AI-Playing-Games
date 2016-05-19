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

#ifndef _GameRulesRoundsModule_h_
#define _GameRulesRoundsModule_h_

#if _MSC_VER > 1000
# pragma once
#endif

#include "SerializeFwd.h"
#include "IGameObject.h"
#include "GameRulesTypes.h"

#ifndef _RELEASE
#define LOG_PRIMARY_ROUND  g_pGameCVars->g_logPrimaryRound!=1 ? (void)(NULL) : CryLog
#else
#define LOG_PRIMARY_ROUND  (0)&sizeof
#endif

class IGameRulesRoundsModule
{
public:
	enum ERoundEndHUDState
	{
		eREHS_Unknown,
		eREHS_HUDMessage,
		eREHS_Top3,
		eREHS_WinningKill,
	};

	virtual ~IGameRulesRoundsModule() {}

	virtual void Init(XmlNodeRef xml) = 0;
	virtual void PostInit() = 0;
	virtual void Update(float frameTime) = 0;

	virtual void OnStartGame() = 0;
	virtual void OnEnterSuddenDeath() = 0;

	virtual bool NetSerialize( TSerialize ser, EEntityAspects aspect, uint8 profile, int flags ) = 0;

	virtual void OnLocalPlayerSpawned() = 0;
	virtual void OnEndGame(int teamId, EntityId playerId, EGameOverReason reason) = 0;
	virtual int GetRoundNumber() = 0;
	virtual int GetRoundsRemaining() const = 0;
	virtual void SetTreatCurrentRoundAsFinalRound(const bool treatAsFinal) = 0;

	virtual int GetPrimaryTeam() const = 0;

	virtual bool CanEnterSuddenDeath() const = 0;
	virtual bool IsInProgress() const	= 0;
	virtual bool IsInSuddenDeath() const = 0;
	virtual bool IsRestarting() const = 0;
	virtual bool IsGameOver() const = 0;
	virtual bool IsRestartingRound(int round) const = 0;
	virtual float GetTimeTillRoundStart() const = 0;

	virtual int GetPreviousRoundWinnerTeamId() const = 0;
	virtual const int* GetPreviousRoundTeamScores(void) const = 0;
	virtual EGameOverReason GetPreviousRoundWinReason() const = 0;

	virtual ERoundEndHUDState GetRoundEndHUDState() const = 0;

	virtual void OnPromoteToServer() = 0;

#if USE_PC_PREMATCH
	virtual void OnPrematchStateEnded(bool isSkipped) = 0; 
#endif // #if USE_PC_PREMATCH

	virtual bool ShowKillcamAtEndOfRound() const = 0;

	virtual void AdjustTimers(CTimeValue adjustment) = 0;
};

#endif // _GameRulesRoundsModule_h_

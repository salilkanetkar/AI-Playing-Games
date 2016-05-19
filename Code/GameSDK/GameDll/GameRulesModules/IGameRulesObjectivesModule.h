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

// Description : Interface for the game rule module to handle objectives


#ifndef _IGAME_RULES_OBJECTIVES_MODULE_H_
#define _IGAME_RULES_OBJECTIVES_MODULE_H_

#if _MSC_VER > 1000
# pragma once
#endif

#include <IGameRulesSystem.h>
#include "GameRulesTypes.h"
#include "SerializeFwd.h"
#include "ItemDefinitions.h"

struct SInteractionInfo;

class IGameRulesObjectivesModule
{
public:
	virtual ~IGameRulesObjectivesModule() {}

	virtual void Init(XmlNodeRef xml) = 0;
	virtual void Update(float frameTime) = 0;

	virtual void OnStartGame() = 0;
	virtual void OnStartGamePost() = 0;
	virtual void OnGameReset() = 0;

	virtual void PostInitClient (ChannelId channelId) = 0;
	virtual bool NetSerialize( TSerialize ser, EEntityAspects aspect, uint8 profile, int flags ) = 0;

	virtual bool HasCompleted(int teamId) = 0;

	virtual void OnHostMigration(bool becomeServer) = 0;		// Host migration

	virtual bool AreSuddenDeathConditionsValid() const = 0;
	virtual void CheckForInteractionWithEntity(EntityId interactId, EntityId playerId, SInteractionInfo& interactionInfo) = 0;
	virtual bool CheckIsPlayerEntityUsingObjective(EntityId playerId) = 0;

	virtual ESpawnEntityState GetObjectiveEntityState(EntityId entityId) = 0;

	virtual int GetAutoAssignTeamId(ChannelId channelId) = 0;	// Only called if neither lobby or teams module assign a team

	virtual void OnEntitySignal(EntityId entityId, int signal) = 0; 

	virtual bool CanPlayerRevive(EntityId playerId) const { return true; }
	virtual float GetPlayerAutoReviveAdditionalTime(IActor* pActor) const { return 0.f; }
	virtual bool RequestReviveOnLoadoutChange() { return true; }
	virtual bool CanPlayerRegenerate(EntityId playerId) const {return true;}
	virtual bool MustShowHealthEffect(EntityId playerId) const {return true;}
	virtual bool IndividualScore() const {return false;}
	virtual bool ShowRoundsAsDraw() const {return false;}
	virtual bool IsWinningKill(const HitInfo &hitInfo) const { return false; }

	virtual void UpdateInitialAmmoCounts(const IEntityClass *pWeaponClass, TAmmoVector &ammo, TAmmoVector &bonusAmmo) {}
	virtual void OnNewGroupIdSelected(uint32 id) {}
	virtual void OnPrematchStateEnded() {}

	// Optional Intro sequence
	virtual bool CanPlayIntroSequence() const {return false;}
	virtual bool SquadChallengesEnabled() const {return true;}
};

#endif // _IGAME_RULES_OBJECTIVES_MODULE_H_

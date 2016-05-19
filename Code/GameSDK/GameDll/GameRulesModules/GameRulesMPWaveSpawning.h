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

#ifndef __GAMERULES_MP_WAVE_SPAWNING_H__
#define __GAMERULES_MP_WAVE_SPAWNING_H__

#include "GameRulesMPSimpleSpawning.h"

class CGameRulesMPWaveSpawning : public CGameRulesRSSpawning
{

public:
	typedef CGameRulesRSSpawning TInherited;

	CGameRulesMPWaveSpawning();
	virtual ~CGameRulesMPWaveSpawning();

	// IGameRulesMPSpawningModule
	virtual void Init(XmlNodeRef xml);
	virtual void Update(float frameTime);
	virtual float GetTimeFromDeathTillAutoReviveForTeam(int teamId) const;
	// ~IGameRulesMPSpawningModule

	// IGameRulesRevivedListener
	virtual void EntityRevived(EntityId entityId);
	// ~IGameRulesRevivedListener

	float GetTeamReviveTimeOverride(int teamId) const; 

private:
	typedef uint8 TRuleFlags;

	// helpers
	bool WaveSpawningEnabled() const; 
	bool WaveSpawningEnabled(int teamId) const; 
	void ResetWaveRespawnTimer(); 

	// data
	float m_fWaveSpawnInterval;
	float m_fWaveSpawnTimer;
	
	// Team 1 / 2 or both teams may opt in for wave spawning
	// LogicState //
	enum ERuleFlag
	{
		ERuleFlag_None									= 0,
		ERuleFlag_team1WaveRespawningEnabled			= 1 << 0,
		ERuleFlag_team2WaveRespawningEnabled			= 1 << 1,
	};
	TRuleFlags m_ruleFlags;
	// ~State // 
};

#endif // __GAMERULES_MP_WAVE_SPAWNING_H__
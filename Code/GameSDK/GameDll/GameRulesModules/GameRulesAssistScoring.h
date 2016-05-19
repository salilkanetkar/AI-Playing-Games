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

// Description : Game rules module to handle scoring points values


#ifndef __GAMERULESASSISTSCORING_H__
#define __GAMERULESASSISTSCORING_H__

#include "IGameRulesAssistScoringModule.h"
#include "IGameRulesKillListener.h"
#include "GameRulesTypes.h"

class CGameRules;

class CGameRulesAssistScoring : 
	public IGameRulesAssistScoringModule, 
	public IGameRulesKillListener
{
protected:
	CGameRules *m_pGameRules;
	float m_maxTimeBetweenAttackAndKillForAssist;
	float m_assistScoreMultiplier;
	TGameRulesScoreInt m_maxAssistScore;

	struct SAttackerData
	{	
		struct SDamageTime
		{
			float m_damage;
			float m_time;

			SDamageTime(float damage, float time)
			{
				m_damage = damage;
				m_time = time;
			}
		};
		typedef std::vector<SDamageTime>			TDamageTimes;

		TDamageTimes m_damageTimes;
		EntityId m_entityId;
		float m_lastShootTime;
		float m_tagExpirationTime;

		SAttackerData(EntityId entityId, float time, float tagDuration, float damageDone )
		{
			m_entityId = entityId;

			if (tagDuration<0.f)
			{
				m_tagExpirationTime=-1.f;
				m_lastShootTime = time;
				m_damageTimes.push_back(SDamageTime(damageDone, time));
			}
			else
			{
				m_lastShootTime = -1.f;
				m_tagExpirationTime = time + tagDuration*1000.f;
			}
		}

	};
	
	typedef std::vector<SAttackerData>					TAttackers;
	typedef std::map<EntityId, TAttackers>			TTargetAttackerMap;

	TTargetAttackerMap m_targetAttackerMap;

public:
	CGameRulesAssistScoring();
	virtual ~CGameRulesAssistScoring();

	virtual void	Init(XmlNodeRef xml);

	virtual void	RegisterAssistTarget(EntityId targetId);
	virtual void	UnregisterAssistTarget(EntityId targetId);
	virtual void  OnEntityHit(const HitInfo &info, const float tagDuration=-1.f );
	virtual EntityId	SvGetMostRecentAttacker(EntityId targetId);

	//IGameRulesKillListener
	virtual void OnEntityKilledEarly(const HitInfo& hitInfo) {};
	virtual void OnEntityKilled(const HitInfo &hitInfo);
	//~IGameRulesKillListener

protected:
	void SvDoScoringForDeath(const EntityId victimId, const EntityId shooterId, const char *weaponClassName, int damage, int material, int hit_type);
	void ClHandleAssistsForDeath(const EntityId victimId, const EntityId shooterId);

	bool m_bTeamSpecificScoring;
};

#endif // __GAMERULESASSISTSCORING_H__
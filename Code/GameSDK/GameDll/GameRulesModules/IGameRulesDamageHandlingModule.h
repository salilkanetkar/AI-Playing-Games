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

#ifndef _GAME_RULES_DAMAGE_HANDLING_MODULE_H_
#define _GAME_RULES_DAMAGE_HANDLING_MODULE_H_

#if _MSC_VER > 1000
# pragma once
#endif

#include <IGameRulesSystem.h>
#include "GameRules.h"

class CWeapon;

class IGameRulesDamageHandlingModule
{
public:

	enum EGameEvents
	{
		eGameEvent_LocalPlayerEnteredMercyTime = 0,
		eGameEvent_TrainRideStarts,
		eGameEvent_TrainRideEnds
	};

	virtual ~IGameRulesDamageHandlingModule() {}

	virtual void Init(XmlNodeRef xml) = 0;
	virtual void PostInit() = 0;
	virtual void Update(float frameTime) = 0;

	virtual bool SvOnHit(const HitInfo &hitInfo) = 0;
	virtual bool SvOnHitScaled(const HitInfo &hitInfo) = 0;
	virtual void SvOnExplosion(const ExplosionInfo &explosionInfo, const CGameRules::TExplosionAffectedEntities& affectedEntities) = 0;
	virtual void SvOnCollision(const IEntity *entity, const CGameRules::SCollisionHitInfo& colHitInfo) = 0;

	virtual void ClProcessHit(Vec3 dir, EntityId shooterId, EntityId weaponId, float damage, uint16 projectileClassId, uint8 hitTypeId) = 0;

	virtual bool AllowHitIndicatorForType(int hitTypeId) = 0;

	virtual void MakeMovementVisibleToAIForEntityClass(const IEntityClass* pEntityClass) = 0;

	virtual void OnGameEvent(const EGameEvents& gameEvent) = 0;

#ifdef SERVER_CHECKS
	virtual void RegisterShotIdentification(EntityId ownerId, CWeapon * pWeapon, uint32 mungedShotId) {}
#endif

	enum ePID_flags
	{
		PID_None = 0,
		PID_Headshot = BIT(1),
	};
};

#endif // _GAME_RULES_DAMAGE_HANDLING_MODULE_H_
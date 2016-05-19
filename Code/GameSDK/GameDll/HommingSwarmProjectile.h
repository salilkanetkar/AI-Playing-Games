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

#pragma once

#ifndef _HOMMING_SWARM_PROJECTILE_H_
#define _HOMMING_SWARM_PROJECTILE_H_

#include "Projectile.h"



class CHommingSwarmProjectile: public CProjectile
{
private:
	struct SVehicleStatus
	{
		SVehicleStatus(IEntity* pEntity, IPhysicalEntity* pPhysics);

		Vec3 position;
		Vec3 velocity;
		Vec3 front;
		float speed;
	};

public:
	DECLARE_COMPONENT_TYPE("CHommingSwarmProjectile",0x0B7CC62BA4144EE8,0xA238A66A6FB9FCE5);
	CHommingSwarmProjectile();
	virtual ~CHommingSwarmProjectile();

	virtual void Update(SEntityUpdateContext &ctx, int updateSlot);
	virtual void HandleEvent(const SGameObjectEvent &);
	virtual void Launch(const Vec3 &pos, const Vec3 &dir, const Vec3 &velocity, float speedScale);

	virtual void Deflected(const Vec3& dir);

	virtual void FullSerialize(TSerialize ser);

	virtual void SetDestination(const Vec3& pos) {CProjectile::SetDestination(pos);}
	virtual void SetDestination(EntityId targetId);

private:
	typedef CProjectile BaseClass;

	Vec3 GetHomingTarget(CWeapon* pOwnerWeapon);

	Vec3 Seek(const SVehicleStatus& vehicle, const Vec3& targetPosition);
	Vec3 Wander(const SVehicleStatus& vehicle, float deltaTime);
	Vec3 Curl(const SVehicleStatus& vehicle, float deltaTime);

	void ExplodeIfMissingTarget(const SVehicleStatus& vehicle, const Vec3& velocity, const Vec3& targetPosition);

	Vec3 m_spawnDirection;
	Vec3 m_hommingDirection;
	Vec3 m_lockedDestination;
	Vec3 m_wanderState;

	EntityId m_fixedTarget;

	float m_wanderTimer;
	float m_controlLostTimer;
	float m_Roll;
	float m_curlDirection;
	float m_curlTime;
	float m_curlShift;
	bool m_hommingBehaviour;
};


#endif

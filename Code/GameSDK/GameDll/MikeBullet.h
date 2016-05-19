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

#ifndef __MIKE_BULLET_H__
#define __MIKE_BULLET_H__

#include "Bullet.h"
#include "AmmoParams.h"


struct IParticleEmitter;


class CBurnEffectManager
{
private:

	struct SBurnPoint
	{
		SBurnPoint()
			:	m_pBurnParams(NULL)
			,	m_effect(NULL)
			,	m_position(ZERO)
			,	m_radius(0.f)
			,	m_accumulation(0.f)
			,	m_accumulationDelay(0.0f)
			,	m_surfaceType(-1)
			,	m_attachedEntityId(0)
			,	m_attachType(GeomType_None)
			,	m_attachForm(GeomForm_Surface)
			,	m_hitType(0)
			,	m_shootByPlayer(true) 
			,	m_shooterFactionID(IFactionMap::InvalidFactionID)
		{};

		const SMikeBulletParams::SBurnParams* m_pBurnParams;
		IParticleEmitter* m_effect;
		Vec3 m_position;
		float m_radius;
		float m_accumulation;
		float m_accumulationDelay;
		int m_surfaceType;
		EntityId m_attachedEntityId;
		EGeomType m_attachType;
		EGeomForm m_attachForm;
		int m_hitType;
		bool m_shootByPlayer;
		uint m_shooterFactionID; // The faction ID of the shooter or IFactionMap::InvalidFactionID if we should always do damage.
	};

	typedef std::vector<SBurnPoint> TBurnPoints;

public:
	CBurnEffectManager();
	~CBurnEffectManager();

	void AddBurnPoint(const EventPhysCollision& pCollision, SMikeBulletParams* pBurnBulletParams, int hitType, bool shooterIsPlayer, const uint8 shooterFactionID);
	void Update(float deltaTime);
	void Reset();

private:
	void PushNewBurnPoint(const EventPhysCollision& collision, CBurnEffectManager::SBurnPoint* burnPoint);
	TBurnPoints::iterator FindBurnPointOnEntity(EntityId entityId, const uint8 shooterFactionID);
	TBurnPoints::iterator FindClosestBurnPoint(const Vec3& point, int surfaceType, const uint8 shooterFactionID);
	void SpawnImpactEffect(const EventPhysCollision& pCollision, const char* effectName);
	void CreateBurnEffect(const EventPhysCollision& pCollision, SBurnPoint* pBurnPoint);
	void UpdateBurnEffect(SBurnPoint* pBurnPoint);
	void DestroyBurnEffect(SBurnPoint* pBurnPoint);
	void ApplySurroundingDamage(float deltaTime);
	bool ShouldBurnPointInflictDamageOntoEntity(const SBurnPoint& burnPoint, IEntity* targetEntity) const;
	void DebugDraw();

	TBurnPoints m_burnPoints;
	float m_damageTimeOut;
};



class CMikeBullet : public CBullet
{
public:
	typedef CBullet BaseClass;


public:

	DECLARE_COMPONENT_TYPE("CMikeBullet", 0x9FC688CD3C2E4975,0x8C5B2347AF1C955E)

	CMikeBullet();

	// CProjectile
	virtual void SetParams(const SProjectileDesc& projectileDesc);
	virtual void HandleEvent(const SGameObjectEvent &);
	virtual void CreateBulletTrail(const Vec3& hitPos) {};


private:

	// The faction ID of the owner entity of the weapon that fired this bullet 
	// (IFactionMap::InvalidFactionID if unknown).
	uint8 m_ownerFactionID;
};

#endif

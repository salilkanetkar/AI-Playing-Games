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

#ifndef _LIGHTNING_BOLT_H_
#define _LIGHTNING_BOLT_H_

#if _MSC_VER > 1000
# pragma once
#endif

#include "StickyProjectile.h"
#include "Projectile.h"
#include "Effects/GameEffects/LightningGameEffect.h"



class CLightningBolt : public CProjectile
{
private:
	typedef CProjectile Parent;

public:
	DECLARE_COMPONENT_TYPE("CLightingBolt",0x15383BAD96754E08,0xB6090A11341CB4CC)
	CLightningBolt();
	~CLightningBolt();

	virtual void Launch(const Vec3 &pos, const Vec3 &dir, const Vec3 &velocity, float speedScale/* =1.0f */);
	virtual void Update(SEntityUpdateContext &ctx, int updateSlot);
	virtual void HandleEvent(const SGameObjectEvent &);
	virtual void ReInitFromPool();
	
	virtual bool NetSerialize(TSerialize ser, EEntityAspects aspect, uint8 profile, int pflags);
	virtual NetworkAspectType GetNetSerializeAspects();

	virtual void OnHit(const HitInfo&);

private:
	void UpdateSparkSize();
	void Strike();
	void OnStrike();
	void ProcessHit(CGameRules* gameRules, EntityId target, float damage, Vec3 position, Vec3 direction, int partId);
	void CreateSpark(const Vec3& start, const Vec3& end, EntityId targetId);
	void HandleArcing(EntityId target, const Vec3& collisionNormal, const SLightningBoltParams& boltParams);

	CStickyProjectile m_stuckProjectile;
    GameSDK::CLightningGameEffect::TIndex m_lightningId;
	float m_strikeCountDown;
};


#endif

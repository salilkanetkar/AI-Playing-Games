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

#ifndef __CSHOTDEBUG_H__
#define __CSHOTDEBUG_H__

#ifndef _RELEASE
#define SHOT_DEBUG
#endif //_RELEASE

#ifdef SHOT_DEBUG

#include "IWeapon.h"
#include "IGameRulesSystem.h"
#include "WeaponSystem.h"

class CShotDebug : public IProjectileListener, public IHitListener
{
public:
	CShotDebug(IActor& owner, IItem& weapon);
	virtual ~CShotDebug();

	void Update(const float dt);
	void OnProjectileHit(const CProjectile& projectile, const EventPhysCollision& collision);

	// IProjectileListener
	virtual void OnProjectilePhysicsPostStep(CProjectile* pProjectile, EventPhysPostStep* pEvent, int bPhysicsThread) {}
	virtual void OnLaunch(CProjectile* pProjectile, const Vec3& pos, const Vec3& velocity);
	// ~IProjectileListener

	//IHitListener
	virtual void OnHit(const HitInfo& hitInfo);
	virtual void OnExplosion(const ExplosionInfo& explosion){}
	virtual void OnServerExplosion(const ExplosionInfo& explosion){}
	//~IHitListener

protected:
private:
	const EntityId m_ownerId;
	const EntityId m_weaponId;

	struct SProjInfo
	{
		struct Launch
		{
			Vec3 pos;
			Vec3 vel;
		};
		struct Impact
		{
			Vec3 pos;
			Vec3 vel;
			Vec3 nrm;
			Vec3 relpos;
			EntityId target;
			int partid;
			short matid;
			bool aimed;
		};
		struct Hit
		{
			float damage;
			int hitType;
		};
		enum EState
		{
			eS_LaunchSet		=BIT(0),
			eS_ImpactSet		=BIT(1),
			eS_HitSet				=BIT(2),
			eS_Inspecting		=BIT(3),

			eS_StopCountdownMask = eS_Inspecting,
			eS_Complete = eS_LaunchSet|eS_ImpactSet,
		};

		SProjInfo(const EntityId _projectileId, const float _lifetime)
			: projectileId(_projectileId)
			, originalLifetime(_lifetime)
			, lifetime(_lifetime)
			, flags(0)
		{}
		Launch launch;
		Impact impact;
		Hit hit;
		const EntityId projectileId;
		const float originalLifetime;
		float lifetime;
		uint8 flags;
	};

	typedef std::map<EntityId, SProjInfo*> ProjectileMap;
	typedef std::list<SProjInfo> ProjectileList;
	ProjectileMap m_projectileMap;
	ProjectileList m_projectiles;
};

#endif //SHOT_DEBUG
#endif //__CSHOTDEBUG_H__

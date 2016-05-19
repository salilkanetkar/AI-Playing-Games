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

// Description : AI grenade weapon


#ifndef __AIGRENADE_H__
#define __AIGRENADE_H__

#if _MSC_VER > 1000
# pragma once
#endif


#include "Weapon.h"

class CAIGrenade : public CWeapon, public IWeaponFiringLocator
{
	struct FinishGrenadeAction;
	typedef CWeapon BaseClass;

public:
	

	DECLARE_COMPONENT_TYPE("CAIGrenade", 0x53FC67C7527F479D,0xB74F32CB48ED4FD9)
	CAIGrenade();
	virtual ~CAIGrenade();

	//IWeapon
	virtual void StartFire();
	virtual void StartFire(const SProjectileLaunchParams& launchParams);
	virtual void OnAnimationEventShootGrenade(const AnimEventInstance &event);
	virtual int  GetAmmoCount(IEntityClass* pAmmoType) const { return 1; } //Always has ammo
	virtual void OnReset();
	virtual void SetCurrentFireMode(int idx);

	virtual void GetMemoryUsage(ICrySizer * s) const
	{
		s->AddObject(this, sizeof(*this));
		CWeapon::GetInternalMemoryUsage(s); // collect memory of parent class
	}

	virtual void PostSerialize();

private:
	virtual bool GetProbableHit(EntityId weaponId, const IFireMode* pFireMode, Vec3& hit);
	virtual bool GetFiringPos(EntityId weaponId, const IFireMode* pFireMode, Vec3& pos);
	virtual bool GetFiringDir(EntityId weaponId, const IFireMode* pFireMode, Vec3& dir, const Vec3& probableHit, const Vec3& firingPos);
	virtual bool GetActualWeaponDir(EntityId weaponId, const IFireMode* pFireMode, Vec3& dir, const Vec3& probableHit, const Vec3& firingPos);
	virtual bool GetFiringVelocity(EntityId weaponId, const IFireMode* pFireMode, Vec3& vel, const Vec3& firingDir);
	virtual void WeaponReleased();
	void SetFiringPos(const char* boneName);

	bool m_waitingForAnimEvent;
	Vec3 m_grenadeLaunchPosition;
	Vec3 m_grenadeLaunchVelocity;
};


#endif // __AIGRENADE_H__
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

#if !defined(__VEHICLE_WEAPON_CONTROLLED_H__)
#define __VEHICLE_WEAPON_CONTROLLED_H__

#if _MSC_VER > 1000
# pragma once
#endif


#include <IItemSystem.h>
#include <CryCharAnimationParams.h>
#include "VehicleMountedWeapon.h"
#include "VehicleWeapon.h"

struct IVehicle;
struct IVehiclePart;
struct IVehicleSeat;

#define WEAPON_CONTROLLED_HIT_RANGE 250.0f

class CControlledLocator : public IWeaponFiringLocator
{
public:

  virtual ~CControlledLocator();

  bool GetProbableHit(EntityId weaponId, const IFireMode* pFireMode, Vec3& hit);
  bool GetFiringPos(EntityId weaponId, const IFireMode* pFireMode, Vec3& pos);
  bool GetFiringDir(EntityId weaponId, const IFireMode* pFireMode, Vec3& dir, const Vec3& probableHit, const Vec3& firingPos);
  bool GetActualWeaponDir(EntityId weaponId, const IFireMode* pFireMode, Vec3& dir, const Vec3& probableHit, const Vec3& firingPos);
  bool GetFiringVelocity(EntityId weaponId, const IFireMode* pFireMode, Vec3& vel, const Vec3& firingDir);
  void WeaponReleased();
};

class CVehicleWeaponControlled : public CVehicleMountedWeapon
{
  typedef CVehicleMountedWeapon Base;

  CControlledLocator  m_ControlledLocator;
  float               m_CurrentTime;
  Ang3                m_Angles;
  bool                m_Firing;
  bool                m_FirePause;
  bool                m_FireBlocked;

public:

	DECLARE_COMPONENT_TYPE("CVehicleWeaponControlled", 0x26DDBD6C62A8455E,0xA80C7CFAE5FED2DA)
  CVehicleWeaponControlled();
  virtual ~CVehicleWeaponControlled() {}

  virtual void  StartFire();
  virtual void  StopFire();
  virtual void  OnReset();

  void StartUse(EntityId userId);
  void StopUse(EntityId userId);

  virtual void Update(SEntityUpdateContext& ctx, int update);
  void         Update3PAnim(CPlayer *player, float goalTime, float frameTime, const Matrix34 &mat);

	virtual void GetMemoryUsage(ICrySizer * s) const
	{
		s->AddObject(this, sizeof(*this));
		CWeapon::GetInternalMemoryUsage(s); // collect memory of parent class
	}
};


class CVehicleWeaponPulseC : public CVehicleWeapon
{
  typedef CVehicleWeapon Base;

  Vec3  m_StartDir;
  Vec3  m_TargetPos;

public:

	DECLARE_COMPONENT_TYPE("CVehicleWeaponPulseC", 0xC9FC68C4253F4CC1,0xB5A66C02E5232012)
  CVehicleWeaponPulseC();
  virtual ~CVehicleWeaponPulseC() {}

  virtual void  StartFire();
  void SetDestination(const Vec3& pos);

  virtual void Update(SEntityUpdateContext& ctx, int update);

  virtual void GetMemoryUsage(ICrySizer * s) const
  {
    s->AddObject(this, sizeof(*this));
    CWeapon::GetInternalMemoryUsage(s); // collect memory of parent class
  }
};


#endif// #if !defined(__VEHICLE_WEAPON_CONTROLLED_H__)
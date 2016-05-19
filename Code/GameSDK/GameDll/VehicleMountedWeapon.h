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

// Description : Mounted machine gun that can be ripped off by the player
//               and move around with it - vehicle mounted version

#pragma once

#ifndef _VEHICLE_MOUNTED_WEAPON_H_
#define _VEHICLE_MOUNTED_WEAPON_H_

#include <IItemSystem.h>
#include <CryCharAnimationParams.h>
#include "HeavyMountedWeapon.h"

struct IVehicle;
struct IVehiclePart;
struct IVehicleSeat;

class CVehicleMountedWeapon : public CHeavyMountedWeapon
{
public:

	DECLARE_COMPONENT_TYPE("CVehicleMountedWeapon", 0x4F98F13000AE4670, 0xA97DC00ADA9C4D21)
	CVehicleMountedWeapon();

	// CWeapon
	virtual void StartUse(EntityId userId);
	virtual void ApplyViewLimit(EntityId userId, bool apply);

	virtual void StartFire();

	virtual void Update(SEntityUpdateContext& ctx, int update);

	virtual void SetAmmoCount(IEntityClass* pAmmoType, int count);
	virtual void SetInventoryAmmoCount(IEntityClass* pAmmoType, int count);

	virtual bool CanZoom() const;

	virtual void GetMemoryUsage(ICrySizer * s) const
	{
		s->AddObject(this, sizeof(*this));
		CHeavyMountedWeapon::GetInternalMemoryUsage(s); // collect memory of parent class
	}	

	virtual bool ShouldBindOnInit() const { return false; }

	virtual bool ApplyActorRecoil() const { return (m_pOwnerSeat == m_pSeatUser); }  

	virtual void FullSerialize(TSerialize ser);
	virtual void PostSerialize();
	// ~CWeapon

	virtual void Use(EntityId userId);
	virtual void StopUse(EntityId userId);
	bool CanRipOff() const;

	bool CanUse(EntityId userId) const;

	virtual void MountAtEntity(EntityId entityId, const Vec3 &pos, const Ang3 &angles);

protected:

	bool CheckWaterLevel() const;
	virtual void PerformRipOff(CActor* pOwner);
	virtual void FinishRipOff();
	void ResetState();

	EntityId m_vehicleId;
	IVehicleSeat* m_pOwnerSeat; // owner seat of the weapon
	IVehicleSeat* m_pSeatUser; // seat of the weapons user

private:

	void CorrectRipperEntityPosition(float timeStep);

	Quat	m_previousVehicleRotation;
	Vec3    m_previousWSpaceOffsetPosition; 
	Vec3	m_localRipUserOffset; 
	float	m_dtWaterLevelCheck;
	bool	m_usedThisFrame; //Stop this item being used multiple times in a single frame (As you end up exiting then re-entering)
};

#endif // _VEHICLEHMG_H_

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

#ifndef _USEABLE_TURRET_H_
#define _USEABLE_TURRET_H_

#include "HeavyMountedWeapon.h"


class CUseableTurret : public CHeavyMountedWeapon
{
private:
	typedef CHeavyMountedWeapon BaseClass;

public:

	enum ECUTFiringMode
	{
		ECUTFM_Rapid,
		ECUTFM_Rockets,
	};

	DECLARE_COMPONENT_TYPE("CUseableTurret", 0x7AA5ADBA743D439F,0xB802065491F316D4)
	CUseableTurret();

	virtual void OnAction(EntityId actorId, const ActionId& actionId, int activationMode, float value);
	virtual void Select(bool select);
	virtual bool CanRipOff() const;
	virtual bool CanUse(EntityId userId) const;

	SC_API void SetLockedEntity(EntityId lockedEntity);

	ECUTFiringMode GetCurrentMode() { return m_currentMode; }

private:
	virtual float GetZoomTimeMultiplier();
	virtual void OnShoot(EntityId shooterId, EntityId ammoId, IEntityClass* pAmmoType, const Vec3 &pos, const Vec3 &dir, const Vec3 &vel);

	void SetFiringMode(ECUTFiringMode mode);
	ECUTFiringMode GetNextMode() const;
	void CenterPlayerView(CPlayer* pPlayer);

	ECUTFiringMode m_currentMode;
	EntityId m_lockedEntity;
};


#endif

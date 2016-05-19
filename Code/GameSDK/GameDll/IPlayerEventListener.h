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

// Description : Player Event Listern interface.

#pragma once

#ifndef __IPlayerEventListener_h__
#define __IPlayerEventListener_h__

#include "IAgent.h"

struct IPlayerEventListener
{
	enum ESpecialMove
	{
		eSM_Jump = 0,
		eSM_SpeedSprint,
	};
	virtual ~IPlayerEventListener(){}
	virtual void OnEnterVehicle(IActor* pActor, const char* strVehicleClassName, const char* strSeatName, bool bThirdPerson) {};
	virtual void OnExitVehicle(IActor* pActor) {};
	virtual void OnToggleThirdPerson(IActor* pActor, bool bThirdPerson) {};
	virtual void OnItemDropped(IActor* pActor, EntityId itemId) {};
	virtual void OnItemPickedUp(IActor* pActor, EntityId itemId) {};
	virtual void OnItemUsed(IActor* pActor, EntityId itemId) {};
	virtual void OnStanceChanged(IActor* pActor, EStance stance) {};
	virtual void OnSpecialMove(IActor* pActor, ESpecialMove move) {};
	virtual void OnDeath(IActor* pActor, bool bIsGod) {};
	virtual void OnObjectGrabbed(IActor* pActor, bool bIsGrab, EntityId objectId, bool bIsNPC, bool bIsTwoHanded) {};
	virtual void OnHealthChanged(IActor* pActor, float newHealth) {};
	virtual void OnRevive(IActor* pActor, bool bIsGod) {};
	virtual void OnSpectatorModeChanged(IActor* pActor, uint8 mode) {};
	virtual void OnSprintStaminaChanged(IActor* pActor, float newStamina) {};
	virtual void OnPickedUpPickableAmmo( IActor* pActor, IEntityClass* pAmmoType, int count ) {}
	virtual void OnIsInWater(IActor* pActor, bool bIsInWater) {}
	virtual void OnHeadUnderwater(IActor* pActor, bool bHeadUnderwater) {}
	virtual void OnOxygenLevelChanged(IActor* pActor, float fNewOxygenLevel) {};
};

#endif // __IPlayerEventListener_h__

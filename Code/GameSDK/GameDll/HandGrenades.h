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

#ifndef _HAND_GRENADES_H_
#define _HAND_GRENADES_H_

#include "Weapon.h"
#include "IActionMapManager.h"

class CThrow;

class CHandGrenades : public CWeapon
{

public:
	DECLARE_COMPONENT_TYPE("CHandGrenades", 0x2A92DEFDDEAD441D,0xB09256E9F0ADD676)

	CHandGrenades();
	virtual ~CHandGrenades();

	virtual void GetMemoryUsage(ICrySizer * s) const
	{
		s->AddObject(this, sizeof(*this));
		CWeapon::GetInternalMemoryUsage(s); // collect memory of parent class
	}

private:

	typedef CWeapon inherited;

	//------------ CWeapon -----------------------
	
	bool CanSelect() const;
	bool CanDeselect() const;
	bool OnActionAttack(EntityId actorId, const ActionId& actionId, int activationMode, float value);
	bool OnActionAttackPrimary(EntityId actorId, const ActionId& actionId, int activationMode, float value) { return OnActionAttack(actorId, actionId, activationMode, value); }
	void StartSprint(CActor* pOwnerActor);
	bool ShouldSendOnShootHUDEvent() const;

	virtual void OnPickedUp(EntityId actorId, bool destroyed);
	virtual void OnDropped(EntityId actorId, bool ownerWasAI);
	virtual void OnSetAmmoCount(EntityId shooterId);
	virtual void OnSelected(bool selected);
	virtual void InitFireModes();

	virtual	uint32 StartDeselection(bool fastDeselect);

	virtual bool AllowInteraction(EntityId interactionEntity, EInteractionType interactionType);

	bool CanOwnerThrowGrenade() const;

	void FumbleGrenade();

	virtual void StartQuickGrenadeThrow();
	virtual void StopQuickGrenadeThrow();

	virtual void ForcePendingActions(uint8 blockedActions = 0);

	virtual bool CancelCharge();

	//------------ ~CWeapon -----------------------

	void UpdateStowedWeapons();

	CThrow* m_pThrow;

	int m_numStowedCopies;
	int m_stowSlot;

	bool m_quickThrowRequested;
	bool m_bInQuickThrow;
	bool m_throwCancelled;
};

#endif
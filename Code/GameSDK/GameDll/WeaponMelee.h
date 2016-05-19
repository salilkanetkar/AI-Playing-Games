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

// Description : C++ Weapon Melee Implementation
//
//               This is a dedicated weapon for the melee intended to replace
//               the current 'firemode' implementation.



#pragma once

#ifndef __WeaponMelee_h__
#define __WeaponMelee_h__

#include "Weapon.h"

struct SMeleeActions;
class CWeaponMelee : public CWeapon
{
	typedef CWeapon BaseClass;
public:

	enum EMeleeStatus
	{
		EMeleeStatus_Default = 0,
		EMeleeStatus_Left,
		EMeleeStatus_Right,
		EMeleeStatus_KillingBlow,
		EMeleeStatus_FinishingMove,
		EMeleeStatus_NUM
	};

	EMeleeStatus GetMeleeAttackAction();
	EMeleeStatus GetMeleeStatusCurrent() const { return m_meleeStatusCurrent; }

protected:

	virtual void OnSelected( bool selected );
	virtual void StartFire();
	virtual void MeleeAttack( bool bShort );
	virtual void Select(bool select);
	virtual void Update(SEntityUpdateContext& ctx, int);
	virtual void SetOwnerId(EntityId ownerId);
	virtual bool CanModify() const;
	virtual bool CanMeleeAttack() const;

public:

	DECLARE_COMPONENT_TYPE("CWeaponMelee", 0x286808E05BD741C6,0xA0726744CDEF113A)
	CWeaponMelee();
	virtual ~CWeaponMelee();

private:

	EMeleeStatus m_meleeStatusNext;
	EMeleeStatus m_meleeStatusCurrent;

	float m_meleeAnimationTime;
	float m_timeSinceAction;
	int m_numberInCombo;

	EMeleeStatus GetMeleeAttackWeapon();
	void RestoreWeapon( const bool bLazyRestore );
	float GetAnimTime() const;
};

#endif // __WeaponMelee_h__

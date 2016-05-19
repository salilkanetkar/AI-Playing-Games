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
//               This is a dedicated weapon for the melee intended to replace
//               the current 'firemode' implementation.


#include "StdAfx.h"

#include "WeaponMelee.h"
#include "Melee.h"

#include "Player.h"

#include "FireModeParams.h"

namespace
{
	bool KillingBlowOverride( const CActor* pOwnerActor )
	{
		return false;
	}
}

DECLARE_DEFAULT_COMPONENT_FACTORY(CWeaponMelee, CWeaponMelee)

CWeaponMelee::CWeaponMelee()
	:
m_meleeStatusNext(EMeleeStatus_Default),
m_meleeStatusCurrent(EMeleeStatus_Default),
m_timeSinceAction(0.0f),
m_numberInCombo(0),
m_meleeAnimationTime(0.0f)
{
}

CWeaponMelee::~CWeaponMelee()
{
}

bool CWeaponMelee::CanMeleeAttack() const
{
	CActor* pOwner = GetOwnerActor();
	if( pOwner && (m_timeSinceAction >= m_meleeAnimationTime) )
	{
		return BaseClass::CanMeleeAttack() || IsSelecting();
	}

	return false;
}

void CWeaponMelee::SetOwnerId(EntityId ownerId)
{
	BaseClass::SetOwnerId(ownerId);

	if( ownerId != 0 && m_melee != NULL )
	{
		m_melee->InitFragmentData();
	}
}

void CWeaponMelee::OnSelected( bool selected )
{
	m_meleeAnimationTime = 0.0f;
	m_timeSinceAction = 0.0f;
	m_meleeStatusNext = EMeleeStatus_Default;
	m_meleeStatusCurrent = EMeleeStatus_Default;
	m_numberInCombo = 0;
}

void CWeaponMelee::StartFire()
{
	// This means someone pressed the trigger during melee.
	if( m_melee->CanAttack() )
	{
		switch( m_meleeStatusNext )
		{
		case EMeleeStatus_FinishingMove:
			break;
		default:
			RestoreWeapon(false);
			break;
		}
	}
}

void CWeaponMelee::MeleeAttack( bool bShort )
{
	if( CanMeleeAttack() )
	{
		CWeapon::MeleeAttack( bShort );

		m_meleeAnimationTime = GetAnimTime();
	}
}

void CWeaponMelee::Update(SEntityUpdateContext& ctx, int slot)
{
	CWeapon::Update( ctx, slot );

	// This check is required because the GameObjectExtention system calls Update 255 times at initialization time.
	if( IsSelected() )
	{
		if( m_timeSinceAction > (m_meleeAnimationTime + m_melee->GetMeleeParams().weapon_restore_delay) )
		{
			RestoreWeapon(false);
		}

		m_timeSinceAction += ctx.fFrameTime;
	}
}

void CWeaponMelee::Select(bool select)
{
	SetPlaySelectAction( !select );

	if( !select )
	{
		SetItemFlag( eIF_PlayFastSelect, true );
	}

	CWeapon::Select(select);
}

CWeaponMelee::EMeleeStatus CWeaponMelee::GetMeleeAttackAction()
{
	m_timeSinceAction = 0.0f;

	const CActor* pOwnerActor = GetOwnerActor();
	if( (pOwnerActor != NULL) && (pOwnerActor->GetActorClass() == CPlayer::GetActorClassType()) )
	{
		if( KillingBlowOverride(pOwnerActor) )
		{
			m_meleeStatusNext = EMeleeStatus_KillingBlow;
		}
		else
		{
			if( m_meleeStatusNext == EMeleeStatus_Default )
			{
				const EntityId lastItemId = pOwnerActor->GetInventory()->GetLastItem();
				const IEntity* piEntity = gEnv->pEntitySystem->GetEntity( lastItemId );
				if( piEntity && piEntity->GetClass() == CItem::sBowClass )
				{
					m_meleeStatusNext = EMeleeStatus_Right;
				}
			}
		}
	}

	switch( m_meleeStatusNext )
	{
	case EMeleeStatus_Left:
	case EMeleeStatus_Default:
		m_meleeStatusNext		 = EMeleeStatus_Right;
		m_meleeStatusCurrent = EMeleeStatus_Left;
		return EMeleeStatus_Left;
	case EMeleeStatus_Right:
		m_meleeStatusNext		 = EMeleeStatus_Left;
		m_meleeStatusCurrent = EMeleeStatus_Right;
		return EMeleeStatus_Right;
	case EMeleeStatus_KillingBlow:
		m_meleeStatusNext		 = EMeleeStatus_Left;
		m_meleeStatusCurrent = EMeleeStatus_KillingBlow;
		return EMeleeStatus_KillingBlow;
	}

	return EMeleeStatus_Default;
}

void CWeaponMelee::RestoreWeapon( const bool bLazyRestore )
{
	CActor* pActor = GetOwnerActor();
	if( pActor )
	{
		const EntityId lastItemId = pActor->GetInventory()->GetLastItem();
		IItem* piLastItem = pActor->GetItem(lastItemId);

		if( piLastItem )
		{
			const EItemFlags flag = bLazyRestore ? eIF_None : eIF_PlayFastSelectAsSpeedBias;
			CItem* pLastItem = static_cast<CItem*> (piLastItem);
			pLastItem->SetItemFlag( flag|eIF_UseFastSelectTag, true );
		}

		pActor->SelectLastItem( false, true );
	}
}



bool CWeaponMelee::CanModify() const
{
	return false;
}

float CWeaponMelee::GetAnimTime() const
{
	return m_animationTime[eIGS_Owner]*0.001f;
}

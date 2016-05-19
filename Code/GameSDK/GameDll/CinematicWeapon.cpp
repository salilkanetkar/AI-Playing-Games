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

#include "StdAfx.h"
#include "CinematicWeapon.h"

#include "GameActions.h"
#include "FireMode.h"

#include "GameRules.h"
#include "CinematicInput.h"

DECLARE_DEFAULT_COMPONENT_FACTORY(CCinematicWeapon, CCinematicWeapon)

CCinematicWeapon::CCinematicWeapon()
	: m_inputClass( CCinematicWeapon::eInputClass_None )
{

}

CCinematicWeapon::~CCinematicWeapon()
{
	Disable();
}

void CCinematicWeapon::HandleEvent( const SGameObjectEvent& goEvent )
{
	if ((goEvent.event == eGFE_ScriptEvent) && (goEvent.param != NULL))
	{
		const char* eventName = static_cast<const char*>(goEvent.param);
		if (strcmp(eventName, "primary") == 0)
		{
			SetPrimary();
		}
		if (strcmp(eventName, "secondary") == 0)
		{
			SetSecondary();
		}
		if (strcmp(eventName, "deactivate") == 0)
		{
			Disable();
		}
	}
}

void CCinematicWeapon::OnAction( EntityId actorId, const ActionId& actionId, int activationMode, float value )
{
	const CGameActions& gameActions = g_pGame->Actions();

	const bool fireAction = (actionId == gameActions.attack1_cine) || (actionId == gameActions.attack2_cine);
	if (fireAction)
	{
		if (activationMode == eAAM_OnPress)
		{
			StartFire();
		}
		else if(activationMode == eAAM_OnHold)
		{
			if((m_fm != NULL) && !m_fm->IsFiring() && m_fm->CanFire())
			{
				StartFire();
			}		
		}
		else
		{
			StopFire();
		}
	}
}

void CCinematicWeapon::StartFire()
{
	BaseClass::StartFire();

	//m_fireSound.Play( GetEntityId() );
}

void CCinematicWeapon::StopFire()
{
	BaseClass::StopFire();

	//m_fireSound.Stop( GetEntityId() );
	//m_stopFireTailSound.Play( GetEntityId() );
}

void CCinematicWeapon::SetupFireSound()
{
	stack_string soundName;

	soundName.Format("CinematicWeapon_%s_Fire", GetEntity()->GetClass()->GetName());
	m_fireSound.SetSignal( soundName.c_str() );

	soundName.Format("CinematicWeapon_%s_Tail", GetEntity()->GetClass()->GetName());
	m_stopFireTailSound.SetSignal( soundName.c_str() );
}

void CCinematicWeapon::SetPrimary()
{
	CGameRules* pGameRules = g_pGame->GetGameRules();
	if (pGameRules != NULL)
	{
		if (m_inputClass == eInputClass_Secondary)
		{
			pGameRules->GetCinematicInput().SetUpWeapon( CCinematicInput::eWeapon_Secondary, NULL );
		}

		pGameRules->GetCinematicInput().SetUpWeapon( CCinematicInput::eWeapon_Primary, GetEntity() );

		m_inputClass = eInputClass_Primary;
	}

	if (IEntity* pParentEntity = GetEntity()->GetParent())
	{
		SetHostId( pParentEntity->GetId() );
	}

	SetupFireSound();
}

void CCinematicWeapon::SetSecondary()
{
	CGameRules* pGameRules = g_pGame->GetGameRules();
	if (pGameRules != NULL)
	{
		if (m_inputClass == eInputClass_Primary)
		{
			pGameRules->GetCinematicInput().SetUpWeapon( CCinematicInput::eWeapon_Primary, NULL );
		}

		pGameRules->GetCinematicInput().SetUpWeapon( CCinematicInput::eWeapon_Secondary, GetEntity() );

		m_inputClass = eInputClass_Secondary;
	}

	if (IEntity* pParentEntity = GetEntity()->GetParent())
	{
		SetHostId( pParentEntity->GetId() );
	}

	SetupFireSound();
}

void CCinematicWeapon::Disable()
{
	CGameRules* pGameRules = g_pGame->GetGameRules();
	if (pGameRules != NULL)
	{
		if (m_inputClass == eInputClass_Primary)
		{
			pGameRules->GetCinematicInput().SetUpWeapon( CCinematicInput::eWeapon_Primary, NULL );
		}
		else if (m_inputClass == eInputClass_Secondary)
		{
			pGameRules->GetCinematicInput().SetUpWeapon( CCinematicInput::eWeapon_Secondary, NULL );
		}

		m_inputClass = eInputClass_None;
	}

	SetHostId(0);

	StopFire();
}
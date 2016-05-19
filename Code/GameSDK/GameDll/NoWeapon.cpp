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
#include "NoWeapon.h"
#include "GameInputActionHandlers.h"
#include "GameActions.h"
#include "Actor.h"
#include "WeaponFPAiming.h"
#include "FireMode.h"

DECLARE_DEFAULT_COMPONENT_FACTORY(CNoWeapon, CNoWeapon)

CNoWeapon::CNoWeapon()
{
	RegisterActions();
}

//////////////////////////////////////////////////////////////////////////
CNoWeapon::~CNoWeapon()
{
}

//////////////////////////////////////////////////////////////////////////
void CNoWeapon::RegisterActions()
{
	CGameInputActionHandlers::TNoWeaponActionHandler& noWeaponActionHandler = g_pGame->GetGameInputActionHandlers().GetCNoWeaponActionHandler();

	if (noWeaponActionHandler.GetNumHandlers() == 0)
	{
		const CGameActions& actions = g_pGame->Actions();

		if(gEnv->bMultiplayer)
		{
			noWeaponActionHandler.AddHandler(actions.special, &CNoWeapon::OnActionMelee);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
void CNoWeapon::Select(bool select)
{
	BaseClass::Select(select);

	SetBusy(!select);
}

//////////////////////////////////////////////////////////////////////////
void CNoWeapon::OnAction(EntityId actorId, const ActionId& actionId, int activationMode, float value)
{
	CGameInputActionHandlers::TNoWeaponActionHandler& noWeaponActionHandler = g_pGame->GetGameInputActionHandlers().GetCNoWeaponActionHandler();

	noWeaponActionHandler.Dispatch(this,actorId,actionId,activationMode,value);
}

//////////////////////////////////////////////////////////////////////////
bool CNoWeapon::OnActionMelee( EntityId actorId, const ActionId& actionId, int activationMode, float value )
{
	if(activationMode == eAAM_OnPress)
	{
		//If we are swimming and can fire under water we might want to do a melee attack
		CActor* pOwnerActor = GetOwnerActor();
		if(pOwnerActor && pOwnerActor->IsSwimming() && CanFireUnderWater())
		{
			CGameInputActionHandlers::TWeaponActionHandler& weaponActionHandler = g_pGame->GetGameInputActionHandlers().GetCWeaponActionHandler();
			weaponActionHandler.Dispatch(this,actorId,actionId,activationMode,value);
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CNoWeapon::UpdateAimAnims(SParams_WeaponFPAiming &aimAnimParams)
{
	if (m_sharedparams->params.hasAimAnims)
	{
		IFireMode* pFireMode = GetFireMode(GetCurrentFireMode());
		aimAnimParams.shoulderLookParams = 
			pFireMode ?
			&static_cast<CFireMode*>(pFireMode)->GetShared()->aimLookParams :
		&m_sharedparams->params.aimLookParams;

		return true;
	}

	return false;
}

bool CNoWeapon::ShouldDoPostSerializeReset() const
{
	return false;
}

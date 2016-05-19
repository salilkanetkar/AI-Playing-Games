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

// Description : Implements a damage behavior which gives camera shake to the
//               player


#include "StdAfx.h"
#include "IVehicleSystem.h"
#include "VehicleDamageBehaviorCameraShake.h"
#include "Game.h"
#include "GameRules.h"
#include <IActorSystem.h>

//m_damageRatio
//------------------------------------------------------------------------
CVehicleDamageBehaviorCameraShake::CVehicleDamageBehaviorCameraShake()
: m_damageMult(1.0f)
{
}

//------------------------------------------------------------------------
bool CVehicleDamageBehaviorCameraShake::Init(IVehicle* pVehicle, const CVehicleParams& table)
{
	m_pVehicle = pVehicle;
	
	if (gEnv->IsClient())
		m_pVehicle->RegisterVehicleEventListener(this, "VehicleDamageBehaviorCameraShake");

	return true;
}

//------------------------------------------------------------------------
CVehicleDamageBehaviorCameraShake::~CVehicleDamageBehaviorCameraShake()
{
	if (gEnv->IsClient())
		m_pVehicle->UnregisterVehicleEventListener(this);
}

//------------------------------------------------------------------------
void CVehicleDamageBehaviorCameraShake::Reset()
{
	m_damageMult = 1.0f;
}

//------------------------------------------------------------------------
void CVehicleDamageBehaviorCameraShake::OnDamageEvent(EVehicleDamageBehaviorEvent event, const SVehicleDamageBehaviorEventParams& behaviorParams)
{
	if (event == eVDBE_Hit)
	{
		m_damageMult = max(1.0f, behaviorParams.componentDamageRatio / 0.25f);
	}
}

//------------------------------------------------------------------------
void CVehicleDamageBehaviorCameraShake::OnVehicleEvent(EVehicleEvent event, const SVehicleEventParams& params)
{
	if (!gEnv->IsClient())
		return;

	if (event == eVE_Damaged)
	{
		float angle = 10.0f * (m_damageMult);
		ShakeClient(angle, 0.2f, 0.05f, 0.25f);
	}
	else if (event == eVE_Hit)
	{
		ShakeClient(5.0f, 0.10f, 0.1f, 0.05f);
	}
}

//------------------------------------------------------------------------
void CVehicleDamageBehaviorCameraShake::ShakeClient(float angle, float shift, float duration, float frequency)
{
	IActorSystem* pActorSystem = gEnv->pGame->GetIGameFramework()->GetIActorSystem();
	assert(pActorSystem);

	EntityId clientId = g_pGame->GetIGameFramework()->GetClientActorId();

	for(TVehicleSeatId seatId=1; seatId<=m_pVehicle->GetLastSeatId(); seatId++)
	{
		if (IVehicleSeat* pSeat = m_pVehicle->GetSeatById(seatId))
		{
			EntityId passengerId = pSeat->GetPassenger();

			if (passengerId == clientId)
			{
				IActor* pActor = pActorSystem->GetActor(passengerId);
				if(pActor)
					pActor->CameraShake(angle, shift, duration, frequency, Vec3(0.0f, 0.0f, 0.0f), 5, "VehicleDamageBehaviorCameraShake");
			}
		}
	}
}

DEFINE_VEHICLEOBJECT(CVehicleDamageBehaviorCameraShake);

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

// Description : Controls internal heat of entity (used together with thermal vision)


#include "StdAfx.h"
#include "EntityEffectsHeat.h"

#include "Game.h"
#include <Components/IComponentRender.h>

#ifndef _RELEASE

#include "GameCVars.h"

class CHeatControllerDebug
{
public:

	static void DebugInfo(IEntity* ownerEntity, const float currentHeat)
	{
		if (g_pGameCVars->g_thermalVisionDebug == 0)
			return;

		const float textColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
		const Vec3 entityPosition = ownerEntity->GetWorldPos();

		gEnv->pRenderer->DrawLabelEx(entityPosition, 1.75f, textColor, true, false, "Thermal vision: %.3f", currentHeat);
	}
};

#else

class CHeatControllerDebug
{
public:
	ILINE static void DebugInfo(IEntity* ownerEntity, const float currentHeat)
	{

	}
};

#endif

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

EntityEffects::CHeatController::CHeatController()
: m_ownerEntity(NULL)
, m_baseHeat(0.0f)
, m_coolDownHeat(-1.0f)
, m_thermalVisionOn(false)
{
}

void EntityEffects::CHeatController::InitWithEntity( IEntity* pEntity, const float baseHeat )
{
	CRY_ASSERT(m_ownerEntity == NULL);
	CRY_ASSERT(pEntity);

	m_ownerEntity = pEntity;
	m_baseHeat = clamp_tpl(baseHeat, 0.0f, 1.0f);
}

void EntityEffects::CHeatController::AddHeatPulse( const float intensity, const float time )
{
	const float currentPulseHeat = (float)fsel(-m_heatPulse.baseTime, 
		0.0f, 
		clamp_tpl((1.0f - (m_heatPulse.runningTime * (float)fres(m_heatPulse.baseTime + FLT_EPSILON))) * m_heatPulse.heat, 0.0f, 1.0f));
	m_heatPulse.heat = clamp_tpl(currentPulseHeat + intensity, 0.0f, 1.0f - m_baseHeat);
	m_heatPulse.baseTime = clamp_tpl((m_heatPulse.baseTime - m_heatPulse.runningTime) + time, 0.0f, 4.5f);	//Fixed to maximum of 4.5secs to cool down
	m_heatPulse.runningTime = 0.0f;
}

bool EntityEffects::CHeatController::Update( const float frameTime )
{
	CRY_ASSERT(m_ownerEntity);

	bool thermalVisionOn = false;
	if (thermalVisionOn != m_thermalVisionOn)
	{
		m_thermalVisionOn = thermalVisionOn;
		SetThermalVisionParams(m_thermalVisionOn ? m_baseHeat : 0.0f);
	}

	const bool heatPulseRunning = (m_heatPulse.baseTime > 0.0f);
	const bool coolingDown = (m_coolDownHeat >= 0.0f);
	const bool requiresUpdate = heatPulseRunning || coolingDown;

	if (!requiresUpdate)
		return false;

	const float entityHeat = coolingDown ? UpdateCoolDown(frameTime) : UpdateHeat(frameTime); 

	if (thermalVisionOn)
	{
		SetThermalVisionParams(entityHeat);
	}

	return true;
}

float EntityEffects::CHeatController::UpdateHeat( const float frameTime )
{
	m_heatPulse.runningTime += frameTime;

	const float pulseFraction = clamp_tpl(m_heatPulse.runningTime * (float)fres(m_heatPulse.baseTime), 0.0f, 1.0f);
	const bool pulseActive = (pulseFraction < 1.0f);

	float pulseHeat = 0.0f;

	if (pulseActive)
	{
		pulseHeat = (m_heatPulse.heat * (1.0f - pulseFraction));	
	}
	else
	{
		m_heatPulse.Reset();
	}

	return clamp_tpl(m_baseHeat + pulseHeat, 0.0f, 1.0f);
}

float EntityEffects::CHeatController::UpdateCoolDown(const float frameTime)
{
	const float cooldownRate = 0.075f;

	m_baseHeat = clamp_tpl(m_baseHeat - (frameTime * cooldownRate), 0.0f, m_baseHeat);
	m_coolDownHeat = (float)fsel(-(m_baseHeat - m_coolDownHeat), -1.0f, m_coolDownHeat);

	return m_baseHeat;
}

void EntityEffects::CHeatController::SetThermalVisionParams( const float scale )
{
	IComponentRender *pEntityRenderProxy = static_cast<IComponentRender *>(m_ownerEntity->GetComponent<IComponentRender>().get());
	if(pEntityRenderProxy)
	{
		pEntityRenderProxy->SetVisionParams(scale, scale, scale, scale);
	}

	CHeatControllerDebug::DebugInfo(m_ownerEntity, scale);
}

void EntityEffects::CHeatController::Revive( const float baseHeat )
{
	m_baseHeat = clamp_tpl(baseHeat, 0.0f, 1.0f);
	m_coolDownHeat = -1.0f;
}

void EntityEffects::CHeatController::CoolDown( const float targetHeat )
{
	m_coolDownHeat = clamp_tpl(targetHeat, 0.0f, 1.0f);
	m_heatPulse.Reset();
}
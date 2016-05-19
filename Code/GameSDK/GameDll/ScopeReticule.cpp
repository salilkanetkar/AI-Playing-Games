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

// Description : Iron Sight

#include "StdAfx.h"
#include "ScopeReticule.h"
#include "WeaponSharedParams.h"



CScopeReticule::CScopeReticule()
:	m_disabledTimeOut(0.0f)
,	m_blinkFrequency(4.0f)
{
}



void CScopeReticule::SetMaterial(IMaterial* pMaterial)
{
	m_scopeReticuleMaterial = pMaterial;
}



void CScopeReticule::SetBlinkFrequency(float blink)
{
	m_blinkFrequency = blink;
}



void CScopeReticule::Disable(float time)
{
	m_disabledTimeOut = time;
}



void CScopeReticule::Update(CWeapon* pWeapon)
{
	if (!m_scopeReticuleMaterial || (m_blinkFrequency==0.f))
		return;

	const float frequency = (float)fsel(-m_blinkFrequency, 12.0f, m_blinkFrequency);
	const float maxOpacity = 0.99f;
	float opacity = maxOpacity;
	if (!pWeapon->CanFire() && !pWeapon->IsDeselecting())
		opacity = (float)fsel(fmod_tpl(gEnv->pTimer->GetCurrTime(), 1.0f/frequency)*frequency-0.5f, maxOpacity, 0.0f);
	m_disabledTimeOut = max(m_disabledTimeOut - gEnv->pTimer->GetFrameTime(), 0.0f);
	opacity = (float)fsel(-m_disabledTimeOut, opacity, 0.0f);

	m_scopeReticuleMaterial->SetGetMaterialParamFloat("opacity", opacity, false);
}

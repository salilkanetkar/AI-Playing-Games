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
#include "WaterEffects.h"


CWaterGameEffects::CWaterGameEffects()
	: m_waterDropletsAmount(-1.0f)
{

}

CWaterGameEffects::~CWaterGameEffects()
{

}

void CWaterGameEffects::Update( float frameTime )
{
	if (m_waterDropletsAmount > 0.0f)
	{
		const float maxScreenTimeInv = (float)fres(1.5f);
		const float newWaterDropletsAmount = m_waterDropletsAmount - (frameTime * maxScreenTimeInv);

		m_waterDropletsAmount = newWaterDropletsAmount;

		gEnv->p3DEngine->SetPostEffectParam( "WaterDroplets_Amount", newWaterDropletsAmount );
	}
	else
	{
		gEnv->p3DEngine->SetPostEffectParam( "WaterDroplets_Amount", 0.0f );

		m_waterDropletsAmount = -1.0f;
		SetActive( false );
	}
}

const char* CWaterGameEffects::GetName( ) const
{
	return "WaterEffects";
}

void CWaterGameEffects::GetMemoryUsage( ICrySizer *pSizer ) const
{
	pSizer->AddObject(this, sizeof(*this));
}

void CWaterGameEffects::OnCameraComingOutOfWater( )
{
	m_waterDropletsAmount = 0.7f;

	if(IsFlagSet(GAME_EFFECT_ACTIVE) == false)
	{
		SetActive( true );
	}
}
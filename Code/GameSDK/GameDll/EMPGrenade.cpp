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
#include "EMPGrenade.h"
#include "Player.h"

DECLARE_DEFAULT_COMPONENT_FACTORY(CEMPGrenade, CEMPGrenade)

CEMPGrenade::CEMPGrenade() : m_bActive(false), m_pulsePos(ZERO)
{
	m_postExplosionLifetime = g_pGameCVars->g_empOverTimeGrenadeLife;
}

CEMPGrenade::~CEMPGrenade()
{
}

void CEMPGrenade::Update( SEntityUpdateContext &ctx, int updateSlot )
{
	if (m_bActive)
	{
		const Matrix34& worldMat = GetEntity()->GetWorldTM();

		if(gEnv->bServer && m_postExplosionLifetime > 0.f)
		{
			m_postExplosionLifetime -= ctx.fFrameTime;
			if(m_postExplosionLifetime <= 0.f)
			{
				Destroy();
			}
		}
	}

	BaseClass::Update(ctx, updateSlot);
}

void CEMPGrenade::HandleEvent( const SGameObjectEvent &event )
{
	CGrenade::HandleEvent(event);

	if (event.event == eGFE_OnCollision)
	{
		if(!m_bActive)
		{

			m_bActive = true;

			const Matrix34& worldMat = GetEntity()->GetWorldTM();
			m_pulsePos = worldMat.GetColumn3();
		}
	}
}

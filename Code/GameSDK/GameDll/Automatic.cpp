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
#include "Automatic.h"
#include "Actor.h"
#include "ScreenEffects.h"

#include "WeaponSharedParams.h"
#include "Game.h"


CRY_IMPLEMENT_GTI(CAutomatic, CSingle);


//------------------------------------------------------------------------
CAutomatic::CAutomatic()
{
}

//------------------------------------------------------------------------
CAutomatic::~CAutomatic()
{
}

//------------------------------------------------------------------------
void CAutomatic::StartReload(int zoomed)
{
	m_firing = false;
	BaseClass::StartReload(zoomed);
}

//------------------------------------------------------------------------
void CAutomatic::StartFire()
{
	BaseClass::StartFire();

	if (m_firing)
		m_pWeapon->PlayAction(GetFragmentIds().spin_down_tail);

	m_pWeapon->RequestStartFire();
}
//------------------------------------------------------------------------
void CAutomatic::Update(float frameTime, uint32 frameId)
{
	BaseClass::Update(frameTime, frameId);

	if (m_firing && CanFire(false))
	{
		m_firing = Shoot(true, m_fireParams->fireparams.autoReload);

		if(!m_firing)
		{
			StopFire();
		}
	}
}

//------------------------------------------------------------------------
void CAutomatic::StopFire()
{
	if(m_firing)
		SmokeEffect();

	m_firing = false;

	m_pWeapon->RequestStopFire();

	BaseClass::StopFire();
}

//---------------------------------------------------
void CAutomatic::GetMemoryUsage(ICrySizer * s) const
{
	s->AddObject(this, sizeof(*this));	
	GetInternalMemoryUsage(s); 
}

void CAutomatic::GetInternalMemoryUsage(ICrySizer * s) const
{
	CSingle::GetInternalMemoryUsage(s);		// collect memory of parent class
}

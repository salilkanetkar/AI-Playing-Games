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
#include "ThrowIndicator.h"

#include "Throw.h"
#include "LTagSingle.h"

#include "UI/HUD/HUDEventDispatcher.h"

CRY_IMPLEMENT_GTI(CThrowIndicator, CIronSight);

//------------------------------------------------------------------------
CThrowIndicator::CThrowIndicator()
	: m_indicatorShowing(false)
{
}

//------------------------------------------------------------------------
CThrowIndicator::~CThrowIndicator()
{
}

//------------------------------------------------------------------------
bool CThrowIndicator::StartZoom(bool stayZoomed, bool fullZoomout, int zoomStep)
{
	if (m_pWeapon->IsOwnerClient())
	{
		CThrow* pThrow = crygti_cast<CThrow*>(m_pWeapon->GetCFireMode(m_pWeapon->GetCurrentFireMode()));
		if((pThrow != NULL) && !pThrow->OutOfAmmo())
		{
			const float lifetime = pThrow->GetProjectileLifeTime();

			SHUDEvent trajectoryEvent(eHUDEvent_DisplayTrajectory);
			trajectoryEvent.AddData(SHUDEventData(true));
			trajectoryEvent.AddData(SHUDEventData(lifetime));
			CHUDEventDispatcher::CallEvent(trajectoryEvent);
			m_indicatorShowing = true;
		}
	}
	return false;
}

//------------------------------------------------------------------------
void CThrowIndicator::StopZoom()
{
	if (m_pWeapon->IsOwnerClient())
	{
		SHUDEvent trajectoryEvent(eHUDEvent_DisplayTrajectory);
		trajectoryEvent.AddData(SHUDEventData(false));
		trajectoryEvent.AddData(SHUDEventData(0.0f));
		CHUDEventDispatcher::CallEvent(trajectoryEvent);
		m_indicatorShowing = false;
	}
}

//------------------------------------------------------------------------
void CThrowIndicator::ExitZoom(bool force)
{
	StopZoom();
}

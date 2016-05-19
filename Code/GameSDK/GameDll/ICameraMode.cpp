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
#include "ICameraMode.h"

#include "Player.h"


ICameraMode::ICameraMode() 
	: m_isBlendingOff(false)
	, m_disableDrawNearest(false)
{

}

ICameraMode::~ICameraMode()
{

}

void ICameraMode::ActivateMode( const CPlayer & clientPlayer )
{
	m_isBlendingOff = false;

	if(m_disableDrawNearest)
	{
		SetDrawNearestFlag(clientPlayer,false);
	}

	Activate(clientPlayer);
}

void ICameraMode::DeactivateMode( const CPlayer & clientPlayer )
{
	m_isBlendingOff = true;

	if(m_disableDrawNearest)
	{
		SetDrawNearestFlag(clientPlayer,true);
	}

	Deactivate(clientPlayer);
}

bool ICameraMode::CanTransition()
{
	return false;
}

void ICameraMode::SetCameraAnimationFactor( const AnimationSettings& animationSettings )
{

}

void ICameraMode::GetCameraAnimationFactor( float &pos, float &rot )
{
	pos = 0.0f; rot = 0.0f;
}

void ICameraMode::Activate( const CPlayer & clientPlayer )
{

}

void ICameraMode::Deactivate( const CPlayer & clientPlayer )
{

}

void ICameraMode::SetDrawNearestFlag( const CPlayer & clientPlayer, bool bSetDrawNearestFlag )
{
	if(!clientPlayer.IsThirdPerson())
	{
		IEntity* pPlayerEntity = clientPlayer.GetEntity();
		if(pPlayerEntity)
		{
			uint32 entitySlotFlags = pPlayerEntity->GetSlotFlags(eIGS_FirstPerson);
			if(bSetDrawNearestFlag)
			{
				entitySlotFlags |= ENTITY_SLOT_RENDER_NEAREST;
			}
			else
			{
				entitySlotFlags &= ~ENTITY_SLOT_RENDER_NEAREST;
			}
			pPlayerEntity->SetSlotFlags(eIGS_FirstPerson,entitySlotFlags);
		}
	}
}
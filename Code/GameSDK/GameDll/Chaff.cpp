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
#include "Game.h"
#include "Chaff.h"
#include "GameRules.h"
#include <IEntitySystem.h>
#include <IGameTokens.h>

#include "WeaponSystem.h"

VectorSet<CChaff*> CChaff::s_chaffs;

DECLARE_DEFAULT_COMPONENT_FACTORY(CChaff,CChaff)

//------------------------------------------------------------------------
CChaff::CChaff()
{
	s_chaffs.insert(this);
	if(s_chaffs.size()>MAX_SPAWNED_CHAFFS)
	{
		if(s_chaffs[0]!=this)
			s_chaffs[0]->Destroy();
		else
			s_chaffs[1]->Destroy(); //Just in case...??
	}
}

//------------------------------------------------------------------------
CChaff::~CChaff()
{
	s_chaffs.erase(this);
}

//------------------------------------------------------------------------

void CChaff::HandleEvent(const SGameObjectEvent &event)
{
	CProjectile::HandleEvent(event);
}

Vec3 CChaff::GetPosition(void)
{
	return m_last;
}
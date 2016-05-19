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
#include "MPPath.h"

#include "GameRules.h"
#include "MPPathFollowingManager.h"

bool CMPPath::Init( IGameObject *pGameObject )
{
	SetGameObject(pGameObject);

	return true;
}

//------------------------------------------------------------------------
DECLARE_DEFAULT_COMPONENT_FACTORY(CMPPath, CMPPath)

CMPPath::~CMPPath()
{
	CMPPathFollowingManager* pPathFollowingManager = g_pGame->GetGameRules() ? g_pGame->GetGameRules()->GetMPPathFollowingManager() : NULL;
	if(pPathFollowingManager)
	{
		pPathFollowingManager->UnregisterPath(GetEntityId());
	}

}

//------------------------------------------------------------------------
void CMPPath::GetMemoryUsage(ICrySizer *pSizer) const
{
	pSizer->Add(*this);
}

//------------------------------------------------------------------------
bool CMPPath::ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params )
{
	ResetGameObject();
	CRY_ASSERT(!"CMPPath::ReloadExtension not implemented");
	return false;
}

//------------------------------------------------------------------------
bool CMPPath::GetEntityPoolSignature( TSerialize signature )
{
	CRY_ASSERT(!"CMPPath::GetEntityPoolSignature not implemented");
	return true;
}

void CMPPath::ProcessEvent(SEntityEvent& details)
{
	if(details.event == ENTITY_EVENT_LEVEL_LOADED)
	{
		CMPPathFollowingManager* pPathFollowingManager = g_pGame->GetGameRules()->GetMPPathFollowingManager();
		if(pPathFollowingManager)
		{
			pPathFollowingManager->RegisterPath(GetEntityId());
		}
	}
}

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
#include "GameAIHelpers.h"
#include <IAgent.h>
#include <IAIObject.h>
#include <IAIActor.h>

CGameAIInstanceBase::CGameAIInstanceBase(EntityId entityID)
{
	Init(entityID);
}

void CGameAIInstanceBase::Init(EntityId entityID)
{
	m_entityID = entityID;

#ifndef RELEASE
	if (IEntity* entity = gEnv->pEntitySystem->GetEntity(entityID))
	{
		m_debugEntityName = entity->GetName();
	}
#endif
}

void CGameAIInstanceBase::SendSignal(const char* signal, IAISignalExtraData* data)
{
	IEntity* entity = gEnv->pEntitySystem->GetEntity(GetEntityID());
	assert(entity);
	if (entity)
	{
		if (IAIObject* aiObject = entity->GetAI())
			if (IAIActor* aiActor = aiObject->CastToIAIActor())
				aiActor->SetSignal(1, signal, NULL, data, 0);
	}
}


// ===========================================================================
//	Send a signal to the AI actor.
//
//	In:		The signal name (NULL is invalid!)
//	In:		Optional signal context data that gets passed to Lua behavior 
//			scripts	(NULL will ignore).
//	In:		Option signal ID (or mode really). Should be a AISIGNAL_xxx
//			value.
//
void CGameAIInstanceBase::SendSignal(
	const char* signal, IAISignalExtraData* data, int nSignalID)
{
	IEntity* entity = gEnv->pEntitySystem->GetEntity(GetEntityID());
	assert(entity != NULL);
	if (entity != NULL)
	{
		IAIObject* aiObject = entity->GetAI();
		if (aiObject != NULL)
		{
			IAIActor* aiActor = aiObject->CastToIAIActor();
			if (aiActor != NULL)
			{
				aiActor->SetSignal(nSignalID, signal, NULL, data, 0);
			}
		}
	}
}

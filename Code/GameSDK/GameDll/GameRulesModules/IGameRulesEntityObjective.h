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

// Description : Interface for an entity based objective


#ifndef _IGAME_RULES_ENTITY_OBJECTIVE_H_
#define _IGAME_RULES_ENTITY_OBJECTIVE_H_

#if _MSC_VER > 1000
# pragma once
#endif

#include "IGameObject.h"
#include "SerializeFwd.h"

class IGameRulesEntityObjective
{
public:
	virtual ~IGameRulesEntityObjective() {}

	virtual void Init(XmlNodeRef xml) = 0;
	virtual void Update(float frameTime) = 0;

	virtual void OnStartGame() = 0;

	virtual bool NetSerialize( TSerialize ser, EEntityAspects aspect, uint8 profile, int flags ) = 0;

	virtual bool IsComplete(int teamId) = 0;

	virtual void AddEntityId(int type, EntityId entityId, int index, bool isNewEntity, const CTimeValue &timeAdded) = 0;
	virtual void RemoveEntityId(int type, EntityId entityId) = 0;
	virtual void ClearEntities(int type) = 0;
	virtual bool IsEntityFinished(int type, int index) = 0;
	virtual bool CanRemoveEntity(int type, int index) = 0;

	virtual void OnHostMigration(bool becomeServer) = 0;		// Host migration

	virtual void OnTimeTillRandomChangeUpdated(int type, float fPercLiveSpan) = 0;

	virtual bool IsPlayerEntityUsingObjective(EntityId playerId) = 0;
};

#endif // _IGAME_RULES_ENTITY_OBJECTIVE_H_

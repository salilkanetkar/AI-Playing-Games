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
#include "StalkerModule.h"
#include "Agent.h"


void StalkerModule::InitializeInstance(const InstanceInitContext<StalkerInstance>& context)
{
	StalkerInstance& instance = context.instance;
	EntityId entityID = context.entityID;

	instance = StalkerInstance();
	instance.Init(entityID);
}

void StalkerModule::DeinitializeInstance(InstanceID instanceID)
{
	StalkerInstance* instance = GetInstanceFromID(instanceID);

	if (instance->rayID)
	{
		g_pGame->GetRayCaster().Cancel(instance->rayID);
		instance->rayID = 0;
		instance->asyncState = AsyncReady;
	}
}

void StalkerModule::UpdateInstance(StalkerInstance& instance, float frameTime)
{
	Agent stalker(instance.GetEntityID());

	IAIObject* liveTarget = (stalker.IsValid() ? stalker.GetLiveTarget() : NULL);
	if (liveTarget)
	{
		if (instance.asyncState == AsyncReady)
		{
			instance.asyncState = AsyncInProgress;
			QueueLineOfSightRay(stalker, liveTarget, instance);
		}

		bool inTargetFov = liveTarget->IsPointInFOV(stalker.GetPos()) == IAIObject::eFOV_Primary;
		if (instance.lastInTargetFov != inTargetFov)
		{
			instance.lastInTargetFov = inTargetFov;
			instance.SendSignal(inTargetFov ? "OnInTargetFov" : "OnNotInTargetFov");
		}
	}
}

void StalkerModule::QueueLineOfSightRay(Agent& stalker, IAIObject* target, StalkerInstance& instance)
{
	PhysSkipList skipList;
	stalker.GetPhysicalSkipEntities(skipList);
	if (IAIActor* aiActor = target->CastToIAIActor())
		aiActor->GetPhysicalSkipEntities(skipList);

	instance.rayID = g_pGame->GetRayCaster().Queue(
		RayCastRequest::HighPriority,
		RayCastRequest(target->GetPos(), stalker.GetPos() - target->GetPos(),
		ent_terrain|ent_static|ent_rigid|ent_sleeping_rigid,
		((geom_colltype_ray << rwi_colltype_bit) | rwi_colltype_any | (10 & rwi_pierceability_mask)),
		&skipList[0], skipList.size()),
		functor(*this, &StalkerModule::LineOfSightRayComplete));
}

void StalkerModule::LineOfSightRayComplete(const QueuedRayID& rayID, const RayCastResult& result)
{
	if (StalkerInstance* instance = FindInstanceForRay(rayID))
	{
		instance->asyncState = AsyncReady;
		instance->rayID = 0;

		Agent stalker(instance->GetEntityID());
		if (stalker.IsValid())
		{
			bool visible = !result;

			if (visible != instance->lastVisibleFromTarget)
			{
				instance->lastVisibleFromTarget = visible;
				instance->SendSignal(visible ? "OnVisibleFromTarget" : "OnNotVisibleFromTarget");
			}
		}
	}
}

StalkerInstance* StalkerModule::FindInstanceForRay(const QueuedRayID& rayID)
{
	Instances::iterator it = m_running->begin();
	Instances::iterator end = m_running->end();

	for ( ; it != end; ++it)
	{
		StalkerInstance* instance = GetInstanceFromID(it->second);

		if (instance != NULL && instance->rayID == rayID)
			return instance;
	}

	return NULL;
}

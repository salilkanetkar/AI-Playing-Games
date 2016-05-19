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

#pragma once

#ifndef StalkerModule_h
#define StalkerModule_h

#include "GameAIHelpers.h"
#include <RayCastQueue.h>

struct StalkerInstance : public CGameAIInstanceBase
{
public:
	StalkerInstance()
		: rayID(0)
		, asyncState(AsyncReady)
		, lastVisibleFromTarget(false)
		, lastInTargetFov(false)
	{
	}

	QueuedRayID rayID;
	AsyncState asyncState;
	bool lastVisibleFromTarget;
	bool lastInTargetFov;
};

class StalkerModule : public AIModuleWithInstanceUpdate<StalkerModule, StalkerInstance, 4, 4>
{
private:
	virtual void InitializeInstance(const InstanceInitContext<StalkerInstance>& context);
	virtual void DeinitializeInstance(InstanceID instanceID);
	virtual const char* GetName() const { return "StalkerModule"; }
	virtual void UpdateInstance(StalkerInstance& instance, float frameTime);

	void QueueLineOfSightRay(class Agent& stalker, IAIObject* target, StalkerInstance& instance);
	void LineOfSightRayComplete(const QueuedRayID& rayID, const RayCastResult& result);
	StalkerInstance* FindInstanceForRay(const QueuedRayID& rayID);	
};

#endif // StalkerModule_h
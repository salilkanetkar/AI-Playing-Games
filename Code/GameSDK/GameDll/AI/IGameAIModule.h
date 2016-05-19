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

#ifndef IGameAIModule_h
#define IGameAIModule_h

// For an overview of the GameAISystem take a look in GameAISystem.cpp

struct IGameAIModule
{
	virtual ~IGameAIModule() {}
	virtual void EntityEnter(EntityId entityID) = 0;
	virtual void EntityLeave(EntityId entityID) = 0;
	virtual void EntityPause(EntityId entityID) = 0;
	virtual void EntityResume(EntityId entityID) = 0;
	virtual void Reset(bool bUnload) {}
	virtual void Update(float dt) {}
	virtual void Serialize(TSerialize ser) {}
	virtual void PostSerialize() {}
	virtual const char* GetName() const = 0;
};

#endif // IGameAIModule_h
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

// Description : Definitions for Lua-caching helpers used by Actors to avoid
//               Lua accessing at game time


#ifndef __ACTORLUACACHE_H__
#define __ACTORLUACACHE_H__

#include "ActorDefinitions.h"
#include "AutoAimManager.h"
#include <Components/IComponentPhysics.h>

#define MAKE_SHARED_PTR(cls) typedef _smart_ptr<cls> cls ## Ptr;

// Cached version of 'physicsParams' Lua table (per class instance)
struct SLuaCache_ActorPhysicsParams : public _reference_target_t
{
	SEntityPhysicalizeParams params;
	pe_player_dimensions playerDim;
	pe_player_dynamics playerDyn;
	bool bIsCached;

	SLuaCache_ActorPhysicsParams() : bIsCached(false) {}
	void GetMemoryUsage(ICrySizer *s) const;
	bool CacheFromTable(SmartScriptTable pEntityTable, const char* szEntityClassName);
};
MAKE_SHARED_PTR(SLuaCache_ActorPhysicsParams);

// Cached version of 'gameParams' Lua table (per class instance)
struct SLuaCache_ActorGameParams : public _reference_target_t
{
	SActorGameParams gameParams;
	SAutoaimTargetRegisterParams autoAimParams;
	bool bIsCached;

	SLuaCache_ActorGameParams() : bIsCached(false) {}
	void GetMemoryUsage(ICrySizer *s) const;
	bool CacheFromTable(SmartScriptTable pEntityTable);
};
MAKE_SHARED_PTR(SLuaCache_ActorGameParams);

// Cached version of Actor properties (per single instance)
struct SLuaCache_ActorProperties : public _reference_target_t
{
	SActorFileModelInfo fileModelInfo;
	float fPhysicMassMult;
	bool bIsCached;

	SLuaCache_ActorProperties() : bIsCached(false), fPhysicMassMult(1.0f) {}
	void GetMemoryUsage(ICrySizer *s) const;
	bool CacheFromTable(SmartScriptTable pEntityTable, SmartScriptTable pProperties);
};
MAKE_SHARED_PTR(SLuaCache_ActorProperties);

#endif //__ACTORLUACACHE_H__

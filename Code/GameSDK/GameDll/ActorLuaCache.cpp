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


#include "StdAfx.h"
#include "ActorLuaCache.h"
#include "Actor.h"

//////////////////////////////////////////////////////////////////////////
void SLuaCache_ActorPhysicsParams::GetMemoryUsage(ICrySizer *s) const
{
	s->Add(*this);
}

//////////////////////////////////////////////////////////////////////////
bool SLuaCache_ActorPhysicsParams::CacheFromTable(SmartScriptTable pEntityTable, const char* szEntityClassName)
{
	assert((bool)pEntityTable);

	if (!bIsCached)
	{
		bIsCached = CActor::LoadPhysicsParams(pEntityTable, szEntityClassName, params, playerDim, playerDyn);
	}

	return bIsCached;
}

//////////////////////////////////////////////////////////////////////////
void SLuaCache_ActorGameParams::GetMemoryUsage(ICrySizer *s) const
{
	s->Add(*this);
}

//////////////////////////////////////////////////////////////////////////
bool SLuaCache_ActorGameParams::CacheFromTable(SmartScriptTable pEntityTable)
{
	assert((bool)pEntityTable);

	if (!bIsCached)
	{
		bIsCached = CActor::LoadGameParams(pEntityTable, gameParams);
		bIsCached &= CActor::LoadAutoAimParams(pEntityTable, autoAimParams);
	}

	return bIsCached;
}

//////////////////////////////////////////////////////////////////////////
void SLuaCache_ActorProperties::GetMemoryUsage(ICrySizer *s) const
{
	s->Add(*this);
	s->AddContainer(fileModelInfo.IKLimbInfo);
}

//////////////////////////////////////////////////////////////////////////
bool SLuaCache_ActorProperties::CacheFromTable(SmartScriptTable pEntityTable, SmartScriptTable pProperties)
{
	assert((bool)pEntityTable);

	if (!bIsCached)
	{
		bIsCached = CActor::LoadFileModelInfo(pEntityTable, pProperties, fileModelInfo);

		if (pProperties)
		{
			pProperties->GetValue("physicMassMult", fPhysicMassMult);
		}
	}

	return bIsCached;
}
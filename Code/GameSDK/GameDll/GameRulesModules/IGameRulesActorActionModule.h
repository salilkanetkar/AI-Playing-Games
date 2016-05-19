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

#ifndef _GAME_RULES_ACTOR_ACTION_MODULE_H_
#define _GAME_RULES_ACTOR_ACTION_MODULE_H_

#if _MSC_VER > 1000
# pragma once
#endif

#include <IGameRulesSystem.h>

struct IActor;

class IGameRulesActorActionModule
{
public:
	virtual ~IGameRulesActorActionModule() {}

	virtual void Init(XmlNodeRef xml) = 0;
	virtual void PostInit() = 0;

	virtual void OnActorAction(IActor *pActor, const ActionId& actionId, int activationMode, float value) = 0;
};

#endif // _GAME_RULES_ACTOR_ACTION_MODULE_H_
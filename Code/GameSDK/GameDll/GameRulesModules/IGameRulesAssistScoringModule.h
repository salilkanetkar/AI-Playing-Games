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

// Description : Interface for the game rule module to handle scoring points


#ifndef _GAME_RULES_ASSIST_SCORING_MODULE_H_
#define _GAME_RULES_ASSIST_SCORING_MODULE_H_

#if _MSC_VER > 1000
# pragma once
#endif

#include <IGameRulesSystem.h>

class IGameRulesAssistScoringModule
{
public:
	virtual ~IGameRulesAssistScoringModule() {}

	virtual void	Init(XmlNodeRef xml) = 0;

	virtual void	RegisterAssistTarget(EntityId targetId) = 0;
	virtual void	UnregisterAssistTarget(EntityId targetId) = 0;
	virtual void  OnEntityHit(const HitInfo &info, const float tagDuration=-1.f) = 0;
//virtual void  ClAwardAssistKillPoints(EntityId victimId) = 0;
//virtual void	SvDoScoringForDeath(IActor *pActor, EntityId shooterId, const char *weaponClassName, int damage, int material, int hit_type) = 0;
	virtual EntityId	SvGetMostRecentAttacker(EntityId targetId) = 0;
};

#endif // _GAME_RULES_ASSIST_SCORING_MODULE_H_

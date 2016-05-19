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

// Description : Game rules module for games that use teams but handle the victory
//               messages using the player's individual scores

#ifndef _GAME_RULES_OBJECTIVE_VICTORY_CONDITIONS_INDIVIDUAL_H_
#define _GAME_RULES_OBJECTIVE_VICTORY_CONDITIONS_INDIVIDUAL_H_

#if _MSC_VER > 1000
# pragma once
#endif

#include "GameRulesObjectiveVictoryConditionsTeam.h"

class CGameRules;

class CGameRulesObjectiveVictoryConditionsIndividualScore : public CGameRulesObjectiveVictoryConditionsTeam
{
public:
	virtual void	OnEndGame(int teamId, EGameOverReason reason, ESVC_DrawResolution winningResolution=ESVC_DrawResolution_invalid, EntityId killedEntity=0, EntityId shooterEntity=0);
};

#endif // _GAME_RULES_OBJECTIVE_VICTORY_CONDITIONS_TEAM_H_
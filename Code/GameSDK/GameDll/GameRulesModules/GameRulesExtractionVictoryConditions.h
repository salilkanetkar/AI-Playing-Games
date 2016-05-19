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

// Description : Game rules module to handle victory conditions for extraction game mode


#ifndef _GAME_RULES_EXTRACTION_VICTORY_CONDITIONS_H_
#define _GAME_RULES_EXTRACTION_VICTORY_CONDITIONS_H_

#if _MSC_VER > 1000
# pragma once
#endif

#include "GameRulesStandardVictoryConditionsTeam.h"

class CGameRules;

class CGameRulesExtractionVictoryConditions : public CGameRulesStandardVictoryConditionsTeam
{
public:

	// IGameRulesVictoryConditionsModule
	virtual void	Update(float frameTime);
	// ~IGameRulesVictoryConditionsModule

	virtual void  TeamCompletedAnObjective(int teamId);

protected:

	void					UpdateResolutionData(int primaryTeam);
	void					CheckObjectives();
	virtual void	TimeLimitExpired();
};

#endif // _GAME_RULES_EXTRACTION_VICTORY_CONDITIONS_H_
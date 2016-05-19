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

#ifndef _GameRulesModulesRegistration_h_
#define _GameRulesModulesRegistration_h_

#if _MSC_VER > 1000
# pragma once
#endif

class IGameRulesTeamsModule;
class IGameRulesStateModule;
class IGameRulesVictoryConditionsModule;
class IGameRulesPlayerSetupModule;
class IGameRulesScoringModule;
class IGameRulesAssistScoringModule;
class IGameRulesPlayerStatsModule;
class IGameRulesSpawningModule;
class IGameRulesDamageHandlingModule;
class IGameRulesActorActionModule;
class IGameRulesSpectatorModule;
class IGameRulesObjectivesModule;
class IGameRulesRoundsModule;
class IGameRulesStatsRecording;

// GAMERULES_MODULE_LIST_FUNC( interface_type, name, lower_case_name (used for variable types), use_in_editor )

// Note: When adding a new module, make sure to add a Get...Module() function to CGameRules since this
// is no longer done as part of the macro (so intelisense finds the functions)

#define GAMERULES_MODULE_TYPES_LIST	\
	GAMERULES_MODULE_LIST_FUNC(IGameRulesStatsRecording, StatsRecording, statsRecording, false); \
	GAMERULES_MODULE_LIST_FUNC(IGameRulesTeamsModule, Teams, teams, true); \
	GAMERULES_MODULE_LIST_FUNC(IGameRulesStateModule, State, state, false);	\
	GAMERULES_MODULE_LIST_FUNC(IGameRulesVictoryConditionsModule, VictoryConditions, victoryConditions, false);	\
	GAMERULES_MODULE_LIST_FUNC(IGameRulesPlayerSetupModule, PlayerSetup, playerSetup, true);	\
	GAMERULES_MODULE_LIST_FUNC(IGameRulesScoringModule, Scoring, scoring, true);	\
	GAMERULES_MODULE_LIST_FUNC(IGameRulesAssistScoringModule, AssistScoring, assistScoring, true);	\
	GAMERULES_MODULE_LIST_FUNC(IGameRulesPlayerStatsModule, PlayerStats, playerStats, true);	\
	GAMERULES_MODULE_LIST_FUNC(IGameRulesSpawningModule, Spawning, spawning, true);	\
	GAMERULES_MODULE_LIST_FUNC(IGameRulesDamageHandlingModule, DamageHandling, damageHandling, true);	\
	GAMERULES_MODULE_LIST_FUNC(IGameRulesActorActionModule, ActorAction, actorAction, true);	\
	GAMERULES_MODULE_LIST_FUNC(IGameRulesSpectatorModule, Spectator, spectator, true);	\
	GAMERULES_MODULE_LIST_FUNC(IGameRulesObjectivesModule, Objectives, objectives, true);		\
	GAMERULES_MODULE_LIST_FUNC(IGameRulesRoundsModule, Rounds, rounds, true);


#endif // _GameRulesModulesRegistration_h_

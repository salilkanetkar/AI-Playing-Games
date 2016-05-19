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

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_devirt_defines.h>
#endif

#include "../GameRulesModules/GameRulesMPSpectator.cpp"
#include "../GameRulesModules/GameRulesObjectiveVictoryConditionsTeam.cpp"
#include "../GameRulesModules/GameRulesSpawningBase.cpp"
#include "../GameRulesModules/GameRulesStandardPlayerStats.cpp"
#include "../GameRulesModules/GameRulesStandardRounds.cpp"
#include "../GameRulesModules/GameRulesStandardScoring.cpp"
#include "../GameRulesModules/GameRulesStandardSetup.cpp"
#include "../GameRulesModules/GameRulesStandardState.cpp"
#include "../GameRulesModules/GameRulesStandardTwoTeams.cpp"
#include "../GameRulesModules/GameRulesStandardVictoryConditionsPlayer.cpp"
#include "../GameRulesModules/GameRulesStandardVictoryConditionsTeam.cpp"
#include "../GameRulesModules/GameRulesStatsRecording.cpp"
#include "../GameRulesModules/GameRulesSurvivorOneVictoryConditions.cpp"
#include "../GameRulesModules/GameRulesCombiCaptureObjective.cpp"
#include "../GameRulesModules/GameRulesHoldObjectiveBase.cpp"
#include "../GameRulesModules/GameRulesKingOfTheHillObjective.cpp"
#include "../GameRulesModules/GameRulesObjective_CTF.cpp"
#include "../GameRulesModules/GameRulesObjective_Extraction.cpp"
#include "../GameRulesModules/GameRulesSimpleEntityBasedObjective.cpp"
#include "../Testing/AutoTester.cpp"
#include "../CodeCheckpointDebugMgr.cpp"
#include "../Testing/FeatureTester.cpp"
#include "../Testing/FeatureTestMgr.cpp"
#include "../AutoEnum.cpp"
#include "../Utility/CryHash.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif

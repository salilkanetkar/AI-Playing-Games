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

#include "../flashlight.cpp"
#include "../FlowWeaponCustomizationNodes.cpp"
#include "../FragmentVariationHelper.cpp"
#include "../GameConstantCVars.cpp"
#include "../GameJobSystem.cpp"
#include "../GameRulesModules/GameRulesMPWaveSpawning.cpp"
#include "../GameRulesModules/GameRulesObjectiveVictoryConditionsIndividualScore.cpp"
#include "../GameTypeInfo.cpp"
#include "../GamePhysicsSettings.cpp"
#include "../HitDeathReactionsDefs.cpp"
#include "../ICameraMode.cpp"
#include "../IntersectionAssistanceUnit.cpp"
#include "../LagOMeter.cpp"
#include "../MPPath.cpp"
#include "../Network/Lobby/GameLobbyCVars.cpp"
#include "../Network/Lobby/MatchmakingEvents.cpp"
#include "../Network/Lobby/MatchmakingHandler.cpp"
#include "../Network/Lobby/MatchmakingTelemetry.cpp"
#include "../Network/Lobby/ScriptBind_MatchMaking.cpp"
#include "../Network/Lobby/TeamBalancing.cpp"
#include "../Nodes/FlowFadeNode.cpp"
#include "../Nodes/FlowMinimapNodes.cpp"
#include "../Nodes/FlowVideoPlayerNodes.cpp"
#include "../Nodes/ModelToHudFlowNodes.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif

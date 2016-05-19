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

#include "../PersistantStats.cpp"
#include "../PlayerModifiableValues.cpp"
#include "../PlayerPlugin.cpp"
#include "../PlayerPlugin_CurrentlyTargetting.cpp"
#include "../PlayerPlugin_Interaction.cpp"
#include "../PlayerProgression.cpp"
#include "../ProgressionUnlocks.cpp"
#include "../SkillKill.cpp"
#include "../SkillRanking.cpp"
#include "../DualCharacterProxy.cpp"
#include "../IKTorsoAim_Helper.cpp"
#include "../LookAim_Helper.cpp"
#include "../TransformationPinning.cpp"
#include "../WeaponFPAiming.cpp"
#include "../Battlechatter.cpp"
#include "../EquipmentLoadout.cpp"
#include "../GameRulesModules/GameRulesAssistScoring.cpp"
#include "../GameRulesModules/GameRulesCommonDamageHandling.cpp"
#include "../GameRulesModules/GameRulesExtractionVictoryConditions.cpp"
#include "../GameRulesModules/GameRulesModulesManager.cpp"
#include "../GameRulesModules/GameRulesMPActorAction.cpp"
#include "../GameRulesModules/GameRulesMPDamageHandling.cpp"
#include "../GameRulesModules/GameRulesMPSimpleSpawning.cpp"
#include "../GameRulesModules/GameRulesMPSpawning.cpp"
#include "../GameRulesModules/GameRulesMPSpawningWithLives.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif

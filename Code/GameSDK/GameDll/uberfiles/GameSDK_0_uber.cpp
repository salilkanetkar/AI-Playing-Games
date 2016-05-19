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

#include "../ActionMultiCoopAnim.cpp"
#include "../AdaptiveCompressor.cpp"
#include "../AI/AICorpse.cpp"
#include "../AI/AISquadManager.cpp"
#include "../AI/EnvironmentDisturbanceManager.cpp"
#include "../AI/RateOfDeath/RateOfDeathHelper.cpp"
#include "../AI/RateOfDeath/RateOfDeathSimple.cpp"
#include "../AI/StalkerModule.cpp"
#include "../AnimActionAIAiming.cpp"
#include "../AnimActionAICoverAction.cpp"
#include "../AI/RadioChatter/RadioChatterFlowNode.cpp"
#include "../AI/RadioChatter/RadioChatterModule.cpp"
#include "../AnimActionAIDetail.cpp"
#include "../AnimActionAILooking.cpp"
#include "../AnimActionAILookPose.cpp"
#include "../AnimActionAIStance.cpp"
#include "../AI/BehaviorTree/BehaviorTreeNodes_Game.cpp"
#include "../AnimActionBlendFromRagdoll.cpp"
#include "../AntiCheat/ServerPlayerTracker.cpp"
#include "../BodyDefinitions.cpp"
#include "../CinematicWeapon.cpp"
#include "../CornerSmoother.cpp"
#include "../DataPatchDownloader.cpp"
#include "../AI/AloneDetectorModule.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif

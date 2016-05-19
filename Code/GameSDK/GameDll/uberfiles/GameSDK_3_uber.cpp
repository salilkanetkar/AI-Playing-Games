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

#include "../PickAndThrowUtilities.cpp"
#include "../PlayerAI.cpp"
#include "../PlayerControl/PlayerEnslavement.cpp"
#include "../PlayerPlugin_InteractiveEntityMonitor.cpp"
#include "../PlayerStateAIMovement.cpp"
#include "../ActionCoopAnim.cpp"
#include "../AI/AIAwarenessToPlayerHelper.cpp"
#include "../AI/AICounters.cpp"
#include "../AI/HazardModule/Hazard.cpp"
#include "../AI/HazardModule/HazardModule.cpp"
#include "../AI/HazardModule/HazardProjectile.cpp"
#include "../AI/HazardModule/HazardRayCast.cpp"
#include "../AI/HazardModule/HazardShared.cpp"
#include "../AI/HazardModule/HazardSphere.cpp"
#include "../AntiCheat/ClientCheatMonitor.cpp"
#include "../AntiCheat/ServerCheatMonitor.cpp"
#include "../Audio/GameAudioUtils.cpp"
#include "../AnimActionAIAimPose.cpp"
#include "../AnimActionAIMovement.cpp"
#include "../AntiCheat/ShotCounter.cpp"
#include "../BasicEventListener.cpp"
#include "../Effects/GameEffects/GameEffectSoftCodeLibrary.cpp"
#include "../Effects/GameEffects/SceneBlurGameEffect.cpp"
#include "../Effects/RenderElements/GameRenderElement.cpp"
#include "../Effects/RenderElements/GameRenderElementSoftCodeLibrary.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif

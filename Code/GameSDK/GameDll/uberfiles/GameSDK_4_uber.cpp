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

#include "../Effects/RenderNodes/GameRenderNodeSoftCodeLibrary.cpp"
#include "../Environment/DangerousRigidBody.cpp"
#include "../Environment/DeflectorShield.cpp"
#include "../GameDll.cpp"
#include "../GameLocalizationManager.cpp"
#include "../GameRulesModules/GameRulesObjective_Predator.cpp"
#include "../GameStartup.cpp"
#include "../Actor.cpp"
#include "../ActorDamageEffectController.cpp"
#include "../ActorImpulseHandler.cpp"
#include "../ActorLuaCache.cpp"
#include "../ActorManager.cpp"
#include "../ActorTelemetry.cpp"
#include "../AIDemoInput.cpp"
#include "../HeavyMountedWeapon.cpp"
#include "../ItemAnimation.cpp"
#include "../MovementAction.cpp"
#include "../MPPathFollowingManager.cpp"
#include "../Network/Lobby/PlaylistActivityTracker.cpp"
#include "../Nodes/AIAssignmentNodes.cpp"
#include "../PlayerEntityInteraction.cpp"
#include "../PlayerPositionChecker.cpp"
#include "../PlayerStateLadder.cpp"
#include "../PlayerStateLinked.cpp"
#include "../PlayerStateEntry.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif

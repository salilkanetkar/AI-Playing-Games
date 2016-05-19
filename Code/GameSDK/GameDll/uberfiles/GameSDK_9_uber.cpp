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

#include "../PlayerMovementDebug.cpp"
#include "../PlayerRotation.cpp"
#include "../PlayerStumble.cpp"
#include "../PlayerVisTable.cpp"
#include "../SpectacularKill.cpp"
#include "../CameraModes.cpp"
#include "../PlayerCamera.cpp"
#include "../MountedGunController.cpp"
#include "../StealthKill.cpp"
#include "../InteractiveActionController.cpp"
#include "../LargeObjectInteraction.cpp"
#include "../SlideController.cpp"
#include "../AutoAimManager.cpp"
#include "../CustomReactionFunctions.cpp"
#include "../HitDeathReactions.cpp"
#include "../HitDeathReactionsSystem.cpp"
#include "../ScriptBind_HitDeathReactions.cpp"
#include "../MovementTransitions.cpp"
#include "../MovementTransitionsController.cpp"
#include "../MovementTransitionsSystem.cpp"
#include "../PlayerStateDead.cpp"
#include "../PlayerStateFly.cpp"
#include "../PlayerStateGround.cpp"
#include "../PlayerStateJump.cpp"
#include "../PlayerStateLedge.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif

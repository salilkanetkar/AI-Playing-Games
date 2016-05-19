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

#include "../UI/UIManager.cpp"
#include "../UI/UIMenuEvents.cpp"
#include "../UI/UIMultiPlayer.cpp"
#include "../UI/UIObjectives.cpp"
#include "../UI/UISettings.cpp"
#include "../UI/Utils/ILoadingMessageProvider.cpp"
#include "../UI/Utils/LocalizedStringManager.cpp"
#include "../UI/Utils/ScreenLayoutManager.cpp"
#include "../UI/Utils/ScreenLayoutUtils.cpp"
#include "../UI/WarningsManager.cpp"
#include "../VehicleActionAutoTarget.cpp"
#include "../VehicleDamageBehaviorAudioFeedback.cpp"
#include "../VehicleMountedWeapon.cpp"
#include "../VehicleMovementHelicopter.cpp"
#include "../QuatTBlender.cpp"
#include "../ScriptBind_Actor.cpp"
#include "../BodyDamage.cpp"
#include "../BodyDestruction.cpp"
#include "../BodyManager.cpp"
#include "../BodyManagerCVars.cpp"
#include "../GodMode.cpp"
#include "../NetPlayerInput.cpp"
#include "../Player.cpp"
#include "../PlayerInput.cpp"
#include "../PlayerMovementController.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif

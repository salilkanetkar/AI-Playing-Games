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

#include "../VTOLVehicleManager/VTOLVehicleManager.cpp"
#include "../EntityUtility/EntityEffects.cpp"
#include "../EntityUtility/EntityEffectsCloak.cpp"
#include "../EntityUtility/EntityEffectsHeat.cpp"
#include "../EntityUtility/EntityScriptCalls.cpp"
#include "../AntiCheatManager.cpp"
#include "../Network/Lobby/CryLobbySessionHandler.cpp"
#include "../EnvironmentalWeapon.cpp"
#include "../Network/Lobby/GameLobbyManager.cpp"
#include "../GameRulesModules/GameRulesSPDamageHandling.cpp"
#include "../GameStateRecorder.cpp"
#include "../LocalPlayerComponent.cpp"
#include "../ModInfoManager.cpp"
#include "../PatchPakManager.cpp"
#include "../MPTrackViewManager.cpp"
#include "../ProgressBar.cpp"
#include "../ScreenResolution.cpp"
#include "../SmokeManager.cpp"
#include "../GameRulesModules/SpawningVisTable.cpp"
#include "../StdAfx.cpp"
#include "../WeaponStats.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif

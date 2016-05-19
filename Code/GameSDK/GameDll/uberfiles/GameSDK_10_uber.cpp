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

#include "../PlayerStateSwim.cpp"
#include "../PlayerStateSwim_WaterTestProxy.cpp"
#include "../PlayerStateUtil.cpp"
#include "../VehicleMovementMPVTOL.cpp"
#include "../Voting.cpp"
#include "../WaypointPath.cpp"
#include "../WeaponBumpOffset.cpp"
#include "../WeaponLookOffset.cpp"
#include "../WeaponMelee.cpp"
#include "../WeaponOffset.cpp"
#include "../WeaponOffsetInput.cpp"
#include "../WeaponRecoilOffset.cpp"
#include "../WeaponStrafeOffset.cpp"
#include "../WeaponZoomOffset.cpp"
#include "../Audio/AudioSignalPlayer.cpp"
#include "../Audio/GameAudio.cpp"
#include "../Audio/Scriptbind_GameAudio.cpp"
#include "../EditorGame.cpp"
#include "../EquipmentSystemInterface.cpp"
#include "../CinematicInput.cpp"
#include "../DLCManager.cpp"
#include "../Game.cpp"
#include "../GameActions.cpp"
#include "../GameCache.cpp"
#include "../GameCVars.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif

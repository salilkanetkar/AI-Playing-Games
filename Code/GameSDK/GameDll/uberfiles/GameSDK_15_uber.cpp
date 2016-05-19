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

#include "../GunTurret.cpp"
#include "../HandGrenades.cpp"
#include "../HeavyWeapon.cpp"
#include "../JAW.cpp"
#include "../LTAG.cpp"
#include "../NoWeapon.cpp"
#include "../PickAndThrowWeapon.cpp"
#include "../VehicleWeapon.cpp"
#include "../VehicleWeaponControlled.cpp"
#include "../VehicleWeaponGuided.cpp"
#include "../Accessory.cpp"
#include "../Laser.cpp"
#include "../LaptopUtil.cpp"
#include "../NetInputChainDebug.cpp"
#include "../StatsAgent.cpp"
#include "../Utility/Wiggle.cpp"
#include "../GameRules.cpp"
#include "../GameRulesClientServer.cpp"
#include "../GameRulesModules/GameRulesObjective_PowerStruggle.cpp"
#include "../ScriptBind_GameRules.cpp"
#include "../Nodes/AchievementNode.cpp"
#include "../Nodes/AINodes.cpp"
#include "../Nodes/ColorGradientNode.cpp"
#include "../Nodes/FeatureTestNode.cpp"
#include "../Nodes/FlowActorNodes.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif

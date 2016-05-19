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

#include "../VehicleMovementArcadeWheeled.cpp"
#include "../VehicleMovementHelicopterArcade.cpp"
#include "../VehicleMovementBase.cpp"
#include "../Vehicle/VehiclePhysicsHelicopter.cpp"
#include "../Vehicle/VehicleMovementDummy.cpp"
#include "../VehicleMovementStdBoat.cpp"
#include "../VehicleMovementTank.cpp"
#include "../VehicleDamageBehaviorBurn.cpp"
#include "../VehicleDamageBehaviorCameraShake.cpp"
#include "../VehicleDamageBehaviorExplosion.cpp"
#include "../VehicleDamageBehaviorTire.cpp"
#include "../VehicleActionAutomaticDoor.cpp"
#include "../VehicleActionDeployRope.cpp"
#include "../VehicleActionEntityAttachment.cpp"
#include "../VehicleActionLandingGears.cpp"
#include "../FlowItemAnimation.cpp"
#include "../Item.cpp"
#include "../ItemAccessory.cpp"
#include "../ItemClientServer.cpp"
#include "../ItemEffect.cpp"
#include "../ItemEvents.cpp"
#include "../ItemPackages.cpp"
#include "../ItemParams.cpp"
#include "../ItemResource.cpp"
#include "../ItemResourceCache.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif

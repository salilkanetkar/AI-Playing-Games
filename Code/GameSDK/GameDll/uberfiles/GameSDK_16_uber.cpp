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

#include "../Nodes/FlowActorSensor.cpp"
#include "../Nodes/FlowCheckAreaNode.cpp"
#include "../Nodes/FlowConvoyNode.cpp"
#include "../Nodes/FlowHitInfoNode.cpp"
#include "../Nodes/FlowNodesInput.cpp"
#include "../Nodes/FlowPlayerStagingNode.cpp"
#include "../Nodes/FlowPlayerStumble.cpp"
#include "../Nodes/FlowPostFXNodes.cpp"
#include "../FlowVehicleNodes.cpp"
#include "../Nodes/G2FlowEntityElectricConnector.cpp"
#include "../Nodes/G2FlowEntityVelocity.cpp"
#include "../Nodes/G2FlowYesNoGestureNode.cpp"
#include "../Nodes/GameNodes.cpp"
#include "../Nodes/MPNodes.cpp"
#include "../Nodes/PressureWaveNode.cpp"
#include "../Nodes/SimulatePlayerInputNode.cpp"
#include "../Nodes/TacticalScanNode.cpp"
#include "../Nodes/WeaponNodes.cpp"
#include "../Editor/GameRealtimeRemoteUpdate.cpp"
#include "../Chaff.cpp"
#include "../KVoltBullet.cpp"
#include "../AfterMatchAwards.cpp"
#include "../ClientHitEffectsMP.cpp"
#include "../CorpseManager.cpp"
#include "../DummyPlayer.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif

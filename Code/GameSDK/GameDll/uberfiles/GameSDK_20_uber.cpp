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

#include "../Network/Lobby/GameBrowser.cpp"
#include "../Network/Lobby/GameLobby.cpp"
#include "../Network/Lobby/GameLobbyData.cpp"
#include "../Network/Lobby/GameServerLists.cpp"
#include "../Network/Lobby/SessionNames.cpp"
#include "../Network/Lobby/SessionSearchSimulator.cpp"
#include "../Network/Squad/SquadManager.cpp"
#include "../DownloadMgr.cpp"
#include "../CircularStatsStorage.cpp"
#include "../StatHelpers.cpp"
#include "../StatsRecordingMgr.cpp"
#include "../TelemetryCollector.cpp"
#include "../XMLStatsSerializer.cpp"
#include "../RecordingBuffer.cpp"
#include "../RecordingSystemPackets.cpp"
#include "../ReplayActor.cpp"
#include "../ReplayObject.cpp"
#include "../MultiplayerEntities/CarryEntity.cpp"
#include "../MultiplayerEntities/NetworkedPhysicsEntity.cpp"
#include "../Graphics/ColorGradientManager.cpp"
#include "../AI/AdvantagePointOccupancyControl.cpp"
#include "../AI/AIBattleFront.cpp"
#include "../AI/DeathManager.cpp"
#include "../AI/GameAIEnv.cpp"
#include "../AI/GameAIHelpers.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif

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

// Description : Game side definitions for lobby user packets


#include "ICryLobby.h"
#include "CryLobbyPacket.h"

#pragma once

enum GameUserPacketDefinitions
{
	eGUPD_LobbyStartCountdownTimer = CRYLOBBY_USER_PACKET_START,
	eGUPD_LobbyGameHasStarted,
	eGUPD_LobbyEndGame,
	eGUPD_LobbyEndGameResponse,
	eGUPD_LobbyUpdatedSessionInfo,
	eGUPD_LobbyMoveSession,
	eGUPD_SquadJoin,
	eGUPD_SquadJoinGame,
	eGUPD_SquadNotInGame,
	eGUPD_SetTeamAndRank,
	eGUPD_SendChatMessage,								// Clients request to send a message to other players
	eGUPD_ChatMessage,										// Server sent message to all appropriate other players.
	eGUPD_ReservationRequest,							// Sent by squad leader client after joined game to identify self as leader and to tell the game server to reserve slots for its members
	eGUPD_ReservationClientIdentify,			// Sent by clients after joined game to identify self to game server so it can check if client passes reserve checks (if any)
	eGUPD_ReservationsMade,								// Sent to a squad leader by a server when requested reservations have been successfully made upon receipt of a eGUPD_ReservationRequest packet 
	eGUPD_ReservationFailedSessionFull,		// Can be sent to clients when there's no room for them in a game session. Generally causes them to "kick" themselves by deleting their own session
	eGUPD_SyncPlaylistContents,						// Sync entire playlist
	eGUPD_SetGameVariant,
	eGUPD_SyncPlaylistRotation,
	eGUPD_SquadLeaveGame,									// Squad: Tell all members in the squad to leave (game host will leave last)
	eGUPD_SquadNotSupported,							// Squads not suported in current gamemode
	eGUPD_UpdateCountdownTimer,
	eGUPD_RequestAdvancePlaylist,
	eGUPD_SyncExtendedServerDetails,
	eGUPD_DetailedServerInfoRequest,
	eGUPD_DetailedServerInfoResponse,
	eGUPD_SquadDifferentVersion,					// Response to SquadJoin packet sent when the client is on a different patch
	eGUPD_SquadKick,
	eGUPD_SquadMerge,
	eGUPD_SetupDedicatedServer,
	eGUPD_SetupJoinCommand,
	eGUPD_SetAutoStartingGame,
	eGUPD_SetupArbitratedLobby,
	eGUPD_TeamBalancingSetup,
	eGUPD_TeamBalancingAddPlayer,
	eGUPD_TeamBalancingRemovePlayer,
	eGUPD_TeamBalancingUpdatePlayer,

	eGUPD_End
};


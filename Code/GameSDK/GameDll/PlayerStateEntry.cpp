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

#include "StdAfx.h"

#include "PlayerStateEvents.h"
#include "Player.h"


class CPlayerStateEntry : private CStateHierarchy<CPlayer>
{
	DECLARE_STATE_CLASS_BEGIN( CPlayer, CPlayerStateEntry )
	DECLARE_STATE_CLASS_END( CPlayer );
};

DEFINE_STATE_CLASS_BEGIN( CPlayer, CPlayerStateEntry, PLAYER_STATE_ENTRY, Root )
DEFINE_STATE_CLASS_END( CPlayer, CPlayerStateEntry );


const CPlayerStateEntry::TStateIndex CPlayerStateEntry::Root( CPlayer& player, const SStateEvent& event )
{
	const EPlayerStateEvent eventID = static_cast<EPlayerStateEvent> (event.GetEventId());
	switch( eventID )
	{
	case PLAYER_EVENT_ENTRY_PLAYER:
		RequestTransitionState(player, PLAYER_STATE_MOVEMENT);
		break;
	case PLAYER_EVENT_ENTRY_AI:
		RequestTransitionState(player, PLAYER_STATE_AIMOVEMENT);
		break;
	}

	return State_Continue;
}

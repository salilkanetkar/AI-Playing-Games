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

#ifndef __TURRET_BEHAVIOR_EVENTS__H__
#define __TURRET_BEHAVIOR_EVENTS__H__

#include "State.h"

struct HitInfo;

enum ETurretStates
{
	eTurretState_Behavior = STATE_FIRST,
};


enum ETurretBehaviorEvent
{
	STATE_EVENT_TURRET_PRE_PHYSICS_UPDATE = STATE_EVENT_CUSTOM,
	STATE_EVENT_TURRET_HIT,
	STATE_EVENT_TURRET_FORCE_STATE,
	STATE_EVENT_TURRET_HACK_FAIL,
};



struct SStateEventPrePhysicsUpdate
	: public SStateEvent
{
	SStateEventPrePhysicsUpdate( const float frameTimeSeconds )
		: SStateEvent( STATE_EVENT_TURRET_PRE_PHYSICS_UPDATE )
	{
		AddData( frameTimeSeconds );
	}

	float GetFrameTimeSeconds() const { return GetData( 0 ).GetFloat(); }
};



struct SStateEventHit
	: public SStateEvent
{
	SStateEventHit( const HitInfo* pHit )
		: SStateEvent( STATE_EVENT_TURRET_HIT )
	{
		CRY_ASSERT( pHit );
		AddData( pHit );
	}

	const HitInfo* GetHit() const { return static_cast< const HitInfo* >( GetData( 0 ).GetPtr() ); }
};



struct SStateEventForceState
	: public SStateEvent
{
	SStateEventForceState( ETurretBehaviorState forcedState )
		: SStateEvent( STATE_EVENT_TURRET_FORCE_STATE )
	{
		AddData( forcedState );
	}

	ETurretBehaviorState GetForcedState() const { return static_cast< ETurretBehaviorState >( GetData( 0 ).GetInt() ); }
};



struct SStateEventHackFail
	: public SStateEvent
{
	SStateEventHackFail( const EntityId hackerEntityId )
		: SStateEvent( STATE_EVENT_TURRET_HACK_FAIL )
	{
		AddData( static_cast< int >( hackerEntityId ) );
	}

	EntityId GetHackerEntityId() const { return static_cast< EntityId >( GetData( 0 ).GetInt() ); }
};

#endif

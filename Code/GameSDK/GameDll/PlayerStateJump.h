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

// Description : Helper class for CStatePlayerMovement::StateJump


#pragma once

#ifndef __PlayerStateJump_h__
#define __PlayerStateJump_h__

#include "PlayerStateLedge.h"

#include "IPlayerEventListener.h"

#include "ActorDefinitions.h"

class CPlayer;

template<typename HOST>
class CStateHierarchy;

class CPlayerStateJump
{
public:

	enum EJumpState
	{
		JState_None,
		JState_Jump,
		JState_Falling,
		JState_Total
	};

	CPlayerStateJump();
	~CPlayerStateJump();

	void OnEnter( CPlayer& player );
	bool OnPrePhysicsUpdate( CPlayer& player, const bool isHeavyWeapon, const SActorFrameMovementParams &movement, float frameTime );
	void OnExit( CPlayer& player, const bool isHeavyWeapon );
	void OnFullSerialize( TSerialize ser, CPlayer& player );
	void OnJump( CPlayer& player, const bool isHeavyWeapon, const float fVerticalSpeedModifier );
	void OnFall( CPlayer& player );

	void SetJumpState(CPlayer &player, EJumpState jumpState);
	EJumpState GetJumpState() const;
	ILINE const float GetExpectedJumpEndHeight() const { return m_expectedJumpEndHeight; }
	ILINE const float GetStartFallingHeight() const { return m_startFallingHeight; }
	bool GetSprintJump() const { return m_bSprintJump; }

private:

	void StartJump(CPlayer& player, const bool isHeavyWeapon, const float fVerticalSpeedModifier );

	ILINE bool IsJumping() const { return m_jumpState != JState_None; }
	ILINE void OnRevive() { m_jumpState = JState_None; }
	void OnMPWeaponSelect( CPlayer& player ) { SetJumpState(player, JState_Jump); }

	void UpdateJumping( CPlayer& player, const bool isHeavyWeapon, const SActorFrameMovementParams& movement, float frameTime );
	void UpdateFalling( CPlayer& player, const bool isHeavyWeapon, const SActorFrameMovementParams& movement, float frameTime );

	bool UpdateCommon( CPlayer& player, const bool isHeavyWeapon, const Vec3 &move, float frameTime, Vec3* pDesiredVel );
	bool UpdateCommon( CPlayer& player, const bool isHeavyWeapon, const SActorFrameMovementParams &movement, float frameTime, Vec3* pDesiredVel );

	void GetDesiredVelocity( const Vec3 & move, const CPlayer &player, Vec3* pDesiredVel ) const;
	void FinalizeVelocity( CPlayer& player, const Vec3& newVelocity );

	void Land( CPlayer &player, const bool isHeavyWeapon, float frameTime );
	void Landed(CPlayer& player, const bool isHeavyWeapon, float fallSpeed);
	const Vec3 CalculateInAirJumpExtraVelocity( const CPlayer& player, const Vec3& desiredVelocity ) const;

	void OnSpecialMove( CPlayer &player, IPlayerEventListener::ESpecialMove specialMove );


	EJumpState		m_jumpState;
	mutable float	m_jumpLock;
	float			m_startFallingHeight;
	float			m_expectedJumpEndHeight;

	bool			m_firstPrePhysicsUpdate;
	bool			m_bSprintJump;
	
	class CPlayerJump *m_jumpAction;
};

#endif //__PlayerStateJump_h__

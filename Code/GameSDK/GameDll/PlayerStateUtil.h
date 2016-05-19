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

// Description : Utility functions for the playerstate

#ifndef __PlayerStateUtil_h__
#define __PlayerStateUtil_h__

#pragma once

class CPlayer;
struct SActorFrameMovementParams;
struct pe_status_living;
struct SCharacterMoveRequest;
struct SStateEvent;
struct SActorPhysics;

class CPlayerStateUtil
{
public:

	static void CalculateGroundOrJumpMovement( const CPlayer& player, const SActorFrameMovementParams &movement, const bool bBigWeaponRestrict, Vec3 &move );
	static bool IsOnGround( CPlayer& player );
	static bool GetPhysicsLivingStat( const CPlayer& player, pe_status_living *livStat );
	static void AdjustMovementForEnvironment( const CPlayer& player, Vec3& movement, const bool bigWeaponRestrict, const bool crouching );
	static void PhySetFly( CPlayer& player );
	static void PhySetNoFly( CPlayer& player, const Vec3& gravity );
	static bool ShouldJump( CPlayer& player, const SActorFrameMovementParams& movement );
	static void RestorePlayerPhysics( CPlayer& player );
	static void UpdatePlayerPhysicsStats( CPlayer& player, SActorPhysics& actorPhysics, float frameTime );
	static void ProcessTurning( CPlayer& player, float frameTime );
	static void InitializeMoveRequest( SCharacterMoveRequest& frameRequest );
	static void FinalizeMovementRequest( CPlayer& player, const SActorFrameMovementParams & movement, SCharacterMoveRequest& frameRequest );
	static void UpdateRemotePlayersInterpolation( CPlayer& player, const SActorFrameMovementParams& movement, SCharacterMoveRequest& frameRequest );
	static bool IsMovingForward( const CPlayer& player, const SActorFrameMovementParams& movement );
	static bool ShouldSprint( const CPlayer& player, const SActorFrameMovementParams& movement, IItem* pCurrentPlayerItem );
	static void ApplyFallDamage( CPlayer& player, const float startFallingHeight, const float startJumpHeight );
	static bool DoesArmorAbsorptFallDamage(CPlayer& player, const float downwardsImpactSpeed, float& absorptedDamageFraction);
	static void CancelCrouchAndProneInputs(CPlayer & player);
	static void ChangeStance( CPlayer& player, const SStateEvent& event );

private:

	// DO NOT IMPLEMENT
	CPlayerStateUtil();
	CPlayerStateUtil( const CPlayerStateUtil& );
	CPlayerStateUtil& operator=( const CPlayerStateUtil& );
};

#endif// __PlayerStateUtil_h__

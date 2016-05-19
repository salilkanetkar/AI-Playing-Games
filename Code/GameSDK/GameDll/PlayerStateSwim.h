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
// Description : Implements the Player swim state

#ifndef __PlayerStateSwim_h__
#define __PlayerStateSwim_h__

#include "Audio/AudioSignalPlayer.h"

struct SActorFrameMovementParams;
class CPlayer;
class CPlayerStateSwim_WaterTestProxy;
class CPlayerStateSwim
{
public:
	static void SetParamsFromXml(const IItemParamsNode* pParams) 
	{
		ScopedSwitchToGlobalHeap useGlobalHeap;
		GetSwimParams().SetParamsFromXml( pParams );
	}

	CPlayerStateSwim();

	void OnEnter( CPlayer& player );
	bool OnPrePhysicsUpdate( CPlayer& player, const SActorFrameMovementParams& movement, float frameTime );
	void OnUpdate( CPlayer& player, float frameTime );
	void OnExit( CPlayer& player );

	static void UpdateSoundListener( CPlayer &player );

	bool DetectJump(CPlayer& player, const SActorFrameMovementParams& movement, float frameTime, float* pVerticalSpeedModifier) const;

private:
	
	CAudioSignalPlayer m_enduranceSpeedSwimSound;

	Vec3 m_gravity;
	float m_lastWaterLevel;
	float m_lastWaterLevelTime;
	float m_verticalVelDueToSurfaceMovement; // e.g. waves.
	float m_headUnderWaterTimer;
	bool m_onSurface;
	bool m_enduranceSwimSoundPlaying;

	void PlayEnduranceSound( const EntityId ownerId );
	void StopEnduranceSound( const EntityId ownerId );

	struct CSwimmingParams
	{
		CSwimmingParams() 
			: m_swimSpeedSprintSpeedMul(2.5f)
			, m_swimUpSprintSpeedMul(2.0f)
			, m_swimSprintSpeedMul(1.4f)
			, m_stateSwim_animCameraFactor(0.25f)
			, m_swimDolphinJumpDepth(0.1f)
			,	m_swimDolphinJumpThresholdSpeed(3.0f)
			, m_swimDolphinJumpSpeedModification(0.0f)
		{}
		void SetParamsFromXml(const IItemParamsNode* pParams);

		float m_swimSpeedSprintSpeedMul;
		float m_swimUpSprintSpeedMul;
		float m_swimSprintSpeedMul;
		float m_stateSwim_animCameraFactor;

		float m_swimDolphinJumpDepth;
		float m_swimDolphinJumpThresholdSpeed;
		float m_swimDolphinJumpSpeedModification;
	};

	static CSwimmingParams s_swimParams;
	static CSwimmingParams& GetSwimParams() { return s_swimParams; }

	// DO NOT IMPLEMENT!
	CPlayerStateSwim( const CPlayerStateSwim& );
	CPlayerStateSwim& operator=( const CPlayerStateSwim& );
};

#endif // __PlayerStateSwim_h__

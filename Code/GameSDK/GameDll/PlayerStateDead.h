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

// Description : Implements the Player ledge state


#ifndef __PlayerStateDead_h__
#define __PlayerStateDead_h__

#pragma once

class CPlayer;
class CPlayerStateMachine;
struct SActorFrameMovementParams;
class CPlayerStateDead
{
	enum EAICorpseUpdateStatus
	{
		eCorpseStatus_WaitingForSwap = 0,
		eCorpseStatus_SwapDone
	};

public:

	struct UpdateCtx
	{
		float frameTime;
	};

	 CPlayerStateDead();
	~CPlayerStateDead();

	void OnEnter( CPlayer& player);
	void OnLeave( CPlayer& player );
	void OnPrePhysicsUpdate( CPlayer& player, const SActorFrameMovementParams& movement, float frameTime );
	void OnUpdate( CPlayer& player, const CPlayerStateDead::UpdateCtx& updateCtx  );
	void Serialize( TSerialize& serializer );

protected:
	void UpdateAICorpseStatus( CPlayer& player, const CPlayerStateDead::UpdateCtx& updateCtx );

private:
	float m_swapToCorpseTimeout;
	EAICorpseUpdateStatus m_corpseUpdateStatus;
};

#endif // __PlayerStateDead_h__

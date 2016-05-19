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

// Description : The player on ground state.


#ifndef __PlayerStateGround_h__
#define __PlayerStateGround_h__

class CPlayer;
class CPlayerMovementAction;
struct SActorFrameMovementParams;
class CPlayerStateGround
{
public:
	CPlayerStateGround();

	void OnEnter( CPlayer& player );
	void OnPrePhysicsUpdate( CPlayer& player, const SActorFrameMovementParams &movement, float frameTime, const bool isHeavyWeapon, const bool isPlayer );
	void OnUpdate( CPlayer& player, float frameTime );
	void OnExit( CPlayer& player );

private:

	bool m_inertiaIsZero;

	void ProcessAlignToTarget(const CAutoAimManager& autoAimManager, CPlayer& player, const IActor* pTarget);
	bool CheckForVaultTrigger(CPlayer & player, float frameTime);
};

#endif // __PlayerStateGround_h__

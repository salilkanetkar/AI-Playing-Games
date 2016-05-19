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

// Description : Implements the Player fly state

#ifndef __PlayerStateFly_h__
#define __PlayerStateFly_h__

#include "UI/HUD/HUDEventDispatcher.h"

class CPlayer;
struct SActorFrameMovementParams;
class CPlayerStateFly
{
public:
	CPlayerStateFly();

	void OnEnter( CPlayer& player );
	bool OnPrePhysicsUpdate( CPlayer& player, const SActorFrameMovementParams &movement, float frameTime );
	void OnExit( CPlayer& player );

private:

	uint8 m_flyMode;
	float m_flyModeDisplayTime;
	void ProcessFlyMode( CPlayer& player, const SActorFrameMovementParams &movement );

};

class CPlayerStateSpectate : public CPlayerStateFly, public IHUDEventListener
{
private:
	#define STAY_FADED_TIME 0.5f

	typedef CPlayerStateFly inherited;

	float m_fFadeOutAmount;
	float m_fFadeForTime;

public:
	CPlayerStateSpectate();
	void ResetFadeParameters() { m_fFadeOutAmount = 1.0f; m_fFadeForTime = STAY_FADED_TIME; }

	virtual void OnHUDEvent(const SHUDEvent& event);

	void OnEnter( CPlayer& player );
	void UpdateFade( float frameTime );
	void OnExit( CPlayer& player );

protected:
	void DrawSpectatorFade();
};

#endif // __PlayerStateFly_h__

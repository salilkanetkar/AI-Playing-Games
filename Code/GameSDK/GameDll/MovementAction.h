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

#ifndef __MOVEMENT_ACTION_H__
#define __MOVEMENT_ACTION_H__

#include "PlayerAnimation.h"

class CPlayer;
struct SActorFrameMovementParams;
struct SCharacterMoveRequest;

class CPlayerBackgroundAction : public TPlayerAction
{
public:

	DEFINE_ACTION("BackgroundAction");

	CPlayerBackgroundAction(int priority, FragmentID id);

	virtual EStatus Update(float timePassed);

};


class CPlayerJump : public TPlayerAction
{
public:

	DEFINE_ACTION("PlayerJump");

	CPlayerJump(FragmentID fragID, int priority)
		:
	TPlayerAction(priority, fragID)
	{
	}

	void TriggerExit()
	{
		m_eStatus = IAction::Finished;
	}


protected:
};

class CPlayerMovementAction : public TPlayerAction
{
public:

	DEFINE_ACTION("PlayerMovement");

	enum EMoveState
	{
		Stand,
		Turn,
		Move,
		InAir,
		Total
	};

	CPlayerMovementAction(int priority);

	void TriggerExit()
	{
		m_eStatus = IAction::Finished;
	}

	virtual void Enter();
	virtual void Exit();

	virtual void OnInitialise();
	virtual EStatus Update(float timePassed);
	virtual EStatus	UpdatePending(float timePassed);
	virtual void OnFragmentStarted();

protected:

	EMoveState CalculateState(float *pTurnAngle = NULL, float *pTravelAngle = NULL, float *pMoveSpeed = NULL);
	void SetState(EMoveState newMoveState);

	int		m_AAID[Total];
	Vec3  m_lastAimDir;

	EMoveState m_moveState;
	EMoveState m_installedMoveState;

	float m_lastTurnDirection;
	float m_lastTravelAngle;
	float m_lastMoveSpeed;

	float m_travelAngleSmoothRateQTX;
	float m_moveSpeedSmoothRateQTX;

	float m_FPTurnSpeed;
	float m_FPTurnSpeedSmoothRateQTX;

	bool m_spinning;
	bool m_smoothMovement;
};

#endif //__MOVEMENT_ACTION_H__

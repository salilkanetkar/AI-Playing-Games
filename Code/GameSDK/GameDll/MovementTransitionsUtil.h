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

// Description : Utility class(es) for movementtransitions system


#pragma once
#ifndef __MOVEMENT_TRANSITIONS_UTIL_H
#define __MOVEMENT_TRANSITIONS_UTIL_H


struct STransitionFuture
{
	STransitionFuture() 
	: vMoveDirection(ZERO)
	, qOrientation(IDENTITY)
	, speed(-1)
	, vMoveTarget(ZERO)
	, hasMoveTarget(false)
 {}

	Vec3  vMoveDirection; // normalized movement direction at the end of the transition
	Quat  qOrientation;   // orientation at the end of the transition
	float speed;          // movement speed at the end of the transition
	Vec3  vMoveTarget;    // movement target at the time of selecting the transition
	bool  hasMoveTarget;  // vMoveTarget is valid only if this parameter is true
};


struct SMovementTransitionsSample
{
	float time;
	float pseudoSpeed;
	Vec3  moveDirection;
	Vec3  desiredVelocity;
	Vec3  bodyDirection;

	void Reset()
	{
		time = 0.0f;
		pseudoSpeed = 0.0f;
		moveDirection.Set(0,0,0);
		desiredVelocity.Set(0,0,0);
		bodyDirection.Set(0,0,0);
	}
};

#endif // __MOVEMENT_TRANSITIONS_UTIL_H

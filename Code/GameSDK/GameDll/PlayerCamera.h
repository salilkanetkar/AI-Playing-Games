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

// Description : Controls player camera update (Refactored from PlayerView)

#pragma once

#ifndef _PLAYER_CAMERA_H_
#define _PLAYER_CAMERA_H_

#include "ICameraMode.h"

class CPlayer;

class CPlayerCamera
{
public:

	CPlayerCamera(const CPlayer & ownerPlayer);
	~CPlayerCamera();

	bool Update(SViewParams& viewParams, float frameTime);
	void SetCameraMode(ECameraMode newMode, const char * why);
	void SetCameraModeWithAnimationBlendFactors(ECameraMode newMode, const ICameraMode::AnimationSettings& animationSettings, const char* why);

	void PostUpdate(const QuatT &camDelta);

	ILINE bool IsTransitioning() const
	{
		return (m_transitionTime > 0.0f);
	}

private:
	ECameraMode GetCurrentCameraMode();
	void UpdateCommon(SViewParams& viewParams, float frameTime);
	void FilterGroundOnlyShakes(SViewParams& viewParams);

	void UpdateTotalTransitionTime();

	// No need to use a dynamic container (eg. vector) as we know exactly how many modes there are going to be... [TF]
	ICameraMode * m_cameraModes[eCameraMode_Last];
	ECameraMode m_currentCameraMode;
	ECameraMode m_previousCameraMode;
	const CPlayer & m_ownerPlayer;

	float		m_transitionTime;
	float		m_totalTransitionTime;
	ECameraMode m_transitionCameraMode;

	bool m_enteredPartialAnimControlledCameraOnLedge;
};

#endif
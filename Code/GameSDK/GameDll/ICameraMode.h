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

// Description : Camera mode interface, enums, etc


#pragma once

#ifndef _ICAMERA_MODE_H_
#define _ICAMERA_MODE_H_

#include "AutoEnum.h"

#define CameraModeList(f)            \
	f(eCameraMode_Default)             \
	f(eCameraMode_SpectatorFollow)     \
	f(eCameraMode_SpectatorFixed)      \
	f(eCameraMode_AnimationControlled) \
	f(eCameraMode_Death)               \
	f(eCameraMode_Death_SinglePlayer)	 \
	f(eCameraMode_Vehicle)             \
	f(eCameraMode_PartialAnimationControlled)					 \

AUTOENUM_BUILDENUMWITHTYPE_WITHINVALID_WITHNUM(ECameraMode, CameraModeList, eCameraMode_Invalid, eCameraMode_Last);

class CPlayer;
struct SViewParams;

struct ICameraMode
{
	struct AnimationSettings
	{
		AnimationSettings()
			: positionFactor(0.0f)
			, rotationFactor(0.0f)
			,	applyResult(false)
			, stableBlendOff(false)
		{

		}

		float positionFactor;
		float rotationFactor;
		bool  applyResult;
		bool  stableBlendOff;
	};

	ICameraMode();
	virtual ~ICameraMode();

	void ActivateMode(const CPlayer & clientPlayer);
	void DeactivateMode(const CPlayer & clientPlayer);

	virtual bool UpdateView(const CPlayer& clientPlayer, SViewParams& viewParams, float frameTime) = 0;
	
	virtual bool CanTransition();
	virtual void SetCameraAnimationFactor(const AnimationSettings& animationSettings);
	virtual void GetCameraAnimationFactor(float &pos, float &rot);

	ILINE const bool IsBlendingOff() const
	{
		return m_isBlendingOff;
	}

protected:
	virtual void Activate(const CPlayer & clientPlayer);
	virtual void Deactivate(const CPlayer & clientPlayer);

	void SetDrawNearestFlag(const CPlayer & clientPlayer, bool bSetDrawNearestFlag);

	bool m_isBlendingOff;
	bool m_disableDrawNearest;
};

#endif

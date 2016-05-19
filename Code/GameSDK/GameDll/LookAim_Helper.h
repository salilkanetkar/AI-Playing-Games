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

// Description : Helper class for setting up and updating Looking and Aiming


#pragma once

#ifndef _LOOKAIM_HELPER_H_
#define _LOOKAIM_HELPER_H_

#include <ICryAnimation.h>
#include "Animation/PoseModifier/LookAtSimple.h"

class CPlayer;


class CLookAim_Helper
{
public:
	CLookAim_Helper();

	void UpdateLook(CPlayer* pPlayer, ICharacterInstance* pCharacter, bool bEnabled, f32 FOV, const Vec3& LookAtTarget, const uint32 lookIKLayer);
	void UpdateDynamicAimPoses(CPlayer* pPlayer, ICharacterInstance* pCharacter, const struct SActorParams& params, const bool aimEnabled, const int32 aimIKLayer, const Vec3& vAimTarget, const struct SMovementState& curMovementState);

	void Reset()
	{
		m_initialized = false;
	}

	bool CanHandFire(int hand) const { return 0 != (m_availableHandsForFiring & (1 << hand)); }

private:

	void Init(CPlayer* pPlayer, ICharacterInstance* pCharacter);

	bool m_initialized;

	// Looking
	bool m_canUseLookAtComplex;
	bool m_canUseLookAtSimple;
	boost::shared_ptr<AnimPoseModifier::CLookAtSimple> m_lookAtSimple;
	float m_lookAtWeight; // only used for LookAtSimple now as old LookIK also does this
	float m_lookAtFadeInSpeed; // only used for LookAtSimple now as old LookIK also does this
	float m_lookAtFadeOutSpeed; // only used for LookAtSimple now as old LookIK also does this
	Vec3 m_lookAtInterpolatedTargetGlobal; // only used for LookAtSimple now as old LookIK also does this
	Vec3 m_lookAtTargetRate; // for generating smooth motion
	Vec3 m_lookAtTargetGlobal; // only used for LookAtSimple now as old LookIK also does this
	float m_lookAtTargetSmoothTime; // only used for LookAtSimple now as old LookIK also does this

	// Aiming
	int m_availableHandsForFiring; // flags where bit i represents hand IItem::eItemHand
	int m_lastAimPoseAnimID;
	float m_lastAimYaw;
	bool m_aimIsSwitchingArms;
	Vec3 m_vLastAimTarget;
};

#endif
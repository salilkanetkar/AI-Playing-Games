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

#pragma once

#ifndef _WEAPON_STRAFE_OFFSET_H_
#define _WEAPON_STRAFE_OFFSET_H_

#include "WeaponLookOffset.h"



class CStrafeOffset
{
public:
	CStrafeOffset();

	void SetStaticParams(const SStaticWeaponSwayParams& params);
	void SetGameParams(const SGameWeaponSwayParams& params);

	QuatT Compute(float frameTime);

private:
	SStaticWeaponSwayParams m_staticParams;
	SGameWeaponSwayParams m_gameParams;

	Vec3  m_smoothedVelocity;
	Vec3  m_lastVelocity;
	float m_interpFront;
	float m_interpSide;
	float m_runFactor;
	float m_sprintFactor;
	float m_noiseFactor;
};



#endif

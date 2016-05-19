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

#ifndef _WEAPON_BUMP_OFFSET_H_
#define _WEAPON_BUMP_OFFSET_H_

struct SParams_WeaponFPAiming;

class CBumpOffset
{
public:
	CBumpOffset();

	QuatT Compute(float frameTime);

	void AddBump(QuatT direction, float attackTime, float releaseTime, float reboundIntensity);

private:
	QuatT ComputeBump(float frameTime);

	QuatT m_direction;
	float m_attackTime;
	float m_releaseTime;
	float m_rebounceIntensity;
	float m_time;
};


#endif

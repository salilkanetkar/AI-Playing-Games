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

#include "StdAfx.h"
#include "WeaponBumpOffset.h"
#include "Utility/Hermite.h"



CBumpOffset::CBumpOffset()
	:	m_direction(IDENTITY)
	,	m_attackTime(0.0f)
	,	m_releaseTime(0.0f)
	,	m_rebounceIntensity(0.0f)
	,	m_time(-1.0f)
{
}



QuatT CBumpOffset::Compute(float frameTime)
{
	QuatT result = QuatT(IDENTITY);

	if (m_time >= 0.0f)
	{
		if (m_time <= m_attackTime + m_releaseTime)
			result = ComputeBump(frameTime);
		else
			m_time = -1.0f;
	}

	return result;
}




void CBumpOffset::AddBump(QuatT direction, float attackTime, float releaseTime, float reboundIntensity)
{
	m_direction = direction;
	m_attackTime = attackTime;
	m_releaseTime = releaseTime;
	m_rebounceIntensity = reboundIntensity;
	m_time = 0.0f;
}



QuatT CBumpOffset::ComputeBump(float frameTime)
{
	float intensity = 0.0f;

	if (m_time <= m_attackTime)
	{
		float t = m_time / m_attackTime;
		intensity = HermiteInterpolate(0.0f, 0.75f, 1.0f, 0.0f, t);
	}
	else
	{
		if (m_rebounceIntensity == 0.0f)
		{
			float t = (m_time-m_attackTime) / m_releaseTime;
			intensity = HermiteInterpolate(1.0f, 0.0f, 0.0f, 0.0f, t);
		}
		else
		{
			if (m_time <= m_attackTime + m_releaseTime * 0.5f)
			{
				float t =
					(m_time-m_attackTime) /
					(m_releaseTime * 0.5f);
				intensity = HermiteInterpolate(1.0f, 0.0f, -m_rebounceIntensity, 0.0f, t);
			}
			else
			{
				float t =
					(m_time-m_attackTime-m_releaseTime*0.5f) /
					(m_releaseTime * 0.5f);
				intensity = HermiteInterpolate(-m_rebounceIntensity, 0.0f, 0.0f, 0.0f, t);
			}
		}
	}

	m_time += frameTime;

	QuatT result = QuatT(IDENTITY);

	if (intensity != 0.0f)
	{
		result.t = m_direction.t * intensity;
		result.q = Quat::CreateSlerp(Quat(IDENTITY), m_direction.q, intensity);
	}

	return result;
}

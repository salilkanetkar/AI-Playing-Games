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
#include "Wiggle.h"
#include "Hermite.h"



CWiggle::CWiggle()
	:	m_frequency(1.0f)
	,	m_time(0.0f)
{
	m_points[0] = cry_random(-1.0f, 1.0f);
	m_points[1] = cry_random(-1.0f, 1.0f);
	m_points[2] = cry_random(-1.0f, 1.0f);
	m_points[3] = cry_random(-1.0f, 1.0f);
}



void CWiggle::SetParams(float frequency)
{
	m_frequency = frequency;
}



float CWiggle::Update(float deltaTime)
{
	m_time += deltaTime * m_frequency;
	while (m_time > 1.0f)
	{
		m_points[0] = m_points[1];
		m_points[1] = m_points[2];
		m_points[2] = m_points[3];
		m_points[3] = cry_random(-1.0f, 1.0f);
		m_time -= 1.0f;
	}

	return CatmullRom(
		m_points[0], m_points[1],
		m_points[2], m_points[3],
		m_time);
}





void CWiggleVec3::SetParams(float frequency)
{
	m_x.SetParams(frequency);
	m_y.SetParams(frequency);
	m_z.SetParams(frequency);
}



Vec3 CWiggleVec3::Update(float deltaTime)
{
	return Vec3(
		m_x.Update(deltaTime),
		m_y.Update(deltaTime),
		m_z.Update(deltaTime));
}

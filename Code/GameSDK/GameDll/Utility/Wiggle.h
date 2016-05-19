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

#ifndef __WIGGLE__H__
#define __WIGGLE__H__


class CWiggle
{
public:
	CWiggle();

	void SetParams(float frequency);
	float Update(float deltaTime);

public:
	float m_points[4];
	float m_frequency;
	float m_time;
};



class CWiggleVec3
{
public:

	void SetParams(float frequency);
	Vec3 Update(float deltaTime);

private:
	CWiggle m_x, m_y, m_z;
};


#endif

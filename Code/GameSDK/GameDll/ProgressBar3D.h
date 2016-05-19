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

// Description : Basic encapsulation of a 3D Hud Progress bar


#ifndef __PROGRESSBAR3D_H_
#define __PROGRESSBAR3D_H_

#include "ProgressBar.h"

struct ProgressBar3DParams
{
	ProgressBar3DParams() : m_EntityId(0), m_Offset(ZERO)
	{
	}

	//If 0 then bar will simply be drawn about m_Offset
	EntityId m_EntityId;
	Vec3		 m_Offset;
	float		 m_height;
	float		 m_width;
};

class CProgressBar3D : public CProgressBar
{
public:
	CProgressBar3D();
	virtual ~CProgressBar3D();

	void Init(const ProgressBarParams& params, const ProgressBar3DParams& params3D); 
	void Render3D();
	void SetProgressValue(float zeroToOneProgress);

private:
	ProgressBar3DParams m_params3D;
};
#endif //__PROGRESSBAR3D_H_
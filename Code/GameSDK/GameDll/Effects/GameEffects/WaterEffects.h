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

// Description : Water related effects


#pragma once

#ifndef _WATER_GAME_EFFECTS_
#define _WATER_GAME_EFFECTS_

#include "GameEffect.h"
#include "Effects/GameEffectsSystem.h"

class CWaterGameEffects : public GameSDKCGameEffect
{
    typedef GameSDKCGameEffect BaseEffectClass;

public:
	CWaterGameEffects( );
	virtual ~CWaterGameEffects( );

	virtual void	Update(float frameTime);
	virtual const char* GetName() const;
	virtual void GetMemoryUsage( ICrySizer *pSizer ) const;

	void OnCameraComingOutOfWater( );

private:

	float m_waterDropletsAmount;
};

#endif // _WATER_GAME_EFFECTS_
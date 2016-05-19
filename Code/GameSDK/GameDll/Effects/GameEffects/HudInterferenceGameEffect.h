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

#ifndef _HUD_INTERFERENCE_GAME_EFFECT_
#define _HUD_INTERFERENCE_GAME_EFFECT_

#pragma once

// Includes
#include "GameEffect.h"
#include "Effects/GameEffectsSystem.h"

//==================================================================================================
// Name: CHudInterferenceGameEffect
// Desc: Manages hud interference - The effect needs to be managed in 1 global place to stop
//		   different game features fighting over setting the values
// Author: James Chilvers
//==================================================================================================
class CHudInterferenceGameEffect : public GameSDKCGameEffect
{
public:
	CHudInterferenceGameEffect();
	~CHudInterferenceGameEffect();

	virtual void	Initialise(const SGameEffectParams* gameEffectParams = NULL);
	virtual void	Update(float frameTime);

	virtual const char* GetName() const { return "Hud interference"; }

	// These need to be called every frame for it to take affect
	SC_API void					SetInterference(float interferenceScale,bool bInterferenceFilter);

private:

	Vec4		m_defaultInterferenceParams;
	float		m_interferenceScale;
	uint8		m_interferenceFilterFlags;

};//------------------------------------------------------------------------------------------------

#endif // _HUD_INTERFERENCE_GAME_EFFECT_

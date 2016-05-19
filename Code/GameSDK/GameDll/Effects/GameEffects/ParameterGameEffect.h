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

#ifndef _PARAMETER_GAME_EFFECT_
#define _PARAMETER_GAME_EFFECT_

#pragma once



// Includes
#include "GameEffect.h"
#include "Effects/GameEffectsSystem.h"

// Forward declarations

//==================================================================================================
// Name: CParameterGameEffect
// Desc: Manages the value of the game effects' parameters when more than one module is trying to
//			modify it at the same time
// Author: Sergi Juarez
//==================================================================================================
class CParameterGameEffect : public GameSDKCGameEffect
{
    DECLARE_TYPE(CParameterGameEffect, GameSDKCGameEffect); // Exposes this type for SoftCoding


public:
	CParameterGameEffect();

	
	virtual void	SetActive(bool isActive);
	virtual void	Update(float frameTime);
	virtual const char* GetName() const;
	        void	Reset();

//************************************************************************************
//		SATURATION EFFECT--
//************************************************************************************
public:
	enum ESaturationEffectUsage
	{
		eSEU_PreMatch = 0,
		eSEU_LeavingBattleArea,
		eSEU_PlayerHealth,
		eSEU_Intro,
		eSEU_NUMTYPES,
	};

	void SetSaturationAmount(const float fAmount, const ESaturationEffectUsage usage);

private:
	bool UpdateSaturation(float frameTime);
	void ResetSaturation();

private:
	struct SSaturationData 
	{
		float m_amount;

		SSaturationData(): m_amount(1.f){}
	};

	typedef CryFixedArray<SSaturationData, eSEU_NUMTYPES> TSaturationEffectExecutionData;
	TSaturationEffectExecutionData m_saturationExecutionData;
//************************************************************************************
//		--SATURATION EFFECT
//************************************************************************************


};

#endif // _SCENEBLUR_GAME_EFFECT_
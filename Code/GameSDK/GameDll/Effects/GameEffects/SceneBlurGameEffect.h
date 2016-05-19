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

#ifndef _SCENEBLUR_GAME_EFFECT_
#define _SCENEBLUR_GAME_EFFECT_

#pragma once

// Includes
#include "GameEffect.h"
#include "Effects/GameEffectsSystem.h"

// Forward declarations

//==================================================================================================
// Name: CSceneBlurGameEffect
// Desc: Manages effects for scene blur - The effect needs to be managed in 1 global place to stop
//		   different game features fighting over setting the values
// Author: Dean Claassen
//==================================================================================================
class CSceneBlurGameEffect : public GameSDKCGameEffect
{
    DECLARE_TYPE(CSceneBlurGameEffect, GameSDKCGameEffect); // Exposes this type for SoftCoding

public:
	enum EGameEffectUsage
	{
		eGameEffectUsage_InterestVideos = 0,
		eGameEffectUsage_SmokeManager,
		eGameEffectUsage_NUMTYPES,
	};

	#define NUMBLENDEDSCENEBLURUSAGES (1)

public:
	CSceneBlurGameEffect();
	~CSceneBlurGameEffect();

	// GameSDKCGameEffect
	virtual void	Initialise(const SGameEffectParams* gameEffectParams = NULL);
	virtual void	Release();
	virtual void	SetActive(bool isActive);

	virtual void	Update(float frameTime);

	virtual const char* GetName() const;

#if DEBUG_GAME_FX_SYSTEM
	static void  DebugOnInputEvent(int keyId);
	static void	 DebugDisplay(const Vec2& textStartPos,float textSize,float textYStep);
#endif

	static void LoadStaticData(IItemParamsNode* pRootNode);
	static void ReloadStaticData(IItemParamsNode* pRootNode);
	static void ReleaseStaticData();
	// ~GameSDKCGameEffect

	void SetBlurAmount(const float fAmount, const EGameEffectUsage usage);
	void SetBlurAmountFromData(const bool bEnable, const EGameEffectUsage usage);

private:
	enum EGameEffectBlendableState
	{
		eGameEffectBlendableState_None = 0,
		eGameEffectBlendableState_InitialDelay,
		eGameEffectBlendableState_BlendingTo,
		eGameEffectBlendableState_Hold,
		eGameEffectBlendableState_BlendingFrom,
	};

	struct SGameEffectExecutionData
	{
		SGameEffectExecutionData()
		: m_fBlurAmount(0.0f)
		, m_fUpdateTime(0.0f)
		, m_effectState(eGameEffectBlendableState_None)
		{
		}

		float m_fBlurAmount;
		float m_fUpdateTime;
		EGameEffectBlendableState m_effectState;
	};

	typedef CryFixedArray<SGameEffectExecutionData, eGameEffectUsage_NUMTYPES> TGameEffectExecutionData;
	TGameEffectExecutionData m_executionData;
};

#endif // _SCENEBLUR_GAME_EFFECT_

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

#ifndef _KILL_CAM_GAME_EFFECT_
#define _KILL_CAM_GAME_EFFECT_

#pragma once

// Includes
#include "GameEffect.h"
#include "Effects/GameEffectsSystem.h"
#include "Effects/HUDEventListeners/LetterBoxHudEventListener.h"
#include "Effects/Tools/CVarActivationSystem.h"
#include "Effects/Tools/PostEffectActivationSystem.h"

//==================================================================================================
// Name: CKillCamGameEffect
// Desc: Kill Cam visual effect
// Author: James Chilvers
//==================================================================================================
class CKillCamGameEffect : public GameSDKCGameEffect
{
    DECLARE_TYPE(CKillCamGameEffect, GameSDKCGameEffect); // Exposes this type for SoftCoding

private:
	//--------------------------------------------------------------------------------------------------
	// Name: SKillCamGameEffectData
	// Desc: Data loaded from xml to control kill cam game effect
	//--------------------------------------------------------------------------------------------------
	struct SEffectData
	{
		SEffectData()
		{
			baseContrast = 1.f;
			baseBrightness = 1.f;
			isInitialised = false;
		}

		CCVarActivationSystem cvarActivationSystem;
		CPostEffectActivationSystem postEffectActivationSystem;
		SLetterBoxParams letterBox;
		float chromaFadeTimeInv;
		float fadeOutTimeInv;
		float baseContrast;
		float baseBrightness;
		bool isInitialised;
	};

public:
	enum EKillCamEffectMode
	{
		eKCEM_KillCam=0,
		eKCEM_KillerCam,
		eKCEM_IntroCam,
		eKCEM_TotalModes
	};

public:
	CKillCamGameEffect();
	~CKillCamGameEffect();

	virtual void	Initialise(const SGameEffectParams* gameEffectParams = NULL);
	virtual void	Release();
	virtual void	SetActive(bool isActive);
	virtual void	Update(float frameTime);

	virtual const char* GetName() const;

	ILINE void SetCurrentMode(EKillCamEffectMode mode) { if(m_currentMode!=mode && IsFlagSet(GAME_EFFECT_ACTIVE)){ SetActive(false); } m_currentMode=mode; }
	ILINE void SetActiveIfCurrentMode(EKillCamEffectMode mode, bool active) { if( m_currentMode==mode ) { SetActive(active); } }

	ILINE void SetRemainingTime( const float remainingTime ) { m_remainingTime = remainingTime; }
	ILINE float GetFadeOutTimeInv( ) const { return s_data[m_currentMode].fadeOutTimeInv; }

#if DEBUG_GAME_FX_SYSTEM
	static void  DebugOnInputEvent(int keyId);
	static void	 DebugDisplay(const Vec2& textStartPos,float textSize,float textYStep);
#endif
	static void LoadStaticData(IItemParamsNode* rootNode);
	static void ReloadStaticData(IItemParamsNode* rootNode);
	static void ReleaseStaticData();

	static float GetBaseBrightness(const EKillCamEffectMode mode) { return s_data[mode].baseBrightness; }
	static float GetBaseContrast(const EKillCamEffectMode mode) { return s_data[mode].baseContrast; }

private:
	static void LoadStaticModeData(const IItemParamsNode* paramNode, SEffectData& data);

	void Start();
	void Stop();

	CLetterBoxHudEventListener m_letterBox[eKCEM_TotalModes];
	EKillCamEffectMode m_currentMode;
	float m_activeTime;
	float m_remainingTime;
	float m_originalBrightness;

	static SEffectData s_data[eKCEM_TotalModes];
};//------------------------------------------------------------------------------------------------

struct SKillCamGameEffectParams : public SGameEffectParams
{
	SKillCamGameEffectParams()
	{
		autoUpdatesWhenActive = false;
	}
};//------------------------------------------------------------------------------------------------

#endif // _KILL_CAM_GAME_EFFECT_

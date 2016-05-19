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

// Description : Continuous health effect running for the local player

#pragma once

#ifndef _PLAYERHEALTH_GAME_EFFECT_
#define _PLAYERHEALTH_GAME_EFFECT_

#include "GameEffect.h"
#include "IMaterialEffects.h"
#include "Effects/GameEffectsSystem.h"

class CActor;
DECLARE_BOOST_POINTERS(CActor);

class CParameterGameEffect;

class CPlayerHealthGameEffect : public GameSDKCGameEffect
{
    typedef GameSDKCGameEffect BaseEffectClass;

public:
	struct SQueuedHit
	{
		SQueuedHit()
			: m_valid(false)
			, m_hitDirection(FORWARD_DIRECTION)
			, m_hitStrength(0.0f)
			, m_hitSpeed(1.0f)
		{

		}

		ILINE void Validate() { m_valid = true; }
		ILINE void Invalidate() { m_valid = false; }
		ILINE bool IsValid() const { return m_valid; }

		Vec3	m_hitDirection;
		float	m_hitStrength;
		float	m_hitSpeed;
	
	private:
		bool	m_valid;
	};

public:
	CPlayerHealthGameEffect();

	virtual void	Initialise(const SGameEffectParams* gameEffectParams = NULL);
	virtual void	Update(float frameTime);
	virtual void	SetActive(bool isActive);

	void InitialSetup(CActor* pClientActor);

	ILINE void SetKillCamData(const EntityId id, const float brightness, const float contrast) {m_killerId = id; m_baseBrightness = brightness; m_baseContrast = contrast; } // For killcam replay

	void ReStart();
	void Start();
	void Stop();
	void OnKill();
	void OnHit(const Vec3& hitDirection, const float hitStrength, const float hitSpeed);

	void EnableExternalControl( bool enable );
	void ExternalSetEffectIntensity( float intensity );

	virtual void GetMemoryUsage( ICrySizer *pSizer ) const
	{
		pSizer->AddObject(this, sizeof(*this));	
	}

	virtual const char* GetName() const { return "Player Health"; }

	static void LoadStaticData(IItemParamsNode* pRootNode);
	static void ReloadStaticData(IItemParamsNode* pRootNode);
	static void ReleaseStaticData();

private:
	void UpdateHealthReadibility(float effectIntensity, float frameTime);

	TMFXEffectId							m_playerHealthEffectId;
	TMFXEffectId							m_playerDeathEffectId;
	CActorWeakPtr							m_clientActor;

	SQueuedHit								m_lastRegisteredHit;
	EntityId									m_killerId; // For killcam replay
	_smart_ptr<ITexture>					m_blurMaskTexture;

	float									m_screenBloodIntensity;
	float									m_radialBlurIntensity;
	float									m_radialBlurTime;
	float									m_lastEffectIntensity;
	float									m_lastRadialBlurIntensity;

	float									m_baseContrast;
	float									m_baseBrightness;

	float									m_externallySetEffectIntensity;

	bool									m_useNewEffect;
	bool									m_useBlurMask;
	bool									m_isExternallyControlled;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

struct SPlayerHealthGameEffectParams : public SGameEffectParams
{
	SPlayerHealthGameEffectParams()
		: playerHealthEffectId(InvalidEffectId)
		, playerDeathEffectId(InvalidEffectId)
		, pClientActor(NULL)
	{
		
	}

	TMFXEffectId		playerHealthEffectId;
	TMFXEffectId		playerDeathEffectId;
	CActor*					pClientActor;
};

#endif // _PLAYERHEALTH_GAME_EFFECT_
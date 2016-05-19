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

#ifndef _EXPLOSION_SCREEN_GAME_EFFECT_
#define _EXPLOSION_SCREEN_GAME_EFFECT_

#pragma once

// Includes
#include "GameEffect.h"
#include "Effects/GameEffectsSystem.h"

// Forward declares
struct SExplosionContainer;

class CDeferredExplosionEffect
{

public:

	enum EDeferredEffectType
	{
		eDET_RadialBlur = 0,
	};

private:

	struct SQueuedRayInfo
	{
		SQueuedRayInfo()
			: explosionPos(ZERO)
			, rayID(0)
			, effectType(eDET_RadialBlur)
			, request(0)
		{

		}

		Vec3				explosionPos;
		QueuedRayID			rayID;
		EDeferredEffectType effectType;
		float				distance;
		float				effectMaxDistance;
		uint32				request;
	};

public:

	CDeferredExplosionEffect()
		: m_requestCounter(0)
	{

	}

	~CDeferredExplosionEffect();

	void RequestRayCast(CDeferredExplosionEffect::EDeferredEffectType effectType, const Vec3 &startPos, const Vec3 &dir, float distance, float effectMaxDistance, int objTypes, int flags, IPhysicalEntity **pSkipEnts, int nSkipEnts); 
	void OnRayCastDataReceived(const QueuedRayID& rayID, const RayCastResult& result);

private:

	int FindRequestedRay(const QueuedRayID& rayID) const;
	void FreeOldestRequestIfNeeded();

	void TriggerRadialBlur(const Vec3& radialBlurCenter, float maxBlurDistance, float distance);

	const static int kMaxQueuedRays = 4;
	CryFixedArray<SQueuedRayInfo, kMaxQueuedRays> m_queuedRays;

	uint32		m_requestCounter;						
};

//==================================================================================================
// Name: CExplosionGameEffect
// Desc: Explosion game effect
// Author: James Chilvers
//==================================================================================================
class CExplosionGameEffect : public GameSDKCGameEffect
{
public:
	CExplosionGameEffect();
	~CExplosionGameEffect();

	void	Initialise(const SGameEffectParams* gameEffectParams = NULL);
	void	Release();
	void	Update(float frameTime);

	void	Explode(SExplosionContainer &explosionContainer);
	void	SetCutSceneActive(bool isCutSceneActive) { m_cutSceneActive = isCutSceneActive; }

#if DEBUG_GAME_FX_SYSTEM
	static void  DebugOnInputEvent(int keyId);
	static void	 DebugDisplay(const Vec2& textStartPos,float textSize,float textYStep);
#endif
	
	static void LoadStaticData(IItemParamsNode* pRootNode);
	static void ReloadStaticData(IItemParamsNode* pRootNode);
	static void ReleaseStaticData();

	const char* GetName() const { return "Explosion"; }

	void		SpawnMaterialEffect(const SExplosionContainer &explosionContainer);

	virtual void GetMemoryUsage( ICrySizer *pSizer ) const
	{
		pSizer->AddObject(this, sizeof(*this));	
	}
private:

	void		SpawnParticleEffect(const SExplosionContainer &explosionContainer);
	void		SpawnScreenExplosionEffect(const SExplosionContainer &explosionContainer);
	void		SpawnCharacterEffects(const SExplosionContainer &explosionContainer);
	void		QueueMaterialEffect(SExplosionContainer &explosionContainer);

	bool		IsPlayer();

	CDeferredExplosionEffect m_deferredScreenEffects;

	bool		m_cutSceneActive;

};//------------------------------------------------------------------------------------------------

//==================================================================================================
// Name: SExplosionGameEffectParams
// Desc: Explosion game effect parameters
// Author: James Chilvers
//==================================================================================================
struct SExplosionGameEffectParams : public SGameEffectParams
{
	SExplosionGameEffectParams()
	{
		
	}

};//------------------------------------------------------------------------------------------------

#endif // _EXPLOSION_SCREEN_GAME_EFFECT_

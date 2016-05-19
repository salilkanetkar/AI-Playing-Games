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

#ifndef __PROJECTILE_AUTOAIM_HELPER_H__
#define __PROJECTILE_AUTOAIM_HELPER_H__

#if !defined(_RELEASE)
#define ALLOW_PROJECTILEHELPER_DEBUGGING 1
#else
#define ALLOW_PROJECTILEHELPER_DEBUGGING 0
#endif

#include "FireModePlugin.h"

class CFireModePlugin_AutoAim : public CFireModePlugin<SFireModePlugin_AutoAimParams>
{
private:
	typedef CFireModePlugin<SFireModePlugin_AutoAimParams> Parent;
	typedef SFireModePlugin_AutoAimParams::SAutoAimModeParams ConeParams;

	struct STargetSelectionParams
	{
		STargetSelectionParams()
		{
			// Some sensible defaults
			m_distanceHeuristicWeighting	= 1.0f;
			m_angleHeuristicWeighting		= 2.0f;
			m_bDisableAutoAimIfPlayerAlreadyHasTarget = true;
			m_bDisableAutoAimIfPlayerIsZoomed = false;
		}

		// Settings for prioritizing target candidates based on distance (e.g. closer better) and/or how central the target is to the aiming reticule.
		float m_distanceHeuristicWeighting;
		float m_angleHeuristicWeighting;

		// If the player already has a target for themselves, do we still attempt to adjust projectile paths?
		bool  m_bDisableAutoAimIfPlayerAlreadyHasTarget;
		bool  m_bDisableAutoAimIfPlayerIsZoomed;
	};

public:
	CRY_DECLARE_GTI(CFireModePlugin_AutoAim);

public:
	CFireModePlugin_AutoAim();
	virtual ~CFireModePlugin_AutoAim();

	// CFireModePlugin
	virtual bool Init(CFireMode* pFiremode, IFireModePluginParams* pPluginParams);
	virtual void Activate(bool activate);
	virtual bool Update(float frameTime, uint32 frameId);
	virtual void AlterFiringDirection(const Vec3& firingPos, Vec3& rFiringDir) const;
	//~CFireModePlugin

	ILINE void SetEnabled(const bool bEnabled) {m_bEnabled = bEnabled;}
	ILINE bool GetEnabled() const {return m_bEnabled;}

private:
	// Adjust the given firing direction to potential targets based on current params
	void AdjustFiringDirection(const Vec3& attackerPos, Vec3& firingDirToAdjust, const bool bCurrentlyZoomed, const EntityId ownerId ) const;

	// Helpers
	IEntity* CalculateBestProjectileAutoAimTarget(const Vec3& attackerPos, const Vec3& attackerDir, const bool bCurrentlyZoomed, const EntityId ownerId) const;
	bool	 AllowedToTargetPlayer(const EntityId attackerId, const EntityId victimEntityId) const;
	bool	 TargetPositionWithinFrontalCone(const Vec3& attackerLocation,const Vec3& victimLocation,const Vec3& attackerFacingdir, const float targetConeRads, float& theta) const;

	ILINE const ConeParams& GetAimConeSettings(const bool bIsZoomed) const { return bIsZoomed ? m_pParams->m_zoomedParams : m_pParams->m_normalParams;}

	// Data
	STargetSelectionParams m_targetSelectionParams;
	bool m_bEnabled;

#if ALLOW_PROJECTILEHELPER_DEBUGGING
	mutable CryFixedStringT<128> m_lastShotAutoAimedStatus; 
	mutable CryFixedStringT<32>  m_lastTargetRejectionReason;
#endif //#if ALLOW_PROJECTILEHELPER_DEBUGGING
};

#endif //__PROJECTILE_AUTOAIM_HELPER_H__
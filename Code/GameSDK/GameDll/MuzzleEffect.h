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

#ifndef __MUZZLEEFFECT_H__
#define __MUZZLEEFFECT_H__

#if _MSC_VER > 1000
# pragma once
#endif

#include "EntityUtility/EntityEffects.h"

class CWeapon;
class CFireMode;
struct SFireModeParams;



class CMuzzleEffect
{
private:
	struct SMuzzleEffectInfo
	{
		EntityEffects::TAttachedEffectId mfId[2];

		SMuzzleEffectInfo()
		{
			mfId[0] = mfId[1] = 0;
		}

		void GetMemoryUsage(ICrySizer *pSizer) const{}
	};

public:
	CMuzzleEffect();

	void Initialize(CFireMode* pFireMode);
	void AttachEmitters(CFireMode* pFireMode, int barrel);
	void DetachEmitters(CFireMode* pFireMode, int barrel);

	void StartFire(CFireMode* pFireMode);
	void StopFire(CFireMode* pFireMode);
	void Shoot(CFireMode* pFireMode, Vec3 potentialTarget, int barrel);

	void GetMemoryUsage(ICrySizer * s) const;

private:
	void MuzzleFlashEffect(CFireMode* pFireMode, int barrel);
	bool GetMuzzleFireLocation(const CFireMode* pFireMode, QuatTS* location) const;
	void MuzzleBeamEffect(bool attach, CFireMode* pFireMode);
	void SetBeamTarget(CFireMode* pFireMode, Vec3 potentialTarget);

	std::vector<SMuzzleEffectInfo> m_mfIds;
	uint32 m_beamFxId[2];
};


#endif

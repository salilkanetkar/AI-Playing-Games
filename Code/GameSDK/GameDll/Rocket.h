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

#ifndef __ROCKET_H__
#define __ROCKET_H__

#if _MSC_VER > 1000
# pragma once
#endif


#include "Projectile.h"


class CRocket : public CProjectile
{
public:
	DECLARE_COMPONENT_TYPE("CRocket", 0x6405DA63BF394A8C,0x86B6465CB2D19399)
	CRocket();
	virtual ~CRocket();


	// CProjectile
	virtual void HandleEvent(const SGameObjectEvent &);
	virtual void Launch(const Vec3 &pos, const Vec3 &dir, const Vec3 &velocity, float speedScale);

	//virtual void Serialize(TSerialize ser, unsigned aspects);
	// ~CProjectile

protected:
	void AutoDropOwnerWeapon();
	void EnableTrail();
	void DisableTrail();
	virtual bool ShouldCollisionsDamageTarget() const;
	virtual void ProcessEvent(SEntityEvent &event);

	Vec3			m_launchLoc;
	bool			m_detonatorFired;
};


#endif // __ROCKET_H__

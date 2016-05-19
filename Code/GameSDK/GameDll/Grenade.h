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

// Description : Grenades


#ifndef __GRENADE_H__
#define __GRENADE_H__

#if _MSC_VER > 1000
# pragma once
#endif

#include "Projectile.h"

class CGrenade : public CProjectile
{
private:
	typedef CProjectile BaseClass;

public:
	DECLARE_COMPONENT_TYPE("CGrenade", 0x05AA279A3D6E43CC, 0x9C539D00902E1867)
	CGrenade();
	virtual ~CGrenade();

	virtual void Explode(const CProjectile::SExplodeDesc& explodeDesc);
	virtual void Launch(const Vec3 &pos, const Vec3 &dir, const Vec3 &velocity, float speedScale /*=1.0f*/);
	virtual void HandleEvent(const SGameObjectEvent &event);

protected:
	virtual bool ShouldCollisionsDamageTarget() const;
	virtual void ProcessEvent(SEntityEvent &event);

	bool m_detonationFailed;
};

class CSmokeGrenade : public CGrenade
{

private:
	typedef CGrenade inherited;

public:
	DECLARE_COMPONENT_TYPE("CSmokeGrenade", 0xC7F0596A333341F8, 0x91A28A0F0C6D6FB6)
	virtual void Launch(const Vec3 &pos, const Vec3 &dir, const Vec3 &velocity, float speedScale /*=1.0f*/);
};

#endif

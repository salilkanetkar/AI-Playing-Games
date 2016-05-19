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

#ifndef __SSHOOT_HELPER_H__
#define __SSHOOT_HELPER_H__

class CProjectile;
struct SAmmoParams;

class SShootHelper
{
public:
	static CProjectile* Shoot(EntityId ownerID, const EntityId weaponID, const char* ammo, int hitTypeId, const Vec3& firePos, const Vec3& fireDir, int damage, bool isProxy = false);
	static void Explode(const EntityId ownerID, const EntityId weaponID, const char* ammo, const Vec3& firePos, const Vec3& fireDir, int damage, float desiredRadius = -1.0f, bool skipExplosionEffect = false);
	static void DoLocalExplodeEffect(EntityId ownerID, const char* ammo, const Vec3& firePos, const Vec3& fireDir, float desiredRadius = -1.0f);
private:
	static const SAmmoParams* GetAmmoParams(const char* ammo);
};

#endif
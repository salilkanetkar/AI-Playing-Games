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

#pragma once

#ifndef _WEAPON_RECOIL_OFFSET_H_
#define _WEAPON_RECOIL_OFFSET_H_

struct SParams_WeaponFPAiming;

namespace Serialization
{
	class IArchive;
}

struct SStaticWeaponRecoilParams
{
	SStaticWeaponRecoilParams();

	void Serialize(Serialization::IArchive& ar);

	float	dampStrength;
	float	fireRecoilTime;
	float	fireRecoilStrengthFirst;
	float	fireRecoilStrength;
	float	angleRecoilStrength;
	float	randomness;
};



class CRecoilOffset
{
public:
	CRecoilOffset();

	QuatT Compute(float frameTime);

	void SetStaticParams(const SStaticWeaponRecoilParams& params);
	void TriggerRecoil(bool firstFire);

private:
	SStaticWeaponRecoilParams m_staticParams;

	Vec3 m_position;
	Vec3 m_fireDirection;
	Ang3 m_angle;
	Ang3 m_angleDirection;
	float m_fireTime;
	bool m_firstFire;
};


#endif

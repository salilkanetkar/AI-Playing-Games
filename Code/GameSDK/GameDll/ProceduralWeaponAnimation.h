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

#ifndef _PROCEDURAL_WEAPON_ANIMATION_H_
#define _PROCEDURAL_WEAPON_ANIMATION_H_

#include <CryExtension/Impl/ClassWeaver.h>

#include "WeaponOffset.h"
#include "WeaponLookOffset.h"
#include "WeaponRecoilOffset.h"
#include "WeaponStrafeOffset.h"
#include "WeaponZoomOffset.h"
#include "WeaponBumpOffset.h"
#include "WeaponOffsetInput.h"

#include "ICryAnimation.h"

class CPlayer;
class CWeaponOffsetInput;


class CProceduralWeaponAnimation
{
public:
	CProceduralWeaponAnimation();

	void Update(float deltaTime);

	CWeaponZoomOffset& GetZoomOffset() {return m_weaponZoomOffset;}
	CLookOffset& GetLookOffset() {return m_lookOffset;}
	CStrafeOffset& GetStrafeOffset() {return m_strafeOffset;}
	CRecoilOffset& GetRecoilOffset() {return m_recoilOffset;}
	CBumpOffset& GetBumpOffset() {return m_bumpOffset;}
	void AddCustomOffset(const QuatT& offset);

	QuatT GetRightOffset() const {return m_rightOffset;}
	QuatT GetLeftOffset() const {return m_leftOffset;}

private:
	void UpdateDebugState();
	void ComputeOffsets(float deltaTime);
	void ResetCustomOffset();

	CWeaponZoomOffset m_weaponZoomOffset;
	CLookOffset m_lookOffset;
	CStrafeOffset m_strafeOffset;
	CRecoilOffset m_recoilOffset;
	CBumpOffset m_bumpOffset;
	QuatT m_customOffset;

	QuatT m_rightOffset;
	QuatT m_leftOffset;

	CWeaponOffsetInput::TWeaponOffsetInput m_weaponOffsetInput;
	bool m_debugInput;
};



#endif

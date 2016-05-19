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

#ifndef _WEAPON_ZOOM_OFFSET_H_
#define _WEAPON_ZOOM_OFFSET_H_

#include "WeaponOffset.h"

struct SParams_WeaponFPAiming;



class CWeaponZoomOffset
{
public:
	CWeaponZoomOffset();

	QuatT Compute(float frameTime);
	QuatT GetLeftHandOffset(float frameTime);

	CWeaponOffsetStack& GetShoulderOffset() {return m_shoulderOffset;}
	CWeaponOffsetStack& GetLeftHandOffset() {return m_leftHandOffset;}
	SWeaponOffset& GetZommOffset() {return m_zoomOffset;}

	void SetZoomTransition(float transition);
	void SetZoomTransitionRotation(float rotation);

private:
	CWeaponOffsetStack m_shoulderOffset;
	CWeaponOffsetStack m_leftHandOffset;
	SWeaponOffset m_zoomOffset;

	float m_zoomRotation;
	float m_zoomTransition;
};



#endif

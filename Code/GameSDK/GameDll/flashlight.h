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

#ifndef FLASH_LIGHT_H
#define FLASH_LIGHT_H

#pragma once


#include "Accessory.h"


class CWeapon;


class CFlashLight : public CAccessory
{
public:
	DECLARE_COMPONENT_TYPE("CFlashLight", 0x497091829B264B63,0x8E8C54B1F707EC0C)
	CFlashLight();
	~CFlashLight();

	virtual void OnAttach(bool attach);
	virtual void OnParentSelect(bool select);
	virtual void OnEnterFirstPerson();
	virtual void OnEnterThirdPerson();

	void ToggleFlashLight();
	static void EnableFlashLight(bool enable);
	static bool IsFlashLightEnabled();

private:
	void EnableLight(bool enable);
	void EnableFogVolume(CWeapon* pWeapon, int slot, bool enable);

	CWeapon* GetWeapon() const;

	EntityEffects::TAttachedEffectId m_lightId;
	EntityId m_fogVolume;

	static bool m_lightEnabled;
	static bool m_flashLightEnabled;
};


#endif

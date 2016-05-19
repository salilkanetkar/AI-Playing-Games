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

// Description : Weapon to be used during cut-scenes with restricted player input


#pragma once

#ifndef _CINEMATIC_WEAPON_H_
#define _CINEMATIC_WEAPON_H_

#include "Weapon.h"
#include "Audio/AudioSignalPlayer.h"

class CCinematicWeapon : public CWeapon
{

	enum EInputClass
	{
		eInputClass_None		 = 0,
		eInputClass_Primary = 1,
		eInputClass_Secondary,
	};

	typedef CWeapon BaseClass;

public:
	DECLARE_COMPONENT_TYPE("CCinematicWeapon", 0x5A91A170766D4562,0x934670D2315ECFB2)
	CCinematicWeapon();
	virtual ~CCinematicWeapon();

	virtual void HandleEvent( const SGameObjectEvent& goEvent );
	virtual void OnAction( EntityId actorId, const ActionId& actionId, int activationMode, float value );

	virtual void StartFire();
	virtual void StopFire();

private:

	void SetupFireSound();

	void SetPrimary();
	void SetSecondary();
	void Disable();

	EInputClass	m_inputClass;
	CAudioSignalPlayer m_fireSound;
	CAudioSignalPlayer m_stopFireTailSound;
};

#endif //_CINEMATIC_WEAPON_H_
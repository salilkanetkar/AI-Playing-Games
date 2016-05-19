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

#ifndef _WEAPON_OFFSET_INPUT_H_
#define _WEAPON_OFFSET_INPUT_H_



#include "IPlayerInput.h"



class CProceduralWeaponAnimation;



class CWeaponOffsetInput : public IInputEventListener
{
private:
	enum Mode
	{
		EMode_None,
		EMode_PositionOffset,
		EMode_RotationOffset,
		EMode_ZAxisOffset,
	};

	enum Sensibility
	{
		ESensibility_Slow,
		ESensibility_Medium,
		ESensibility_Fast,
	};

	enum Hand
	{
		EHand_Right,
		EHand_Left,
	};

public:
	typedef boost::shared_ptr<CWeaponOffsetInput> TWeaponOffsetInput;

public:
	CWeaponOffsetInput();

	virtual void Update();
	virtual bool OnInputEvent(const SInputEvent &inputEvent);

	static TWeaponOffsetInput Get();

	void SetRightDebugOffset(const SWeaponOffset& offset);
	void AddRightDebugOffset(const SWeaponOffset& offset);
	SWeaponOffset GetRightDebugOffset() const {return m_debugRightOffset;}

	void SetLeftDebugOffset(const SWeaponOffset& offset);
	void AddLeftDebugOffset(const SWeaponOffset& offset);
	SWeaponOffset GetLeftDebugOffset() const {return m_debugLeftOffset;}

private:
	void AddOffset(Vec3 pos, Ang3 ang);

	SWeaponOffset m_debugRightOffset;
	SWeaponOffset m_debugLeftOffset;

	Vec2 m_offset;
	Mode m_mode;
	Sensibility m_sensibility;
	Hand m_hand;
};


#endif

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

// Description : LTAG Implementation


#pragma once

#ifndef _LTAG_H_
#define _LTAG_H_

#include "Weapon.h"
#include "HandGrenades.h"

class CLTag :	public CWeapon
{
public:

	DECLARE_COMPONENT_TYPE("CLTag", 0xE246C6C3A5DA4A73,0xAE1242D0CCACFC5D)
	CLTag();
	virtual ~CLTag();

	virtual void Reset();
	virtual void FullSerialize( TSerialize ser );
	virtual void OnSelected(bool selected);
	
	virtual void StartFire(const SProjectileLaunchParams& launchParams);

	virtual void OnAction(EntityId actorId, const ActionId& actionId, int activationMode, float value);

	virtual void GetMemoryUsage(ICrySizer * s) const
	{
		s->AddObject(this, sizeof(*this));
		CWeapon::GetInternalMemoryUsage(s); // collect memory of parent class
	}
	virtual void ProcessEvent(SEntityEvent& event);
	//virtual bool NetSerialize( TSerialize ser, EEntityAspects aspect, uint8 profile, int flags );
	//virtual void Select(bool select);
	virtual void StartChangeFireMode();

protected:

	virtual void AnimationEvent(ICharacterInstance *pCharacter, const AnimEventInstance &event);

private:
	void UpdateGrenades();
	void HideGrenadeAttachment(ICharacterInstance* pWeaponCharacter, const char* attachmentName, bool hide);

	typedef CWeapon inherited;

	bool OnActionSwitchFireMode(EntityId actorId, const ActionId& actionId, int activationMode, float value);
};

#endif // _LTAG_H_
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

// Description : Binocular Implementation

#ifndef __BINOCULAR_H__
#define __BINOCULAR_H__

#if _MSC_VER > 1000
# pragma once
#endif


#include <IItemSystem.h>
#include "Weapon.h"


class CBinocular :	public CWeapon
{
	typedef CWeapon BaseClass;

public:


	DECLARE_COMPONENT_TYPE("CBinocular", 0xEA4F34DF85C547A7,0xA207C87936CEAA9D)
	CBinocular();
	virtual ~CBinocular();

	virtual void OnAction(EntityId actorId, const ActionId& actionId, int activationMode, float value);
	
	virtual bool OnActionSpecial(EntityId actorId, const ActionId& actionId, int activationMode, float value);
	virtual void Select(bool select);
	virtual void UpdateFPView(float frameTime);
	virtual bool AllowZoomToggle() { return false; }

	virtual void GetMemoryUsage(ICrySizer * s) const
	{
		s->AddObject(this, sizeof(*this));
		CWeapon::GetInternalMemoryUsage(s); // collect memory of parent class
	}
	virtual bool CanModify() const;
	virtual bool CanFire() const;
	virtual void StartFire();
	virtual void OnZoomIn();
	virtual void OnZoomOut();

	virtual bool AllowInteraction(EntityId interactionEntity, EInteractionType interactionType);

protected:
	
	virtual bool ShouldDoPostSerializeReset() const;

private:



	bool ShouldUseSoundAttenuation(const CActor& ownerActor) const;
	void SwitchSoundAttenuation(const CActor& ownerActor, const float coneInRadians) const;
	void UpdateSoundAttenuation(const CActor& ownerActor) const;

	bool OnActionChangeZoom(EntityId actorId, const ActionId& actionId, int activationMode, float value);
	bool OnActionSprint(EntityId actorId, const ActionId& actionId, int activationMode, float value);
	bool TrumpAction(EntityId actorId, const ActionId& actionId, int activationMode, float value);
};

#endif // __BINOCULAR_H__
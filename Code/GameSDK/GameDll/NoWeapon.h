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

#ifndef __NO_WEAPON__
#define __NO_WEAPON__

#pragma once

#include "Weapon.h"

class CNoWeapon: public CWeapon
{
	typedef CWeapon BaseClass;

public:
	DECLARE_COMPONENT_TYPE("CNoWeapon", 0x2A9A6E11E4ED4F53, 0x85587C8EEB71C679)

	CNoWeapon();
	virtual ~CNoWeapon();

	virtual void OnAction(EntityId actorId, const ActionId& actionId, int activationMode, float value);
	virtual void Select(bool select);

	virtual bool UpdateAimAnims(SParams_WeaponFPAiming &aimAnimParams);

protected:
	virtual bool ShouldDoPostSerializeReset() const;

private:

	void RegisterActions();
	bool OnActionMelee(EntityId actorId, const ActionId& actionId, int activationMode, float value);
};

#endif
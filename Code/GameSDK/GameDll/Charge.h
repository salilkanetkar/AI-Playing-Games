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

// Description : Single-shot Fire Mode Implementation

#ifndef __CHARGE_H__
#define __CHARGE_H__

#if _MSC_VER > 1000
# pragma once
#endif

#include "EntityUtility/EntityEffects.h"
#include "Automatic.h"

class CCharge :
	public CAutomatic
{
public:
	CRY_DECLARE_GTI(CCharge);

	CCharge();
	virtual ~CCharge();

	virtual void Update(float frameTime, uint32 frameId);
	virtual void GetMemoryUsage(ICrySizer * s) const;

	virtual void Activate(bool activate);

	virtual void StartFire();
	virtual void StopFire();

	virtual bool Shoot(bool resetAnimation, bool autoreload, bool isRemote=false);

	virtual void ChargeEffect(bool attach);
	virtual void ChargedShoot();
	
protected:

	int							m_charged;
	bool						m_charging;
	float						m_chargeTimer;
	bool						m_autoreload;

	EntityEffects::TAttachedEffectId m_chargeEffectId;
	float						m_chargedEffectTimer;
};

#endif //__CHARGE_H__

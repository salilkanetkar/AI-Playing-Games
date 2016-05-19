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

// Description : Grenade that delivers multiple EMP pulses over a given time period


#ifndef __EMP_GRENADE_H__
#define __EMP_GRENADE_H__

#include "Grenade.h"


class CEMPGrenade : public CGrenade
{
private:
	typedef CGrenade BaseClass;

public:
	DECLARE_COMPONENT_TYPE("CEMPGrenade", 0xB0906C1951554A85,0xAC81906ADEFCD419)
	CEMPGrenade();
	virtual ~CEMPGrenade();

	virtual void Update( SEntityUpdateContext &ctx, int updateSlot);
	virtual void HandleEvent(const SGameObjectEvent &event);

private:
	
	Vec3 m_pulsePos;

	float m_postExplosionLifetime;
	bool	m_bActive;
};

#endif //__EMP_GRENADE_H__

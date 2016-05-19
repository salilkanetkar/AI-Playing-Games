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

#ifndef __HEALTH__H__
#define __HEALTH__H__

#include "Utility/MaskedVar.h"

class CHealth
{
private:
	TMaskedFloat m_health;
	float m_healthMax;
	TMaskedInt m_healthAsRoundedPercentage;

public:
	CHealth() : m_health(100.0f), m_healthMax(100.0f), m_healthAsRoundedPercentage(100) {}

	ILINE float GetHealth() const { return m_health; }
	ILINE void  SetHealth( float fHealth ) { m_health = fHealth;m_healthAsRoundedPercentage = int_ceil( m_health * 100.0f / m_healthMax); }
	ILINE float GetHealthMax() const { return m_healthMax; }
	ILINE void  SetHealthMax( float fHealthMax ) { m_healthMax = fHealthMax; }
	ILINE int   GetHealthAsRoundedPercentage() const { return m_healthAsRoundedPercentage; }
	ILINE bool  IsDead() const { return( m_health <= 0.0f ); }
};

#endif
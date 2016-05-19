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

// Description : Controls internal heat of entity (used together with thermal vision)

// IMPORTANT
//
// Add an object of this class to your entity (weapon, actor...), and ensure its
// life time is tied to your entity, because this is working with an entity pointer.


#pragma once

#ifndef _ENTITY_EFFECTS_HEAT_H_
#define _ENTITY_EFFECTS_HEAT_H_

namespace EntityEffects
{
	class CHeatController
	{
		struct SHeatPulse
		{
			SHeatPulse()
				: heat(0.0f)
				, baseTime(0.0f)
				, runningTime(0.0f)
			{

			}

			void Reset()
			{
				heat = 0.0f;
				baseTime = 0.0f;
				runningTime = 0.0f;
			}

			float heat;
			float baseTime;
			float runningTime;
		};

	public:
		CHeatController();

		void InitWithEntity(IEntity* pEntity, const float baseHeat);
		bool Update(const float frameTime);
		void AddHeatPulse(const float intensity, const float time);

		void Revive(const float baseHeat);
		void CoolDown(const float targetHeat);

	private:

		float UpdateHeat(const float frameTime);
		float UpdateCoolDown(const float frameTime);
		void  SetThermalVisionParams(const float scale);

		IEntity*	m_ownerEntity;
		float		m_baseHeat;
		float		m_coolDownHeat;

		SHeatPulse	m_heatPulse;
		bool		m_thermalVisionOn;
	};
}

#endif
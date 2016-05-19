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

#ifndef __SPRINT_STAMINA__H__
#define __SPRINT_STAMINA__H__

#include "Audio/AudioSignalPlayer.h"

#if !defined(_RELEASE)
	#define DEBUG_SPRINT_STAMINA
#endif

struct IItemParamsNode;

class CSprintStamina
{
	struct Settings
	{
		Settings()
			: m_depleteRatePerSec(0.2f) 
			,	m_regenDelaySecs(3.8f)
			,	m_regenDelayExtremeSecs(4.0f)
			,	m_regenRatePerSec(50.0f)
			,	m_breatheSoundStaminaThreshold(0.5f)
			, m_minimumSprintingTimeToPlayStopSound(0.0f)
		{

		}

		float m_depleteRatePerSec;
		float m_regenDelaySecs;
		float m_regenDelayExtremeSecs;
		float m_regenRatePerSec;
		float m_breatheSoundStaminaThreshold;
		float m_minimumSprintingTimeToPlayStopSound;
	};

public:

	struct UpdateContext
	{
		UpdateContext( const EntityId _playerId, const float _frameTime, const float consumptionScale, const bool _sprinting, const bool _localClient )
			: playerId(_playerId) 
			, frameTime(_frameTime)
			, consumptionScale(consumptionScale)
			, sprinting(_sprinting)
			, localClient(_localClient)
		{

		}

		EntityId playerId;
		float frameTime;
		float consumptionScale;
		bool  sprinting;
		bool  localClient;
	};

	CSprintStamina();

	static void LoadSettings( const IItemParamsNode* pParamsNode );

	void Reset(  const EntityId playerId  );
	void Update( const UpdateContext& updateCtx );
	bool HasChanged() { return m_staminaHasChanged; };
	float Get() const { return m_stamina; }

#ifdef DEBUG_SPRINT_STAMINA
	void Debug( const IEntity* pEntity );
#endif

private:

	static Settings m_settings;

	CAudioSignalPlayer m_runBreathingLoop;

	float m_stamina;
	float m_staminaRegenDelay;
	float m_sprintingTime;

	bool m_staminaReducedPrevUpdate;
	bool m_staminaHasChanged;
};

#endif //__SPRINT_STAMINA__H__
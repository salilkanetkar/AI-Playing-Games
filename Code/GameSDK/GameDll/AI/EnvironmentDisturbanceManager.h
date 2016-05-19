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

#ifndef EnvironmentDisturbanceManager_h
#define EnvironmentDisturbanceManager_h

#include "IVisionMap.h"

namespace GameAI
{
	class ObservableEvent
	{
	public:
		ObservableEvent()
			: m_expirationTime(0.0f)
			, m_position(ZERO)
		{};

		void Initialize( const Vec3& position, float duration, uint8 faction, const char* signal );
		void Release();

		bool IsExpired( CTimeValue currentTime );
		bool HasBeenObservedBy( EntityId entityId );
		void SetObservedBy( EntityId entityId );
		VisionID GetVisionId() { return m_visionId; }
		const Vec3& GetPosition() { return m_position; }
		const char* GetSignal() { return m_signal; }

	private:
		CTimeValue m_expirationTime;
		VisionID   m_visionId;
		Vec3       m_position;
		string     m_signal;

		std::vector<EntityId> m_obeservedBy;
	};

	class EnvironmentDisturbanceManager
	{
	public:
		EnvironmentDisturbanceManager()
		{
		};

		~EnvironmentDisturbanceManager();;

		void Reset();
		void Update();

		void AddObservableEvent( const Vec3& position, float duration, const char* signal, EntityId sourceEntityId = 0 );

	private:
		void RemoveExpiredEvents();

		typedef std::vector<ObservableEvent> ObservableEvents;
		ObservableEvents m_observableEvents;
	};
}

#endif //EnvironmentDisturbanceManager_h

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

// Description : Helper to calculate a value that represents AI awareness toward the player.


#pragma once

#ifndef __AIAWARENESSTOPLAYERHELPER_H__
#define __AIAWARENESSTOPLAYERHELPER_H__

struct IAIActor;
struct IAIObject;
class CActor;

class CAIAwarenessToPlayerHelper
{
	public:
		struct IListener
		{
			virtual	~IListener(){}
			virtual void AwarenessChanged( int value ) = 0; // listeners are notified only when the integer value changes, not every time the internal float values change.
		};

		// entities that need to be added to the awareness calculation, but that are not AIActors (turrets and towers atm)
		struct IAwarenessEntity
		{
			virtual	~IAwarenessEntity(){}
			virtual int GetAwarenessToActor( IAIObject* pAIObject, CActor* pActor ) const = 0;
		};

		enum
		{
			AI_Awarness_To_Player_Aware = 50,
			AI_Awarness_To_Player_Alerted = 100
		};

		enum VisorIconColor
		{
			Green,
			Orange,
			Red
		};
	
	public:
		CAIAwarenessToPlayerHelper() { Reset(); }
		void Update( float frameTime );

		void Serialize( TSerialize ser );
		float GetFloatAwareness() const { return m_actualAwareness; };  // 0..100 value.
		int GetIntAwareness() const { return m_intCurrentAwareness; };  // 0..100 value.
		void Reset();
		void AddListener( IListener *pListener );
		void RemoveListener( IListener *pListener );
		VisorIconColor GetMarkerColorForAgent(const EntityId entityId) const;
		void RegisterAwarenessEntity( IAwarenessEntity* pAwarenessEntity );
		void UnregisterAwarenessEntity( IAwarenessEntity* pAwarenessEntity );

		void AddTurret(const EntityId turretId);
		void RemoveTurret(const EntityId turretId);


	private:
		void NotifyListeners();
		int GetAlertnessAffectedByVisibility(const IAIActor& aiActor, const IAIObject& playerAiObject, const bool playerIsCloaked) const;
		void RecalculateAwareness();

		static const float kAIAwarenessToPlayerAware;
		static const float kAIAwarenessToPlayerAlerted;

		int m_intCurrentAwareness;
		float m_actualAwareness; // 0..100 value
		float m_animatedAwarenessThatStrivesTowardsActualAwareness; // 0..100 value
		float m_timeToRecalculateAwareness;

		typedef std::vector<IListener *> TListenersVector;
		TListenersVector m_listeners;

		// entities that need to be added to the awareness calculation, but that are not actual AI objects (turrets and towers atm)
		typedef std::vector<IAwarenessEntity*> SAwarenessEntitiesVector;
		SAwarenessEntitiesVector m_awarenessEntities;
};

#endif //__AIAWARENESSTOPLAYERHELPER_H__

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

// Description : Smart proximity mine

#pragma once

#ifndef _SMART_MINE_H_
#define _SMART_MINE_H_

#include <IGameObject.h>

#include "../State.h"
#include "../EntityUtility/EntityEffects.h"

#define SMART_MINE_MAIN_UPDATE_SLOT   0

// Events sent to mines (i.e. from minefield)
enum EMineGameObjectEvent
{
	eMineGameObjectEvent_RegisterListener = eGFE_Last,
	eMineGameObjectEvent_UnRegisterListener,
	eMineGameObjectEvent_OnNotifyDestroy,
};

// Events sent to the event listeners
enum EMineEventListenerGameObjectEvent
{
	eMineEventListenerGameObjectEvent_Enabled = eGFE_Last,
	eMineEventListenerGameObjectEvent_Disabled,
	eMineEventListenerGameObjectEvent_Destroyed
};

//////////////////////////////////////////////////////////////////////////
/// FSM defines

enum ESmartMineStates
{
	eSmartMineState_Behavior = STATE_FIRST,
};

enum ESmartMineBehaviorEvent
{
	STATE_EVENT_SMARTMINE_ENTITY_ENTERED_AREA = STATE_EVENT_CUSTOM,
	STATE_EVENT_SMARTMINE_ENTITY_LEFT_AREA,
	STATE_EVENT_SMARTMINE_UPDATE,
	STATE_EVENT_SMARTMINE_TRIGGER_DETONATE,
	STATE_EVENT_SMARTMINE_HIDE,
	STATE_EVENT_SMARTMINE_UNHIDE
};

struct SSmartMineEvent_TriggerEntity : public SStateEvent
{
	SSmartMineEvent_TriggerEntity( ESmartMineBehaviorEvent eventType, const EntityId entityId )
		: SStateEvent( eventType )
	{
		AddData( (int)entityId );
	}

	EntityId GetTriggerEntity() const 
	{
		return static_cast<EntityId>(GetData(0).GetInt());
	}
};

struct SSmartMineEvent_Update : public SStateEvent
{
	SSmartMineEvent_Update( const float frameTime )
		: SStateEvent( STATE_EVENT_SMARTMINE_UPDATE )
	{
		AddData( frameTime );
	}

	float GetFrameTime() const 
	{
		return GetData(0).GetFloat();
	}
};

//////////////////////////////////////////////////////////////////////////
/// Smart Mine

class CSmartMine : public CGameObjectExtensionHelper<CSmartMine, IGameObjectExtension>
{
public:
	DECLARE_COMPONENT_TYPE("CSmartMine", 0x9E3CFF9F60BE4D79, 0x84FB98557CAAE7F0)
	typedef CryFixedArray<EntityId, 4> TrackedEntities; //Up to 4 targets should be more than enough... 

	CSmartMine();
	virtual ~CSmartMine();

	// IGameObjectExtension
	virtual bool Init( IGameObject * pGameObject );
	virtual void InitClient (ChannelId channelId) {};
	virtual void PostInit( IGameObject * pGameObject );
	virtual void PostInitClient (ChannelId channelId) {};
	virtual bool ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params );
	virtual void PostReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params ) {}
	virtual bool GetEntityPoolSignature( TSerialize signature );
	//virtual void Release();
	virtual void FullSerialize( TSerialize ser );
	virtual bool NetSerialize( TSerialize ser, EEntityAspects aspect, uint8 profile, int flags ) { return false; };
	virtual void PostSerialize() {};
	virtual void SerializeSpawnInfo( TSerialize ser, IEntity * ) {}
	virtual ISerializableInfoPtr GetSpawnInfo() {return 0;}
	virtual void Update( SEntityUpdateContext& ctx, int slot );
	virtual void HandleEvent( const SGameObjectEvent& gameObjectEvent );
	virtual void ProcessEvent( SEntityEvent& entityEvent );
	virtual void SetChannelId (ChannelId id) {};
	virtual void SetAuthority( bool auth ) {};
	virtual void PostUpdate( float frameTime ) { CRY_ASSERT(false); }
	virtual void PostRemoteSpawn() {};
	virtual void GetMemoryUsage( ICrySizer *pSizer ) const;
	// ~IGameObjectExtension

	void StartTrackingEntity( const EntityId entityId );
	void StopTrackingEntity( const EntityId entityId );

	ILINE bool NeedsToKeepTracking( ) const { return (m_trackedEntities.size() > 0); }
	ILINE uint32 GetTrackedEntitiesCount() const { return m_trackedEntities.size(); }
	ILINE EntityId GetTrackedEntityId( const uint32 idx ) const { CRY_ASSERT( idx < m_trackedEntities.size() ); return m_trackedEntities[idx]; }

	bool IsHostileEntity( const EntityId entityId ) const;
	bool ContinueTrackingEntity( const EntityId entityId ) const;
	bool ShouldStartTrackingEntity( const EntityId entityId ) const;

	void AddToTacticalManager();
	void RemoveFromTacticalManager();
	void UpdateTacticalIcon();
	void OnEnabled();
	void OnDisabled();

	void SetFaction( const uint8 factionId ) { m_factionId = factionId; }

	ILINE EntityEffects::CEffectsController& GetEffectsController() { return m_effectsController; }

	void NotifyMineListenersEvent( const EMineEventListenerGameObjectEvent event );

private:
	typedef std::vector<EntityId> TMineEventListeners;

	void Reset();

	DECLARE_STATE_MACHINE( CSmartMine, Behavior );

	EntityEffects::CEffectsController m_effectsController;

	TrackedEntities	m_trackedEntities; 

	TMineEventListeners	m_mineEventListeners;

	bool  m_enabled;
	bool  m_inTacticalManager;
	uint8 m_factionId;
};

#endif //_SMART_MINE_H_

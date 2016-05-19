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

// Description : Minefield to handle groups of mines


#pragma once

#ifndef _MINE_FIELD_H_
#define _MINE_FIELD_H_

#include <IGameObject.h>

#include "SmartMine.h"

//////////////////////////////////////////////////////////////////////////
/// Mine field

class CMineField : public CGameObjectExtensionHelper<CMineField, IGameObjectExtension>
{
public:
	DECLARE_COMPONENT_TYPE("CMineField",0x8F6A41B845294A58,0x829752D41CCED172)
	CMineField();
	virtual ~CMineField();

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
	virtual void SerializeSpawnInfo( TSerialize ser, IEntity* ent) {}
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

private:
	enum EMineFieldState
	{
		eMineFieldState_Showing = 0,
		eMineFieldState_NotShowing,
	};

	enum EMineState
	{
		eMineState_Enabled		= 0x01,
		eMineState_Destroyed	= 0x02,
	};

	struct SMineData
	{
		SMineData()
		: m_state(eMineState_Enabled)
		, m_entityId(0)
		{
		}

		int					m_state;
		EntityId		m_entityId;
	};

	typedef std::vector<SMineData> TMinesData;

	void SetState( const EMineFieldState state, const bool bForce = false );
	ILINE EMineFieldState GetState() const { return m_currentState; }
	void AddToTacticalManager();
	void RemoveFromTacticalManager();
	void NotifyAllMinesEvent( const EMineGameObjectEvent event );
	void NotifyMineEvent( const EntityId targetEntity, const EMineGameObjectEvent event );
	void Reset( const bool bEnteringGameMode );
	SMineData* GetMineData( const EntityId entityId );
	void UpdateState();

	TMinesData							m_minesData;
	EMineFieldState					m_currentState;
};

#endif //_MINE_FIELD_H_

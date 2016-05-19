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

#ifndef _AI_CORPSE_H_
#define _AI_CORPSE_H_

#include <IGameObject.h>
#include <CryFlags.h>

#define AI_CORPSES_ENABLE_SERIALIZE 0

#if !defined(_RELEASE)
	#define AI_CORPSES_DEBUG_ENABLED 1
#else
	#define AI_CORPSES_DEBUG_ENABLED 0
#endif

struct IAttachment;
struct CEntityAttachment;

class CAICorpse : public CGameObjectExtensionHelper<CAICorpse, IGameObjectExtension>
{
	struct AttachedItem
	{
		enum
		{
			MaxWeapons = 2,
		};

		AttachedItem()
			: id(0) 
			, pClass(NULL)
		{

		}
		
		EntityId						id;
		IEntityClass*				pClass;
		string	            attachmentName;
	};

public:
	DECLARE_COMPONENT_TYPE("CAICorpse", 0xF9426AA921D74622, 0x9B3321C58BABA2C9)
	CAICorpse();
	virtual ~CAICorpse();

	// IGameObjectExtension
	virtual bool Init( IGameObject * pGameObject ) override;
	virtual void InitClient (ChannelId channelId) override {};
	virtual void PostInit( IGameObject * pGameObject ) override;
	virtual void PostInitClient (ChannelId channelId) override {};
	virtual bool ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params ) override;
	virtual void PostReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params ) override {}
	virtual bool GetEntityPoolSignature( TSerialize signature ) override;
	//virtual void Release();
	virtual void FullSerialize( TSerialize ser ) override;
	virtual bool NetSerialize( TSerialize ser, EEntityAspects aspect, uint8 profile, int flags )  override { return false; };
	virtual void PostSerialize() override;
	virtual void SerializeSpawnInfo( TSerialize ser , IEntity *) override {}
	virtual ISerializableInfoPtr GetSpawnInfo() override {return 0;}
	virtual void Update( SEntityUpdateContext& ctx, int slot ) override {};
	virtual void HandleEvent( const SGameObjectEvent& gameObjectEvent ) override;
	virtual void ProcessEvent( SEntityEvent& entityEvent ) override {};
	virtual void SetChannelId (ChannelId id) override {};
	virtual void SetAuthority( bool auth ) override {};
	virtual void PostUpdate( float frameTime ) override { CRY_ASSERT(false); }
	virtual void PostRemoteSpawn() override {};
	virtual void GetMemoryUsage( ICrySizer *pSizer ) const override;
	// ~IGameObjectExtension

	void SetupFromSource( IEntity& sourceEntity, ICharacterInstance& characterInstance, const uint32 priority);
	void AboutToBeRemoved();

	uint32 GetPriority() const { return m_priority; }
private:

	EntityId CloneAttachedItem( const CAICorpse::AttachedItem& attachedItem, IAttachment* pAttachment);

#if AI_CORPSES_ENABLE_SERIALIZE
	string m_modelName;
#endif

	CryFixedArray<AttachedItem, AttachedItem::MaxWeapons> m_attachedItemsInfo;
	
	uint32 m_priority;
};

DECLARE_COMPONENT_POINTERS(CAICorpse)

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

class CAICorpseManager
{
private:

	struct CorpseInfo
	{
		enum Flags
		{
			eFlag_PhysicsDisabled = BIT(0),
			eFlag_FarAway = BIT(1)
		};

		CorpseInfo( const EntityId _corpseId, const uint32 _priority )
			: corpseId(_corpseId)
		{
		}

		IEntity* GetCorpseEntity() 
		{
			return gEnv->pEntitySystem->GetEntity(corpseId);
		}

		CAICorpse* GetCorpse()
		{
			IGameObject* pGameObject = g_pGame->GetIGameFramework()->GetGameObject(corpseId);
			if(pGameObject != NULL)
			{
				return static_cast<CAICorpse*>(pGameObject->QueryExtension("AICorpse"));
			}

			return NULL;
		}

		EntityId   corpseId;
		CCryFlags<uint32>  flags;
	};

	typedef std::vector<CorpseInfo> TCorpseArray;

public:
	
	struct SCorpseParameters
	{
		enum Priority
		{
			ePriority_Normal = 0,
			ePriority_High   =  1,
			ePriority_VeryHight = 2,
		};

		Priority priority;
	};

	CAICorpseManager();
	~CAICorpseManager();
	
	void Reset();

	EntityId SpawnAICorpseFromEntity( IEntity& sourceEntity, const SCorpseParameters& corpseParams ); 

	void RegisterAICorpse( const EntityId corpseId, const uint32 priority );
	void UnregisterAICorpse( const EntityId corpseId );

	void Update( const float frameTime );

	void RemoveAllCorpses( const char* requester );

#if AI_CORPSES_DEBUG_ENABLED
	void DebugDraw( );
#else
	ILINE void DebugDraw() {}
#endif

	static CAICorpseManager* GetInstance() { return s_pThis; }

	static CAICorpseManager::SCorpseParameters::Priority GetPriorityForClass( const IEntityClass* pEntityClass );

private:

	void RemoveSomeCorpses();
	void RemoveCorpse( const EntityId corpseId );

	CorpseInfo* FindCorpseInfo( const EntityId corpseId );

	TCorpseArray  m_corpsesArray;
	uint32				m_maxCorpses;
	uint32				m_lastUpdatedCorpseIdx;

	static CAICorpseManager* s_pThis;
};

#endif //_AI_CORPSE_H_

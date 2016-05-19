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

// Description : Crysis2 interactive object, for playing co-operative animations with player


#pragma once

#ifndef __CRYSIS2_INTERACTIVE_OBJECT_H__
#define __CRYSIS2_INTERACTIVE_OBJECT_H__

#include <IGameObject.h>
#include "InteractiveObjectEnums.h"
#include "ItemString.h"

#include <ICryMannequinDefs.h>

#define INTERACTIVE_OBJECT_EX_ANIMATIONS_DEBUG	0

class CInteractiveObjectEx : public CGameObjectExtensionHelper<CInteractiveObjectEx, IGameObjectExtension>
{


private:

	enum EState
	{
		eState_NotUsed = 0,
		eState_InUse,
		eState_Used, //Has been used at least one time but can still be used
		eState_Done
	};

	struct SInteractionDataSet
	{
		SInteractionDataSet();
		~SInteractionDataSet(){};

		QuatT			m_alignmentHelperLocation;
		float			m_interactionRadius;
		float			m_interactionAngle;
		TagID			m_targetTagID;
		ItemString m_helperName;
	};

public:
	DECLARE_COMPONENT_TYPE("CInteractiveObjectEx", 0x49D4506245854784, 0x8BCC8A1EDF3AE947)
	CInteractiveObjectEx();
	virtual ~CInteractiveObjectEx();

	// IGameObjectExtension
	virtual bool Init(IGameObject *pGameObject);
	virtual void InitClient (ChannelId channelId);
	virtual void PostInit(IGameObject *pGameObject);
	virtual void PostInitClient (ChannelId channelId);
	virtual bool ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params );
	virtual void PostReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params ) {}
	virtual bool GetEntityPoolSignature( TSerialize signature );
	//virtual void Release();
	virtual void FullSerialize( TSerialize ser );
	virtual bool NetSerialize( TSerialize ser, EEntityAspects aspect, uint8 profile, int flags );
	virtual void PostSerialize();
	virtual void SerializeSpawnInfo( TSerialize ser , IEntity *ent);
	virtual ISerializableInfoPtr GetSpawnInfo();
	virtual void Update( SEntityUpdateContext &ctx, int updateSlot);
	virtual void PostUpdate(float frameTime );
	virtual void PostRemoteSpawn();
	virtual void HandleEvent( const SGameObjectEvent &goEvent);
	virtual void ProcessEvent(SEntityEvent &entityEvent);
	virtual void SetChannelId (ChannelId id);
	virtual void SetAuthority(bool auth);
	virtual void GetMemoryUsage(ICrySizer *pSizer) const;
	//~IGameObjectExtension

	//Script callbacks
	int CanUse(EntityId entityId) const;
	virtual void Use(EntityId entityId);	
	virtual void StopUse(EntityId entityId);
	virtual void AbortUse();
	//~Script callbacks

	void StartUseSpecific(EntityId entityId, int interactionIndex);
	void OnExploded(const Vec3& explosionSource);

private:

	bool Reset();

	void StartUse(EntityId entityId);
	void ForceInstantStandaloneUse(const int interactionIndex);
	void CalculateHelperLocation(const char* helperName, QuatT& helper) const;
	void Physicalize(pe_type physicsType, bool forcePhysicalization = false);
	void ParseAllInteractions(const SmartScriptTable& interactionProperties, std::vector<char*>& interactionNames); 
	void InitAllInteractionsFromMannequin();
	int  CalculateSelectedInteractionIndex( const EntityId entityId ) const;

	// returns -1 if not interaction constraints satsified, else returns index of first interaction the user can perform
	int  CanUserPerformAnyInteraction(EntityId userId) const;
	bool InteractionConstraintsSatisfied(const IEntity* pUserEntity, const SInteractionDataSet& interactionDataSet) const; 
	bool CanStillBeUsed();
	void HighlightObject(bool highlight);

	void ForceSkeletonUpdate( bool on );

#ifndef _RELEASE
	void DebugRender() const; 
#endif //#ifndef _RELEASE

protected:
	bool IsValidName(const char* name) const;

	uint32 GetCrcForName(const char* name) const;

private:
	typedef std::vector<SInteractionDataSet> SInteractionDataSetArray;
	SInteractionDataSetArray m_interactionDataSets;
	SInteractionDataSet m_loadedInteractionData;

	EState	m_state;
	int		m_physicalizationAfterAnimation;
	int		m_activeInteractionIndex; // Index into m_InteractionDataSets to indicate active interaction. 

	TagID m_interactionTagID;
	TagID m_stateTagID;

	uint32	m_currentLoadedCharacterCrc;
	bool		m_bHighlighted;
	bool		m_bRemoveDecalsOnUse;
	bool		m_bStartInteractionOnExplosion;
};

DECLARE_COMPONENT_POINTERS(CInteractiveObjectEx)

DECLARE_COMPONENT_POINTERS(CInteractiveObjectEx)


class CDeployableBarrier : public CInteractiveObjectEx
{
public:
	DECLARE_COMPONENT_TYPE("CDeployableBarrier", 0x31F35A76CB6F4D17, 0xBA7CC227E2BF0AC0)
};


#endif //__CRYSIS2_INTERACTIVE_OBJECT_H__

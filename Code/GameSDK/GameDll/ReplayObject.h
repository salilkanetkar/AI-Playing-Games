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

// Description : A replay entity spawned during KillCam replay


#ifndef __REPLAYOBJECT_H__
#define __REPLAYOBJECT_H__

#include <ICryMannequin.h>

class CReplayObjectAction : public TAction<SAnimationContext>
{
private:
	typedef TAction<SAnimationContext> BaseClass;
public:
	CReplayObjectAction(FragmentID fragID, const TagState &fragTags, uint32 optionIdx, bool trumpsPrevious, const int priority );
	virtual EPriorityComparison ComparePriority(const IAction &actionCurrent) const;
private:
	bool m_trumpsPrevious;
};

class CReplayItemList
{
public:
	CReplayItemList(){}
	~CReplayItemList(){}
	void AddItem( const EntityId itemId );
	void OnActionControllerDeleted();

private:
	typedef std::vector<EntityId> TItemVec;
	TItemVec m_items;
};

class CReplayObject : public CGameObjectExtensionHelper<CReplayObject, IGameObjectExtension>
{
public:
	
	DECLARE_COMPONENT_TYPE("CReplayObject",0x33C6715F798A4F11,0x9644FEC0A506ACDC)

	CReplayObject();
	virtual ~CReplayObject();

	// IGameObjectExtension
	virtual bool Init(IGameObject *pGameObject);
	virtual void InitClient (ChannelId channelId) {}
	virtual void PostInit(IGameObject *pGameObject) {}
	virtual void PostInitClient (ChannelId channelId) {}
	virtual bool ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params );
	virtual void PostReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params ) {}
	virtual bool GetEntityPoolSignature( TSerialize signature );
	//virtual void Release() { delete this; }
	virtual void FullSerialize( TSerialize ser ) {}
	virtual bool NetSerialize( TSerialize ser, EEntityAspects aspect, uint8 profile, int flags ) { return true; }
	virtual void PostSerialize() {}
	virtual void SerializeSpawnInfo( TSerialize ser, IEntity * ) {}
	virtual ISerializableInfoPtr GetSpawnInfo() {return 0;}
	virtual void Update( SEntityUpdateContext &ctx, int updateSlot) {}
	virtual void PostUpdate(float frameTime ) {}
	virtual void PostRemoteSpawn() {}
	virtual void HandleEvent( const SGameObjectEvent &) {}
	virtual void ProcessEvent(SEntityEvent &) {}
	virtual void SetChannelId (ChannelId id) {}
	virtual void SetAuthority(bool auth) {}
	virtual void GetMemoryUsage(ICrySizer * s) const {}
	//~IGameObjectExtension

	void SetTimeSinceSpawn(float time) { assert(time >= 0); m_timeSinceSpawn = time; }

protected:
	float m_timeSinceSpawn;
};
DECLARE_COMPONENT_POINTERS(CReplayObject)

#endif //!__REPLAYOBJECT_H__

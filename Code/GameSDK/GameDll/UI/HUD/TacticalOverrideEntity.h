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

// Description : HUD Tactical override entity


#ifndef __HUD_TACTICALOVERRIDE_ENTITY_H__
#define __HUD_TACTICALOVERRIDE_ENTITY_H__

// CTacticalOverrideEntity

class CTacticalOverrideEntity : public CGameObjectExtensionHelper<CTacticalOverrideEntity, IGameObjectExtension>
{
public:
	DECLARE_COMPONENT_TYPE("CTacticalOverrideEntity",0x6AFBF98D27BF4EB8,0xAE7ED056E2E0D97F)
	CTacticalOverrideEntity();
	virtual ~CTacticalOverrideEntity();

	// IGameObjectExtension
	virtual bool Init(IGameObject *pGameObject);
	virtual void InitClient (ChannelId channelId);
	virtual void PostInit(IGameObject *pGameObject);
	virtual void PostInitClient (ChannelId channelId) {}
	//virtual void Release();
	virtual void FullSerialize(TSerialize ser) {};
	virtual bool NetSerialize(TSerialize ser, EEntityAspects aspect, uint8 profile, int flags) { return true; }
	virtual void PostSerialize() {}
	virtual void SerializeSpawnInfo(TSerialize ser, IEntity *) {}
	virtual ISerializableInfoPtr GetSpawnInfo() { return 0; }
	virtual void Update(SEntityUpdateContext &ctx, int updateSlot) {}
	virtual void PostUpdate(float frameTime) {}
	virtual void PostRemoteSpawn() {}
	virtual void HandleEvent(const SGameObjectEvent& details) {}
	virtual void ProcessEvent(SEntityEvent& details);
	virtual void SetChannelId (ChannelId id) {}
	virtual void SetAuthority(bool auth) {}
	virtual void GetMemoryUsage(ICrySizer *pSizer) const;
	virtual bool ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params );
	virtual void PostReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params ) {}
	virtual bool GetEntityPoolSignature( TSerialize signature );
	//~IGameObjectExtension

protected:
	bool m_bMappedToParent;
};

DECLARE_COMPONENT_POINTERS(CTacticalOverrideEntity)

#endif // __HUD_TACTICALOVERRIDE_ENTITY_H__


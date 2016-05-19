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

#ifndef __MP_PATH_H__
#define __MP_PATH_H__

#include <IGameObject.h>

class CMPPath : public CGameObjectExtensionHelper<CMPPath, IGameObjectExtension, 1>
{
public:
	DECLARE_COMPONENT_TYPE("CMPPath",0x8E5DDAA8977E4CD4,0xA5C3E9517352FA84)
	~CMPPath();
	// IGameObjectExtension
	virtual bool Init(IGameObject *pGameObject) override;
	virtual void InitClient (ChannelId channelId) override {};
	virtual void PostInit(IGameObject *pGameObject) override {};
	virtual void PostInitClient (ChannelId channelId) override {}
	//virtual void Release(); // No longer used
	virtual void FullSerialize(TSerialize ser) override {};
	virtual bool NetSerialize(TSerialize ser, EEntityAspects aspect, uint8 profile, int flags) override { return true; }
	virtual void PostSerialize() override {}
	virtual void SerializeSpawnInfo(TSerialize ser, IEntity *) override {}
	virtual ISerializableInfoPtr GetSpawnInfo() override { return 0; }
	virtual void Update(SEntityUpdateContext &ctx, int updateSlot) override {};
	virtual void PostUpdate(float frameTime) override {}
	virtual void PostRemoteSpawn() override {}
	virtual void HandleEvent(const SGameObjectEvent& details) override {}
	virtual void ProcessEvent(SEntityEvent& details) override;
	virtual void SetChannelId (ChannelId id) override {}
	virtual void SetAuthority(bool auth) override {}
	virtual void GetMemoryUsage(ICrySizer *pSizer) const override;
	virtual bool ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params ) override;
	virtual void PostReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params ) override {}
	virtual bool GetEntityPoolSignature( TSerialize signature ) override;
	//~IGameObjectExtension
};
#endif // __MP_PATH_H__

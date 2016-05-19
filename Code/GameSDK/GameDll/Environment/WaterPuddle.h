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

#ifndef WATER_PUDDLE_H
#define WATER_PUDDLE_H


#include <IGameObject.h>
#include "ActorManager.h"



class CWaterPuddle;



class CWaterPuddleManager
{
private:
	struct SWaterPuddle
	{
		CWaterPuddle* m_pPuddle;
		EntityId m_entityId;
	};

public:
	void AddWaterPuddle(CWaterPuddle* pPuddle);
	void RemoveWaterPuddle(CWaterPuddle* pPuddle);
	void Reset();

	CWaterPuddle* FindWaterPuddle(Vec3 point);

private:
	std::vector<SWaterPuddle> m_waterPuddles;
};



class CWaterPuddle : public CGameObjectExtensionHelper<CWaterPuddle, IGameObjectExtension>
{
public:
	DECLARE_COMPONENT_TYPE("CWaterPuddle", 0x64461535D9DA4F50,0x81ACB5EFB0C76DC1)
	CWaterPuddle();
	~CWaterPuddle();

	// IGameObjectExtension
	virtual bool Init(IGameObject * pGameObject);
	virtual void InitClient (ChannelId channelId);
	virtual void PostInit(IGameObject * pGameObject);
	virtual void PostInitClient (ChannelId channelId);
	virtual bool ReloadExtension(IGameObject * pGameObject, const SEntitySpawnParams &params);
	virtual void PostReloadExtension(IGameObject * pGameObject, const SEntitySpawnParams &params);
	virtual bool GetEntityPoolSignature(TSerialize signature);
	//virtual void Release();
	virtual void FullSerialize(TSerialize ser);
	virtual bool NetSerialize(TSerialize ser, EEntityAspects aspect, uint8 profile, int flags);
	virtual void PostSerialize();
	virtual void SerializeSpawnInfo(TSerialize ser, IEntity *);
	virtual ISerializableInfoPtr GetSpawnInfo();
	virtual void Update(SEntityUpdateContext& ctx, int slot);
	virtual void HandleEvent(const SGameObjectEvent& gameObjectEvent);
	virtual void ProcessEvent(SEntityEvent& entityEvent);
	virtual void SetChannelId (ChannelId id);
	virtual void SetAuthority(bool auth);
	virtual void PostUpdate(float frameTime);
	virtual void PostRemoteSpawn();
	virtual void GetMemoryUsage(ICrySizer *pSizer) const;
	// ~IGameObjectExtension

	void ZapEnemiesOnPuddle(int ownTeam, EntityId shooterId, EntityId weaponId, float damage, int hitTypeId, IParticleEffect* hitEffect);

private:
	void ApplyHit(const SActorData& actorData, EntityId shooterId, EntityId weaponId, float damage, int hitTypeId, float waterLevel, IParticleEffect* hitEffect);
};

DECLARE_COMPONENT_POINTERS(CWaterPuddle)


#endif

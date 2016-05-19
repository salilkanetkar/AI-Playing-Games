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

#ifndef __DANGEROUS_RIGID_BODY_H__
#define __DANGEROUS_RIGID_BODY_H__

#include <IGameObject.h>

class CDangerousRigidBody : public CGameObjectExtensionHelper<CDangerousRigidBody, IGameObjectExtension, 1>
{
public:
        DECLARE_COMPONENT_TYPE("CDangerousRigidBody", 0xF28883A5EE194A2B,0x97A577B420AD613E)
	static const NetworkAspectType ASPECT_DAMAGE_STATUS	= eEA_GameServerC;
	
	static int sDangerousRigidBodyHitTypeId;

	CDangerousRigidBody();

	// IGameObjectExtension
	virtual bool Init(IGameObject *pGameObject);
	virtual void InitClient (ChannelId channelId);
	virtual void PostInit(IGameObject *pGameObject) {}
	virtual void PostInitClient (ChannelId channelId) {}
	//virtual void Release();
	virtual void FullSerialize(TSerialize ser) {};
	virtual bool NetSerialize(TSerialize ser, EEntityAspects aspect, uint8 profile, int flags);
	virtual void PostSerialize() {}
	virtual void SerializeSpawnInfo(TSerialize ser, IEntity *) {}
	virtual ISerializableInfoPtr GetSpawnInfo() { return 0; }
	virtual void Update(SEntityUpdateContext &ctx, int updateSlot) {};
	virtual void PostUpdate(float frameTime) {}
	virtual void PostRemoteSpawn() {}
	virtual void HandleEvent(const SGameObjectEvent& event) {};
	virtual void ProcessEvent(SEntityEvent& event) override;
	virtual void SetChannelId (ChannelId id) {}
	virtual void SetAuthority(bool auth) {}
	virtual void GetMemoryUsage(ICrySizer *pSizer) const;
	virtual bool ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params );
	virtual void PostReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params ) {};
	virtual bool GetEntityPoolSignature( TSerialize signature );
	// IGameObjectExtension

	void SetIsDangerous(bool isDangerous, EntityId triggerPlayerId);

private:
	void Reset();

	float	m_damageDealt;
	float m_lastHitTime;
	float m_timeBetweenHits;
	bool m_dangerous;
	bool m_friendlyFireEnabled;
	uint8 m_activatorTeam;
};
DECLARE_COMPONENT_POINTERS(CDangerousRigidBody)

#endif //__DANGEROUS_RIGID_BODY_H__

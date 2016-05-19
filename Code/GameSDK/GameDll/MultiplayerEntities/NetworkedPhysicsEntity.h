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

// Description: Entity that can change it's physicalisation state during a game.

#ifndef __NETWORKEDPHYSICSENTITY_H__
#define __NETWORKEDPHYSICSENTITY_H__

class CNetworkedPhysicsEntity :	public CGameObjectExtensionHelper<CNetworkedPhysicsEntity, IGameObjectExtension, 2>,
																public IGameObjectProfileManager
{
public:
	DECLARE_COMPONENT_TYPE("CNetworkedPhysicalEntity",0x83890DF6419C4C47,0x9DBB99DAE8C6D345)
	enum ePhysicalization
	{
		ePhys_NotPhysicalized,
		ePhys_PhysicalizedRigid,
		ePhys_PhysicalizedStatic,
	};

	CNetworkedPhysicsEntity();
	virtual ~CNetworkedPhysicsEntity();

	// IGameObjectExtension
	virtual bool Init(IGameObject *pGameObject);
	virtual void InitClient (ChannelId channelId) {}
	virtual void PostInit(IGameObject *pGameObject) {}
	virtual void PostInitClient (ChannelId channelId) {}
	virtual bool ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params );
	virtual void PostReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params ) {}
	virtual bool GetEntityPoolSignature( TSerialize signature );
	//virtual void Release();
	virtual void FullSerialize(TSerialize ser) {};
	virtual bool NetSerialize(TSerialize ser, EEntityAspects aspect, uint8 profile, int flags);
	virtual void PostSerialize() {}
	virtual void SerializeSpawnInfo(TSerialize ser, IEntity *) {}
	virtual ISerializableInfoPtr GetSpawnInfo() { return 0; }
	virtual void Update(SEntityUpdateContext &ctx, int updateSlot) {};
	virtual void PostUpdate(float frameTime) {}
	virtual void PostRemoteSpawn() {}
	virtual void HandleEvent(const SGameObjectEvent& event) {}
	virtual void ProcessEvent(SEntityEvent& event) {}
	virtual void SetChannelId (ChannelId id) {}
	virtual void SetAuthority(bool auth);
	virtual void GetMemoryUsage(ICrySizer *pSizer) const;
	// ~IGameObjectExtension

	// IGameObjectProfileManager
	virtual bool SetAspectProfile( EEntityAspects aspect, uint8 profile );
	virtual uint8 GetDefaultProfile( EEntityAspects aspect );
	// ~IGameObjectProfileManager

	void Physicalize(ePhysicalization physicsType);

private:
	void ReadPhysicsParams();

	SEntityPhysicalizeParams m_physicsParams;
	ePhysicalization m_physicsType;
	ePhysicalization m_requestedPhysicsType;
};
DECLARE_COMPONENT_POINTERS(CNetworkedPhysicsEntity)

#endif //__NETWORKEDPHYSICSENTITY_H__

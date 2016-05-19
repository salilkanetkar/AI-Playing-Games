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

// Description : Carry entity, used for CTFFlag


#ifndef __CARRYENTITY_H__
#define __CARRYENTITY_H__

#include "NetworkedPhysicsEntity.h"

typedef CNetworkedPhysicsEntity TParent;

struct IAttachment;

class CCarryEntity :	public TParent
{
public:
	DECLARE_COMPONENT_TYPE("CCarryEntity", 0x445B52FB646F45F1, 0x88DAC233DD62C49A);
	CCarryEntity();
	virtual ~CCarryEntity() {}

	// IGameObjectExtension
	virtual bool Init(IGameObject *pGameObject);
	virtual void GetMemoryUsage(ICrySizer *pSizer) const;
	virtual void PostInit(IGameObject *pGameObject);
	// ~IGameObjectExtension

	void SetSpawnedWeaponId(EntityId weaponId);
	void AttachTo(EntityId actorId);

private:
	void Attach(EntityId actorId);
	void Detach();

	typedef CryFixedStringT<8> TSmallString;

	TSmallString m_actionSuffix;
	TSmallString m_actionSuffixAG;

	uint32 m_playerTagCRC;

	EntityId m_spawnedWeaponId;
	EntityId m_attachedActorId;
	EntityId m_previousWeaponId;
	EntityId m_cachedLastItemId;

	QuatT m_oldAttachmentRelTrans;

	bool m_bSpawnedWeaponAttached;
};

#endif //__CARRYENTITY_H__


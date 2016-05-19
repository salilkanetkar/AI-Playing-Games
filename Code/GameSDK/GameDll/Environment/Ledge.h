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

// Description : Object for ledge placement in the levels

#pragma once

#ifndef _LEDGE_H_
#define _LEDGE_H_

#include <IGameObject.h>

class CLedgeObject : public CGameObjectExtensionHelper<CLedgeObject, IGameObjectExtension>
{

	struct LedgeProperties
	{
		LedgeProperties(const IEntity& entity);

		float ledgeCornerMaxAngle;
		float ledgeCornerEndAdjustAmount;
		bool ledgeFlipped;
		uint16 ledgeFlags_MainSide;
		uint16 ledgeFlags_OppositeSide;


	private:
		LedgeProperties();
	};

public:
	DECLARE_COMPONENT_TYPE("CLedgeObject", 0x935AEBEC8F1C4483, 0x9D948893D6BBBAA7)
	CLedgeObject();
	virtual ~CLedgeObject();

	// IGameObjectExtension
	virtual bool Init( IGameObject * pGameObject );
	virtual void InitClient (ChannelId channelId) {};
	virtual void PostInit( IGameObject * pGameObject );
	virtual void PostInitClient (ChannelId channelId) {};
	virtual bool ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params );
	virtual void PostReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params ) {}
	virtual bool GetEntityPoolSignature( TSerialize signature );
	//virtual void Release();
	virtual void FullSerialize( TSerialize ser ) {};
	virtual bool NetSerialize( TSerialize ser, EEntityAspects aspect, uint8 profile, int flags ) { return false; };
	virtual void PostSerialize() {};
	virtual void SerializeSpawnInfo( TSerialize ser , IEntity *) {}
	virtual ISerializableInfoPtr GetSpawnInfo() {return 0;}
	virtual void Update( SEntityUpdateContext& ctx, int slot ) { };
	virtual void HandleEvent( const SGameObjectEvent& gameObjectEvent );
	virtual void ProcessEvent( SEntityEvent& entityEvent );
	virtual void SetChannelId (ChannelId id) {};
	virtual void SetAuthority( bool auth ) {};
	virtual void PostUpdate( float frameTime ) { CRY_ASSERT(false); }
	virtual void PostRemoteSpawn() {};
	virtual void GetMemoryUsage( ICrySizer *pSizer ) const;
	// ~IGameObjectExtension

protected:

	virtual bool IsStatic() const
	{
		return false;
	}

private:

	void UpdateLocation();
	void ComputeLedgeMarkers();
	
	ILINE bool IsFlipped() const { return m_flipped; };

	bool m_flipped;
};

//////////////////////////////////////////////////////////////////////////

class CLedgeObjectStatic : public CLedgeObject
{
public:
	DECLARE_COMPONENT_TYPE("CLedgeObjectStatic", 0x4F8F4249A8B04627,0xAC5A5464CE5435EB)

	CLedgeObjectStatic();
	virtual ~CLedgeObjectStatic();

protected:

	virtual bool IsStatic() const
	{
		return true;
	}

};

#endif //_LEDGE_H_

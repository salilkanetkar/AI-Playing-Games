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

// Description : Snow entity


#ifndef __SNOW_H__
#define __SNOW_H__
#pragma once

#include <IGameObject.h>

namespace GameSDK{
class CSnow : public CGameObjectExtensionHelper<CSnow, IGameObjectExtension>
{
public:
	DECLARE_COMPONENT_TYPE("CSnow", 0x02DEC788DF154925,0xAD5686D98F8B61C0)
	CSnow();
	virtual ~CSnow();

	// IGameObjectExtension
	virtual bool Init(IGameObject *pGameObject);
	virtual void InitClient (ChannelId channelId) {};
	virtual void PostInit(IGameObject *pGameObject);
	virtual void PostInitClient (ChannelId channelId) {};
	virtual bool ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params );
	virtual void PostReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params ) {}
	virtual bool GetEntityPoolSignature( TSerialize signature );
	//virtual void Release();
	virtual bool NetSerialize(TSerialize ser, EEntityAspects aspect, uint8 profile, int pflags) { return true; }
	virtual void FullSerialize(TSerialize ser);
	virtual void PostSerialize() {}
	virtual void SerializeSpawnInfo( TSerialize ser, IEntity * ) {}
	virtual ISerializableInfoPtr GetSpawnInfo() {return 0;}
	virtual void Update( SEntityUpdateContext &ctx, int updateSlot);
	virtual void PostUpdate(float frameTime ) {};
	virtual void PostRemoteSpawn() {};
	virtual void HandleEvent( const SGameObjectEvent &);
	virtual void ProcessEvent(SEntityEvent &);
	virtual void SetChannelId (ChannelId id) {}
	virtual void SetAuthority(bool auth);
	virtual void GetMemoryUsage(ICrySizer *pSizer) const { pSizer->Add(*this); }

	//~IGameObjectExtension

	bool Reset();

protected:

	bool	m_bEnabled;
	float	m_fRadius;

	// Surface params.
	float	m_fSnowAmount;
	float	m_fFrostAmount;
	float	m_fSurfaceFreezing;

	// Snowfall params.
	int		m_nSnowFlakeCount;
	float	m_fSnowFlakeSize;
	float	m_fSnowFallBrightness;
	float	m_fSnowFallGravityScale;
	float	m_fSnowFallWindScale;
	float	m_fSnowFallTurbulence;
	float	m_fSnowFallTurbulenceFreq;

private:
	CSnow(const CSnow&);
	CSnow& operator = (const CSnow&);
};

DECLARE_COMPONENT_POINTERS(CSnow)
} //namespace GameSDK



#endif //__RAIN_H__

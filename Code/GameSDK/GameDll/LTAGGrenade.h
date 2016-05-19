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

# pragma once

#ifndef _LTAG_GRENADE_H_
#define _LTAG_GRENADE_H_

#include "Projectile.h"
#include "ItemDefinitions.h"
#include "StickyProjectile.h"

struct IAttachment;

class CLTAGGrenade : public CProjectile
{
private:
	typedef CProjectile inherited;


public:
	DECLARE_COMPONENT_TYPE("CLTAGGrendade", 0xA4E79D43C6544F61,0x9C44DB5A487FEAC0)
	CRY_DECLARE_GTI(CProjectile);

	CLTAGGrenade();
	virtual ~CLTAGGrenade();


	// CProjectile
	virtual void ReInitFromPool();

	virtual void HandleEvent(const SGameObjectEvent &);
	virtual void Launch(const Vec3 &pos, const Vec3 &dir, const Vec3 &velocity, float speedScale);
	virtual void Update(SEntityUpdateContext &ctx, int updateSlot);
	virtual bool NetSerialize(TSerialize ser, EEntityAspects aspect, uint8 profile, int pflags);
	virtual NetworkAspectType GetNetSerializeAspects();
	// ~CProjectile

	void SetGrenadeType(ELTAGGrenadeType grenadeType)
	{
		m_grenadeType = grenadeType; 
		CHANGED_NETWORK_STATE(this, eEA_GameServerStatic);
	}

protected:
	enum EState
	{
		EState_NONE,

		ERicochetState_FLYING,
		ERicochetState_PROXY,
		ERicochetState_ARMED,
		ERicochetState_LAST = ERicochetState_ARMED,

		EStickyState_SAFE,
		EStickyState_UNSAFE,
		EStickyState_ARMING,
	};

	void UpdateLTagTimeOut(const SLTagGrenadeParams::SCommonParams& grenadeParams);

	void OnCollision(const SGameObjectEvent &event);

	void ProximityGrenadeUpdate(SEntityUpdateContext &ctx, const SLTagGrenadeParams::SCommonParams& grenadeParams);
	void StateUpdate(SEntityUpdateContext &ctx, const SLTagGrenadeParams::SCommonParams& grenadeParams);

	void ChangeTexture(const string& textureName);
	void ChangeTrail(const string& trailString);

	void ExplodeGrenade(IActor* pHitActor=0);

	bool IsOwnerToClose();

	int PlaySound(const string& soundName);
	void StopSound(int id);

	void ChangeState(EState state);
	void StateEnter(EState state);
	void StateExit(EState state);

	void UpdateStoredTracjectory(const Vec3& pos);

	virtual bool ShouldCollisionsDamageTarget() const;

	const SLTagGrenadeParams::SCommonParams& GetModeParams() const;

	CStickyProjectile	m_stickyProjectile;

	Vec3				m_launchLoc;
	Vec3				m_normal;
	
	ELTAGGrenadeType	m_grenadeType;


	
	bool		m_enemyKilledByCollision;

	float		m_extraArmTime;
	float		m_activeTime;

	EState	m_state;

	IAttachment* m_characterAttachment;

	//int				m_armedSoundId;

	// Specialised Net Lerping
	enum {k_maxNetPoints=32};
	enum {k_netStateInvalid=0, k_netStateReading=1, k_netStateWriting=2};
	Vec3 m_lastPosSet;
	Vec3 m_netDesiredPos;
	Vec3 m_netDesiredVel;
	Vec3 m_lastPos[k_maxNetPoints];
	int16 m_netState;
	int16 m_wasLaunchedByLocalPlayer;
	volatile int m_postStepLock;

public:
	EState NetGetState() const { return m_state; }
	void NetSetState(EState inState);
};


#endif // __LTAG_GRENADE_H__

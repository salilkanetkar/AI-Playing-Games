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

#ifndef __DEFLECTOR_SHIELD_H__
#define __DEFLECTOR_SHIELD_H__

#if _MSC_VER > 1000
# pragma once
#endif



class CProjectile;


class CDeflectorShield : public CGameObjectExtensionHelper<CDeflectorShield, IGameObjectExtension>
{
private:
	struct SDeflectedEnergy
	{
		// Note: we need to store the deflection position and direction 
		// in the local-space of the collider so that things don't get 
		// messed up when the collider has been moved during the deflection
		// delay (otherwise it might actually spawn a deflected projectile
		// inside the collider again, for example).

		// The impact position in the local-space of the shield collider.
		Vec3 m_localPosition;

		// The deflection normal direction in the local-space of the shield collider.
		Vec3 m_localDirection;

		float m_delay;
		int m_damage;
	};
	typedef std::deque<SDeflectedEnergy> TDeflectedEnergies;

public:
	DECLARE_COMPONENT_TYPE("CDeflectorSheild",0x312A769409E04997,0x9759CD7FEF2AF478)
	CDeflectorShield();

	// IGameObjectExtension
	virtual void GetMemoryUsage(ICrySizer *pSizer) const;
	virtual bool Init(IGameObject * pGameObject);
	virtual void PostInit(IGameObject * pGameObject);
	virtual void InitClient (ChannelId channelId);
	virtual void PostInitClient (ChannelId channelId);
	virtual bool ReloadExtension(IGameObject * pGameObject, const SEntitySpawnParams &params);
	virtual void PostReloadExtension(IGameObject * pGameObject, const SEntitySpawnParams &params);
	virtual bool GetEntityPoolSignature(TSerialize signature);
	//virtual void Release();
	virtual void FullSerialize(TSerialize ser);
	virtual bool NetSerialize(TSerialize ser, EEntityAspects aspect, uint8 profile, int pflags);
	virtual void PostSerialize();
	virtual void SerializeSpawnInfo(TSerialize ser, IEntity *);
	virtual ISerializableInfoPtr GetSpawnInfo();
	virtual void Update(SEntityUpdateContext& ctx, int updateSlot);
	virtual void HandleEvent(const SGameObjectEvent& event);
	virtual void ProcessEvent(SEntityEvent& event);	
	virtual void SetChannelId (ChannelId id);
	virtual void SetAuthority(bool auth );
	virtual const void * GetRMIBase() const;
	virtual void PostUpdate(float frameTime);
	virtual void PostRemoteSpawn();
	// ~IGameObjectExtension

	// Deflection control:
	void SetNonDeflectedOwnerGroup(int pGroupID);
	void SetPhysicsCollisionResponse(bool normalCollResonseFlag);

	// Recharge/depletion control:	
	bool IsDepleted() const;
	void Recharged();
	void Depleted();
	void SetInvulnerability(const bool invulnerableFlag);


private:
	void LoadScriptProperties();
	void PreCacheAmmoResources();

	void ProcessCollision(const EventPhysCollision& pCollision);
	void ProcessProjectile(CProjectile* pProjectile, Vec3 hitPosition, Vec3 hitNormal, Vec3 hitDirection);
	void UpdateDeflectedEnergies(float deltaTime);
	void ValidateUpdateSlot();
	void ShootDeflectedEnergy(const SDeflectedEnergy& energy);
	void PurgeDeflectedEnergiesBuffer();

	// Deflection control:
	bool CanProjectilePassThroughShield(const CProjectile* pProjectile) const;

	// Life-time:
	bool IsDead() const;

	void DebugDraw();

	TDeflectedEnergies m_deflectedEnergies;
	IEntityClass* m_pAmmoClass;
	IParticleEffect* m_pDeflectedEffect;
	int m_minDamage;
	int m_maxDamage;
	float m_dropMinDistance;
	float m_dropPerMeter;
	float m_spread;
	int m_hitTypeId;

	float m_energyRadius;
	float m_invEnergyDelay;

	// Any entity (or its owner) that is a member of this group will not be 
	// deflected (0 if none).
	int m_NonDeflectedOwnersGroupID;
};

DECLARE_COMPONENT_POINTERS(CDeflectorShield)

DECLARE_COMPONENT_POINTERS(CDeflectorShield)


#endif

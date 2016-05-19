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

#ifndef _SMOKE_MANAGER_H_
#define _SMOKE_MANAGER_H_

#include "Weapon.h"

#define MAX_SMOKE_INSTANCES 32

enum ESmokeInstanceState
{
	eSIS_Unassigned = 0,
	eSIS_Active_PhysicsAwake,
	eSIS_Active_PhysicsAsleep,
	eSIS_ForDeletion
};

struct SSmokeInstance
{
	SSmokeInstance()
		: pObstructObject(NULL)
	{

	}
	
	void RemoveObstructionObject();

	Vec3  vPositon;
	float fCurrentRadius;
	float	fTimer;
	float fMaxRadius;
	EntityId grenadeId;
	int32 state;
	IPhysicalEntity *pObstructObject;
};

class CSmokeManager
{
public:
	CSmokeManager();
	virtual ~CSmokeManager();

	static CSmokeManager * GetSmokeManager();

	void Reset();
	void ReleaseObstructionObjects();

	void Update(float dt);
	void CreateNewSmokeInstance(EntityId grenadeId, EntityId grenadeOwnerId, float fMaxRadius);

	bool CanSeePointThroughSmoke(const Vec3& vTarget, const Vec3& vSource) const;
	bool CanSeeEntityThroughSmoke(const EntityId entityId) const;
	bool CanSeeEntityThroughSmoke(const EntityId entityId, const Vec3& vSource) const;

	bool IsPointInSmoke(const Vec3& vPos, float& outInsideFactor) const;

private:
	void UpdateSmokeInstance(SSmokeInstance& smokeInstance, float dt);
	void Init();

	void CullOtherSmokeEffectsInProximityWhenGrenadeHasLanded(SSmokeInstance& smokeInstance, IEntity* pGrenade);
	void GetClientPos(Vec3&) const;
	bool ClientInsideSmoke(float& outInsideFactor) const;
	void SetSmokeSoundmood(const bool enable);
	void SetBlurredVision(const float blurAmmount, const float frameTime);

	void CreateSmokeObstructionObject(SSmokeInstance& smokeInstance);

	void LoadParticleEffects();
	void ReleaseParticleEffects();

#ifndef _RELEASE
	void DrawSmokeDebugSpheres();
#endif

	SSmokeInstance	m_smokeInstances[MAX_SMOKE_INSTANCES];
	char						PRFETCH_PADDING[116];									//128 bytes - sizeof(Variables below this). Over-allocation avoids
																												// potential memory page prefetch issues

	const static float kInitialDelay;
	const static float kMaxPhysicsSleepTime;
	const static float kMaxSmokeRadius;
	const static float kSmokeEmitEndTime;
	const static float kSmokeLingerTime;
	const static float kSmokeRadiusIncrease;
	const static float kBlurStrength;
	const static float kBlurBrightness;
	const static float kBlurContrast;
	const static uint32 kMaxSmokeEffectsInSameArea;
	const static float kClientReduceBlurDelta;

	IParticleEffect*	m_pExplosionParticleEffect;
	IParticleEffect*	m_pInsideSmokeParticleEffect;
	IParticleEffect*	m_pOutsideSmokeParticleEffect;

	IParticleEmitter* m_pInsideSmokeEmitter;

	int m_numActiveSmokeInstances;

	float m_clientBlurAmount;
	bool m_clientInSmoke;

	bool m_loadedParticleEffects;
};

#endif //_SMOKE_MANAGER_H_
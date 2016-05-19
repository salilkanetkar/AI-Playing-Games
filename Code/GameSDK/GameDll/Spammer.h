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

#ifndef _SPAMMER_H_
#define _SPAMMER_H_


#include "Single.h"


class CSpammerCloudTargets
{
public:
	struct STarget
	{
		EntityId m_target;
		int m_numLocks;
	};

public:
	CSpammerCloudTargets();

	bool Empty() const;
	void Clear();

	void LockOn(EntityId target);
	int GetNumLockOns() const;
	int GetNumLockOns(EntityId target) const;
	const STarget& GetTarget(int idx) const;
	int GetNumTargets() const;

	EntityId UnlockNext();

private:
	std::vector<STarget> m_targets;
	int m_numLockOns;
};



class CSpammerPotentialTargets
{
public:
	struct STarget
	{
		EntityId m_target;
		float m_probability;
	};

public:

	void Clear();
	void AddTarget(EntityId target, float probability);

public:
	std::vector<STarget> m_potentialTargets;
	float m_totalProbability;
};



class CSpammer : public CSingle
{
private:
	enum EState
	{
		EState_None,
		EState_LoadingIn,
		EState_Bursting,
	};

	typedef CSingle BaseFiremode;
public:
	CRY_DECLARE_GTI(CSpammer);

	CSpammer();

	virtual void Activate(bool activate);
	virtual void Update(float frameTime, uint32 frameId);
	virtual void StartFire();
	virtual void StopFire();

	ILINE const CSpammerPotentialTargets& GetPotentialTargets() { return m_potentialTargets; }
	ILINE const CSpammerCloudTargets& GetLockOnTargets() { return m_targetsAssigned; }

private:
	bool ShootRocket(EntityId target);

	void UpdateLoadIn(float frameTime);
	void UpdateBurst(float frameTime);
	void UpdatePotentialTargets();

	void StartLoadingIn();
	void StartBursting();

	void AddTarget();
	void ShootNextTarget();

	Vec3 GetWeaponPosition(const Vec3& probableHit) const;
	Vec3 GetWeaponDirection(const Vec3& firingPosition, const Vec3& probableHit) const;

	EntityId GetNextLockOnTarget() const;

	EState m_state;
	CSpammerPotentialTargets m_potentialTargets;
	CSpammerCloudTargets m_targetsAssigned;
	float m_timer;
	float m_nextFireTimer;
	int m_numLoadedRockets;
	bool m_firingPending;
};


#endif

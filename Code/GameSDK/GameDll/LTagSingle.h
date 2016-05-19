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

// Description : Ltag version of single firemode. Requires some extra functionality
//               for animation, projectile spawning, etc


#pragma once

#ifndef _LTAG_SINGLE_H_
#define _LTAG_SINGLE_H_

#include "Single.h"
#include "LTAGGrenade.h"
#include "Throw.h"

class CLTagSingle : public CSingle
{
private:
	typedef CSingle Parent;
	struct EndCockingAction;
	struct ScheduleReload;

public:
	CRY_DECLARE_GTI(CLTagSingle);

	CLTagSingle();
	virtual ~CLTagSingle();

	//CSingle
	virtual void Activate(bool activate);
	virtual void UpdateFPView(float frameTime);

	virtual void OnShoot(EntityId shooterId, EntityId ammoId, IEntityClass* pAmmoType, const Vec3 &pos, const Vec3 &dir, const Vec3 &vel);

	virtual void SetProjectileLaunchParams(const SProjectileLaunchParams &launchParams);
	//~CSingle

	bool NextGrenadeType();
	const ELTAGGrenadeType GetCurrentGrenadeType() const;
	//bool NetSerialize( TSerialize ser, EEntityAspects aspect, uint8 profile, int flags );
	//uint NetGetGrenadeType() const { return static_cast<uint>(m_grenadeType); }
	//void NetSetGrenadeType(uint type);
	void NetShootEx(const Vec3 &pos, const Vec3 &dir, const Vec3 &vel, const Vec3 &hit, float extra, int predictionHandle);

	void GetMemoryUsage(ICrySizer * s) const
	{
		s->AddObject(this, sizeof(*this));	
		CSingle::GetInternalMemoryUsage(s);		// collect memory of parent class
	}

protected:
	virtual void SetReloadFragmentTags(CTagState& fragTags, int ammoCount);

	void SwitchGrenades ();
	void UpdateGrenadeAttachment(ICharacterInstance* pCharacter, const char* attachmentName, const char* model);

	ELTAGGrenadeType m_grenadeType;
	bool	m_fpModelInitialised;
};



#endif

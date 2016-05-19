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

// Description : VehicleWeapon Implementation


#if !defined(__VEHICLE_WEAPON_GUIDED_H__)
#define __VEHICLE_WEAPON_GUIDED_H__


#include "VehicleWeapon.h"

struct IVehicle;
struct IVehiclePart;
struct IVehicleSeat;
struct IVehicleAnimation;

class CVehicleWeaponGuided : public CVehicleWeapon
{
public:

	DECLARE_COMPONENT_TYPE("CVehicleWeaponGuided", 0x74E770A760674A8D,0x86F86562CA3E1CB4)
	CVehicleWeaponGuided();
	virtual ~CVehicleWeaponGuided() {};
  
	// CWeapon
	virtual void ReadProperties(IScriptTable *pScriptTable);
	virtual bool Init(IGameObject * pGameObject);
	virtual void PostInit(IGameObject * pGameObject);
	virtual void Reset();

	virtual void StartFire();

	virtual void SetDestination(const Vec3& pos);
	virtual const Vec3& GetDestination();

	virtual void Update(SEntityUpdateContext& ctx, int update);

	//Vec3 GetSlotHelperPos(int slot, const char *helper, bool worldSpace, bool relative) const;

protected:

	enum eWeaponGuidedState
	{
		eWGS_INVALID,
		eWGS_PREPARATION,
		eWGS_WAIT,
		eWGS_FIRE,
		eWGS_FIRING,
		eWGS_POSTSTATE,
	};

	eWeaponGuidedState	m_State;
	eWeaponGuidedState	m_NextState;

	Vec3				m_DesiredHomingTarget;
	
	string				m_VehicleAnimName;
	string				m_PreStateName;
	string				m_PostStateName;

	float					m_firedTimer;
	
	IVehicleAnimation	*m_pVehicleAnim;
	int					m_PreState;
	int					m_PostState;
};



#endif //#if !defined(__VEHICLE_WEAPON_GUIDED_H__)
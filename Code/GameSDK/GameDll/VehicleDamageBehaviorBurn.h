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

// Description : Implements a damage behavior which burn stuff

#ifndef __VEHICLEDAMAGEBEHAVIORBURN_H__
#define __VEHICLEDAMAGEBEHAVIORBURN_H__

class CVehicle;

class CVehicleDamageBehaviorBurn
	: public IVehicleDamageBehavior
{
	IMPLEMENT_VEHICLEOBJECT
public:

	CVehicleDamageBehaviorBurn();
	virtual ~CVehicleDamageBehaviorBurn();

	virtual bool Init(IVehicle* pVehicle, const CVehicleParams& table);
	virtual void Reset();
	virtual void Release() { delete this; }

	virtual void OnDamageEvent(EVehicleDamageBehaviorEvent event, const SVehicleDamageBehaviorEventParams& behaviorParams);

	virtual void Serialize(TSerialize ser, EEntityAspects aspects);
	virtual void Update(const float deltaTime);
  virtual void OnVehicleEvent(EVehicleEvent event, const SVehicleEventParams& params);

	virtual void GetMemoryUsage(ICrySizer * s) const{ s->Add(*this); }

protected:

  void Activate(bool activate);

	IVehicle* m_pVehicle;
	IVehicleHelper* m_pHelper;

  float m_damageRatioMin;
	float m_damage;
  float m_selfDamage;
	float m_interval;
	float m_radius;

	bool m_isActive;
	float m_timeCounter;

	EntityId m_shooterId;
  int m_timerId;
};

#endif

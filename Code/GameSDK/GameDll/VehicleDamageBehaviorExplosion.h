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

// Description : Implements a damage behavior which create an explosion


#ifndef __VEHICLEDAMAGEBEHAVIOREXPLOSION_H__
#define __VEHICLEDAMAGEBEHAVIOREXPLOSION_H__

class CVehicle;

class CVehicleDamageBehaviorExplosion
	: public IVehicleDamageBehavior
{
	IMPLEMENT_VEHICLEOBJECT
public:

	CVehicleDamageBehaviorExplosion();
	virtual ~CVehicleDamageBehaviorExplosion() {}

	virtual bool Init(IVehicle* pVehicle, const CVehicleParams& table);
	virtual void Reset();
	virtual void Release() { delete this; }

	virtual void OnDamageEvent(EVehicleDamageBehaviorEvent event, const SVehicleDamageBehaviorEventParams& behaviorParams);

	virtual void Serialize(TSerialize ser, EEntityAspects aspects);
	virtual void Update(const float deltaTime) {}
  virtual void OnVehicleEvent(EVehicleEvent event, const SVehicleEventParams& params){}

	virtual void GetMemoryUsage(ICrySizer * s) const { s->Add(*this); }

protected:

	IVehicle* m_pVehicle;

	float m_damage;
	float m_minRadius;
	float m_radius;
	float m_minPhysRadius;
	float m_physRadius;
	float m_pressure;
	float m_soundRadius;
	IVehicleHelper* m_pHelper;

  bool m_exploded;
};

#endif

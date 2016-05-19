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

// Description : Implements a vehicle action for landing gears


#ifndef __VEHICLEACTIONLANDINGGEARS_H__
#define __VEHICLEACTIONLANDINGGEARS_H__

class CVehicleActionLandingGears
	: public IVehicleAction
{
	IMPLEMENT_VEHICLEOBJECT;

public:

	CVehicleActionLandingGears();
	virtual ~CVehicleActionLandingGears();

	// IVehicleAction
	virtual bool Init(IVehicle* pVehicle, const CVehicleParams& table);
	virtual void Reset();
	virtual void Release() { delete this; }

	virtual int OnEvent(int eventType, SVehicleEventParams& eventParams);
	void GetMemoryStatistics(ICrySizer * s) { s->Add(*this); }
	// ~IVehicleAction

	// IVehicleObject
	virtual void Serialize(TSerialize ser, EEntityAspects aspects);
	virtual void Update(const float deltaTime);
  virtual void OnVehicleEvent(EVehicleEvent eventType, const SVehicleEventParams& params);
	// ~IVehicleObject

	bool AreLandingGearsOpen();
	void ExtractGears();
	void RetractGears();

protected:

	IVehicle* m_pVehicle;

	// Settings variables (do not change outside Init)
	float m_altitudeToRetractGears;
	float m_landingDamages;
	float m_velocityMax;
	float m_minTimeForChange;

	bool m_isOnlyAutoForPlayer;

	IVehicleAnimation* m_pLandingGearsAnim;
	TVehicleAnimStateId m_landingGearOpenedId;
	TVehicleAnimStateId m_landingGearClosedId;

	IVehiclePart* m_pPartToBlockRotation;

	// Status variables
	bool m_isDriverPlayer;
	bool m_isDestroyed;
	float m_damageReceived;

	float m_animTime;
	float m_animGoal;
	float m_timer;
};

#endif

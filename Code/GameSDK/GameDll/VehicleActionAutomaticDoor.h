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
// Description : Implements a vehicle action for an automatic door

#ifndef __VEHICLEACTIONAUTOMATICDOOR_H__
#define __VEHICLEACTIONAUTOMATICDOOR_H__

class CVehicleActionAutomaticDoor
: public IVehicleAction
{
	IMPLEMENT_VEHICLEOBJECT;

public:

	CVehicleActionAutomaticDoor();
	virtual ~CVehicleActionAutomaticDoor();

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
  virtual void OnVehicleEvent(EVehicleEvent event, const SVehicleEventParams& params);
	// ~IVehicleObject

	void OpenDoor(bool value);
	void BlockDoor(bool value);

	bool IsOpened();

protected:

	IVehicle* m_pVehicle;
	
	IVehicleAnimation* m_pDoorAnim;
	TVehicleAnimStateId m_doorOpenedStateId;
	TVehicleAnimStateId m_doorClosedStateId;

	float m_timeMax;
	float m_eventSamplingTime;
	bool m_isTouchingGroundBase;

	float m_timeOnTheGround;
	float m_timeInTheAir;
	bool m_isTouchingGround;
	bool m_isOpenRequested;
	bool m_isBlocked;
	bool m_isDisabled;

	float m_animGoal;
	float m_animTime;

	friend class CScriptBind_AutomaticDoor;
};

#endif

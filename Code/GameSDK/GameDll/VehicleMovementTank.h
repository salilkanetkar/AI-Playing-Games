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

// Description : Implements movement type for tracked vehicles

#ifndef __VEHICLEMOVEMENTTANK_H__
#define __VEHICLEMOVEMENTTANK_H__

#include "VehicleMovementArcadeWheeled.h"

#if !defined(_RELEASE)
#define DEBUG_TANK_AI
#endif

class CVehicleMovementTank
  :   public CVehicleMovementArcadeWheeled
{
private:
	typedef CVehicleMovementArcadeWheeled inherited;

public:

	CVehicleMovementTank();
	virtual ~CVehicleMovementTank();

	// overrides from StdWheeled
	virtual bool Init(IVehicle* pVehicle, const CVehicleParams& table);  
	virtual void PostInit();
	virtual void Reset();

	virtual void ProcessAI(const float deltaTime);
	virtual void ProcessMovement(const float deltaTime);

	virtual void OnEvent(EVehicleMovementEvent event, const SVehicleMovementEventParams& params);
	virtual void OnAction(const TVehicleActionId actionId, int activationMode, float value);

	virtual void Update(const float deltaTime);

	virtual void GetMemoryUsage(ICrySizer * pSizer) const;
	// ~StdWheeled

	virtual float GetEnginePedal(){ return m_currPedal; }

protected:  

	virtual bool DoGearSound() { return false; }
	virtual float GetMinRPMSoundRatio() { return 0.6f; }  
#if ENABLE_VEHICLE_DEBUG
	virtual void DebugDrawMovement(const float deltaTime);
#endif
	virtual float GetWheelCondition() const;

	float m_currPedal;
	float m_currSteer;

	typedef std::vector<IVehiclePart*> TTreadParts;
	TTreadParts m_treadParts;    

#ifdef DEBUG_TANK_AI
	struct Debug
	{
		Vec3 targetPos;
		float inputSpeed;
	};
	Debug m_debug;
#endif

};

#endif

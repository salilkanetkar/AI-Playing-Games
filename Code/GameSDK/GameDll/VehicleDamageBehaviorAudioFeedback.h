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

// Description : Implements a damage behavior that plays sounds when the
//               vehicle is hit  different for first and third person


#ifndef __VEHICLE_DAMAGE_BEHAVIOR_AUDIO_FEEDBACK_H__
#define __VEHICLE_DAMAGE_BEHAVIOR_AUDIO_FEEDBACK_H__

#include "Audio/AudioTypes.h"
#include "IVehicleSystem.h"

class CVehicleDamageBehaviorAudioFeedback
	: public IVehicleDamageBehavior
{
	IMPLEMENT_VEHICLEOBJECT
public:

	CVehicleDamageBehaviorAudioFeedback();
	virtual ~CVehicleDamageBehaviorAudioFeedback();

	virtual bool Init(IVehicle* pVehicle, const CVehicleParams& table);
	virtual void Reset() {}
	virtual void Release() { delete this; }

	virtual void OnDamageEvent(EVehicleDamageBehaviorEvent event, const SVehicleDamageBehaviorEventParams& behaviorParams) {};

	virtual void Serialize(TSerialize ser, EEntityAspects aspects) {}
	virtual void Update(const float deltaTime) {}
	virtual void OnVehicleEvent(EVehicleEvent event, const SVehicleEventParams& params);

	virtual void GetMemoryUsage(ICrySizer * s) const { s->Add(*this); }

protected:
	TAudioSignalID GetSignal() const;

	TAudioSignalID m_firstPersonSignal;
	TAudioSignalID m_thirdPersonSignal;
	EntityId m_vehicleId;
};

#endif //__VEHICLE_DAMAGE_BEHAVIOR_AUDIO_FEEDBACK_H__

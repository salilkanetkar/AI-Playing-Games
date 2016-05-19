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

// Description : Makes the vehicle a target for auto asist


#ifndef __VEHICLEACTIONAUTOTARGET_H__
#define __VEHICLEACTIONAUTOTARGET_H__

#include "IVehicleSystem.h"
#include "AutoAimManager.h"

class CVehicleActionAutoTarget
	: public IVehicleAction
{
	IMPLEMENT_VEHICLEOBJECT;

public:
	CVehicleActionAutoTarget();
	virtual ~CVehicleActionAutoTarget();

	virtual bool Init(IVehicle* pVehicle, const CVehicleParams& table);
	virtual void Reset();
	virtual void Release();

	virtual int OnEvent(int eventType, SVehicleEventParams& eventParams);
	virtual void OnVehicleEvent(EVehicleEvent event, const SVehicleEventParams& params);

	// IVehicleObject
	virtual void Serialize(TSerialize ser, EEntityAspects aspects) {};
	virtual void Update(const float deltaTime) {};
	// ~IVehicleObject

protected:
	SAutoaimTargetRegisterParams m_autoAimParams;

	IVehicle* m_pVehicle;
	bool m_RegisteredWithAutoAimManager;

private:
	static const char * m_name;
};

#endif //__VEHICLEACTIONAUTOTARGET_H__

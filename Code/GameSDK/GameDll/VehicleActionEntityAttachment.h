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

// Description : Implements a vehicle action for Entity Attachment


#ifndef __VEHICLEACTIONENTITYATTACHMENT_H__
#define __VEHICLEACTIONENTITYATTACHMENT_H__

class CVehicleActionEntityAttachment
	: public IVehicleAction
{
	IMPLEMENT_VEHICLEOBJECT;

public:

	CVehicleActionEntityAttachment();
	virtual ~CVehicleActionEntityAttachment();

	// IVehicleAction
	virtual bool Init(IVehicle* pVehicle, const CVehicleParams& table);
	virtual void Reset();
	virtual void Release() { delete this; }

	virtual int OnEvent(int eventType, SVehicleEventParams& eventParams);
	void GetMemoryStatistics(ICrySizer * s) { s->Add(*this); }
	// ~IVehicleAction

	// IVehicleObject
	virtual void Serialize(TSerialize ser, EEntityAspects aspects) {}
	virtual void Update(const float deltaTime);
	virtual void OnVehicleEvent(EVehicleEvent event, const SVehicleEventParams& params){}
	// ~IVehicleObject

	bool DetachEntity();
	bool IsEntityAttached() { return m_isAttached; }

	EntityId GetAttachmentId() { return m_entityId; }

protected:

	void SpawnEntity();

	IVehicle* m_pVehicle;

	string m_entityClassName;
	IVehicleHelper* m_pHelper;

	EntityId m_entityId;
	bool m_isAttached;

	float m_timer;
};

#endif

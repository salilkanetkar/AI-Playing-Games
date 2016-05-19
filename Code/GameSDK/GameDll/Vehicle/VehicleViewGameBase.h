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

// Description : Implements a base class for the vehicle views


#ifndef __VEHICLEVIEWBASE_H__
#define __VEHICLEVIEWBASE_H__

class CVehicleViewGameBase
	: public IVehicleView
{
public:

	CVehicleViewGameBase();

	// IVehicleView
	virtual bool Init(IVehicleSeat* pSeat, const CVehicleParams& table);
	virtual void Reset();
	virtual void ResetPosition() {};
	virtual void Release() { delete this; }

	virtual const char* GetName() { return NULL; }  
	virtual bool IsThirdPerson() = 0;
	virtual bool IsPassengerHidden() { return m_hidePlayer; }

	virtual void OnStartUsing(EntityId passengerId);
	virtual void OnStopUsing();

	virtual void OnAction(const TVehicleActionId actionId, int activationMode, float value);
	virtual void UpdateView(SViewParams &viewParams, EntityId playerId) {}

	virtual void Update(const float frameTime);
	virtual void Serialize(TSerialize serialize, EEntityAspects);

	virtual void SetDebugView(bool debug) { m_isDebugView = debug; }
	virtual bool IsDebugView() { return m_isDebugView; }

	virtual bool ShootToCrosshair() { return true; }
	virtual bool IsAvailableRemotely() const { return m_isAvailableRemotely; }
	// ~IVehicleView

	virtual void OnVehicleEvent(EVehicleEvent event, const SVehicleEventParams& params){}

	bool Init(IVehicleSeat* pSeat);

protected:

	IVehicle* m_pVehicle;
	IVehiclePart* m_pAimPart;
	IVehicleSeat* m_pSeat;

	bool m_hidePlayer;
	bool m_isDebugView;
	bool m_isAvailableRemotely;
	bool m_playerViewThirdOnExit;

	typedef std::vector <string> TVehiclePartNameVector;
	TVehiclePartNameVector m_hideParts;
};

#endif

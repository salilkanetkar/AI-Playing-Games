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

// Description : Implements a class which handle client actions on vehicles.


#ifndef __VEHICLECLIENT_H__
#define __VEHICLECLIENT_H__

#include "IVehicleSystem.h"

class CPlayer;

enum EVehicleActionExtIds
{
	eVAI_ActionsExt = eVAI_Others,
	eVAI_RipoffWeapon,
};

enum EVehicleEventExtIds
{
	eVE_EventsExt = eVE_Last,
};

class CVehicleClient
	: public IVehicleClient
{
public:

	virtual bool Init();
	virtual void Reset();
	virtual void Release() { delete this; }

	virtual void OnAction(IVehicle* pVehicle, EntityId actorId, const ActionId& actionId, int activationMode, float value);
	virtual void PreUpdate(IVehicle* pVehicle, EntityId actorId, float frameTime);
	virtual void OnEnterVehicleSeat(IVehicleSeat* pSeat);
	virtual void OnExitVehicleSeat(IVehicleSeat* pSeat);

protected:

	void ProcessXIAction(IVehicle* pVehicle, const EntityId actorId, const float value, const TVehicleActionId leftAction, const TVehicleActionId rightAction, bool& leftFlag, bool& rightFlag);
	void EnableActionMaps(IVehicleSeat* pSeat, bool enable);
	void ResetFlags();
	bool ShouldInvertPitch(IVehicle* pVehicle) const;

	typedef std::map<ActionId, int> TActionNameIdMap;
	TActionNameIdMap m_actionNameIds;

private:
	void InsertActionMapValue(const char * pString, int eVehicleAction);

	struct SPairedAction
	{
		float m_postive;
		float m_negative;

		void Reset()
		{
			m_postive = 0.f;
			m_negative = 0.f;
		}

		float GetAccumlated()
		{
			return m_postive + m_negative;
		}
	};

	Ang3 m_xiRotation;
  SPairedAction m_fLeftRight;
  SPairedAction m_fForwardBackward;
  SPairedAction m_fAccelDecel;
	bool m_bMovementFlagForward;
	bool m_bMovementFlagBack;
	bool m_bMovementFlagRight;
	bool m_bMovementFlagLeft;
	bool m_bMovementFlagUp;
	bool m_bMovementFlagDown;
	bool m_bMovementFlagStrafeLeft;
	bool m_bMovementFlagStrafeRight;

  bool m_tp;

};

#endif

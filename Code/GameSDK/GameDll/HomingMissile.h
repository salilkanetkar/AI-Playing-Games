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

// Description : HomingMissile


#ifndef __HomingMissile_H__
#define __HomingMissile_H__

#if _MSC_VER > 1000
# pragma once
#endif


#include "Rocket.h"

#define ASPECT_DESTINATION eEA_GameClientDynamic

class CHomingMissile : public CRocket
{
public:
	CHomingMissile();
	virtual ~CHomingMissile();

	DECLARE_COMPONENT_TYPE("CHomingMissile", 0xE528F07231F3421E,0x903A48AF5594F515)
  
	// CRocket	
	virtual bool Init(IGameObject *pGameObject);
	virtual void Update(SEntityUpdateContext &ctx, int updateSlot);
	virtual void Launch(const Vec3 &pos, const Vec3 &dir, const Vec3 &velocity, float speedScale);
	virtual void SetDestination(const Vec3& pos);

	virtual void SetDestination(EntityId targetId)
	{
		m_targetId = targetId;
	}

	virtual void Deflected(const Vec3& dir);

	virtual void FullSerialize(TSerialize ser);
	virtual bool NetSerialize(TSerialize ser, EEntityAspects aspect, uint8 profile, int flags);
	virtual NetworkAspectType GetNetSerializeAspects();
	// ~CRocket

	void OnRayCastDataReceived(const QueuedRayID& rayID, const RayCastResult& result);

protected:

	void SetViewMode(CItem::eViewMode viewMode);

	virtual void UpdateControlledMissile(float frameTime);   //LAW missiles
	virtual void UpdateCruiseMissile(float frameTime);       //Vehicle missiles

	void SerializeDestination( TSerialize ser );

	void UpdateHomingGuide();

	ILINE bool HasTarget() const { return !m_destination.IsZeroFast(0.3f); }; //Net serialize inaccuracy means checking for actual zero is not sufficient

	Vec3 m_homingGuidePosition;
	Vec3 m_homingGuideDirection;

	Vec3 m_destination;
  
	EntityId	m_targetId;

	float m_lockedTimer;
	float m_controlLostTimer;

	QueuedRayID m_destinationRayId;

	// status
	bool m_isCruising;
	bool m_isDescending;
	bool m_trailEnabled;
};


#endif // __HomingMissile_H__

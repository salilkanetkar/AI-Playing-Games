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

// Description : The internal representation of a hazardous sphere area within the 
//               hazard system.


#include "StdAfx.h"

#include "HazardSphere.h"

#include "HazardShared.h"

#include "HazardModule.h"

#include "../Agent.h"



using namespace HazardSystem;


// ============================================================================
// ============================================================================
// ============================================================================
//
// -- HazardSphere -- HazardSphere -- HazardSphere -- HazardSphere --
//
// ============================================================================
// ============================================================================
// ============================================================================


HazardSphere::HazardSphere() :
	m_CenterPos(ZERO)
	, m_Radius(0.0f)	
{
}


// ============================================================================
//	Constructor.
//
//	In:		The center position of the hazard sphere in world-space.
//	In:		The radius of the sphere (>= 0.0) (in meters).
//
HazardSphere::HazardSphere(
	const Vec3& centerPos, const float radius) :
	m_CenterPos(centerPos)
	, m_Radius(radius)
{
}


HazardSphere::~HazardSphere()
{
	// Nothing to do here.
}


void HazardSphere::Serialize(TSerialize ser)
{
	ser.BeginGroup("HazardSphere");

	ser.Value("CenterPos", m_CenterPos);
	ser.Value("Radius", m_Radius);

	ser.EndGroup();
}


// ============================================================================
// ============================================================================
// ============================================================================
//
// -- HazardDataSphere -- HazardDataSphere -- HazardDataSphere --
//
// ============================================================================
// ============================================================================
// ============================================================================


HazardDataSphere::HazardDataSphere() :
	m_Context()
	, m_RadiusSq(0.0f)
{
}


HazardDataSphere::HazardDataSphere(const HazardDataSphere& source) :
	m_Context(source.m_Context)
	, m_RadiusSq(source.m_RadiusSq)
{
}


void HazardDataSphere::Serialize(TSerialize ser)
{
	HazardData::Serialize(ser);

	ser.BeginGroup("HazardDataSphere");

	m_Context.Serialize(ser);

	if (ser.IsReading())
	{
		m_RadiusSq = m_Context.m_Radius * m_Context.m_Radius;
	}

	ser.EndGroup();
}


// ===========================================================================
//	Get the hazard sphere ID.
//
//	Returns:		The hazard sphere ID.
//
HazardSphereID HazardDataSphere::GetTypeInstanceID() const
{
	return HazardSphereID(HazardData::GetInstanceID());
}


// ============================================================================
//	Get the 'direction' normal vector of the hazard.
//
//	Returns:	The direction normal vector of the hazard (or a 0 vector
//				if there is no specific direction, such as an explosion).
//
const Vec3& HazardDataSphere::GetNormal() const
{
	return Vec3Constants<float>::fVec3_Zero;
}


// ============================================================================
//	Query if the agent is/can be aware of the danger.
//
//	In:			The agent.
//	In:			The avoid position in world-space.
//
//	Returns:	True if the agent is/can be aware of the danger; otherwise
//				false.
//
bool HazardDataSphere::IsAgentAwareOfDanger(
	const Agent& agent, const Vec3& avoidPos) const
{	
	return true;
}


// ===========================================================================
// Process possible collision between an agent and the hazard.
//
//	In:		The agent.
//	Out:	The collision result (NULL is invalid!)
//
void HazardDataSphere::CheckCollision(Agent& agent, HazardCollisionResult* result) const
{
	assert(result != NULL);
	result->Reset();

	if (Distance::Point_PointSq(agent.GetPos(), m_Context.m_CenterPos) > 
		m_RadiusSq)
	{
		return;
	}		

	result->m_CollisionFlag = true;
	result->m_HazardOriginPos = m_Context.m_CenterPos;
	return;
}


#if !defined(_RELEASE)


// ============================================================================
//	Render debug information.
//
//	In,out:		The debug renderer.
//
void HazardDataSphere::DebugRender (IPersistentDebug& debugRenderer) const
{
	debugRenderer.AddSphere(m_Context.m_CenterPos, m_Context.m_Radius, 
		HazardModule::debugColor, HazardModule::debugPrimitiveFadeDelay);
}


#endif // !defined(_RELEASE)

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

// Description : Utility classes for pick&throw mechanic

#pragma once

#ifndef _PICKANDTHROW_UTILITIES_H_
#define _PICKANDTHROW_UTILITIES_H_

struct IActor;
struct IStatObj;
#if !defined(LINUX) && !defined(APPLE) && !defined(ORBIS)
struct IStatObj::SSubObject;
#endif
namespace PickAndThrow
{
	class CObstructionCheck
	{

	public:
		CObstructionCheck();
		~CObstructionCheck();

		void DoCheck( IActor* pOwnerActor, EntityId objectId);
		void IntersectionTestComplete(const QueuedIntersectionID& intersectionID, const IntersectionTestResult& result);

		void Reset();

		ILINE bool IsObstructed() const { return m_obstructed; }

	private:

		QueuedIntersectionID	m_queuedPrimitiveId;
		bool					m_obstructed;
	};

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	IStatObj::SSubObject* FindHelperObject( const char* pHelperName, const EntityId objectId, const int slot );
	IStatObj::SSubObject* FindHelperObject_Basic( const char* pHelperName, const EntityId objectId, const int slot );
	IStatObj::SSubObject* FindHelperObject_Extended( const char* pHelperName, const EntityId objectId, const int slot );
	IStatObj::SSubObject* FindHelperObject_RecursivePart( IStatObj* pObj, const char* pHelperName );
	int FindActiveSlot( const EntityId objectId );

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	bool TargetEntityWithinFrontalCone(const Vec3& attackerLocation,const Vec3& victimLocation,const Vec3& attackerFacingdir, const float targetConeRads, float& theta);
	bool AllowedToTargetPlayer(const EntityId attackerId, const EntityId victimEntityId);

	ILINE float SelectAnimDurationOverride(const float cVarOverride, const float XMLOverride)
	{
		// This is the equivalent of the following more verbose version...
		/*

		float desiredDuration     =  cVarOverride;
		
		// If CVAR override not set.. we fall back to XML
		if(cVarOverride < 0.0f)
		{
			desiredDuration = XMLOverride;
		}

		return desiredDuration;

		*/

		return static_cast<float>(fsel(cVarOverride, cVarOverride, XMLOverride));
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}

#endif //_PICKANDTHROW_UTILITIES_H_

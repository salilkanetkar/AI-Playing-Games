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

#pragma once

#ifndef AdvantagePointOccupancyControl_h
#define AdvantagePointOccupancyControl_h



#if defined(CRYAISYSTEM_DEBUG)
struct IRenderAuxGeom;
#endif

class CAdvantagePointOccupancyControl
{
	typedef std::map<EntityId, Vec3> OccupiedAdvantagePoints;

public:
	CAdvantagePointOccupancyControl();
	~CAdvantagePointOccupancyControl();

	void Reset();
	void OccupyAdvantagePoint(EntityId entityId, const Vec3& position);
	void ReleaseAdvantagePoint(EntityId entityId);
	bool IsAdvantagePointOccupied(const Vec3& position) const;
	bool IsAdvantagePointOccupied(const Vec3& position, const EntityId ignoreEntityId) const;

	void Update();

private:

	bool MatchAdvantagePointPosition(const Vec3& position, const Vec3& AdvantagePoint) const;

#if defined(CRYAISYSTEM_DEBUG)

	void DebugDraw() const;
	inline void DebugDrawAdvantagePoint(IRenderAuxGeom* debugRenderer, const EntityId entityID, const Vec3& occupiedPos) const;

#endif


	// TODO: Investigate if we can use tAIObjectID instead of position /Mario
	OccupiedAdvantagePoints m_occupiedAdvantagePoints;

#if defined(CRYAISYSTEM_DEBUG)
	// 0 if debug visualization is disabled, otherwise enabled.
	static int ai_AdvantagePointOccupancyDebug;
#endif
};

#endif //AdvantagePointOccupancyControl_h
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

// Description : Player movement debug for non-release builds


#ifndef _PLAYER_MOVEMENT_DEBUG_H_
#define _PLAYER_MOVEMENT_DEBUG_H_

struct IDebugHistoryManager;

#if !defined(_RELEASE)
	#define PLAYER_MOVEMENT_DEBUG_ENABLED
#endif

#ifdef PLAYER_MOVEMENT_DEBUG_ENABLED

class CPlayerDebugMovement
{
public:
	CPlayerDebugMovement();
	~CPlayerDebugMovement();

	void DebugGraph_AddValue(const char* id, float value) const;
	void Debug(const IEntity* pPlayerEntity);

	void LogFallDamage(const IEntity* pPlayerEntity, const float velocityFraction, const float impactVelocity, const float damage);
	void LogFallDamageNone(const IEntity* pPlayerEntity, const float impactVelocity);
	void LogVelocityStats(const IEntity* pPlayerEntity, const pe_status_living& livStat, const float fallSpeed, const float impactVelocity);

	void GetInternalMemoryUsage(ICrySizer * pSizer) const;

private:
	 IDebugHistoryManager* m_pDebugHistoryManager;
};


#endif

#endif
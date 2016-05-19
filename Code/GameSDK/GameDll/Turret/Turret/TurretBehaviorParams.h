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

#ifndef __TURRET_BEHAVIOR_PARAMS__H__
#define __TURRET_BEHAVIOR_PARAMS__H__



namespace TurretBehaviorParams
{
	struct SRandomOffsetParams
	{
		float updateSeconds;
		float range;

		SRandomOffsetParams();
		void Reset( SmartScriptTable pScriptTable );
	};


	struct SRandomOffsetRuntime
	{
		CTimeValue nextUpdateTime;
		float value;

		SRandomOffsetRuntime();
	};


	struct SUndeployedParams
	{
		bool isThreat;

		SUndeployedParams();
		void Reset( SmartScriptTable pScriptTable );
	};


	struct SSearchSweepParams
	{
		float yawRadiansHalfLimit;
		float yawSweepVelocity;
		float sweepDistance;
		float sweepHeight;
		float scanDelaySeconds;
		float retaliationTimeoutSeconds;
		SRandomOffsetParams randomOffset;

		SSearchSweepParams();
		void Reset( SmartScriptTable pScriptTable );
	};


	struct SSearchSweepRuntime
	{
		float sweepDirection;
		bool arrivedAtSweepEnd;
		SRandomOffsetRuntime randomOffset;

		SSearchSweepRuntime();
	};


	struct SSearchSweepTowardsLocationRuntime
	{
		float sweepYawDirection;
		float targetYawRadians;
		bool arrivedAtSweepEnd;

		SSearchSweepTowardsLocationRuntime();
	};


	struct SSearchSweepPauseParams
	{
		float limitPauseSeconds;
		SRandomOffsetParams randomOffset;

		SSearchSweepPauseParams();
		void Reset( SmartScriptTable pScriptTable );
	};


	struct SSearchSweepPauseRuntime
	{
		CTimeValue exitTime;

		SSearchSweepPauseRuntime();
	};


	struct SFollowTargetParams
	{
		float reevaluateTargetSeconds;
		float minFireDelaySeconds;
		float maxFireDelaySeconds;
		float aimVerticalOffset;
		float predictionDelaySeconds;
		float keepViewRangeTimeoutSeconds;
		SRandomOffsetParams randomOffset;

		SFollowTargetParams();
		void Reset( SmartScriptTable pScriptTable );

		float GetFireDelaySeconds() const;
	};


	struct SFollowTargetRuntime
	{
		CTimeValue reevaluateTime;
		CTimeValue startFireTime;
		SRandomOffsetRuntime randomOffset;

		SFollowTargetRuntime();
	};


	struct SFireTargetParams
	{
		float minStopFireSeconds;
		float maxStopFireSeconds;
		SRandomOffsetParams randomOffset;

		SFireTargetParams();
		void Reset( SmartScriptTable pScriptTable );

		float GetStopFireSeconds() const;
	};


	struct SFireTargetRuntime
	{
		CTimeValue stopFireTime;

		SFireTargetRuntime();
	};


	struct SLostTargetRuntime
	{
		Vec3 lastTargetKnownPosition;
		Vec3 lastTargetKnownVelocity;

		Vec3 predictedPosition;
		Vec3 predictedVelocity;
		EntityId lastEntityId;

		CTimeValue targetLostTimeStart;
		CTimeValue backToSearchTime;

		bool firing;
		CTimeValue nextSwitchFireTime;

		SLostTargetRuntime();

		void UpdateFromEntity( IEntity* pEntity, const float lastValueWeight );
	};

	struct SLostTargetParams
	{
		float backToSearchSeconds;
		float dampenVelocityTimeSeconds;
		float lastVelocityValueWeight;

		SLostTargetParams();
		void Reset( SmartScriptTable pScriptTable );
	};


	struct SBehavior
	{
		SSearchSweepParams searchSweepParams;
		SSearchSweepRuntime searchSweepRuntime;

		SSearchSweepPauseParams searchSweepPauseParams;
		SSearchSweepPauseRuntime searchSweepPauseRuntime;

		SFollowTargetParams followTargetParams;
		SFollowTargetRuntime followTargetRuntime;

		SFireTargetParams fireTargetParams;
		SFireTargetRuntime fireTargetRuntime;

		SLostTargetParams lostTargetParams;
		SLostTargetRuntime lostTargetRuntime;

		SUndeployedParams undeployedParams;

		SSearchSweepTowardsLocationRuntime sweepTowardsLocationRuntime;

		CTimeValue timeNow;

		void UpdateTimeNow();
		void Reset( SmartScriptTable pScriptTable );
	};
}

#endif

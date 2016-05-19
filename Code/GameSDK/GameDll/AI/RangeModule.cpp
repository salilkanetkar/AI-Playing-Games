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

#include "StdAfx.h"
#include "RangeModule.h"
#include "Agent.h"

RangeContainer::RangeID RangeContainer::AddRange(const Range& range)
{
	assert(m_ranges.size() <= std::numeric_limits<RangeID>::max());
	RangeID id = m_ranges.size();
	m_ranges.push_back(range);
	return id;
}

bool RangeContainer::GetTargetDistances(float& distToAttentionTargetSq, float& distToLiveTargetSq) const
{
	Agent agent(m_entityID);
	assert(agent.IsValid());
	IF_UNLIKELY (!agent.IsValid())
		return false;

	if (IAIObject* attentionTarget = agent.GetAttentionTarget())
	{
		distToAttentionTargetSq = agent.GetEntityPos().GetSquaredDistance(attentionTarget->GetPos());
		
		if (IAIObject* liveTarget = agent.GetLiveTarget())
		{
			distToLiveTargetSq = agent.GetEntityPos().GetSquaredDistance(liveTarget->GetPos());
			return true;
		}
	}

	return false;
}

void RangeContainer::Update(float frameTime)
{
	float distToAttentionTargetSq = 0.0f;
	float distToLiveTargetSq = 0.0f;

	if (GetTargetDistances(distToAttentionTargetSq, distToLiveTargetSq))
	{
		Ranges::iterator it = m_ranges.begin();
		Ranges::iterator end = m_ranges.end();

		for ( ; it != end; ++it)
		{
			Range& range = *it;

			float distToTargetSq = 0.0f;
			switch (range.targetMode)
			{
			case Range::UseAttentionTargetDistance:
				distToTargetSq = distToAttentionTargetSq;
				break;
			case Range::UseLiveTargetDistance:
				distToTargetSq = distToLiveTargetSq;
				break;
			default:
				assert(0);
				break;
			}

			Range::State newState = (distToTargetSq < range.rangeSq) ? Range::Inside : Range::Outside;

			if (newState != range.state)
			{
				range.state = newState;

				if (newState == Range::Inside && !range.enterSignal.empty())
					SendSignal(range.enterSignal.c_str());
				else if (newState == Range::Outside && !range.leaveSignal.empty())
					SendSignal(range.leaveSignal.c_str());
			}
		}
	}
}

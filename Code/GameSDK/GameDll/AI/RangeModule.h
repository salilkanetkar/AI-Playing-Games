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

#ifndef RangeModule_h
#define RangeModule_h

#include "GameAIHelpers.h"
#include <limits>

class RangeContainer : public CGameAIInstanceBase
{
public:
	typedef uint8 RangeID;

	struct Range
	{
		Range() : rangeSq(0.0f), state(Outside), targetMode(UseAttentionTargetDistance) {}

		enum State
		{
			Inside,
			Outside
		};

		enum TargetMode
		{
			UseAttentionTargetDistance,
			UseLiveTargetDistance
		};

		string enterSignal;
		string leaveSignal;
		float rangeSq;
		State state;
		TargetMode targetMode;
	};

	void Update(float frameTime);
	RangeID AddRange(const Range& range);

	void ResetRanges()
	{
		m_ranges.clear();
	}

	const Range* GetRange(RangeID id) const
	{
		assert(id < m_ranges.size());
		return (id < m_ranges.size()) ? &m_ranges[id] : 0;
	}

	void ChangeRange(RangeID id, float distance)
	{
		assert(id < m_ranges.size());

		if (id < m_ranges.size())
		{
			m_ranges[id].rangeSq = square(distance);
		}
	}

private:
	bool GetTargetDistances(float& distToAttentionTargetSq, float& distToLiveTarget) const;

	typedef std::vector<Range> Ranges;
	Ranges m_ranges;
};

class RangeModule : public AIModuleWithInstanceUpdate<RangeModule, RangeContainer, 16, 8>
{
public:
	virtual const char* GetName() const { return "RangeModule"; }
};

#endif // RangeModule_h
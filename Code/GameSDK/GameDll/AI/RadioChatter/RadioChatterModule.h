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

#include "../GameAIHelpers.h"

class RadioChatterInstance : public CGameAIInstanceBase
{
};

// Plays radio chatter through a character's intercom every now and then.
// It grabs a couple of the characters closest to the camera and randomly
// picks one of them to play the sound. Sweet.
class RadioChatterModule : public AIModule<RadioChatterModule, RadioChatterInstance, 12, 1>
{
public:
	RadioChatterModule()
	{
		SetDefaultSilenceDuration();
		SetDefaultSound();
	}

	virtual const char* GetName() const
	{
		return "RadioChatter";
	}

	virtual void Update(float updateTime) override;
	virtual void Reset(bool bUnload) override;
	virtual void Serialize(TSerialize ser) override;

	void SetDefaultSilenceDuration();
	void SetSilenceDuration(float min, float max);

	void SetDefaultSound();
	void SetSound(const char* name);

	void SetEnabled(bool enabled);

private:
	typedef float SquaredDistanceToCamera;
	typedef std::pair<IEntity*, SquaredDistanceToCamera> EntityAndDistance;
	typedef std::vector<EntityAndDistance> ChatterCandidates;

	static bool CloserToCameraPred(const EntityAndDistance& left, const EntityAndDistance& right);

	void PlayChatterOnRandomNearbyAgent();
	void PlayChatterOnEntity(IEntity& entity);
	void GatherCandidates(ChatterCandidates& candidates);
	void RefreshNextChatterTime();

	string m_chatterSoundName;
	CTimeValue m_nextChatterTime;
	float m_minimumSilenceDurationBetweenChatter;
	float m_maximumSilenceDurationBetweenChatter;
	bool m_enabled;
};
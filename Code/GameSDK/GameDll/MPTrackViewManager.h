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

#ifndef MP_TRACK_VIEW_MANAGER
#define MP_TRACK_VIEW_MANAGER

#include "GameRules.h"
#include "IMovieSystem.h"

class CMPTrackViewManager : public IMovieListener
{
public:
	CMPTrackViewManager();
	~CMPTrackViewManager();

	void Init();
	void Update();

	void Server_SynchAnimationTimes(CGameRules::STrackViewParameters& params); 
	void Client_SynchAnimationTimes(const CGameRules::STrackViewParameters& params);
	void AnimationRequested(const CGameRules::STrackViewRequestParameters& params);
	bool HasTrackviewFinished(const CryHashStringId& id) const;

	IAnimSequence* FindTrackviewSequence(int trackviewId);

private:

	// IMovieListener
	virtual void OnMovieEvent(IMovieListener::EMovieEvent movieEvent, IAnimSequence* pAnimSequence);
	// ~IMovieListener

	int m_FinishedTrackViews[CGameRules::STrackViewParameters::sMaxTrackViews];
	float m_FinishedTrackViewTimes[CGameRules::STrackViewParameters::sMaxTrackViews];
	int m_FinishedTrackViewCount;
	bool m_movieListener;

};

#endif
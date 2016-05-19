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

#ifndef __ANIM_ACTION_AI_DETAIL__
#define __ANIM_ACTION_AI_DETAIL__

#include "ICryMannequin.h"
#include "FragmentVariationHelper.h"

////////////////////////////////////////////////////////////////////////////
class CAnimActionAIDetail : public TAction<SAnimationContext>
{
	friend bool mannequin::UpdateFragmentVariation<CAnimActionAIDetail>(class CAnimActionAIDetail* pAction, class CFragmentVariationHelper* pFragmentVariationHelper, const FragmentID fragmentID, const TagState& requestedFragTags, const bool forceUpdate, const bool trumpSelf);

public:
	typedef TAction<SAnimationContext> TBase;

	DEFINE_ACTION("AIDetail");

	enum EMovementDetail
	{
		None,
		Idle,
		Move,
		Turn,
	};

	CAnimActionAIDetail();

	// -- IAction Implementation ------------------------------------------------
	virtual EPriorityComparison ComparePriority(const IAction &actionCurrent) const
	{
		return (IAction::Installed == actionCurrent.GetStatus() && IAction::Installing & ~actionCurrent.GetFlags()) ? Higher : TBase::ComparePriority(actionCurrent);
	}

	virtual void Enter();
	virtual void Exit();

	virtual void OnInitialise();
	virtual EStatus Update(float timePassed);
	virtual EStatus	UpdatePending(float timePassed);
	virtual void OnSequenceFinished(int layer, uint32 scopeID);
	// -- ~IAction Implementation -----------------------------------------------

	void RequestDetail(EMovementDetail detail);

	static bool IsSupported( const SAnimationContext& context );

private:
	void UpdateFragmentVariation(bool forceUpdate = false);

private:
	const struct SMannequinAIDetailParams* m_pManParams;

	CFragmentVariationHelper m_fragmentVariationHelper;

	FragmentID m_requestedDetail;
};


#endif //__ANIM_ACTION_AI_DETAIL__
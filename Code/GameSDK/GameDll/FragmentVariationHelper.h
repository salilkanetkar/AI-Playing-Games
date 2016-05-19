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

// Description : Helper class for selection and re-selection of (random) fragment variations

#ifndef __FRAGMENT_VARIATION_HELPER_H__
#define __FRAGMENT_VARIATION_HELPER_H__

#if _MSC_VER > 1000
# pragma once
#endif

#include "ICryMannequin.h"


// -------------------------------------------------------------------------
class CFragmentVariationHelper
{
public:
	CFragmentVariationHelper();
	~CFragmentVariationHelper();

	void SetFragmentId( const FragmentID fragmentId );
	void SetTagState( const SFragTagState& tagState );

	bool Update( const IAnimationDatabase* pDatabase, const bool forceReevaluate = false );
	void OnFragmentEnd();

	FragmentID GetFragmentId() const;
	TagState GetFragmentTagState() const;
	TagState GetTagState() const;
	uint32 GetOptionIndex() const;

protected:
	bool Reevaluate( const IAnimationDatabase* pDatabase, const bool forceReevaluate );

private:
	FragmentID m_currentFragmentId;
	FragmentID m_requestedFragmentId;

	SFragTagState m_currentTagState;
	SFragTagState m_requestedTagState;

	SFragTagState m_selectedTagState;
	uint32 m_selectedOptionIndex;

	bool m_reachedFragmentEnd;
};

// -------------------------------------------------------------------------
namespace mannequin
{
	// returns true when a fragment is queued (could be the same one in case of forcedUpdate)
	template<class ActionType>
	bool UpdateFragmentVariation(ActionType* pAction, class CFragmentVariationHelper* pFragmentVariationHelper, const FragmentID fragmentID, const TagState& requestedFragTags, const bool forceUpdate = false, const bool trumpSelf = true)
	{
		CRY_ASSERT(pAction);
		CRY_ASSERT(pFragmentVariationHelper);

		pFragmentVariationHelper->SetFragmentId(fragmentID);
		
		const SAnimationContext& context = pAction->GetContext();
		const TagState globalTagState = context.state.GetMask();

		const IScope& rootScope = pAction->GetRootScope();
		const TagState scopeAdditionalTags = rootScope.GetAdditionalTags();

		const TagState combinedGlobalTags = context.controllerDef.m_tags.GetUnion(globalTagState, scopeAdditionalTags);

		pFragmentVariationHelper->SetTagState(SFragTagState(combinedGlobalTags, requestedFragTags));

		const IAnimationDatabase& database = rootScope.GetDatabase();
		const bool fragmentChanged = pFragmentVariationHelper->Update(&database, forceUpdate);

		if (fragmentChanged || forceUpdate)
		{
			const FragmentID fragmentId = pFragmentVariationHelper->GetFragmentId();
			const TagState fragTags = pFragmentVariationHelper->GetFragmentTagState();
			const uint32 optionIndex = pFragmentVariationHelper->GetOptionIndex();
			const uint32 userToken = 0;

			pAction->SetFragment(fragmentId, fragTags, optionIndex, userToken, trumpSelf);
			return true;
		}
		else
		{
			return false;
		}
	}

}

#endif // __FRAGMENT_VARIATION_HELPER_H__

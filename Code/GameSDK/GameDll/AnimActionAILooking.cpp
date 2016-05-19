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
#include "AnimActionAILooking.h"

#include "PlayerAnimation.h"


//////////////////////////////////////////////////////////////////////////
#define MAN_AILOOKING_FRAGMENTS( x ) \
	x( Looking )

#define MAN_AILOOKING_TAGS( x )

#define MAN_AILOOKING_TAGGROUPS( x )

#define MAN_AILOOKING_SCOPES( x )

#define MAN_AILOOKING_CONTEXTS( x )

#define MAN_AILOOKING_CHANGEFRAGMENT_FRAGMENT_TAGS( x )

#define MAN_AILOOKING_FRAGMENT_TAGS( x )

MANNEQUIN_USER_PARAMS( SMannequinAiLookingUserParams, MAN_AILOOKING_FRAGMENTS, MAN_AILOOKING_TAGS, MAN_AILOOKING_TAGGROUPS, MAN_AILOOKING_SCOPES, MAN_AILOOKING_CONTEXTS, MAN_AILOOKING_FRAGMENT_TAGS );


//////////////////////////////////////////////////////////////////////////
FragmentID CAnimActionAILooking::FindFragmentId( const SAnimationContext& context )
{
	const SMannequinAiLookingUserParams* pUserParams = GetMannequinUserParams< SMannequinAiLookingUserParams >( context );
	CRY_ASSERT( pUserParams != NULL );

	return pUserParams->fragmentIDs.Looking;
}

//////////////////////////////////////////////////////////////////////////
CAnimActionAILooking::CAnimActionAILooking()
	: TBase( PP_Lowest, FRAGMENT_ID_INVALID, TAG_STATE_EMPTY, IAction::NoAutoBlendOut | IAction::Interruptable )
{
}


//////////////////////////////////////////////////////////////////////////
void CAnimActionAILooking::OnInitialise()
{
	const FragmentID fragmentId = FindFragmentId( *m_context );
	CRY_ASSERT( fragmentId != FRAGMENT_ID_INVALID );
	SetFragment( fragmentId );
}


//////////////////////////////////////////////////////////////////////////
IAction::EStatus CAnimActionAILooking::Update( float timePassed )
{
	TBase::Update( timePassed );

	const IScope& rootScope = GetRootScope();
	const bool foundNewBestMatchingFragment = rootScope.IsDifferent( m_fragmentID, m_fragTags );
	if ( foundNewBestMatchingFragment )
	{
		SetFragment( m_fragmentID, m_fragTags );
	}

	return m_eStatus;
}


//////////////////////////////////////////////////////////////////////////
bool CAnimActionAILooking::IsSupported( const SAnimationContext& context )
{
	const FragmentID fragmentId = FindFragmentId( context );
	const bool isSupported = ( fragmentId != FRAGMENT_ID_INVALID );
	return isSupported;
}
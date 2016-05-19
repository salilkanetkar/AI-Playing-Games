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
#include "AnimActionAIAiming.h"

#include "PlayerAnimation.h"


//////////////////////////////////////////////////////////////////////////
#define MAN_AIAIMING_FRAGMENTS( x ) \
	x( Aiming )

#define MAN_AIAIMING_TAGS( x )

#define MAN_AIAIMING_TAGGROUPS( x )

#define MAN_AIAIMING_SCOPES( x )

#define MAN_AIAIMING_CONTEXTS( x )

#define MAN_AIAIMING_CHANGEFRAGMENT_FRAGMENT_TAGS( x )

#define MAN_AIAIMING_FRAGMENT_TAGS( x )

MANNEQUIN_USER_PARAMS( SMannequinAiAimingUserParams, MAN_AIAIMING_FRAGMENTS, MAN_AIAIMING_TAGS, MAN_AIAIMING_TAGGROUPS, MAN_AIAIMING_SCOPES, MAN_AIAIMING_CONTEXTS, MAN_AIAIMING_FRAGMENT_TAGS );


//////////////////////////////////////////////////////////////////////////
FragmentID CAnimActionAIAiming::FindFragmentId( const SAnimationContext& context )
{
	const SMannequinAiAimingUserParams* pUserParams = GetMannequinUserParams< SMannequinAiAimingUserParams >( context );
	CRY_ASSERT( pUserParams != NULL );

	return pUserParams->fragmentIDs.Aiming;
}


//////////////////////////////////////////////////////////////////////////
CAnimActionAIAiming::CAnimActionAIAiming()
: TBase( PP_Lowest, FRAGMENT_ID_INVALID, TAG_STATE_EMPTY, IAction::NoAutoBlendOut | IAction::Interruptable )
{
}


//////////////////////////////////////////////////////////////////////////
void CAnimActionAIAiming::OnInitialise()
{
	const FragmentID fragmentId = FindFragmentId( *m_context );
	CRY_ASSERT( fragmentId != FRAGMENT_ID_INVALID );
	SetFragment( fragmentId );
}


//////////////////////////////////////////////////////////////////////////
IAction::EStatus CAnimActionAIAiming::Update( float timePassed )
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
bool CAnimActionAIAiming::IsSupported( const SAnimationContext& context )
{
	const FragmentID fragmentId = FindFragmentId( context );
	const bool isSupported = ( fragmentId != FRAGMENT_ID_INVALID );
	return isSupported;
}
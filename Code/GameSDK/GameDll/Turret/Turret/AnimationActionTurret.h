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

#ifndef __ANIMATION_ACTION_TURRET__H__
#define __ANIMATION_ACTION_TURRET__H__

#include <ICryMannequin.h>

class CAnimationActionTurret
	: public TAction< SAnimationContext >
{
public:
	typedef TAction< SAnimationContext > BaseClass;

	DEFINE_ACTION( "AnimationActionTurret" );

	CAnimationActionTurret( FragmentID fragmentId )
	 : TAction< SAnimationContext >( 0, fragmentId, TAG_STATE_EMPTY, IAction::NoAutoBlendOut )
	{
	}

	~CAnimationActionTurret()
	{
	}

	virtual EPriorityComparison ComparePriority( const IAction& currentAction ) const
	{
		assert( &currentAction != this );
		return (IAction::Installed == currentAction.GetStatus() && IAction::Installing & ~currentAction.GetFlags()) ? Higher : BaseClass::ComparePriority(currentAction);
	}

	virtual EStatus Update( float elapsedSeconds )
	{
		const IScope& rootScope = GetRootScope();
		const bool foundBetterMatchingFragment = rootScope.IsDifferent( m_fragmentID, m_fragTags );
		if ( foundBetterMatchingFragment )
		{
			SetFragment( m_fragmentID, m_fragTags );
		}

		return BaseClass::Update( elapsedSeconds );
	}
};

#endif
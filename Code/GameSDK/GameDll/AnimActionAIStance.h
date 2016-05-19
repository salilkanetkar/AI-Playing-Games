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

#ifndef __ANIM_ACTION_AI_STANCE__H__
#define __ANIM_ACTION_AI_STANCE__H__

#include "ICryMannequin.h"
#include "IAgent.h"

class CPlayer;

class CAnimActionAIStance
	: public TAction< SAnimationContext >
{
public:
	typedef TAction< SAnimationContext > TBase;

	DEFINE_ACTION( "AIStance" );

	CAnimActionAIStance( int priority, CPlayer* pPlayer, const EStance targetStance );

	virtual void Enter();
	virtual void Exit();
	virtual EStatus Update( float elapsedSeconds );
	virtual EStatus UpdatePending( float timePassed );


	virtual void OnInitialise();

	EStance GetTargetStance() const { return m_targetStance; }
	bool IsPlayerAnimationStanceSet() const { return m_isPlayerAnimationStanceSet; }

	ActionScopes FindStanceActionScopeMask( const SAnimationContext& context ) const;
	bool FragmentExistsInDatabase( const SAnimationContext& context, const IAnimationDatabase& database ) const;
private:
	void SetMovementParameters();
	void RestoreMovementParameters();

	void SetPlayerAnimationStanceOnce();
	EStance GetPlayerAnimationStance() const;

	bool FindFragmentInfo( const SAnimationContext& context, FragmentID& fragmentIdOut, SFragTagState& fragTagStateOut ) const;

private:
	CPlayer* const m_pPlayer;
	const EStance m_targetStance;
	bool m_isPlayerAnimationStanceSet;
};


#endif

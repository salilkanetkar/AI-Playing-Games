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

#ifndef __SCRIPT_BIND_HIT_DEATH_REACTIONS_H
#define __SCRIPT_BIND_HIT_DEATH_REACTIONS_H

#include "HitDeathReactionsDefs.h"

class CPlayer;
struct HitInfo;

class CScriptBind_HitDeathReactions : public CScriptableBase
{
public:
	CScriptBind_HitDeathReactions(ISystem *pSystem, IGameFramework *pGameFramework);
	virtual ~CScriptBind_HitDeathReactions();

	//! <description>Notifies a hit event to the hit death reactions system</description>
	//! 	<param name="scriptHitInfo = script table with the hit info</param>
	//! <returns>TRUE if the hit is processed successfully, FALSE otherwise</returns>
	int										OnHit(IFunctionHandler *pH, SmartScriptTable scriptHitInfo);


	//! <description>Executes a hit reaction using the default C++ execution code</description>
	//! 	<param name="reactionParams = script table with the reaction parameters</param>
	int										ExecuteHitReaction (IFunctionHandler *pH, SmartScriptTable reactionParams);

	//! <description>Executes a death reaction using the default C++ execution code</description>
	//! 	<param name="reactionParams = script table with the reaction parameters</param>
	int										ExecuteDeathReaction (IFunctionHandler *pH, SmartScriptTable reactionParams);

	//! <returns>Ends the current reaction</returns>
	int										EndCurrentReaction (IFunctionHandler *pH);

	//! <description>Run the default C++ validation code and returns its result</description>
	//! 	<param name="validationParams = script table with the validation parameters</param>
	//! 	<param name="scriptHitInfo = script table with the hit info</param>
	//! <returns>TRUE is the validation was successful, FALSE otherwise</returns>
	int										IsValidReaction (IFunctionHandler *pH, SmartScriptTable validationParams, SmartScriptTable scriptHitInfo);

	//! <description>Starts an animation through the HitDeathReactions. Pauses the animation graph while playing it
	//! 		and resumes automatically when the animation ends</description>
	//! 	<param name="sAnimName</param>
	//! 	<param name="bLoop">false</param>
	//! 	<param name="fBlendTime">0.2f</param>
	//! 	<param name="iSlot">0</param>
	//! 	<param name="iLayer">0</param>
	//! 	<param name="fAniSpeed">1.0f</param>
	int										StartReactionAnim(IFunctionHandler *pH);

	//! <code>EndReactionAnim</code>
	//! <description>Ends the current reaction anim, if any</description>
	int										EndReactionAnim(IFunctionHandler *pH);

	//! <description>Starts an interactive action.</description>
	//! 	<param name="szActionName">name of the interactive action</param>
	int										StartInteractiveAction(IFunctionHandler *pH, const char* szActionName);

	virtual void GetMemoryUsage(ICrySizer *pSizer) const
	{
		pSizer->AddObject(this, sizeof(*this));
	}

private:
	CPlayer*							GetAssociatedActor(IFunctionHandler *pH) const;
	CHitDeathReactionsPtr GetHitDeathReactions(IFunctionHandler *pH) const;

	SmartScriptTable	m_pParams;

	ISystem*					m_pSystem;
	IGameFramework*		m_pGameFW;
};

#endif // __SCRIPT_BIND_HIT_DEATH_REACTIONS_H

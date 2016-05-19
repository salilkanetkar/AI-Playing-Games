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

// Description : Game-side logic for controlling the threat level of an AI
//               agent s current target


#include "StdAfx.h"
#include "TargetTrackThreatModifier.h"
#include "GameCVars.h"
#include "IAIObject.h"
#include "IAIActor.h"
#include "IAIActorProxy.h"

//////////////////////////////////////////////////////////////////////////
CTargetTrackThreatModifier::CTargetTrackThreatModifier()
{
	ITargetTrackManager *pTargetTrackManager = gEnv->pAISystem->GetTargetTrackManager();
	if (pTargetTrackManager)
		pTargetTrackManager->SetTargetTrackThreatModifier(this);

	IConsole *pConsole = gEnv->pConsole;
	assert(pConsole);

	m_pCVar_CloakMinDist = pConsole->GetCVar("ai_CloakMinDist");
	m_pCVar_CloakMaxDist = pConsole->GetCVar("ai_CloakMaxDist");
	m_pCVar_SOMSpeedRelaxed = pConsole->GetCVar("ai_SOMSpeedRelaxed");
	m_pCVar_SOMSpeedCombat = pConsole->GetCVar("ai_SOMSpeedCombat");
}

//////////////////////////////////////////////////////////////////////////
CTargetTrackThreatModifier::~CTargetTrackThreatModifier()
{
	ITargetTrackManager *pTargetTrackManager = gEnv->pAISystem->GetTargetTrackManager();
	if (pTargetTrackManager)
		pTargetTrackManager->ClearTargetTrackThreatModifier();
}

//////////////////////////////////////////////////////////////////////////
void CTargetTrackThreatModifier::ModifyTargetThreat(IAIObject &ownerAI, IAIObject &targetAI, const ITargetTrack &track, float &outThreatRatio, EAITargetThreat &outThreat) const
{
	if (track.GetTargetType() > AITARGET_SOUND && outThreat >= AITHREAT_AGGRESSIVE)
	{
		outThreatRatio = 1.0f;
	}
}

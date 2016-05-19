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

// Description : Allows game modules system to talk to IGameStatistics system


#include "StdAfx.h"
#include "GameRulesStatsRecording.h"
#include "IXml.h"
#include "GameRules.h"
#include "IGameStatistics.h"
#include "ICryAnimation.h"
#include "StatsRecordingMgr.h"
#include "StatHelpers.h"

void CGameRulesStatsRecording::Init(
	XmlNodeRef			inXML)
{
	m_gameStatistics=g_pGame->GetIGameFramework()->GetIGameStatistics();
	m_actorSystem=g_pGame->GetIGameFramework()->GetIActorSystem();
	m_statsMgr=g_pGame->GetStatsRecorder();
	assert(m_gameStatistics);
	assert(m_actorSystem);
}

void CGameRulesStatsRecording::OnInGameBegin()
{
	if (m_statsMgr)
	{
		m_statsMgr->BeginRound();
	}
}

void CGameRulesStatsRecording::OnPostGameBegin()
{
	if (m_statsMgr)
	{
		m_statsMgr->StopTrackingAllPlayerStats();
		m_statsMgr->EndRound();
	}
}

void CGameRulesStatsRecording::OnGameEnd()
{
	if (m_statsMgr)
	{
		m_statsMgr->EndRound();
	}
}

void CGameRulesStatsRecording::OnPlayerRevived(
	IActor			*inActor)
{
	if (m_statsMgr)
	{
		m_statsMgr->StartTrackingStats(inActor);
	}
}

void CGameRulesStatsRecording::OnPlayerKilled(
	IActor			*inActor)
{
	if (m_statsMgr)
	{
		m_statsMgr->StopTrackingStats(inActor);
	}
}

#if USE_PC_PREMATCH
void CGameRulesStatsRecording::OnPrematchEnd(
	IActor			*inActor)
{
	if (m_statsMgr)
	{
		m_statsMgr->StopTrackingStats(inActor);
	}
}
#endif 
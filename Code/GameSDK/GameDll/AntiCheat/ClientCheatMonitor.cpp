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

// Description : Central storage and processing of all gamecode client side 
//               monitoring

#include "StdAfx.h"
#include "AntiCheat/ClientCheatMonitor.h"
#include "GameCVars.h"
#include "GameRules.h"
#include "LocalPlayerComponent.h"

#if CLIENT_CHEAT_MONITOR_ENABLED
//========================================================================
// Construction/Destruction
//========================================================================
CClientCheatMonitor::CClientCheatMonitor()
	:m_pFramework(NULL)
{
}

CClientCheatMonitor::~CClientCheatMonitor()
{
	m_pFramework->UnregisterListener(this);
}

//========================================================================
// Init
//========================================================================
void CClientCheatMonitor::Init(IGameFramework *pFramework)
{
	pFramework->RegisterListener(this,"CClientCheatMonitor", FRAMEWORKLISTENERPRIORITY_DEFAULT);

	m_pFramework = pFramework;
}

//========================================================================
// IOnPostUpdate
//========================================================================
void CClientCheatMonitor::OnPostUpdate(float fDeltaTime)
{
}

//========================================================================
// OnSaveGame
//========================================================================
void CClientCheatMonitor::OnSaveGame(ISaveGame* pSaveGame)
{
}

//========================================================================
// OnLoadGame
//========================================================================
void CClientCheatMonitor::OnLoadGame(ILoadGame* pLoadGame)
{
}

//========================================================================
// OnLevelEnd
//========================================================================
void CClientCheatMonitor::OnLevelEnd(const char* nextLevel)
{
}

//========================================================================
// OnActionEvent
//========================================================================
void CClientCheatMonitor::OnActionEvent(const SActionEvent& event)
{
}

//========================================================================
// UploadTelemetry
//========================================================================
void CClientCheatMonitor::UploadTelemetry()
{
}
#endif

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

// Description : CryLobby session handler implementation.

#include "StdAfx.h"
#include "CryLobbySessionHandler.h"
#include "GameLobby.h"
#include "GameLobbyManager.h"
#include "PlayerProgression.h"
#include "UI/ProfileOptions.h"

//-------------------------------------------------------------------------
CCryLobbySessionHandler::CCryLobbySessionHandler()
{
//	g_pGame->GetIGameFramework()->SetGameSessionHandler(this);
	m_userQuit = false;
}

//-------------------------------------------------------------------------
CCryLobbySessionHandler::~CCryLobbySessionHandler()
{
	g_pGame->ClearGameSessionHandler(); // Must clear pointer in game if cry action deletes the handler.
}

//-------------------------------------------------------------------------
bool CCryLobbySessionHandler::ShouldCallMapCommand( const char *pLevelName, const char *pGameRules )
{
	bool result = false;

	CGameLobby* pGameLobby = g_pGame->GetGameLobby();
	if (pGameLobby)
	{
		result = pGameLobby->ShouldCallMapCommand(pLevelName, pGameRules);
		if(result)
		{
			IPlatformOS* pPlatform = gEnv->pSystem->GetPlatformOS();

			SStreamingInstallProgress progress;
			pPlatform->QueryStreamingInstallProgressForLevel(pLevelName, &progress);
			const bool bLevelReady = SStreamingInstallProgress::eState_Completed == progress.m_state;
			if(!bLevelReady)
			{
				// we can jump directly into MP from system game invitation avoiding frontend, so update streaming install priorities here
				pPlatform->SwitchStreamingInstallPriorityToLevel(pLevelName);
				gEnv->pSystem->GetISystemEventDispatcher()->OnSystemEvent( ESYSTEM_EVENT_LEVEL_NOT_READY, (UINT_PTR)pLevelName, 0 );
			}
			return bLevelReady;
		}
	}

	return result;
}
//-------------------------------------------------------------------------
void CCryLobbySessionHandler::JoinSessionFromConsole(CrySessionID session)
{
	CGameLobby* pGameLobby = g_pGame->GetGameLobby();
	if (pGameLobby)
	{
		pGameLobby->JoinServer(session, "JoinSessionFromConsole", CryMatchMakingInvalidConnectionUID, true);
	}
}

//-------------------------------------------------------------------------
void CCryLobbySessionHandler::LeaveSession()
{
	CGameLobbyManager* pGameLobbyManager = g_pGame->GetGameLobbyManager();
	if (pGameLobbyManager)
	{
		pGameLobbyManager->LeaveGameSession(CGameLobbyManager::eLSR_Menu);
	}
}

//-------------------------------------------------------------------------
int CCryLobbySessionHandler::StartSession()
{
	m_userQuit = false;
	return (int) eCLE_Success;
}

//-------------------------------------------------------------------------
int CCryLobbySessionHandler::EndSession()
{
	if (IPlayerProfileManager *pPlayerProfileManager = g_pGame->GetIGameFramework()->GetIPlayerProfileManager())
	{
		CPlayerProgression *pPlayerProgression = CPlayerProgression::GetInstance();
		if (pPlayerProgression)
		{
			pPlayerProgression->OnEndSession();
		}

		CGameLobbyManager *pLobbyManager = g_pGame->GetGameLobbyManager();
		if (pLobbyManager)
		{
			const unsigned int controllerIndex = pPlayerProfileManager->GetExclusiveControllerDeviceIndex();
			if (pLobbyManager->GetOnlineState(controllerIndex) == eOS_SignedIn)
			{
				CryLog("CCryLobbySessionHandler::EndSession() saving profile");
				//Quitting the session from in game
				g_pGame->GetProfileOptions()->SaveProfile(ePR_All);
			}
			else
			{
				CryLog("CCryLobbySessionHandler::EndSession() not saving as we're signed out");
			}
		}
	}

	return (int) eCLE_Success;
}

//-------------------------------------------------------------------------
void CCryLobbySessionHandler::OnUserQuit()
{
	m_userQuit = true;

	if (g_pGame->GetIGameFramework()->StartedGameContext() == false)
	{
		g_pGame->GetGameLobbyManager()->LeaveGameSession(CGameLobbyManager::eLSR_Menu);
	}
}

//-------------------------------------------------------------------------
void CCryLobbySessionHandler::OnGameShutdown()
{
	const CGame::EHostMigrationState  migrationState = (g_pGame ? g_pGame->GetHostMigrationState() : CGame::eHMS_NotMigrating);

	CryLog("CCryLobbySessionHandler::OnGameShutdown(), m_userQuit=%s, migrationState=%d", (m_userQuit ? "true" : "false"), migrationState);
#if 0 // old frontend
	CMPMenuHub* pMPMenu = NULL;
	CFlashFrontEnd *pFlashFrontEnd = g_pGame ? g_pGame->GetFlashMenu() : NULL;
	if (pFlashFrontEnd)
	{
		pMPMenu = pFlashFrontEnd->GetMPMenu();
	}
#endif
	if(m_userQuit)
	{
		LeaveSession();
	}
#if 0 // old frontend
	if (pMPMenu)
	{
		// If we're still on the loading screen, clear it
		pMPMenu->ClearLoadingScreen();
	}
#endif
}

//-------------------------------------------------------------------------
CrySessionHandle CCryLobbySessionHandler::GetGameSessionHandle() const
{
	CrySessionHandle result = CrySessionInvalidHandle;

	CGameLobby* pGameLobby = g_pGame->GetGameLobby();
	if (pGameLobby)
	{
		result = pGameLobby->GetCurrentSessionHandle();
	}

	return result;
}

//-------------------------------------------------------------------------
bool CCryLobbySessionHandler::ShouldMigrateNub() const
{
	bool bResult = true;

	CGameLobby* pGameLobby = g_pGame->GetGameLobby();
	if (pGameLobby)
	{
		bResult = pGameLobby->ShouldMigrateNub();
	}

	return bResult;
}

//-------------------------------------------------------------------------
bool CCryLobbySessionHandler::IsMultiplayer() const
{
	bool result = false;

	CGameLobbyManager *pLobbyManager = g_pGame->GetGameLobbyManager();
	if (pLobbyManager)
	{
		result = pLobbyManager->IsMultiplayer();
	}

	return result;
}

//-------------------------------------------------------------------------
int CCryLobbySessionHandler::GetNumberOfExpectedClients()
{
	int result = 0;

	CGameLobby* pGameLobby = g_pGame->GetGameLobby();
	if (pGameLobby)
	{
		result = pGameLobby->GetNumberOfExpectedClients();
	}

	return result;
}

//-------------------------------------------------------------------------
bool CCryLobbySessionHandler::IsGameSessionMigrating() const
{
	return g_pGame->IsGameSessionHostMigrating();
}

//-------------------------------------------------------------------------
bool CCryLobbySessionHandler::IsMidGameLeaving() const
{
	bool result = false;

	const CGameLobby* pGameLobby = g_pGame->GetGameLobby();
	if (pGameLobby)
	{
		result = pGameLobby->IsMidGameLeaving();
	}

	return result;
}

//-------------------------------------------------------------------------
bool CCryLobbySessionHandler::IsGameSessionMigratable() const
{
	bool result = false;

	CGameLobby* pGameLobby = g_pGame->GetGameLobby();
	if (pGameLobby)
	{
		result = pGameLobby->IsSessionMigratable();
	}

	return result;
}

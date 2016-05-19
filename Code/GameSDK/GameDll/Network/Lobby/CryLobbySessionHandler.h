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


#ifndef __CRYLOBBY_SESSION_HANDLER_H__
#define __CRYLOBBY_SESSION_HANDLER_H__

//#include <IGameSessionHandler.h>
#include "ICryMatchMaking.h"

class CCryLobbySessionHandler //: public IGameSessionHandler
{
public:
	CCryLobbySessionHandler();
	virtual ~CCryLobbySessionHandler();

	// IGameSessionHandler
	virtual bool ShouldCallMapCommand(const char *pLevelName, const char *pGameRules);
	virtual void JoinSessionFromConsole(CrySessionID session);
	virtual void LeaveSession();
	
	virtual int StartSession();
	virtual int EndSession();

	virtual void OnUserQuit();
	virtual void OnGameShutdown();

	virtual CrySessionHandle GetGameSessionHandle() const;
	virtual bool ShouldMigrateNub() const;

	virtual bool IsMultiplayer() const;
	virtual int GetNumberOfExpectedClients();

	virtual bool IsGameSessionMigrating() const;
	virtual bool IsMidGameLeaving() const;
	virtual bool IsGameSessionMigratable() const;
	// ~IGameSessionHandler

protected:
	bool m_userQuit;
};

#endif //__CRYLOBBY_SESSION_HANDLER_H__

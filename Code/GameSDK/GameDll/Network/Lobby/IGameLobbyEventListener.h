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

// Description : Interface for Game Lobby events


#ifndef _IGAMELOBBYEVENTLISTENER_H_
#define _IGAMELOBBYEVENTLISTENER_H_

#if _MSC_VER > 1000
# pragma once
#endif

#include <ICryLobbyUI.h>

class IGameLobbyEventListener
{
public:
	virtual ~IGameLobbyEventListener() {}

	virtual void InsertedUser(CryUserID userId, const char *userName) = 0;
	virtual void SessionChanged(const CrySessionHandle inOldSession, const CrySessionHandle inNewSession) = 0;
};

#endif // _IGAMELOBBYEVENTLISTENER_H_
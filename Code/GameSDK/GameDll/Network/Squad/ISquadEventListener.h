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

// Description : Interface for squad manager events


#ifndef _ISQUADEVENTLISTENER_H_
#define _ISQUADEVENTLISTENER_H_

#if _MSC_VER > 1000
# pragma once
#endif

#include <ICryLobbyUI.h>

class ISquadEventListener
{
public:
	// Local squad events
	enum ESquadEventType
	{
		eSET_CreatedSquad,
		eSET_MigratedSquad,
		eSET_JoinedSquad,
		eSET_LeftSquad,
	};

public:
	virtual ~ISquadEventListener() {}

	virtual void AddedSquaddie(CryUserID userId) = 0;
	virtual void RemovedSquaddie(CryUserID userId) = 0;
	virtual void UpdatedSquaddie(CryUserID userId) = 0;
	virtual void SquadLeaderChanged(CryUserID userId) = 0;

	virtual void SquadEvent(ISquadEventListener::ESquadEventType eventType) = 0;
};

#endif // _ISQUADEVENTLISTENER_H_

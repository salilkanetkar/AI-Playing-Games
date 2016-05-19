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

#ifndef __RICHPRESENCE_H__
#define __RICHPRESENCE_H__

#include "GameMechanismManager/GameMechanismBase.h"

class CRichPresence : public CGameMechanismBase
{
	public:

		enum ERichPresenceState
		{
			eRPS_None,
			eRPS_Idle,
			eRPS_FrontEnd,
			eRPS_Lobby,
			eRPS_InGame,
		};

		enum ERichPresenceType
		{
			eRPT_String = 0,
			eRPT_Param1,
			eRPT_Param2,
			eRPT_Max,
		};

	public:

		CRichPresence();
		virtual ~CRichPresence();

		// CGameMechanismBase
		virtual void Update(float dt);
		// ~CGameMechanismBase

		void LoadXmlFromFile(const char* path);
		bool SetRichPresence(ERichPresenceState state);
		CrySessionID GetPendingRichPresenceSessionID() const { return m_pendingSessionID; }
	
	private:

		void OnSetRichPresenceCallback(CryLobbyTaskID taskID, ECryLobbyError error);

		static void SetRichPresenceCallback(CryLobbyTaskID taskID, ECryLobbyError error, void* pArg);

	private:

		typedef std::map<CryFixedStringT<128>, int> TRichPresenceMap;
		TRichPresenceMap m_richPresence;
		
		ERichPresenceState m_currentState;
		ERichPresenceState m_pendingState;
		ERichPresenceState m_desiredState;

		CryLobbyTaskID m_taskID;

		CrySessionID m_currentSessionID;
		CrySessionID m_pendingSessionID;

		float m_updateTimer;
		bool m_refresh;
};

#endif // __RICHPRESENCE_H__

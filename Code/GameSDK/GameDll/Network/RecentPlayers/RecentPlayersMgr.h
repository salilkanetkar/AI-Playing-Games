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

#ifndef __CRECENTPLAYERSMGR_H__
#define __CRECENTPLAYERSMGR_H__

//---------------------------------------------------------------------------

#include "Network/Squad/ISquadEventListener.h"
#include "Network/Lobby/IGameLobbyEventListener.h"
#include <CryFixedArray.h>
#include "ICryLobby.h"
#include "Network/FriendManager/GameFriendData.h"
#include "IRecentPlayersMgrEventListener.h"

//---------------------------------------------------------------------------
// CRecentPlayersMgr
//     A class to manage and store potential new friends a player has encountered since running the game
//---------------------------------------------------------------------------
class CRecentPlayersMgr : public ISquadEventListener, public IGameLobbyEventListener
{
public:
	typedef struct SRecentPlayerData
	{
		CryUserID m_userId;
		TLobbyUserNameString m_name;
		TGameFriendId m_internalId;

		static TGameFriendId __s_friend_internal_ids;

		SRecentPlayerData(CryUserID &inUserId, const char *inNameString)
		{
			m_userId = inUserId;
			m_name = inNameString;
			m_internalId = __s_friend_internal_ids++;
		}
	};
	
	static const int k_maxNumRecentPlayers=50;
	typedef CryFixedArray<SRecentPlayerData, k_maxNumRecentPlayers> TRecentPlayersArray;


	CRecentPlayersMgr();
	virtual ~CRecentPlayersMgr();

	void Update(const float inFrameTime);

	void RegisterRecentPlayersMgrEventListener(IRecentPlayersMgrEventListener *pListener);
	void UnregisterRecentPlayersMgrEventListener(IRecentPlayersMgrEventListener *pListener);

	// ISquadEventListener
	virtual void AddedSquaddie(CryUserID userId);
	virtual void RemovedSquaddie(CryUserID userId) {}
	virtual void UpdatedSquaddie(CryUserID userId);
	virtual void SquadLeaderChanged(CryUserID oldLeaderId, CryUserID newLeaderId) {}
	virtual void SquadNameChanged(const char *pInNewName) { }
	virtual void SquadEvent(ISquadEventListener::ESquadEventType eventType) { }
	// ~ISquadEventListener

	// IGameLobbyEventListener
	virtual void InsertedUser(CryUserID userId, const char *userName);
	virtual void SessionChanged(const CrySessionHandle inOldSession, const CrySessionHandle inNewSession) { }
	// ~IGameLobbyEventListener

	const TRecentPlayersArray *GetRecentPlayers() const { return &m_players; }
	const SRecentPlayerData *FindRecentPlayerDataFromInternalId(TGameFriendId inInternalId);

	void OnUserChanged(CryUserID localUserId);

protected:
	typedef std::vector<IRecentPlayersMgrEventListener*> TRecentPlayersFriendsEventListenersVec;
	TRecentPlayersFriendsEventListenersVec m_recentPlayersEventListeners;

	TRecentPlayersArray m_players;
	CryUserID m_localUserId;

	void AddOrUpdatePlayer(CryUserID &inUserId, const char *inUserName);
	SRecentPlayerData *FindRecentPlayerDataFromUserId(CryUserID &inUserId);
	void EventRecentPlayersUpdated();
};
//---------------------------------------------------------------------------

#endif //__CRECENTPLAYERSMGR_H__

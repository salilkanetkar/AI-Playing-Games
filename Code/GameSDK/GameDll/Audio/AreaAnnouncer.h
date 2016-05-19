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

// Description : Plays Announcements based upon AreaBox triggers placed in levels

#ifndef __AREAANNOUNCER_H__
#define __AREAANNOUNCER_H__

#include "GameRulesModules/IGameRulesRevivedListener.h"
#include <CryFixedArray.h>
#include "Audio/AudioSignalPlayer.h"

#define AREA_ANNOUNCERS 2

class CAreaAnnouncer : IGameRulesRevivedListener
{
public:
	CAreaAnnouncer();
	~CAreaAnnouncer();

	void Init();
	void Reset();

	void Update(const float dt);

	virtual void EntityRevived(EntityId entityId);

#if !defined(_RELEASE)
	static void CmdPlay(IConsoleCmdArgs* pCmdArgs);
	static void CmdReload(IConsoleCmdArgs* pCmdArgs);
#endif

protected:

	struct SAnnouncementArea
	{
#if !defined(_RELEASE)
		const static int k_maxNameLength = 64;
		char m_name[k_maxNameLength];
#endif
		EntityId m_areaProxyId;
		TAudioSignalID m_signal[AREA_ANNOUNCERS];
	};

	bool AnnouncerRequired();
	void LoadAnnouncementArea(const IEntity* pEntity, const char* areaName);

	TAudioSignalID BuildAnnouncement(const EntityId clientId);
	TAudioSignalID GenerateAnnouncement(const int* actorCount, const int k_areaCount, const EntityId clientId);
	int GetAreaAnnouncerTeamIndex(const EntityId clientId);

	const static int k_maxAnnouncementAreas = 16;
	CryFixedArray<SAnnouncementArea, k_maxAnnouncementAreas> m_areaList;
};

#endif // __AREAANNOUNCER_H__
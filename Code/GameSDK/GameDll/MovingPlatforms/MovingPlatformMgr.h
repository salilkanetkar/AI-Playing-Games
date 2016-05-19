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

#ifndef __GAME_MOVING_PLATFORM_MGR_H__
#define __GAME_MOVING_PLATFORM_MGR_H__ 

#include "GameRules.h"

class CMovingPlatformMgr
{
	struct SContact
	{
		SContact()
			: fTimeSinceFirstContact(0.f)
			, fTimeSinceLastContact(0.f)
		{}
		ILINE void Update(const float dt) { fTimeSinceFirstContact += dt; fTimeSinceLastContact += dt; }
		ILINE void Refresh() { fTimeSinceLastContact = 0.f; }
		float fTimeSinceFirstContact;
		float fTimeSinceLastContact;
	};

public:
	CMovingPlatformMgr();
	~CMovingPlatformMgr();

	int OnCollisionLogged( const EventPhys* pEvent );
	int OnDeletedLogged( const EventPhys* pEvent );
	void Update( const float dt );
	void Reset();

	/* Static Physics Event Receivers */
	static int StaticOnCollision( const EventPhys * pEvent );
	static int StaticOnDeleted( const EventPhys * pEvent );

protected:
	typedef std::map<EntityId, SContact> TContactList;
	TContactList m_contacts;
};

#endif

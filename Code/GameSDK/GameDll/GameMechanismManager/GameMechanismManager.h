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

#ifndef __GAMEMECHANISMMANAGER_H__
#define __GAMEMECHANISMMANAGER_H__

#include "GameMechanismEvents.h"

class CGameMechanismBase;

class CGameMechanismManager
{
	public:
	CGameMechanismManager();
	~CGameMechanismManager();
	void Update(float dt);
	void Inform(EGameMechanismEvent gmEvent, const SGameMechanismEventData * data = NULL);
	void RegisterMechanism(CGameMechanismBase * mechanism);
	void UnregisterMechanism(CGameMechanismBase * mechanism);

	static ILINE CGameMechanismManager * GetInstance()
	{
		assert (s_instance);
		return s_instance;
	}

	private:
	static CGameMechanismManager * s_instance;
	CGameMechanismBase * m_firstMechanism;

#if !defined(_RELEASE)
	int m_cvarWatchEnabled;
	int m_cvarLogEnabled;
#endif
};

#endif //__GAMEMECHANISMMANAGER_H__
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

#include "StdAfx.h"
#include "GameMechanismBase.h"
#include "GameMechanismManager.h"

CGameMechanismBase::CGameMechanismBase(const char * className)
{
	memset (& m_linkedListPointers, 0, sizeof(m_linkedListPointers));

#if INCLUDE_NAME_IN_GAME_MECHANISMS
	m_className = className;
#endif

	CGameMechanismManager * manager = CGameMechanismManager::GetInstance();
	manager->RegisterMechanism(this);
}

CGameMechanismBase::~CGameMechanismBase()
{
	CGameMechanismManager * manager = CGameMechanismManager::GetInstance();
	manager->UnregisterMechanism(this);
}

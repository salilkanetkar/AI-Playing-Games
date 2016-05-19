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

#ifndef __GAMEMECHANISMEVENTS_H__
#define __GAMEMECHANISMEVENTS_H__

#include "AutoEnum.h"

#define GameMechanismEventList(f)   \
	f(kGMEvent_GameRulesInit)         \
	f(kGMEvent_GameRulesRestart)      \
	f(kGMEvent_GameRulesDestroyed)    \
	f(kGMEvent_LocalPlayerInit)       \
	f(kGMEvent_LocalPlayerDeinit)     \
	f(kGMEvent_LoadGame)              \
	f(kGMEvent_SaveGame)              \

struct SGameMechanismEventData
{
	union
	{
		struct { ILoadGame * m_interface; } m_data_LoadGame;
		struct { ISaveGame * m_interface; } m_data_SaveGame;
	};
};

AUTOENUM_BUILDENUMWITHTYPE(EGameMechanismEvent, GameMechanismEventList);

#endif //__GAMEMECHANISMEVENTS_H__
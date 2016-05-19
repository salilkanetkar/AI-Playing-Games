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

#ifndef __PLAYER_PROGRESSION_TYPES_H
#define __PLAYER_PROGRESSION_TYPES_H

#pragma once

#include "ProgressionUnlocks.h"

typedef std::vector<SUnlock> TUnlockElements;
typedef std::vector<TUnlockElements> TUnlockElementsVector;

enum EPPSuitData
{
	ePPS_Level = 0,
	ePPS_MaxLevel,
	ePPS_XP,
	ePPS_LifetimeXP,
	ePPS_XPToNextLevel,
	ePPS_XPLastMatch,
	ePPS_XPInCurrentLevel,
	ePPS_XPMatchStart,
	ePPS_MatchStartLevel,
	ePPS_MatchStartXPInCurrentLevel,
	ePPS_MatchStartXPToNextLevel,
};

#endif //#ifndef __PLAYER_PROGRESSION_TYPES_H
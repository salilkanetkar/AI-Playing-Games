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

#ifndef _GameRulesGladiatorTeams_h_
#define _GameRulesGladiatorTeams_h_

#if _MSC_VER > 1000
# pragma once
#endif

#include "GameRulesStandardTwoTeams.h"
#include "CryFixedString.h"

class CGameRulesGladiatorTeams : public CGameRulesStandardTwoTeams
{
public:
	virtual int		GetAutoAssignTeamId(EntityId playerId) { return 0; }		// Defer team selection for objectives module
	virtual void	RequestChangeTeam(EntityId playerId, int teamId, bool onlyIfUnassigned) {};
};

#endif // _GameRulesGladiatorTeams_h_

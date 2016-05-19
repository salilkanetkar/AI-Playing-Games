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

#ifndef _GameRulesStandardTwoTeams_h_
#define _GameRulesStandardTwoTeams_h_

#if _MSC_VER > 1000
# pragma once
#endif

#include "IGameRulesTeamsModule.h"
#include "CryFixedString.h"

class CGameRules;

class CGameRulesStandardTwoTeams : public IGameRulesTeamsModule
{
public:
	CGameRulesStandardTwoTeams();
	virtual ~CGameRulesStandardTwoTeams();

	virtual void Init(XmlNodeRef xml);
	virtual void PostInit();

	virtual void RequestChangeTeam(EntityId playerId, int teamId, bool onlyIfUnassigned);

	virtual int GetAutoAssignTeamId(EntityId playerId);

	virtual bool	CanTeamModifyWeapons(int teamId);

protected:
	void DoTeamChange(EntityId playerId, int teamId);

	CGameRules *m_pGameRules;
	bool m_bCanTeamModifyWeapons[2];
};

#endif // _GameRulesStandardTwoTeams_h_
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

#pragma once

#ifndef BODY_DAMAGE_MANAGER_CVARS_H
#define BODY_DAMAGE_MANAGER_CVARS_H

class CBodyManagerCVars
{
	friend class CBodyDamageProfile;
public:
	static void RegisterCommands();
	static void RegisterVariables();
	static void UnregisterCommands(IConsole* pConsole);
	static void UnregisterVariables(IConsole* pConsole);

	static int IsBodyDamageLogEnabled() { return g_bodyDamage_log; }
	static int IsBodyDestructionDebugEnabled() { return g_bodyDestruction_debug; }
	static bool IsBodyDestructionDebugFilterFor(const char* entityName)
	{
		CRY_ASSERT(entityName);
		CRY_ASSERT(g_bodyDestruction_debugFilter);

		const char* filter = g_bodyDestruction_debugFilter->GetString();
		
		return (strcmp(filter, entityName) == 0);
	}

	static bool IsBodyDestructionDebugFilterEnabled()
	{
		const char* filter = g_bodyDestruction_debugFilter->GetString();

		return ((strlen(filter) > 0) && (strcmp(filter, "0") != 0));
	}

private:
	static void Reload(IActor* pIActor);
	static void Reload(IEntity* pEntity);
	static void ReloadBodyDamage(IConsoleCmdArgs* pArgs);
	static void ReloadBodyDestruction(IConsoleCmdArgs* pArgs);

	static int g_bodyDamage_log;
	static int g_bodyDestruction_debug;

	static ICVar* g_bodyDestruction_debugFilter;
};

#endif
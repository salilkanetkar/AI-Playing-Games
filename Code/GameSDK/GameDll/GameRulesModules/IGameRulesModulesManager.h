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

#ifndef _IGameRulesModulesManager_h_
#define _IGameRulesModulesManager_h_

#if _MSC_VER > 1000
# pragma once
#endif

#include "IGameFramework.h"
#include "GameRulesModules/GameRulesModulesRegistration.h"

class IGameRulesModulesManager
{
public:
	virtual ~IGameRulesModulesManager() {}

// Register as a factory for each module type
#define GAMERULES_MODULE_LIST_FUNC(type, name, lowerCase, useInEditor) DECLARE_GAMEOBJECT_FACTORY(type)
	GAMERULES_MODULE_TYPES_LIST
#undef GAMERULES_MODULE_LIST_FUNC

	virtual void Init() = 0;

	virtual int GetRulesCount() = 0;

	virtual const char* GetRules(int index) = 0;
};

#endif // _IGameRulesModulesManager_h_

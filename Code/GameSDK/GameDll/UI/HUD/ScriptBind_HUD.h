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

// Description : Script Binding for HUD


#ifndef __SCRIPTBIND_HUD_H__
#define __SCRIPTBIND_HUD_H__

#if _MSC_VER > 1000
# pragma once
#endif

#include <IScriptSystem.h>

struct IGameFramework;

class CScriptBind_HUD :
	public CScriptableBase
{
public:
	CScriptBind_HUD(ISystem *pSystem, IGameFramework *pGameFramework);
	virtual ~CScriptBind_HUD();

	virtual void GetMemoryUsage(ICrySizer *pSizer) const
	{
		pSizer->AddObject(this, sizeof(*this));
	}

protected:
	int SetObjectiveStatus(IFunctionHandler *pH,const char* pObjectiveID, int status, bool silent);
	int SetObjectiveEntity(IFunctionHandler *pH,const char* pObjectiveID,const char* entityName);
	int ClearObjectiveEntity(IFunctionHandler *pH,const char* pObjectiveID);
	int AddEntityToRadar(IFunctionHandler *pH, ScriptHandle entityId);
	
	int RemoveEntityFromRadar(IFunctionHandler *pH, ScriptHandle entityId);
	int AddEntitySilhouette(IFunctionHandler *pH, ScriptHandle entityId, float r, float g, float b, float a);
	
	int OnGameStatusUpdate(IFunctionHandler *pH, int goodBad, const char *msg);
	int RemoveObjective(IFunctionHandler *pH, ScriptHandle entityId);


private:
	void RegisterGlobals();
	void RegisterMethods();

	ISystem						*m_pSystem;
	IGameFramework		*m_pGameFW;
};

#endif //__SCRIPTBIND_HUD_H__

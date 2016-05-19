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

// Description : Script bind functions forCrysis2 interactive object


#pragma once

#ifndef _SCRIPTBIND_INTERACTIVE_OBJECT_H_
#define _SCRIPTBIND_INTERACTIVE_OBJECT_H_

#include <IScriptSystem.h>
#include <ScriptHelpers.h>

#include "InteractiveObjectRegistry.h"


class CInteractiveObjectEx;

class CScriptBind_InteractiveObject :
	public CScriptableBase
{

private:

	typedef std::map<EntityId, CInteractiveObjectEx*> TInteractiveObjectsMap;

public:
	CScriptBind_InteractiveObject(ISystem *pSystem, IGameFramework *pGameFramework);
	virtual ~CScriptBind_InteractiveObject();

	virtual void GetMemoryUsage(ICrySizer *pSizer) const;
	

	void AttachTo(CInteractiveObjectEx *pInteractiveObject);
	void Detach(EntityId entityId);

	int CanUse(IFunctionHandler *pH, ScriptHandle userId);
	int Use(IFunctionHandler *pH, ScriptHandle userId);
	int StopUse(IFunctionHandler *pH, ScriptHandle userId);
	int AbortUse(IFunctionHandler *pH);

	ILINE CInteractiveObjectRegistry& GetObjectDataRegistry() { return m_objectDataRegistry; }

private:
	void RegisterMethods();

	CInteractiveObjectEx *GetInteractiveObject(IFunctionHandler *pH);

	ISystem					*m_pSystem;
	IGameFramework	*m_pGameFrameWork;

	TInteractiveObjectsMap m_interactiveObjectsMap;
	CInteractiveObjectRegistry m_objectDataRegistry;
};

#endif
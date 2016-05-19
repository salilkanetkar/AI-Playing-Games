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

// Description : Script Binding for Item

#ifndef __SCRIPTBIND_ITEM_H__
#define __SCRIPTBIND_ITEM_H__

#if _MSC_VER > 1000
# pragma once
#endif


#include <IScriptSystem.h>
#include <ScriptHelpers.h>


struct IItemSystem;
struct IGameFramework;
class CItem;
class CActor;


class CScriptBind_Item :
	public CScriptableBase
{
public:
	CScriptBind_Item(ISystem *pSystem, IGameFramework *pGameFramework);
	virtual ~CScriptBind_Item();

	virtual void GetMemoryUsage(ICrySizer *pSizer) const
	{
		pSizer->AddObject(this, sizeof(*this));
	}

	void AttachTo(CItem *pItem);

	int Reset(IFunctionHandler *pH);

	int CanPickUp(IFunctionHandler *pH, ScriptHandle userId);
	int CanUse(IFunctionHandler *pH, ScriptHandle userId);
	int CanUseVehicle(IFunctionHandler *pH, ScriptHandle userId);
	int IsPickable(IFunctionHandler *pH);
	int IsMounted(IFunctionHandler *pH);
	int GetUsableText(IFunctionHandler *pH);

	int GetOwnerId(IFunctionHandler *pH);
	int StartUse(IFunctionHandler *pH, ScriptHandle userId);
	int StopUse(IFunctionHandler *pH, ScriptHandle userId);
	int Use(IFunctionHandler *pH, ScriptHandle userId);
	int IsUsed(IFunctionHandler *pH);
	int OnUsed(IFunctionHandler *pH, ScriptHandle userId);

	int GetMountedDir(IFunctionHandler *pH);
	int SetMountedAngleLimits(IFunctionHandler *pH, float min_pitch, float max_pitch, float yaw_range);

  int OnHit(IFunctionHandler *pH, SmartScriptTable hitTable);
  int IsDestroyed(IFunctionHandler *pH);

	int HasAccessory(IFunctionHandler *pH, const char* accessoryName);

	int AllowDrop(IFunctionHandler *pH);
	int DisallowDrop(IFunctionHandler *pH);

private:
	void RegisterGlobals();
	void RegisterMethods();

	CItem *GetItem(IFunctionHandler *pH);
	CActor *GetActor(EntityId actorId);

	ISystem						*m_pSystem;
	IGameFramework		*m_pGameFW;

	SmartScriptTable	m_stats;
	SmartScriptTable	m_params;
};


#endif //__SCRIPTBIND_ITEM_H__
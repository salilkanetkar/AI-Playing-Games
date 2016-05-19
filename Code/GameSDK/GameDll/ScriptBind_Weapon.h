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

// Description : Script Binding for Weapon


#ifndef __SCRIPTBIND_WEAPON_H__
#define __SCRIPTBIND_WEAPON_H__

#if _MSC_VER > 1000
# pragma once
#endif


#include <IScriptSystem.h>
#include <ScriptHelpers.h>


struct IItemSystem;
struct IGameFramework;
class CItem;
class CWeapon;


class CScriptBind_Weapon :
	public CScriptableBase
{
public:
	CScriptBind_Weapon(ISystem *pSystem, IGameFramework *pGameFramework);
	virtual ~CScriptBind_Weapon();

	virtual void GetMemoryUsage(ICrySizer *pSizer) const
	{
		pSizer->AddObject(this, sizeof(*this));
	}

	void AttachTo(CWeapon *pWeapon);

	int SetAmmoCount(IFunctionHandler *pH);
	int GetAmmoCount(IFunctionHandler *pH);
	int GetClipSize(IFunctionHandler *pH);

	int GetAmmoType(IFunctionHandler *pH);

	int SupportsAccessory(IFunctionHandler *pH, const char *accessoryName);
	int GetAccessory(IFunctionHandler *pH, const char *accessoryName);
	int AttachAccessory(IFunctionHandler *pH, const char *className, bool attach, bool force);
	int SwitchAccessory(IFunctionHandler *pH, const char *className);

	int SetCurrentFireMode(IFunctionHandler *pH, const char *name);

	int Reload(IFunctionHandler *pH);

private:
	void RegisterGlobals();
	void RegisterMethods();

	CItem *GetItem(IFunctionHandler *pH);
	CWeapon *GetWeapon(IFunctionHandler *pH);

	ISystem						*m_pSystem;
	IGameFramework		*m_pGameFW;
};


#endif //__SCRIPTBIND_ITEM_H__
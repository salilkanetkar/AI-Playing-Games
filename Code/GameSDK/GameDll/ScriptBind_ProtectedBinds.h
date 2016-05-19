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

// Description : Script Binding for anything we only want to be accessed at controlled/protected points in the application


#ifndef __SCRIPTBIND_PROTECTED_H__
#define __SCRIPTBIND_PROTECTED_H__

//Base class include
#include <ScriptHelpers.h>

//Important includes
//#include <IScriptSystem.h>

//Pre-declarations
struct ISystem;
struct IPlayerProfile;

//////////////////////////////////////////////////////////////////////////
class CScriptBind_ProtectedBinds :
	public CScriptableBase
{

public:
	CScriptBind_ProtectedBinds( ISystem *pSystem );
	virtual ~CScriptBind_ProtectedBinds();

	virtual void GetMemoryUsage(ICrySizer *pSizer) const
	{
		pSizer->AddObject(this, sizeof(*this));
	}


	// Persistant Stats
	int GetPersistantStat(IFunctionHandler *pH, const char *name);
	int SetPersistantStat(IFunctionHandler *pH, const char *name, SmartScriptTable valueTab);
	int SavePersistantStatsToBlaze(IFunctionHandler *pH);

	//Profile Functions
	int GetProfileAttribute( IFunctionHandler *pH, const char* name );
	int SetProfileAttribute(  IFunctionHandler *pH, const char* name, SmartScriptTable valueTab );

	int ActivateDemoEventEntitlement( IFunctionHandler *pH );

	void	Enable();
	void	Disable();

protected:

private:
	void RegisterGlobals();
	void RegisterMethods();

	IPlayerProfile*		GetCurrentUserProfile();

	ISystem*					m_pSystem;
	bool							m_active;
};

#endif //__SCRIPTBIND_PROTECTED_H__

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

#ifndef __SCRIPT_BIND__TURRET__H__
#define __SCRIPT_BIND__TURRET__H__

#include <IScriptSystem.h>
#include <ScriptHelpers.h>


class CTurret;

class CScriptBind_Turret
	: public CScriptableBase
{
public:
	CScriptBind_Turret( ISystem* pSystem );
	virtual ~CScriptBind_Turret();

	void AttachTo( CTurret* pTurret );
	void DettachFrom( CTurret* pTurret );

	int Enable( IFunctionHandler* pH );
	int Disable( IFunctionHandler* pH );

	int OnPropertyChange( IFunctionHandler* pH );
	int OnHit( IFunctionHandler* pH, SmartScriptTable scriptHitInfo );
	int SetStateById( IFunctionHandler* pH, int stateId );

	int SetFactionToPlayerFaction( IFunctionHandler* pH );
};

#endif

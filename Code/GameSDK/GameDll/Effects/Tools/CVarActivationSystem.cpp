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

#include "StdAfx.h"
#include "CVarActivationSystem.h"
#include "IItemSystem.h"
#include "Effects/GameEffectsSystem.h"

//--------------------------------------------------------------------------------------------------
// Name: Initialise
// Desc: Initialises cvar activation system from data
//       Uses the xml node name for the cvar, and activeValue attribute
//			 eg <cl_fov activeValue="85"/>
//--------------------------------------------------------------------------------------------------
void CCVarActivationSystem::Initialise(const IItemParamsNode* cvarListXmlNode)
{
	if(cvarListXmlNode)
	{
		const IItemParamsNode* cvarXmlNode = NULL;
		SCVarParam* param = NULL;
		int cvarCount = cvarListXmlNode->GetChildCount();
		m_cvarParam.resize(cvarCount);
		for(int i=0; i<cvarCount; i++)
		{
			param = &m_cvarParam[i];
			cvarXmlNode = cvarListXmlNode->GetChild(i);
			param->cvar = gEnv->pConsole->GetCVar(cvarXmlNode->GetName());
			FX_ASSERT_MESSAGE(param->cvar,"Failed to find a CVAR for a game effect");
			cvarXmlNode->GetAttribute("activeValue",param->activeValue);
			param->originalValue = 0.0f;
		}
	}
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: Release
// Desc: Releases data used for CVar activation system
//--------------------------------------------------------------------------------------------------
void CCVarActivationSystem::Release()
{
	m_cvarParam.Free();
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: StoreCurrentValues
// Desc: Stores current values of CVars
//--------------------------------------------------------------------------------------------------
void CCVarActivationSystem::StoreCurrentValues()
{
	SCVarParam* param = NULL;
	for(uint32 i=0; i<m_cvarParam.Size(); i++)
	{
		param = &m_cvarParam[i];

		if(param->cvar)
		{
			param->originalValue = param->cvar->GetFVal();
		}
	}
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: SetCVarsActive
// Desc: Sets active status of cvars
//--------------------------------------------------------------------------------------------------
void CCVarActivationSystem::SetCVarsActive(bool isActive)
{
	SCVarParam* param = NULL;
	float value = 0.0f;
	for(uint32 i=0; i<m_cvarParam.Size(); i++)
	{
		param = &m_cvarParam[i];

		if(param->cvar)
		{
			if(isActive)
			{
				param->cvar->Set(param->activeValue);
			}
			else
			{
				param->cvar->Set(param->originalValue);
			}
		}
	}
}//-------------------------------------------------------------------------------------------------
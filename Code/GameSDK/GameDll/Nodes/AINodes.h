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

#ifndef AINodes_H
#define AINodes_H

#include "G2FlowBaseNode.h"
#include "AI/Assignment.h"

class CFlowNode_BattleFrontControl : public CFlowBaseNode<eNCT_Instanced>
{
public:
	enum EInputPorts
	{
		EIP_Group,
		EIP_Position,
		EIP_Activate,
		EIP_Deactivate,
	};

	static const SInputPortConfig inputPorts[];

	CFlowNode_BattleFrontControl(SActivationInfo * activationInformation)
		: m_enabled(false)
	{
	}

	virtual void GetConfiguration(SFlowNodeConfig& config);
	virtual void ProcessEvent(EFlowEvent event, SActivationInfo *activationInformation);
	virtual void GetMemoryUsage(ICrySizer * sizer) const;
	virtual IFlowNodePtr Clone(SActivationInfo *pActInfo) { return new CFlowNode_BattleFrontControl(pActInfo); }

private:
	bool m_enabled;
};

class CFlowNode_SetTurretFaction : public CFlowBaseNode<eNCT_Singleton>
{
public:
	enum InputPort
	{
		InputPort_Faction,
		InputPort_Set,
	};

	CFlowNode_SetTurretFaction(SActivationInfo* /*pActInfo*/)
	{
	}

	virtual void GetConfiguration(SFlowNodeConfig& config);
	virtual void ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo);
	virtual void GetMemoryUsage(ICrySizer * sizer) const { sizer->Add(*this); }

private:
	void SetFaction(SActivationInfo* pActInfo);
	class CGunTurret* GetTurret(IEntity& entity) const;
};


class CFlowNode_AICorpses : public CFlowBaseNode<eNCT_Singleton>
{
public:
	enum InputPort
	{
		InputPort_CleanCorpses,
	};

	CFlowNode_AICorpses(SActivationInfo* /*pActInfo*/)
	{
	}

	virtual void GetConfiguration(SFlowNodeConfig& config);
	virtual void ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo);

	virtual void GetMemoryUsage(ICrySizer * sizer) const;

};


#endif // AINodes_H

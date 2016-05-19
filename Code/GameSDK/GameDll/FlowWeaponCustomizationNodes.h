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

#ifndef __FlowWeaponCustomizationNodes_H__
#define __FlowWeaponCustomizationNodes_H__
#include "Nodes/G2FlowBaseNode.h"

//--------------------------------------------------------------------------------------------
class CFlashUIInventoryNode : public CFlowBaseNode<eNCT_Instanced>
{
public:
	CFlashUIInventoryNode( SActivationInfo * pActInfo );
	~CFlashUIInventoryNode();

	virtual void GetConfiguration( SFlowNodeConfig &config );
	virtual void ProcessEvent( EFlowEvent event, SActivationInfo *pActInfo );
	virtual void GetMemoryUsage(ICrySizer * s) const { s->Add(*this); }

	IFlowNodePtr Clone(SActivationInfo* pActInfo)
	{
		return new CFlashUIInventoryNode(pActInfo);
	}

private:
	enum EInputs
	{
		eI_Call = 0,
	};

	enum EOutputs
	{
		eO_OnCall = 0,
		eO_Args,
	};
};

//--------------------------------------------------------------------------------------------
class CFlashUIGetEquippedAccessoriesNode : public CFlowBaseNode<eNCT_Instanced>
{
public:
	CFlashUIGetEquippedAccessoriesNode( SActivationInfo * pActInfo ) {};
	~CFlashUIGetEquippedAccessoriesNode();

	virtual void GetConfiguration( SFlowNodeConfig &config );
	virtual void ProcessEvent( EFlowEvent event, SActivationInfo *pActInfo );
	virtual void GetMemoryUsage(ICrySizer * s) const { s->Add(*this); }

	IFlowNodePtr Clone(SActivationInfo* pActInfo)
	{
		return new CFlashUIGetEquippedAccessoriesNode(pActInfo);
	}

private:
	enum EInputs
	{
		eI_Call = 0,
		eI_Weapon,
	};

	enum EOutputs
	{
		eO_OnCall = 0,
		eO_Args,
	};
};

//--------------------------------------------------------------------------------------------
class CFlashUIGetCompatibleAccessoriesNode : public CFlowBaseNode<eNCT_Instanced>
{
public:
	CFlashUIGetCompatibleAccessoriesNode ( SActivationInfo * pActInfo ) {};
	~CFlashUIGetCompatibleAccessoriesNode ();

	virtual void GetConfiguration( SFlowNodeConfig &config );
	virtual void ProcessEvent( EFlowEvent event, SActivationInfo *pActInfo );
	virtual void GetMemoryUsage(ICrySizer * s) const { s->Add(*this); }
	
	IFlowNodePtr Clone(SActivationInfo* pActInfo)
	{
		return new CFlashUIGetCompatibleAccessoriesNode(pActInfo);
	}
private:
	enum EInputs
	{
		eI_Call = 0,
		eI_Weapon,
	};

	enum EOutputs
	{
		eO_OnCall = 0,
		eO_Args,
	};
};

//--------------------------------------------------------------------------------------------
class CFlashUICheckAccessoryState: public CFlowBaseNode<eNCT_Instanced>
{
public:
	CFlashUICheckAccessoryState ( SActivationInfo * pActInfo ) {};
	~CFlashUICheckAccessoryState ();

	virtual void GetConfiguration( SFlowNodeConfig &config );
	virtual void ProcessEvent( EFlowEvent event, SActivationInfo *pActInfo );
	virtual void GetMemoryUsage(ICrySizer * s) const { s->Add(*this); }

	IFlowNodePtr Clone(SActivationInfo* pActInfo)
	{
		return new CFlashUICheckAccessoryState(pActInfo);
	}
private:
	enum EInputs
	{
		eI_Call = 0,
		eI_Accessory,
		eI_Weapon,
	};

	enum EOutputs
	{
		eO_Equipped = 0,
		eO_InInventory,
		eO_DontHave,
	};
};

//--------------------------------------------------------------------------------------------
class CSetEquipmentLoadoutNode: public CFlowBaseNode<eNCT_Instanced>
{
public:
	CSetEquipmentLoadoutNode ( SActivationInfo * pActInfo ) {};
	~CSetEquipmentLoadoutNode () {};

	virtual void GetConfiguration( SFlowNodeConfig &config );
	virtual void ProcessEvent( EFlowEvent event, SActivationInfo *pActInfo );
	virtual void GetMemoryUsage(ICrySizer * s) const { s->Add(*this); }

	IFlowNodePtr Clone(SActivationInfo* pActInfo)
	{
		return new CSetEquipmentLoadoutNode(pActInfo);
	}
private:
	enum EInputs
	{
		eI_Set = 0,
		eI_EquipLoadout,
	};

	enum EOutputs
	{
	};
};


#endif
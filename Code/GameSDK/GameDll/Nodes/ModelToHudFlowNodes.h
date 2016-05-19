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

#ifndef __ModelToHudFlowNodes_H__
#define __ModelToHudFlowNodes_H__
#include "Nodes/G2FlowBaseNode.h"
#include "UI/Menu3dModels/MenuRender3DModelMgr.h"

class CFlowSetupModelPostRender: public CFlowBaseNode<eNCT_Instanced>
{
public:
	enum EInputs
	{
		IN_START,
		IN_SHUTDOWN,
		IN_MC,
		IN_AMBIENTLIGHTCOLOR,
		IN_AMBIENTLIGHTSTRENGTH,
		IN_LIGHTCOLOR1,
		IN_LIGHTCOLOR2,
		IN_LIGHTCOLOR3,
		IN_DEBUGSCALE,
	};

	CFlowSetupModelPostRender( SActivationInfo * pActInfo );
	virtual IFlowNodePtr Clone(SActivationInfo *pActInfo);
	virtual void GetConfiguration(SFlowNodeConfig& config);
	virtual void ProcessEvent( EFlowEvent event, SActivationInfo *pActInfo );
	virtual void GetMemoryUsage(ICrySizer * s) const;

private:
	CMenuRender3DModelMgr::TAddedModelIndex characterModelIndex;
	char* playerModelName;
	string sUIElement;
	string sMovieClipName;
};


class CFlowAddModelToPostRender: public CFlowBaseNode<eNCT_Instanced>
{
public:
	enum EInputs
	{
		IN_ADD,
		IN_MODEL,
		IN_SCALE,
		IN_ANIM,
		IN_ANIM_SPEED,
		IN_ENTITYPOS,
		IN_ENTITYROT,
		IN_ENTITYCONTROT,
		IN_SCREENUV,
		IN_SCREENU2V2,
	};

	CFlowAddModelToPostRender( SActivationInfo * pActInfo );
	virtual IFlowNodePtr Clone(SActivationInfo *pActInfo);
	virtual void GetConfiguration(SFlowNodeConfig& config);
	virtual void ProcessEvent( EFlowEvent event, SActivationInfo *pActInfo );
	virtual void GetMemoryUsage(ICrySizer * s) const;

private:
	CMenuRender3DModelMgr::TAddedModelIndex characterModelIndex;
	char* playerModelName;
	string sUIElement;
	string sMovieClipName;
};

#endif
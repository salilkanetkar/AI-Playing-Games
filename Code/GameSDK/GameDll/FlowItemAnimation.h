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

#ifndef __FLOWITEMANIMATIOn_H__
#define __FLOWITEMANIMATIOn_H__

#include "Game.h"
#include "Item.h"
#include "Actor.h"
#include "Nodes/G2FlowBaseNode.h"
#include "Nodes/G2FlowBaseNode.h"

class CFlowItemAction : public CFlowBaseNode<eNCT_Instanced>
{
private:

public:

	CFlowItemAction( SActivationInfo * pActInfo );

	IFlowNodePtr Clone( SActivationInfo * pActInfo );
	virtual void GetConfiguration(SFlowNodeConfig& config);
	virtual void ProcessEvent( EFlowEvent event, SActivationInfo *pActInfo );
	virtual void GetMemoryUsage(ICrySizer * s) const;

private:
	void StartDoneCountDown(SActivationInfo* pActInfo, float time);
	IItem* GetItem(SActivationInfo* pActInfo) const;
	void Activate(SActivationInfo* pActInfo);
	void Update(SActivationInfo* pActInfo);

	float m_timerCountDown;
};

#endif //__FLOWITEMANIMATIOn_H__

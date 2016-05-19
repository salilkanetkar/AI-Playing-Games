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

#ifndef SCREEN_FADER_NODE_H
#define SCREEN_FADER_NODE_H

#include "GameFlowBaseNode.h"

namespace EngineFacade
{
	struct IGameEnvironment;
}

class CFlowNode_ScreenFader : public CGameFlowBaseNode
{
public:
	static const SInputPortConfig inputPorts[];

	CFlowNode_ScreenFader(IGameEnvironment& environment, SActivationInfo* activationInformation);

	virtual void GetConfiguration(SFlowNodeConfig& config);
	virtual void ProcessActivateEvent(SActivationInfo* activationInformation);
	virtual void GetMemoryStatistics(ICrySizer* sizer);

	enum EInputPorts
	{
		eInputPorts_FadeIn,
		eInputPorts_FadeOut,
		eInputPorts_FadeInTime,
		eInputPorts_FadeOutTime,
		eInputPorts_FadeColor,
		eInputPorts_UseCurrentColor,
		eInputPorts_Texture,
		eInputPorts_Count,
	};

private:
	IGameEnvironment& m_environment;
};

#endif 
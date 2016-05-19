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

// Description : Player ability manager.


#ifndef __MANUAL_FRAME_STEP_H__
#define __MANUAL_FRAME_STEP_H__

#include "GameRulesModules/IGameRulesModuleRMIListener.h"

class CManualFrameStepManager
	: public IInputEventListener
	, public IGameRulesModuleRMIListener
{
public:
	CManualFrameStepManager();
	virtual ~CManualFrameStepManager();

	bool Update();
	
	bool IsEnabled() const;
	void Enable(bool enable);
	void Toggle();
	void RequestFrames(uint8 numFrames);

	// IInputEventListener
	virtual bool OnInputEvent(const SInputEvent& inputEvent);
	// ~IInputEventListener

	// IGameRulesModuleRMIListener
	virtual void OnSingleEntityRMI(CGameRules::SModuleRMIEntityParams params);
	virtual void OnDoubleEntityRMI(CGameRules::SModuleRMITwoEntityParams params){}
	virtual void OnEntityWithTimeRMI(CGameRules::SModuleRMIEntityTimeParams params){}
	virtual void OnSvClientActionRMI(CGameRules::SModuleRMISvClientActionParams params, EntityId fromEid){}
	// ~IGameRulesModuleRMIListener

private:
	int         m_rmiListenerIdx;
	int32       m_framesLeft;
	float       m_previousFixedStep;
};

#endif

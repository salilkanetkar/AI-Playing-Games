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

// Description : This node includes different generic VR functionality


#include "StdAfx.h"

#include "Nodes/G2FlowBaseNode.h"
#include <IHMDDevice.h>
#include "ICryAnimation.h"
#include <IHMDDevice.h>
#include <IHMDManager.h>

class CVRTools : public CFlowBaseNode<eNCT_Singleton>
{
	enum INPUTS
	{
		EIP_RecenterPose = 0
	};

	enum OUTPUTS
	{
		EOP_Done = 0,
		EOP_Triggered,
		EOP_Failed,
	};

public:
	CVRTools( SActivationInfo * pActInfo )
	{
	}

	virtual void GetMemoryUsage(ICrySizer * s) const
	{
		s->Add(*this);
	}

	virtual void GetConfiguration( SFlowNodeConfig &config )
	{
		static const SInputPortConfig in_config[] = {
			InputPortConfig_Void( "RecentrePose",_HELP("Resets the tracking origin to the headset's current location, and sets the yaw origin to the current headset yaw value") ),
			{0}
		};
		static const SOutputPortConfig out_config[] = {
			OutputPortConfig_AnyType("Done", _HELP("The selected operation has been acknoledge. This output will always get triggered.") ),
			OutputPortConfig_AnyType("Triggered", _HELP("The selected operation has been triggered.") ),
			OutputPortConfig_AnyType("Failed", _HELP("The selected operation did not work as expected (e.g. the VR operation was not supported).") ),
			{0}
		};
		config.sDescription = _HELP( "Various VR-specific utils" );
		config.pInputPorts = in_config;
		config.pOutputPorts = out_config;
		config.SetCategory(EFLN_APPROVED);
	}

	virtual void ProcessEvent(EFlowEvent event, SActivationInfo *pActInfo)
	{
		switch (event)
		{
		case eFE_Activate:
			{
				if(IsPortActive(pActInfo, EIP_RecenterPose))
				{
					bool triggered = false;
					IHMDManager* pHmDManager = gEnv->pSystem->GetHMDManager();
					IHMDDevice* pDev = pHmDManager ? pHmDManager->GetHMDDevice() : NULL;
					if (pDev && pHmDManager->IsStereoSetupOk())
					{
						const HMDTrackingState& sensorState = pDev->GetTrackingState();
						if (sensorState.CheckStatusFlags(HS_IsUsable))
						{
							pDev->RecenterPose();
							triggered = true;
						}
					}

					ActivateOutput(pActInfo, triggered ? EOP_Triggered : EOP_Failed, true);
					ActivateOutput(pActInfo, EOP_Done, true);
				}
			}
			break;
		}
	}
};

class CVRGetCameraAngles : public CFlowBaseNode<eNCT_Singleton>
{
	enum INPUTS
	{
		EIP_Read = 0,
	};

	enum OUTPUTS
	{
		EOP_Done = 0,
		EOP_Roll,
		EOP_Pitch,
		EOP_Yaw
	};

public:
	CVRGetCameraAngles( SActivationInfo * pActInfo )
	{
	}

	virtual void GetMemoryUsage(ICrySizer * s) const
	{
		s->Add(*this);
	}

	virtual void GetConfiguration( SFlowNodeConfig &config )
	{
		static const SInputPortConfig in_config[] = {
			InputPortConfig<float>( "Read",_HELP("Read the camera angles (Roll,Pitch,Yaw)") ),
			{0}
		};
		static const SOutputPortConfig out_config[] = {
			OutputPortConfig_AnyType("Done", _HELP("The selected operation has been acknoledge. This output will always get triggered.") ),
			OutputPortConfig_AnyType("Roll", _HELP("Camera Roll.") ),
			OutputPortConfig_AnyType("Pitch", _HELP("Camera Pitch;") ),
			OutputPortConfig_AnyType("Yaw", _HELP("Camera Yaw;") ),
			{0}
		};
		config.sDescription = _HELP( "Various VR-specific utils" );
		config.pInputPorts = in_config;
		config.pOutputPorts = out_config;
		config.SetCategory(EFLN_APPROVED);
	}

	virtual void ProcessEvent(EFlowEvent event, SActivationInfo *pActInfo)
	{
		switch (event)
		{
		case eFE_Activate:
			{
				if(IsPortActive(pActInfo, EIP_Read))
				{
					if (IRenderer * pRenderer = gEnv->pRenderer)
					{
						const CCamera &rCam = pRenderer->GetCamera();
						const Ang3 angles = rCam.GetAngles();
						ActivateOutput(pActInfo, EOP_Roll, angles.z);
						ActivateOutput(pActInfo, EOP_Pitch, angles.y);
						ActivateOutput(pActInfo, EOP_Yaw, angles.x);

						ActivateOutput(pActInfo, EOP_Done, true);
					}
				}
			}
			break;
		}
	}
};


REGISTER_FLOW_NODE( "VR:Tools", CVRTools);
REGISTER_FLOW_NODE( "VR:GetCameraAngles", CVRGetCameraAngles);

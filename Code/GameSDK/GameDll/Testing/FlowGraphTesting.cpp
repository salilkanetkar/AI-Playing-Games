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

#include "FlowGraphTesting.h"

CryUnit::StringStream& operator << (CryUnit::StringStream& stringStream, const SInputPortConfig& portConfig)
{
    stringStream << portConfig.name << ":" << portConfig.humanName;
    return stringStream;
}

namespace GameTesting
{
	CFlowNodeTestingFacility::CFlowNodeTestingFacility( IFlowNode& nodeToTest, const unsigned int inputPortsCount ) : m_nodeToTest(nodeToTest)
		, m_inputData(0)
	{
		CRY_ASSERT(inputPortsCount > 0);

		SFlowNodeConfig flowNodeConfiguration;
		nodeToTest.GetConfiguration(flowNodeConfiguration);

		m_inputData = new TFlowInputData[inputPortsCount];
		for (unsigned int inputIndex = 0; inputIndex < inputPortsCount; ++inputIndex)
		{
			const SInputPortConfig& inputPort = flowNodeConfiguration.pInputPorts[inputIndex];
			const TFlowInputData& defaultData = inputPort.defaultData;

			m_inputData[inputIndex] = defaultData;
		}
	}

	CFlowNodeTestingFacility::~CFlowNodeTestingFacility()
	{
		delete[] m_inputData;
		m_inputData = 0;
	}

	void CFlowNodeTestingFacility::ProcessEvent( IFlowNode::EFlowEvent event )
	{
		IFlowNode::SActivationInfo activationInformation(0, 0, 0, m_inputData);
		m_nodeToTest.ProcessEvent(event, &activationInformation);
	}
}
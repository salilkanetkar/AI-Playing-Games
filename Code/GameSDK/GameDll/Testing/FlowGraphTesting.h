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

#ifndef FLOW_GRAPH_TESTING_H_INCLUDED
#define FLOW_GRAPH_TESTING_H_INCLUDED

#include <IFlowSystem.h>

CryUnit::StringStream& operator << (CryUnit::StringStream& stringStream, const SInputPortConfig& portConfig);

namespace GameTesting
{
	class CFlowNodeTestingFacility
	{
	public:
		CFlowNodeTestingFacility(IFlowNode& nodeToTest, const unsigned int inputPortsCount);
		~CFlowNodeTestingFacility();

		void ProcessEvent(IFlowNode::EFlowEvent event);

		template <class InputType>
		void SetInputByIndex(const unsigned int inputIndex, const InputType& value)
		{
			m_inputData[inputIndex].Set(value);
		}

	private:
		IFlowNode& m_nodeToTest;
		TFlowInputData* m_inputData;
	};
}

#endif //FLOW_GRAPH_TESTING_H_INCLUDED

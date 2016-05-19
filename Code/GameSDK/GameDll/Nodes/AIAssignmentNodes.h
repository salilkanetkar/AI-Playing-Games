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

#ifndef AIAssignmentNodes_h
#define AIAssignmentNodes_h

#include "G2FlowBaseNode.h"
#include "AI/Assignment.h"

//////////////////////////////////////////////////////////////////////////

class AssignmentFlowNodeBase 
	: public CFlowBaseNode<eNCT_Singleton>
{
public:
	virtual int GetSetPortNumber() const = 0;
	virtual Assignment SpecifyAssignment(SActivationInfo* pActInfo) = 0;

	void ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo);

protected:

	void DispatchAssignment( Assignment assignment, IEntity* entity );
};

//////////////////////////////////////////////////////////////////////////

class ClearAssignmentFlowNode
	: public AssignmentFlowNodeBase
{
public:
	enum InputPort
	{
		InputPort_Set,
	};

	ClearAssignmentFlowNode(SActivationInfo* pActInfo)	{}

	virtual void GetConfiguration( SFlowNodeConfig& config );
	virtual void GetMemoryUsage( ICrySizer * sizer ) const { sizer->Add(*this); }

	int GetSetPortNumber() const { return InputPort_Set; }
	Assignment SpecifyAssignment(SActivationInfo* pActInfo);
};

//////////////////////////////////////////////////////////////////////////

class DefendAreaAssignmentFlowNode
	: public AssignmentFlowNodeBase
{
public:
	enum InputPort
	{
		InputPort_Set,
		InputPort_Position,
		InputPort_Radius,
	};

	DefendAreaAssignmentFlowNode(SActivationInfo* pActInfo)	{}

	virtual void GetConfiguration( SFlowNodeConfig& config );
	virtual void GetMemoryUsage( ICrySizer * sizer ) const { sizer->Add(*this); }

	int GetSetPortNumber() const { return InputPort_Set; }
	Assignment SpecifyAssignment(SActivationInfo* pActInfo);
};

//////////////////////////////////////////////////////////////////////////

class HoldPositionAssignmentFlowNode
	: public AssignmentFlowNodeBase
{
public:
	enum InputPort
	{
		InputPort_Set,
		InputPort_Position,
		InputPort_Radius,
		InputPort_Direction,
		InputPort_UseCover,
	};

	HoldPositionAssignmentFlowNode(SActivationInfo* pActInfo)	{}

	virtual void GetConfiguration( SFlowNodeConfig& config );
	virtual void GetMemoryUsage( ICrySizer * sizer ) const { sizer->Add(*this); }

	int GetSetPortNumber() const { return InputPort_Set; }
	Assignment SpecifyAssignment(SActivationInfo* pActInfo);
};

//////////////////////////////////////////////////////////////////////////

class CombatMoveAssignmentFlowNode
	: public AssignmentFlowNodeBase
{
public:
	enum InputPort
	{
		InputPort_Set,
		InputPort_Position,
		InputPort_UseCover,
	};

	CombatMoveAssignmentFlowNode(SActivationInfo* pActInfo)	{}

	virtual void GetConfiguration( SFlowNodeConfig& config );
	virtual void GetMemoryUsage( ICrySizer * sizer ) const { sizer->Add(*this); }

	int GetSetPortNumber() const { return InputPort_Set; }
	Assignment SpecifyAssignment(SActivationInfo* pActInfo);
};

//////////////////////////////////////////////////////////////////////////


#endif //AIAssignmentNodes_h

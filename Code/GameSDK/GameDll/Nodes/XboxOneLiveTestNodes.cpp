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
#include "Game.h"
#include "Nodes/G2FlowBaseNode.h"


//////////////////////////////////////////////////////////////////////////
class CFlowXboxLiveEventTest : public CFlowBaseNode<eNCT_Instanced>
{
public:
	CFlowXboxLiveEventTest( SActivationInfo * pActInfo ) {}

	virtual ~CFlowXboxLiveEventTest() {}

	IFlowNodePtr Clone( SActivationInfo * pActInfo )
	{
		return new CFlowXboxLiveEventTest(pActInfo);
	}

	void Serialize(SActivationInfo* pActInfo, TSerialize ser) {}

	enum EInputPorts
	{
		EIP_Send = 0,
		EIP_Poll,
	};

	enum EOutputPorts
	{
		EOP_Success = 0,
		EOP_Fail,
	};

	virtual void GetConfiguration(SFlowNodeConfig& config)
	{
		static const SInputPortConfig inputs[] = {
			InputPortConfig_Void("Send", _HELP("Send test event")),
			InputPortConfig_Void("Poll", _HELP("Poll test event count")),
			{0}
		};

		static const SOutputPortConfig outputs[] = {
			OutputPortConfig_Void     ("Success",  _HELP("Triggers if sending succeeded")),
			OutputPortConfig_Void     ("Fail",  _HELP("Triggers if sending failed")),
			{0}
		};

		config.pInputPorts = inputs;
		config.pOutputPorts = outputs;
		config.sDescription = _HELP("Send test event to xbox live");
		config.SetCategory(EFLN_ADVANCED);
	}

	virtual void ProcessEvent( EFlowEvent event, SActivationInfo *pActInfo )
	{
		switch (event)
		{
		case eFE_Initialize:
			{
			}
			break;
		case eFE_Activate:
			break;
		}
	}

	virtual void GetMemoryUsage(ICrySizer * s) const
	{
		s->Add(*this);
	}
};


//////////////////////////////////////////////////////////////////////////
class CFlowXboxLiveLeaderboardTest : public CFlowBaseNode<eNCT_Instanced>
{
public:
	CFlowXboxLiveLeaderboardTest( SActivationInfo * pActInfo ) {}

	virtual ~CFlowXboxLiveLeaderboardTest() {}

	IFlowNodePtr Clone( SActivationInfo * pActInfo )
	{
		return new CFlowXboxLiveLeaderboardTest(pActInfo);
	}

	void Serialize(SActivationInfo* pActInfo, TSerialize ser) {}

	enum EInputPorts
	{
		EIP_Poll = 0,
	};

	enum EOutputPorts
	{
		EOP_Success = 0,
		EOP_Fail,
	};

	virtual void GetConfiguration(SFlowNodeConfig& config)
	{
		static const SInputPortConfig inputs[] = {
			InputPortConfig_Void("Poll", _HELP("Poll leaderboard")),
			{0}
		};

		static const SOutputPortConfig outputs[] = {
			OutputPortConfig_Void     ("Success",  _HELP("Triggers if sending succeeded")),
			OutputPortConfig_Void     ("Fail",  _HELP("Triggers if sending failed")),
			{0}
		};

		config.nFlags |= EFLN_TARGET_ENTITY;
		config.pInputPorts = inputs;
		config.pOutputPorts = outputs;
		config.sDescription = _HELP("Read an example leaderboard");
		config.SetCategory(EFLN_ADVANCED);
	}

	virtual void ProcessEvent( EFlowEvent event, SActivationInfo *pActInfo )
	{
		switch (event)
		{
		case eFE_Initialize:
			{
			}
			break;
		case eFE_Activate:
			break;
		}
	}

	virtual void GetMemoryUsage(ICrySizer * s) const
	{
		s->Add(*this);
	}
};


//////////////////////////////////////////////////////////////////////////
class CFlowXboxLivePartyTest : public CFlowBaseNode<eNCT_Instanced>
{
public:
	CFlowXboxLivePartyTest( SActivationInfo * pActInfo ) {}

	virtual ~CFlowXboxLivePartyTest() {}

	IFlowNodePtr Clone( SActivationInfo * pActInfo )
	{
		return new CFlowXboxLivePartyTest(pActInfo);
	}

	void Serialize(SActivationInfo* pActInfo, TSerialize ser) {}

	enum EInputPorts
	{
		EIP_Poll = 0,
		EIP_Launch,
		EIP_Leave,
	};

	enum EOutputPorts
	{
		EOP_Success = 0,
		EOP_Fail,
	};

	virtual void GetConfiguration(SFlowNodeConfig& config)
	{
		static const SInputPortConfig inputs[] = {
			InputPortConfig_Void("Poll", _HELP("Poll party info")),
			InputPortConfig_Void("Launch", _HELP("Launch match")),
			InputPortConfig_Void("Leave", _HELP("Launch match")),
			{0}
		};

		static const SOutputPortConfig outputs[] = {
			OutputPortConfig_Void     ("Success",  _HELP("Triggers if sending succeeded")),
			OutputPortConfig_Void     ("Fail",  _HELP("Triggers if sending failed")),
			{0}
		};

		config.pInputPorts = inputs;
		config.pOutputPorts = outputs;
		config.sDescription = _HELP("poll party info for xbox one live");
		config.SetCategory(EFLN_ADVANCED);
	}

	virtual void ProcessEvent( EFlowEvent event, SActivationInfo *pActInfo )
	{
		switch (event)
		{
		case eFE_Initialize:
			{
			}
			break;
		case eFE_Activate:
			break;
		}
	}

	virtual void GetMemoryUsage(ICrySizer * s) const
	{
		s->Add(*this);
	}
};


//////////////////////////////////////////////////////////////////////////
class CFlowXboxLiveCheckHost : public CFlowBaseNode<eNCT_Instanced>
{
public:
	CFlowXboxLiveCheckHost( SActivationInfo * pActInfo ) {}

	virtual ~CFlowXboxLiveCheckHost() {}

	IFlowNodePtr Clone( SActivationInfo * pActInfo )
	{
		return new CFlowXboxLiveCheckHost(pActInfo);
	}

	void Serialize(SActivationInfo* pActInfo, TSerialize ser) {}

	enum EInputPorts
	{
		EIP_Poll = 0,
	};

	enum EOutputPorts
	{
		EOP_Host = 0,
		EOP_Client,
	};

	virtual void GetConfiguration(SFlowNodeConfig& config)
	{
		static const SInputPortConfig inputs[] = {
			InputPortConfig_Void("Poll", _HELP("Poll if user is host")),
			{0}
		};

		static const SOutputPortConfig outputs[] = {
			OutputPortConfig_Void     ("Host",  _HELP("Triggers if sending succeeded")),
			OutputPortConfig_Void     ("Client",  _HELP("Triggers if sending failed")),
			{0}
		};

		config.pInputPorts = inputs;
		config.pOutputPorts = outputs;
		config.sDescription = _HELP("check if this user is host or client for xbox one live");
		config.SetCategory(EFLN_ADVANCED);
	}

	virtual void ProcessEvent( EFlowEvent event, SActivationInfo *pActInfo )
	{
		switch (event)
		{
		case eFE_Initialize:
			{
			}
			break;
		case eFE_Activate:
			break;
		}
	}

	virtual void GetMemoryUsage(ICrySizer * s) const
	{
		s->Add(*this);
	}
};

//////////////////////////////////////////////////////////////////////////
REGISTER_FLOW_NODE( "XboxLive:XboxLiveEventTest", CFlowXboxLiveEventTest);
REGISTER_FLOW_NODE( "XboxLive:XboxLiveLeaderboardTest", CFlowXboxLiveLeaderboardTest);
REGISTER_FLOW_NODE( "XboxLive:XboxLivePartyTest", CFlowXboxLivePartyTest);
REGISTER_FLOW_NODE( "XboxLive:XboxLiveCheckHost", CFlowXboxLiveCheckHost);

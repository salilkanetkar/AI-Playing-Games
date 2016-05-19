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

#ifndef _GameRulesPlayerSetupModule_h_
#define _GameRulesPlayerSetupModule_h_

#if _MSC_VER > 1000
# pragma once
#endif


class IGameRulesPlayerSetupModule
{
public:
	virtual ~IGameRulesPlayerSetupModule() {}

	virtual void Init(XmlNodeRef xml) = 0;
	virtual void PostInit() = 0;

	virtual void OnClientConnect(ChannelId channelId, bool isReset, const char* playerName, bool isSpectator) = 0;
	virtual void OnPlayerRevived(EntityId playerId) = 0;
	virtual void OnActorJoinedFromSpectate(IActor* pActor, ChannelId channelId) = 0;

	virtual void SvOnStartNewRound(bool isReset) = 0;
};

#endif // _GameRulesPlayerSetupModule_h_
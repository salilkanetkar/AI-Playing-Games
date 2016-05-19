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

#ifndef _GAME_RULES_STATS_RECORDING_MODULE_H_
#define _GAME_RULES_STATS_RECORDING_MODULE_H_

struct HitInfo;
class XmlNodeRef;
struct IStatsTracker;

#include "../GameRulesTypes.h"

class IGameRulesStatsRecording
{
	public:
		virtual			~IGameRulesStatsRecording() {}

		virtual void	Init(
							XmlNodeRef		inXML)=0;

		virtual void	OnInGameBegin()=0;
		virtual void	OnPostGameBegin()=0;
		virtual void	OnGameEnd()=0;
		virtual void	OnPlayerRevived(
							IActor			*inActor)=0;
		virtual void	OnPlayerKilled(
							IActor			*inActor)=0;
		 
#if USE_PC_PREMATCH
		virtual void OnPrematchEnd(
							IActor			*inActor)=0;
#endif
};

#endif // _GAME_RULES_STATS_RECORDING_MODULE_H_

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

// Description : Game rules module to allow a game mode based on module to use the IGameStatistics
//               interface


#ifndef __GAMERULESSTATSRECORDING_H__
#define __GAMERULESSTATSRECORDING_H__

#include "IGameRulesStatsRecording.h"

struct IGameStatistics;
struct IActor;
class CStatsRecordingMgr;

class CGameRulesStatsRecording : public IGameRulesStatsRecording
{
	protected:
		IGameStatistics		*m_gameStatistics;
		IActorSystem		*m_actorSystem;
		CStatsRecordingMgr	*m_statsMgr;

	public:
							CGameRulesStatsRecording() :
								m_gameStatistics(NULL),
								m_actorSystem(NULL),
								m_statsMgr(NULL)
							{
							}

		virtual void		Init(
								XmlNodeRef		xml);
		virtual void		OnInGameBegin();
		virtual void		OnPostGameBegin();
		virtual void		OnGameEnd();
		virtual void		OnPlayerRevived(
								IActor			*inActor);
		virtual void		OnPlayerKilled(
								IActor			*inActor);

#if USE_PC_PREMATCH
		virtual void OnPrematchEnd(
								IActor			*inActor);
#endif
};

#endif // __GAMERULESSTATSRECORDING_H__


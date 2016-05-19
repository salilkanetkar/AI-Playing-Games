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

// Description : This the declaration for CStatsAgent


#ifndef __STATS_AGENT_H__
#define __STATS_AGENT_H__

#pragma once

class ICmdLineArg;

class CStatsAgent
{
public:
	static void CreatePipe( const ICmdLineArg* pPipeName );
	static void ClosePipe( void );
	static void Update( void );

	static void SetDelayMessages(bool enable);
	static void SetDelayTimeout(const int timeout);
private:
	static bool s_delayMessages;
	static int s_iDelayMessagesCounter;
	CStatsAgent( void ) {} // Prevent instantiation
};

#endif

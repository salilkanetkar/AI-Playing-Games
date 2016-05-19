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

// Description : Wrapper around platform-dependent pipe comms


#ifndef __STATS_AGENT_PIPES_H__
#define __STATS_AGENT_PIPES_H__

#pragma once

class CStatsAgentPipe
{
public:
	static void OpenPipe(const char *szPipeName);
	static void ClosePipe();

	static bool Send(const char *szMessage, const char *szPrefix = 0, const char *szDebugTag = 0);
	static const char* Receive();

	static bool PipeOpen();

private:
	CStatsAgentPipe(); // prevent instantiation

	static bool CreatePipe(const char *szName);
};

#endif // __STATS_AGENT_PIPES_H__

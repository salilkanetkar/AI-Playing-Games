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

// Description : Defines ENABLE_GAME_CODE_COVERAGE

#ifndef __GAME_CODE_COVERAGE_ENABLED_H_
#define __GAME_CODE_COVERAGE_ENABLED_H_

#include <ICodeCheckpointMgr.h>

//===============================================================================================

// 1 = Disable the game DLL's own code coverage system and use the engine's ICodeCoverageMgr instance IF IT'S ENABLED
// 0 = Use the game's own code coverage system if available (fall back to using engine's system if ENABLE_GAME_CODE_COVERAGE gets set to 0 by something else)
#define GAME_SHOULD_PRIORITISE_ENGINE_CODE_COVERAGE_SYSTEM					1

//===============================================================================================

#if defined(CODECHECKPOINT_ENABLED) && (GAME_SHOULD_PRIORITISE_ENGINE_CODE_COVERAGE_SYSTEM)
	#define ENABLE_GAME_CODE_COVERAGE     0
#elif defined(_RELEASE)
	#define ENABLE_GAME_CODE_COVERAGE			0		// Final release - never enable!
#elif !defined(_DEBUG)
	#if defined(WIN64) || defined(WIN32)
		#define ENABLE_GAME_CODE_COVERAGE		1		// Profile builds on PC
	#else
		#define ENABLE_GAME_CODE_COVERAGE		0		// Profile builds on consoles
	#endif
#else
	#if defined(WIN64) || defined(WIN32)
		#define ENABLE_GAME_CODE_COVERAGE		1		// Debug builds on PC
	#else
		#define ENABLE_GAME_CODE_COVERAGE		1		// Debug builds on consoles
	#endif
#endif

#if defined(CODECHECKPOINT_ENABLED) && !ENABLE_GAME_CODE_COVERAGE
	#define ENABLE_SHARED_CODE_COVERAGE 1
#endif

#endif // __GAME_CODE_COVERAGE_ENABLED_H_
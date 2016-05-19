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

// Description : Interface class for anything which wants to be informed of
//               code coverage checkpoints being hit


#pragma once

#ifndef __I_GAME_CODE_COVERAGE_LISTENER_H_
#define __I_GAME_CODE_COVERAGE_LISTENER_H_

#include "GameCodeCoverage/GameCodeCoverageEnabled.h"

#if ENABLE_GAME_CODE_COVERAGE

class CGameCodeCoverageCheckPoint;

class IGameCodeCoverageListener
{
	public:
	virtual void InformCodeCoverageCheckpointHit(CGameCodeCoverageCheckPoint * cp) = 0;
};

#endif // ENABLE_GAME_CODE_COVERAGE

#endif // __I_GAME_CODE_COVERAGE_LISTENER_H_
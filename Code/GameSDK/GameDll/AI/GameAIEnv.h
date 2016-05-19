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

#ifndef GameAIEnv_h
#define GameAIEnv_h


// Forward declarations:
namespace HazardSystem
{
	class HazardModule;
};

struct GameAIEnv
{
	GameAIEnv();

	class CAIPressureModule* pressureModule;
	class CAIAggressionModule* aggressionModule;
	class CAIBattleFrontModule* battleFrontModule;
	class SearchModule* searchModule;
	class StalkerModule* stalkerModule;
	class RangeModule* rangeModule;
	class AloneDetectorModule* aloneDetectorModule;
	class HazardSystem::HazardModule* hazardModule;
	class RadioChatterModule* radioChatterModule;
};

extern GameAIEnv gGameAIEnv;

#endif // GameAIEnv_h

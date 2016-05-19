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

#ifndef GAME_TESTING_EDITOR_SMOCK_TEST_FIXTURE_H
#define GAME_TESTING_EDITOR_SMOCK_TEST_FIXTURE_H

#include "BinariesPathHelper.h"

struct ISystem;
class CEditorGame;

namespace GameTesting
{
	CRY_TEST_FIXTURE(EditorSmokeTestFixture, CryUnit::ITestFixture, EditorSmokeTestSuite)
    {
    public:
        void SetUp();
        void TearDown();

    private:
        void CreateSystem(SSystemInitParams& initParams);
        HMODULE LoadSystemLibrary(const SSystemInitParams& systemInit);
        static ISystem* g_system;

    protected:
		BinariesPathHelper m_pathHelper;
        static CEditorGame* g_editorGame;
    };

}

#endif

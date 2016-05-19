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

#include "Stdafx.h"
#include "GameStartup.h"
#include "EditorSmokeTestFixture.h"
#include "Editor/EditorGame.h"
#include <CryLibrary.h>
#include <IEntitySystem.h>
using namespace GameTesting;

ISystem* EditorSmokeTestFixture::g_system = NULL;
CEditorGame* EditorSmokeTestFixture::g_editorGame = NULL;

#ifdef WIN32

void EditorSmokeTestFixture::CreateSystem(SSystemInitParams& initParams)
{
    m_pathHelper.FillBinariesDir(initParams);
    initParams.bEditor = true;

    HMODULE module = LoadSystemLibrary(initParams);
    CRY_ASSERT_MESSAGE(module, "Unable to load CrySystem.dll");

    SetCurrentDirectory(m_pathHelper.GetCurrentDir());
    PFNCREATESYSTEMINTERFACE createSystemInterface = (PFNCREATESYSTEMINTERFACE) GetProcAddress(module, "CreateSystemInterface");
    CRY_ASSERT_MESSAGE(createSystemInterface, "Unable to find CreateSystemInterface");

    g_system = createSystemInterface(initParams);
    CRY_ASSERT_MESSAGE(g_system, "Unable to create ISystem");
    ModuleInitISystem(g_system, "EditorSmokeTestFixture");
}

HMODULE EditorSmokeTestFixture::LoadSystemLibrary(const SSystemInitParams& systemInit)
{
    char binFullPath[256];
    strcpy_s(binFullPath, m_pathHelper.GetCurrentDir());
    strcat_s(binFullPath, systemInit.szBinariesDir);
    SetCurrentDirectory(binFullPath);
    return CryLoadLibrary("CrySystem.dll");
}

#else

void EditorSmokeTestFixture::CreateSystem(SSystemInitParams& initParams)
{

}

HMODULE EditorSmokeTestFixture::LoadSystemLibrary(const SSystemInitParams& systemInit)
{
    return NULL;
}

#endif

void EditorSmokeTestFixture::SetUp()
{
    m_pathHelper.CacheCurrDir();

    if (!g_system)
    {
        SSystemInitParams initParams;
        CreateSystem(initParams);

        g_editorGame = new CEditorGame(initParams.szBinariesDir);

        struct DummyGameToEditorInterface : public IGameToEditorInterface
        {
            virtual void SetUIEnums(const char *sEnumName, const char **sStringsArray, int nStringCount) {}
        };

        ASSERT_IS_TRUE(g_editorGame->Init(g_system, new DummyGameToEditorInterface()));
    }
}

void EditorSmokeTestFixture::TearDown()
{
    m_pathHelper.RestoreCachedCurrDir();
}

CRY_TEST_WITH_FIXTURE(LoadCXPLevelInEditorMode, EditorSmokeTestFixture)
{
    const char* level = "Game/Levels/Crysis2_CXP";

    g_editorGame->OnBeforeLevelLoad();
    ASSERT_IS_TRUE(gEnv->p3DEngine->InitLevelForEditor( level, "Mission0"));
    g_editorGame->OnAfterLevelLoad(level, level);

    g_editorGame->SetGameMode(true);

    SEntityEvent event;
    event.event = ENTITY_EVENT_RESET;
    event.nParam[0] = 1;
    gEnv->pEntitySystem->SendEventToAll( event );

    event.event = ENTITY_EVENT_LEVEL_LOADED;
    gEnv->pEntitySystem->SendEventToAll( event );

    event.event = ENTITY_EVENT_START_GAME;
    gEnv->pEntitySystem->SendEventToAll( event );
}


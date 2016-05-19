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

#include "StdAfx.h"
#include "GameRules.h"


using namespace GameTesting;

//--------------------------------------------------------------------------------
CRY_TEST_FIXTURE(GameRulesTestFixture, GameBaseTestFixture, GameTestSuite)
{
	CGameRules &GetGameRules() { return dummyGameRules; }

private:

	CGameRules dummyGameRules;
};

//--------------------------------------------------------------------------------
CRY_TEST_WITH_FIXTURE(TestGameRulesOnCollision, GameRulesTestFixture)
{
	IGameRules::SGameCollision dummyEvent;
	dummyEvent.pCollision = NULL;

	ASSERT_IS_TRUE(GetGameRules().OnCollision(dummyEvent));
}

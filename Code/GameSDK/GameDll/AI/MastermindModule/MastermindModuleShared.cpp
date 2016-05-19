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

// Description : Various definitions that are shared between the mastermind module and
//               depended systems.

#include "StdAfx.h"
#include "MastermindModule.h"


using namespace Mastermind;


// ============================================================================
// ============================================================================
// ============================================================================
//
// -- MastermindModuleInstanceConfig -- MastermindModuleInstanceConfig --
//
// ============================================================================
// ============================================================================
// ============================================================================


MastermindModuleInstanceConfig::MastermindModuleInstanceConfig() :
	m_SearchRadius(0.0f)
	, m_ResurrectionRadius(0.0f)
	, m_ResurrectablesAvailableSignal()
	, m_ResurrectablesUnavailableSignal()
	, m_ShieldForwardOffset(0.0f)
	, m_ShieldUpwardOffset(0.0f)
	, m_HusksSpawnedSignal()
	, m_HusksAllDestroyedSignal()
	, m_EnemySpottedByHuskNotifyDelay(0.0f)
{
}

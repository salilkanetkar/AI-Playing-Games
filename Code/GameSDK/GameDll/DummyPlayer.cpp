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

// Description : A dummy player used to simulate a client player for profiling purposes


#include "StdAfx.h"

#if (USE_DEDICATED_INPUT)

#include "DummyPlayer.h"
#include "NetPlayerInput.h"
#include "Weapon.h"
#include "GameCVars.h"
#include "GameRules.h"

DECLARE_DEFAULT_COMPONENT_FACTORY(CDummyPlayer, CDummyPlayer)

CDummyPlayer::CDummyPlayer()
{
	m_netPlayerProgression.SetRandomValues();
}

CDummyPlayer::~CDummyPlayer()
{
}

bool CDummyPlayer::Init( IGameObject * pGameObject )
{
	bool bResult = CPlayer::Init(pGameObject);
	m_isPlayer = true;
	return bResult;
}

void CDummyPlayer::Update(SEntityUpdateContext& ctx, int updateSlot)
{
	CPlayer::Update(ctx, updateSlot);

	if(!gEnv->bServer)
		return;

	if (!GetPlayerInput() || (GetPlayerInput()->GetType() != IPlayerInput::DEDICATED_INPUT))
	{
		CDedicatedInput* const pDedicatedInput = new CDedicatedInput(this);

		pDedicatedInput->GiveItems();
		
		m_pPlayerInput.reset(pDedicatedInput);
	}
}

EDefaultableBool CDummyPlayer::GetFire()
{
	CDedicatedInput* pPlayerInput = (CDedicatedInput*)GetPlayerInput();
	if (pPlayerInput)
	{
		return pPlayerInput->GetFire();
	}
	return eDB_Default;
}

void CDummyPlayer::SetFire(EDefaultableBool value)
{
	CDedicatedInput* pPlayerInput = (CDedicatedInput*)GetPlayerInput();
	if (pPlayerInput)
	{
		pPlayerInput->SetFire(value);
	}
}

EDefaultableBool CDummyPlayer::GetMove()
{
	CDedicatedInput* pPlayerInput = (CDedicatedInput*)GetPlayerInput();
	if (pPlayerInput)
	{
		return pPlayerInput->GetMove();
	}
	return eDB_Default;
}

void CDummyPlayer::SetMove(EDefaultableBool value)
{
	CDedicatedInput* pPlayerInput = (CDedicatedInput*)GetPlayerInput();
	if (pPlayerInput)
	{
		pPlayerInput->SetMove(value);
	}
}

void CDummyPlayer::OnChangeTeam()
{
	SetMultiplayerModelName();
	FullyUpdateActorModel();
}

#endif //USE_DEDICATED_INPUT

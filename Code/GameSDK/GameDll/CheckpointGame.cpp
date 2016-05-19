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

// Description : Checkpoint Save/Load system for Game04


#include "StdAfx.h"
#include "CheckpointGame.h"
#include "Game.h"
#include <ICheckPointSystem.h>

#include "GameActions.h"
#include "Player.h"

CCheckpointGame CCheckpointGame::m_Instance;

const static char* PLAYER_DATA_SECTION			= "PlayerData";
const static char* INVENTORY_SECTION			= "PlayerInventory";

//////////////////////////////////////////////////////////////////////////
CCheckpointGame::CCheckpointGame()
{

}

//////////////////////////////////////////////////////////////////////////
CCheckpointGame::~CCheckpointGame()
{

}

//////////////////////////////////////////////////////////////////////////
void CCheckpointGame::Init()
{
	g_pGame->GetIGameFramework()->GetICheckpointSystem()->SetGameHandler(this);
}

//////////////////////////////////////////////////////////////////////////
void CCheckpointGame::OnWriteData(XmlNodeRef parentNode)
{
	// Write out player data
	WritePlayerData(parentNode);
}

//////////////////////////////////////////////////////////////////////////
void CCheckpointGame::OnReadData(XmlNodeRef parentNode)
{
	// Read in player data
	ReadPlayerData(parentNode);
}

//////////////////////////////////////////////////////////////////////////
void CCheckpointGame::OnPreResetEngine()
{
	// Cleanup game systems

}

//////////////////////////////////////////////////////////////////////////
void CCheckpointGame::OnPostResetEngine()
{
	//send "game start" event
	SEntityEvent event;
	event.event = ENTITY_EVENT_START_GAME;
	event.nParam[0] = 0;
	gEnv->pEntitySystem->SendEventToAll( event );

}

//////////////////////////////////////////////////////////////////////////
void CCheckpointGame::OnRestartGameplay()
{

}

//////////////////////////////////////////////////////////////////////////
void CCheckpointGame::WritePlayerData(XmlNodeRef parentNode)
{
	ICheckpointSystem *pSystem = g_pGame->GetIGameFramework()->GetICheckpointSystem();
	CRY_ASSERT(pSystem);

	XmlNodeRef node = GetISystem()->CreateXmlNode(PLAYER_DATA_SECTION);

	CPlayer *pPlayer = static_cast<CPlayer *>(g_pGame->GetIGameFramework()->GetClientActor());

	CRY_ASSERT(pPlayer);

	//write player pos
	//node->setAttr("PlayerPos", pHero->GetEntity()->GetWorldPos());
	XmlNodeRef playerTM = GetISystem()->CreateXmlNode("PlayerTM");
	node->addChild(playerTM);
	pSystem->SerializeWorldTM(pPlayer->GetEntity(), playerTM, true);

	//serialize player inventory
	WritePlayerInventory(node);

	parentNode->addChild(node);
}

//////////////////////////////////////////////////////////////////////////
void CCheckpointGame::WritePlayerInventory(XmlNodeRef parentNode)
{
	//create serialization writer
	XmlNodeRef node = GetISystem()->CreateXmlNode(INVENTORY_SECTION);
	IXmlSerializer *pSerializer = GetISystem()->GetXmlUtils()->CreateXmlSerializer();
	ISerialize *pWriter = pSerializer->GetWriter(node);

	//get serialization data
	TSerialize ser = TSerialize(pWriter);
	CPlayer *pPlayer = static_cast<CPlayer *>(g_pGame->GetIGameFramework()->GetClientActor());
	CRY_ASSERT(pPlayer);
	pPlayer->GetInventory()->FullSerialize(ser);

	//add to parent node
	parentNode->addChild(node);

	pSerializer->Release();
}

//////////////////////////////////////////////////////////////////////////
void CCheckpointGame::ReadPlayerData(XmlNodeRef data)
{
	ICheckpointSystem *pSystem = g_pGame->GetIGameFramework()->GetICheckpointSystem();
	CRY_ASSERT(pSystem);

	XmlNodeRef playerData = data->findChild(PLAYER_DATA_SECTION);
	if(!playerData)
	{
		CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "Failed reading player data from checkpoint, player position won't be set.");
		return;
	}

	CPlayer *pPlayer = static_cast<CPlayer *>(g_pGame->GetIGameFramework()->GetClientActor());
	CRY_ASSERT(pPlayer);

	pPlayer->Revive(CActor::kRFR_Spawn);
	pPlayer->Physicalize(STANCE_STAND);

	//this will set the player to the required location
	XmlNodeRef playerTM = playerData->findChild("PlayerTM");
	if(playerTM)
		pSystem->SerializeWorldTM(pPlayer->GetEntity(), playerTM, false);

	//read player inventory from stream
	ReadPlayerInventory(playerData);
}

//////////////////////////////////////////////////////////////////////////
void CCheckpointGame::ReadPlayerInventory(XmlNodeRef parentNode)
{
	//get source node
	XmlNodeRef node = parentNode->findChild(INVENTORY_SECTION);
	if(!node)
	{
		CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "Couldn't find Player Inventory section while reading checkpoint.");
		return;
	}

	//create serialization reader
	IXmlSerializer *pSerializer = GetISystem()->GetXmlUtils()->CreateXmlSerializer();
	ISerialize *pReader = pSerializer->GetReader(node);

	//read serialization data
	TSerialize ser = TSerialize(pReader);
	CPlayer *pPlayer = static_cast<CPlayer *>(g_pGame->GetIGameFramework()->GetClientActor());
	CRY_ASSERT(pPlayer);
	pPlayer->GetInventory()->FullSerialize(ser);

	// Make sure all the inventory data changes are applied
	gEnv->pGame->GetIGameFramework()->GetIItemSystem()->SetActorItem(pPlayer, pPlayer->GetCurrentItemId(), false);

	pSerializer->Release();
}

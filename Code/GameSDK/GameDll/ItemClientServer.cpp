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
#include "Item.h"
#include "ItemSharedParams.h"
#include "Actor.h"


//------------------------------------------------------------------------
EntityId CItem::NetGetOwnerId() const
{
	return m_owner.GetId();
}

//------------------------------------------------------------------------
void CItem::NetSetOwnerId(EntityId id)
{
	if (id==m_owner.GetId())
		return;

	CryLogAlways("%s::NetSetOwnerId(%s)", GetEntity()->GetName(), GetActor(id)?GetActor(id)->GetEntity()->GetName():"null");

	if (id)
		PickUp(id, true);
	else
	{
		Drop();

		CActor *pActor=GetOwnerActor();
		if (pActor)
			pActor->GetInventory()->SetCurrentItem(0);
	}
}

//------------------------------------------------------------------------
void CItem::InitClient (ChannelId channelId)
{
	const int numAccessories = m_accessories.size();
	
	// send the differences between the current, and the initial setup
	for (int i = 0; i < numAccessories; i++)
	{
		uint16 classId = 0;
		bool result = g_pGame->GetIGameFramework()->GetNetworkSafeClassId(classId, m_accessories[i].pClass->GetName());

#if !defined(_RELEASE)
		if(!result)
		{
			char errorMsg[256];
			sprintf(errorMsg, "CItem::InitClient failed to find network safe class id for %s", m_accessories[i].pClass->GetName());
			CRY_ASSERT_MESSAGE(result, errorMsg);
		}
#endif
		if(result)
			GetGameObject()->InvokeRMI(ClAttachInitialAccessory(), AccessoryParams(classId), eRMI_ToClientChannel, channelId);
	}

	IActor *pOwner=GetOwnerActor();
	if (!pOwner)
		return;

	// only send the pickup message if the player is connecting
	// for items spawned during gameplay, CItem::PickUp is already sending the pickup message
//	INetChannel *pNetChannel = m_pGameFramework->GetNetChannel(channelId);
	INetwork *pNetwork = gEnv->pSystem->GetINetwork();

#if HACK_NET_STARTUP_SEQUENCE
	// TODO : figure out if this is needed with Gridmate
	if (pNetChannel && pNetChannel->GetContextViewState()<eCVS_InGame)
	{
		if (!m_stats.mounted && !m_stats.used)
		{
			pOwner->GetGameObject()->InvokeRMIWithDependentObject(CActor::ClPickUp(), 
				CActor::PickItemParams(GetEntityId(), m_stats.selected, false), eRMI_ToClientChannel, GetEntityId(), channelId);
			GetOwnerActor()->GetGameObject()->InvokeRMI(CActor::ClPickUp(), 
			CActor::PickItemParams(GetEntityId(), m_stats.selected, false), eRMI_ToClientChannel, channelId);
		}
	}
#endif

	if (m_stats.mounted && m_stats.used)
	{
		pOwner->GetGameObject()->InvokeRMIWithDependentObject(CActor::ClStartUse(), 
			CActor::ItemIdParam(GetEntityId()), eRMI_ToClientChannel, GetEntityId(), channelId);
	}
}

//------------------------------------------------------------------------
void CItem::PostInitClient (ChannelId channelId)
{
}

//------------------------------------------------------------------------
IMPLEMENT_RMI(CItem, SvRequestAttachAccessory)
{
	if (IInventory *pInventory=GetActorInventory(GetOwnerActor()))
	{
		char accessoryName[128];
		bool result = g_pGame->GetIGameFramework()->GetNetworkSafeClassName(accessoryName, sizeof(accessoryName), params.accessoryClassId);

#if !defined(_RELEASE)
	if(!result)
	{
		char errorMsg[256];
		sprintf(errorMsg, "CItem::SvRequestAttachAccessory failed to find network safe class name for id %d", params.accessoryClassId);
		CRY_ASSERT_MESSAGE(result, errorMsg);
	}
#endif

		if (accessoryName[0] != '\0' && pInventory->GetCountOfClass(accessoryName)>0)
		{
			DoSwitchAccessory(accessoryName);
			GetGameObject()->InvokeRMI(ClAttachAccessory(), params, eRMI_ToAllClients|eRMI_NoLocalCalls);

			return true;
		}
	}
	
	return true; // set this to false later
}

//------------------------------------------------------------------------
IMPLEMENT_RMI(CItem, ClAttachAccessory)
{
	char accessoryName[128];
	bool result = g_pGame->GetIGameFramework()->GetNetworkSafeClassName(accessoryName, sizeof(accessoryName), params.accessoryClassId);

#if !defined(_RELEASE)
	if(!result)
	{
		char errorMsg[256];
		sprintf(errorMsg, "CItem::ClAttachAccessory failed to find network safe class name for id %d", params.accessoryClassId);
		CRY_ASSERT_MESSAGE(result, errorMsg);
	}
#endif

	DoSwitchAccessory(accessoryName, false);

	return true;
}

//------------------------------------------------------------------------
IMPLEMENT_RMI(CItem, ClAttachInitialAccessory)
{
	char accessoryName[128];
	bool result = g_pGame->GetIGameFramework()->GetNetworkSafeClassName(accessoryName, sizeof(accessoryName), params.accessoryClassId);

#if !defined(_RELEASE)
	if(!result)
	{
		char errorMsg[256];
		sprintf(errorMsg, "CItem::ClAttachAccessory failed to find network safe class name for id %d", params.accessoryClassId);
		CRY_ASSERT_MESSAGE(result, errorMsg);
	}
#endif

	DoSwitchAccessory(accessoryName, true);

	return true;
}


//------------------------------------------------------------------------
IMPLEMENT_RMI(CItem, SvRequestDetachAccessory)
{
	if (IInventory *pInventory=GetActorInventory(GetOwnerActor()))
	{
		char accessoryName[128];
		bool result = g_pGame->GetIGameFramework()->GetNetworkSafeClassName(accessoryName, sizeof(accessoryName), params.accessoryClassId);

#if !defined(_RELEASE)
		if(!result)
		{
			char errorMsg[256];
			sprintf(errorMsg, "CItem::SvRequestDetachAccessory failed to find network safe class name for id %d", params.accessoryClassId);
			CRY_ASSERT_MESSAGE(result, errorMsg);
		}
#endif

		if (accessoryName[0] != '\0')
		{
			AttachAccessory(accessoryName, false, true, true);
			GetGameObject()->InvokeRMI(ClDetachAccessory(), params, eRMI_ToRemoteClients);

			return true;
		}
	}
	return true; 
}

//------------------------------------------------------------------------
IMPLEMENT_RMI(CItem, ClDetachAccessory)
{
	char accessoryName[128];
	bool result = g_pGame->GetIGameFramework()->GetNetworkSafeClassName(accessoryName, sizeof(accessoryName), params.accessoryClassId);

#if !defined(_RELEASE)
	if(!result)
	{
		char errorMsg[256];
		sprintf(errorMsg, "CItem::ClDetachAccessory failed to find network safe class name for id %d", params.accessoryClassId);
		CRY_ASSERT_MESSAGE(result, errorMsg);
	}
#endif

	AttachAccessory(accessoryName, false, true, true);
	return true;
}

//------------------------------------------------------------------------
IMPLEMENT_RMI(CItem, SvRequestEnterModify)
{
	// TODO: Unclear, should this in fact be GetLocalChannelID Instead?
	GetGameObject()->InvokeRMI(ClEnterModify(), params, eRMI_ToOtherClients, gEnv->pNetwork->GetServerChannelId());

	return true;
}

//------------------------------------------------------------------------
IMPLEMENT_RMI(CItem, SvRequestLeaveModify)
{
	// TODO: Unclear, should this in fact be GetLocalChannelID Instead?
	GetGameObject()->InvokeRMI(ClLeaveModify(), params, eRMI_ToOtherClients, gEnv->pNetwork->GetServerChannelId());

	return true;
}

//------------------------------------------------------------------------
IMPLEMENT_RMI(CItem, ClEnterModify)
{
	PlayAction(GetFragmentIds().enter_modify, 0, false, eIPAF_Default );

	return true;
}

//------------------------------------------------------------------------
IMPLEMENT_RMI(CItem, ClLeaveModify)
{
	PlayAction(GetFragmentIds().leave_modify, 0);

	return true;
}

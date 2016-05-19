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

// Description : A replay entity spawned during KillCam replay


#include "StdAfx.h"
#include "ReplayObject.h"
#include "IItemSystem.h"

DECLARE_DEFAULT_COMPONENT_FACTORY(CReplayObject, CReplayObject)

CReplayObject::CReplayObject()
: m_timeSinceSpawn(0)
{
}

CReplayObject::~CReplayObject()
{
}

//------------------------------------------------------------------------
bool CReplayObject::Init(IGameObject *pGameObject)
{
	SetGameObject(pGameObject);

	return true;
}

//------------------------------------------------------------------------
bool CReplayObject::ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params )
{
	ResetGameObject();

	CRY_ASSERT_MESSAGE(false, "CReplayObject::ReloadExtension not implemented");
	
	return false;
}

//------------------------------------------------------------------------
bool CReplayObject::GetEntityPoolSignature( TSerialize signature )
{
	CRY_ASSERT_MESSAGE(false, "CReplayObject::GetEntityPoolSignature not implemented");
	
	return true;
}

//------------------------------------------------------------------------
//- REPLAY ACTION
//------------------------------------------------------------------------

CReplayObjectAction::CReplayObjectAction( FragmentID fragID, const TagState &fragTags, uint32 optionIdx, bool trumpsPrevious, const int priority )
	: BaseClass(priority, fragID)
	, m_trumpsPrevious(trumpsPrevious)
{
	m_fragTags = fragTags;
	m_optionIdx = optionIdx;
}

EPriorityComparison CReplayObjectAction::ComparePriority( const IAction &actionCurrent ) const
{
	if (m_trumpsPrevious)
	{
		return ((IAction::Installed == actionCurrent.GetStatus() && IAction::Installing & ~actionCurrent.GetFlags()) ? Higher : BaseClass::ComparePriority(actionCurrent));
	}
	else
	{
		return Equal;
	}
}

//////////////////////////////////////////////////////////////////////////

void CReplayItemList::AddItem( const EntityId itemId )
{
	m_items.push_back(itemId);
}

void CReplayItemList::OnActionControllerDeleted()
{
	IItemSystem* pItemSys = g_pGame->GetIGameFramework()->GetIItemSystem();
	TItemVec::const_iterator end = m_items.end();
	for(TItemVec::const_iterator it = m_items.begin(); it!=end; ++it)
	{
		if(IItem* pItem = pItemSys->GetItem(*it))
		{
			pItem->UpdateCurrentActionController();
		}
	}

	m_items.clear();

}

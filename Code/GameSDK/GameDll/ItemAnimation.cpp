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

// Description : Helper functionality for item animation control


#include "StdAfx.h"

#include "ItemAnimation.h"
#include "Player.h"
#include "Weapon.h"

CActionItemIdle::CActionItemIdle(int priority, FragmentID fragmentID, FragmentID idleBreakFragmentID, const TagState fragTags, CPlayer& playerRef)
	:	BaseClass(priority, fragmentID, fragTags, IAction::Interruptable|IAction::NoAutoBlendOut)
	, m_ownerPlayer(playerRef)
	, m_fragmentIdle(fragmentID)
	, m_fragmentIdleBreak(idleBreakFragmentID)
	, m_lastIdleBreakTime(0.0f)
	, m_playingIdleBreak(false)
{
}


IAction::EStatus CActionItemIdle::Update(float timePassed)
{
	UpdateFragmentTags();

	CWeapon *weapon = m_ownerPlayer.GetWeapon(m_ownerPlayer.GetCurrentItemId());
	bool canPlayIdleBreak = !weapon || !(weapon->IsZoomed() || weapon->IsZoomingInOrOut());
	if (m_playingIdleBreak)
	{
		if (!canPlayIdleBreak)
		{
			m_playingIdleBreak = false;
		}
	}
	else if (canPlayIdleBreak)
	{
		const float currentTime = gEnv->pTimer->GetAsyncCurTime();
		IPlayerInput* pClientInput = m_ownerPlayer.GetPlayerInput();
		if (pClientInput)
		{
			const float idleBreakDelay = g_pGameCVars->cl_idleBreaksDelayTime;
			const float lastInputTime = pClientInput->GetLastRegisteredInputTime();
			const float referenceTime = (float)fsel((lastInputTime - m_lastIdleBreakTime), lastInputTime, m_lastIdleBreakTime);

			if ((currentTime - referenceTime) > idleBreakDelay)
			{
				m_playingIdleBreak = true;
				SetFragment(m_fragmentIdleBreak, m_fragTags);
				m_lastIdleBreakTime = currentTime;
			}
		}
	}

	if (!m_playingIdleBreak)
	{
		if (GetRootScope().IsDifferent(m_fragmentIdle, m_fragTags))
		{
			SetFragment(m_fragmentIdle, m_fragTags);
		}
	}

	return BaseClass::Update(timePassed);
}

void CActionItemIdle::OnInitialise()
{

	UpdateFragmentTags();
}

void CActionItemIdle::OnSequenceFinished(int layer, uint32 scopeID)
{
	if (GetRootScope().GetID() == scopeID && m_playingIdleBreak && (layer == 0))
	{
		m_playingIdleBreak = false;
		m_lastIdleBreakTime = gEnv->pTimer->GetAsyncCurTime();
	}
}


void CActionItemIdle::UpdateFragmentTags()
{
	CItem* pItem = static_cast<CItem*>(m_ownerPlayer.GetCurrentItem());
	CWeapon* pWeapon = pItem ? static_cast<CWeapon*>(pItem->GetIWeapon()) : 0;
	const CTagDefinition* pTagDefinition = m_context->controllerDef.GetFragmentTagDef(m_fragmentID);

	if(pItem && pTagDefinition)
	{
		CTagState fragTags(*pTagDefinition);
		fragTags = m_fragTags;
		pItem->SetFragmentTags(fragTags);
		m_fragTags = fragTags.GetMask();
	}
	if (pWeapon)
	{
		SetParam(CItem::sActionParamCRCs.zoomTransition, pWeapon->GetZoomTransition());
	}
}



//-------------------------------------------------------------------------------------

CItemSelectAction::CItemSelectAction(int priority, FragmentID fragmentID, const TagState &fragTags, CItem& _item)
	:	BaseClass(priority, fragmentID, fragTags)
	, m_ItemID(_item.GetEntityId())
	, m_bSelected(false)
{}

void CItemSelectAction::OnAnimationEvent(ICharacterInstance *pCharacter, const AnimEventInstance &event)
{
	const SActorAnimationEvents& animEventsTable = CActor::GetAnimationEventsTable();
	if (animEventsTable.m_stowId == event.m_EventNameLowercaseCRC32)
	{
		SelectWeapon();
	}
}

void CItemSelectAction::Enter()
{
	BaseClass::Enter();
	if( m_ItemID )
	{
		CItem* pItem = (CItem*)g_pGame->GetIGameFramework()->GetIItemSystem()->GetItem( m_ItemID );

		UnhideWeapon(pItem);
	}
}

void CItemSelectAction::Exit()
{
	SelectWeapon();

	BaseClass::Exit();
}

void CItemSelectAction::SelectWeapon()
{	
	if(m_bSelected)
		return;

	if( m_ItemID )
	{
		CItem* pItem = (CItem*)g_pGame->GetIGameFramework()->GetIItemSystem()->GetItem( m_ItemID );
		
		if( pItem )
		{
			if (pItem->IsSelectGrabbingWeapon())
			{
				pItem->DoSelectWeaponGrab();
				m_bSelected = true;
			}

			UnhideWeapon(pItem);

			pItem->OnItemSelectActionComplete();
		}
		else
		{
			ForceFinish();
		}
	}
}

void CItemSelectAction::ItemSelectCancelled()
{
    ForceFinish();
	SelectWeapon();
}

void CItemSelectAction::UnhideWeapon(CItem* pItem)
{
	if( pItem && pItem->AreAnyItemFlagsSet( CItem::eIF_UseAnimActionUnhide ) )
	{
		pItem->Hide(false);
		pItem->AttachToBack(false);
		if (pItem->ShouldAttachWhenSelected())
		{
			pItem->AttachToHand(true);
		}
		pItem->ClearItemFlags(CItem::eIF_UseAnimActionUnhide);
	}
}

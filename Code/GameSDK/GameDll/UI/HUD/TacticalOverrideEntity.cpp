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

// Description : HUD Tactical override entity


#include "StdAfx.h"
#include "TacticalOverrideEntity.h"

#include "TacticalManager.h"

//------------------------------------------------------------------------
DECLARE_DEFAULT_COMPONENT_FACTORY(CTacticalOverrideEntity, CTacticalOverrideEntity)

CTacticalOverrideEntity::CTacticalOverrideEntity()
: m_bMappedToParent(false)
{
}

//------------------------------------------------------------------------

CTacticalOverrideEntity::~CTacticalOverrideEntity()
{
}

//------------------------------------------------------------------------
bool CTacticalOverrideEntity::Init(IGameObject *pGameObject)
{
	SetGameObject(pGameObject);
	
	return true;
}

//------------------------------------------------------------------------
void CTacticalOverrideEntity::PostInit(IGameObject *pGameObject)
{
}

//------------------------------------------------------------------------
void CTacticalOverrideEntity::InitClient (ChannelId channelId)
{
}

//------------------------------------------------------------------------
//void CTacticalOverrideEntity::Release()
//{
//	CRY_ASSERT(m_bMappedToParent == false); // Done from Detach event / from reset
//
//	delete this;
//}

//------------------------------------------------------------------------
void CTacticalOverrideEntity::GetMemoryUsage(ICrySizer *pSizer) const
{
	pSizer->Add(*this);
}

//------------------------------------------------------------------------
bool CTacticalOverrideEntity::ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params )
{
	ResetGameObject();
	CRY_ASSERT(!"CTacticalOverrideEntity::ReloadExtension not implemented");
	return false;
}

//------------------------------------------------------------------------
bool CTacticalOverrideEntity::GetEntityPoolSignature( TSerialize signature )
{
	CRY_ASSERT(!"CTacticalOverrideEntity::GetEntityPoolSignature not implemented");
	return true;
}

//------------------------------------------------------------------------
void CTacticalOverrideEntity::ProcessEvent(SEntityEvent &event)
{
	switch (event.event)
	{
	case ENTITY_EVENT_ATTACH_THIS:
		{
			const EntityId parentId = (EntityId) event.nParam[0];
			g_pGame->GetTacticalManager()->AddOverrideEntity(parentId, GetEntityId());
			m_bMappedToParent = true;
		}
		break;
	case ENTITY_EVENT_DETACH_THIS:
		{
			if (m_bMappedToParent)
			{
				g_pGame->GetTacticalManager()->RemoveOverrideEntity(GetEntityId());
				m_bMappedToParent = false;
			}
		}
		break;
	case ENTITY_EVENT_RESET:
		{
			if(gEnv->IsEditor())
			{
				if (event.nParam[0]) // Entering game mode
				{
					if (!m_bMappedToParent) // Could already be added if just linked the entity, won't be if loaded the level with linked entity
					{
						IEntity* pEntity = GetEntity();
						if (pEntity)
						{
							IEntity* pParent = pEntity->GetParent();
							if (pParent)
							{
								g_pGame->GetTacticalManager()->AddOverrideEntity(pParent->GetId(), GetEntityId());
								m_bMappedToParent = true;
							}
							else
							{
								GameWarning("CTacticalOverrideEntity::ProcessEvent: EntityId: %u, doesn't have an attached parent, this entity is a waste", GetEntityId());
							}
						}
					}
				}
				else // Exiting game mode
				{
					if (m_bMappedToParent)
					{
						g_pGame->GetTacticalManager()->RemoveOverrideEntity(GetEntityId());
						m_bMappedToParent = false;
					}
				}
			}
		}
		break;
	}
}

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

// Description : Holds a CMovementTransitions object for each entity class


#include "StdAfx.h"
#include "Player.h"
#include "MovementTransitions.h"
#include "MovementTransitionsSystem.h"

///////////////////////////////////////////////////////////////////////////////
CMovementTransitionsSystem::CMovementTransitionsSystem()
{
}


///////////////////////////////////////////////////////////////////////////////
CMovementTransitionsSystem::~CMovementTransitionsSystem()
{
	MovementTransitionsVector::iterator iEnd = m_entityTransitions.end();
	for(MovementTransitionsVector::iterator i = m_entityTransitions.begin(); i != iEnd; ++i)
	{
		delete (*i);
	}
}

///////////////////////////////////////////////////////////////////////////////
void CMovementTransitionsSystem::Flush()
{
	MovementTransitionsVector::iterator iEnd = m_entityTransitions.end();
	for(MovementTransitionsVector::iterator i = m_entityTransitions.begin(); i != iEnd; ++i)
	{
		delete (*i);
	}
	stl::free_container(m_entityTransitions);
}

///////////////////////////////////////////////////////////////////////////////
void CMovementTransitionsSystem::GetMemoryUsage(ICrySizer* s) const
{
	s->AddObject(this, sizeof(*this));

	MovementTransitionsVector::const_iterator iEnd = m_entityTransitions.end();
	for(MovementTransitionsVector::const_iterator i = m_entityTransitions.begin(); i != iEnd; ++i)
	{
		(*i)->GetMemoryUsage(s);
	}
}


///////////////////////////////////////////////////////////////////////////////
void CMovementTransitionsSystem::Reload() const
{
	MovementTransitionsVector::const_iterator iEnd = m_entityTransitions.end();
	for(MovementTransitionsVector::const_iterator i = m_entityTransitions.begin(); i != iEnd; ++i)
	{
		(*i)->Load();
	}
}


///////////////////////////////////////////////////////////////////////////////
CMovementTransitions*const CMovementTransitionsSystem::GetMovementTransitions(IEntity* pEntity)
{
	return GetMovementTransitions(pEntity->GetClass(), pEntity->GetScriptTable());
}


///////////////////////////////////////////////////////////////////////////////
CMovementTransitions*const CMovementTransitionsSystem::GetMovementTransitions(IEntityClass* pEntityClass, SmartScriptTable pEntityScript)
{
	// Check for useSpecialMovementTransitions property in LUA
	if(!pEntityScript)
		return NULL;

	SmartScriptTable pPropertiesTable;
	pEntityScript->GetValue("Properties", pPropertiesTable);
	if (!pPropertiesTable)
		return NULL;

	int useMovementTransitions = 0;
	if(!pPropertiesTable->GetValue("useSpecialMovementTransitions", useMovementTransitions) || !useMovementTransitions)
		return NULL;

	// Look for cached movement transitions
	MovementTransitionsVector::iterator iEnd = m_entityTransitions.end();
	for(MovementTransitionsVector::iterator i = m_entityTransitions.begin(); i != iEnd; ++i)
	{
		if ((*i)->GetEntityClass() == pEntityClass)
		{
			return (*i);
		}
	}

	// Create new movement transition
	CMovementTransitions* pTransitions = new CMovementTransitions(pEntityClass);
	CRY_ASSERT(pTransitions);
	if (pTransitions)
		m_entityTransitions.push_back(pTransitions);
	return pTransitions;
}


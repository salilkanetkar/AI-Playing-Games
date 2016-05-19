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
#include "MockEntitySystem.h"

using namespace EngineFacade;



CMockEngineEntity::CMockEngineEntity() : 
	CNullEngineEntity(0x7777),
	m_worldPos(ZERO),
	m_worldRotation(ZERO),
	m_worldAngles(ZERO)
{
}

// ---------------------------------------------------

IEnginePhysicalEntity& CMockEngineEntity::GetPhysicalEntity()
{
	return m_mockedPhysicalEntity;
}

// ---------------------------------------------------

Vec3 CMockEngineEntity::GetWorldPos() const
{
	return m_worldPos;
}

// ---------------------------------------------------

void CMockEngineEntity::SetWorldPos( Vec3 worldPos )
{
	m_worldPos = worldPos;
}

// ---------------------------------------------------

Quat CMockEngineEntity::GetWorldRotation() const
{
	return m_worldRotation;
}

// ---------------------------------------------------

const Matrix34& CMockEngineEntity::GetSlotWorldTM( int nSlot ) const
{
	return m_WorldMatrix;
}

// ---------------------------------------------------

const Matrix34& CMockEngineEntity::GetWorldTM() const
{
	return m_WorldMatrix;
}

// ---------------------------------------------------

Ang3 CMockEngineEntity::GetWorldAngles() const
{
	return m_worldAngles;
}


// ---------------------------------------------------

void CMockEngineEntity::SetWorldRotation( Quat rotation )
{
	m_worldRotation = rotation;
}

// ---------------------------------------------------
// ---------------------------------------------------
// ---------------------------------------------------

CMockEntitySystem::CMockEntitySystem() 
:	mockedEntity( new CMockEngineEntity())
{
}

// ---------------------------------------------------

IEngineEntity::Ptr CMockEntitySystem::GetEntityByID( EntityId id )
{
	return mockedEntity;
}

// ---------------------------------------------------

void CMockEntitySystem::Use(EngineFacade::IEngineEntity::Ptr entity)
{
    mockedEntity = entity;
}

// ---------------------------------------------------

CMockEnginePhysicalEntity::CMockEnginePhysicalEntity() : 
	setParamsResult(0),
	m_actionCounter(0)
{
}

// ---------------------------------------------------

void CMockEnginePhysicalEntity::SetParamsResult( int result )
{
	setParamsResult = result;
}

// ---------------------------------------------------

int CMockEnginePhysicalEntity::SetParams( pe_params* params )
{
	return setParamsResult;
}

// ---------------------------------------------------

void CMockEnginePhysicalEntity::SetReturnParams( pe_player_dynamics params )
{
	setReturnParams = params;
}

// ---------------------------------------------------

int CMockEnginePhysicalEntity::GetParams( pe_params* params )
{
	*params = setReturnParams;
	return 1;
}

// ---------------------------------------------------

void CMockEnginePhysicalEntity::Action( pe_action* action )
{
	++m_actionCounter;
}

// ---------------------------------------------------

int CMockEnginePhysicalEntity::GetActionCount()
{
	return m_actionCounter;
}


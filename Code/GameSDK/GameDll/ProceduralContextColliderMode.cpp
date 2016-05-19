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
#include "ProceduralContextColliderMode.h"


CRYREGISTER_CLASS( CProceduralContextColliderMode );


//////////////////////////////////////////////////////////////////////////
CProceduralContextColliderMode::CProceduralContextColliderMode()
{
}


//////////////////////////////////////////////////////////////////////////
CProceduralContextColliderMode::~CProceduralContextColliderMode()
{
}


//////////////////////////////////////////////////////////////////////////
void CProceduralContextColliderMode::Update( float timePassedSeconds )
{
	IAnimatedCharacter* pAnimatedCharacter = GetAnimatedCharacter();
	IF_UNLIKELY ( pAnimatedCharacter == NULL )
	{
		return;
	}

	EColliderMode mode = eColliderMode_Undefined;

	const size_t requestCount = m_requestList.GetCount();
	for ( size_t i = 0; i < requestCount; ++i )
	{
		const SColliderModeRequest& request = m_requestList.GetRequest( i );
		mode = ( request.mode != eColliderMode_Undefined ) ? request.mode : mode;
	}

	pAnimatedCharacter->RequestPhysicalColliderMode( mode, eColliderModeLayer_Animation, "ProcContextUpdate" );
}


//////////////////////////////////////////////////////////////////////////
uint32 CProceduralContextColliderMode::RequestColliderMode( const EColliderMode colliderMode )
{
	SColliderModeRequest request;
	request.mode = colliderMode;

	return m_requestList.AddRequest( request );
}


//////////////////////////////////////////////////////////////////////////
void CProceduralContextColliderMode::CancelRequest( const uint32 cancelRequestId )
{
	m_requestList.RemoveRequest( cancelRequestId );
}


//////////////////////////////////////////////////////////////////////////
IAnimatedCharacter* CProceduralContextColliderMode::GetAnimatedCharacter() const
{
	const EntityId entityId = m_entity->GetId();
	IActor* pActor = g_pGame->GetIGameFramework()->GetIActorSystem()->GetActor( entityId );
	IAnimatedCharacter* pAnimatedCharacter = ( pActor != NULL ) ? pActor->GetAnimatedCharacter() : NULL;
	return pAnimatedCharacter;
}
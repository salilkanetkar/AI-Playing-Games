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
#include "ProceduralContextMovementControlMethod.h"


CRYREGISTER_CLASS( CProceduralContextMovementControlMethod );


//////////////////////////////////////////////////////////////////////////
CProceduralContextMovementControlMethod::CProceduralContextMovementControlMethod()
{
}


//////////////////////////////////////////////////////////////////////////
CProceduralContextMovementControlMethod::~CProceduralContextMovementControlMethod()
{
}


//////////////////////////////////////////////////////////////////////////
void CProceduralContextMovementControlMethod::Update( float timePassedSeconds )
{
	IAnimatedCharacter* pAnimatedCharacter = GetAnimatedCharacter();
	IF_UNLIKELY ( pAnimatedCharacter == NULL )
	{
		return;
	}

	EMovementControlMethod horizontal = eMCM_Undefined;
	EMovementControlMethod vertical = eMCM_Undefined;

	const size_t requestCount = m_requestList.GetCount();
	for ( size_t i = 0; i < requestCount; ++i )
	{
		const SMCMRequest& request = m_requestList.GetRequest( i );
		horizontal = ( request.horizontal != eMCM_Undefined ) ? request.horizontal : horizontal;
		vertical = ( request.vertical != eMCM_Undefined ) ? request.vertical : vertical;
	}

	pAnimatedCharacter->SetMovementControlMethods( eMCMSlot_Animation, horizontal, vertical, "ProcContextUpdate" );
}


//////////////////////////////////////////////////////////////////////////
uint32 CProceduralContextMovementControlMethod::RequestMovementControlMethod( const EMovementControlMethod horizontal, const EMovementControlMethod vertical )
{
	SMCMRequest request;
	request.horizontal = horizontal;
	request.vertical = vertical;

	return m_requestList.AddRequest( request );
}


//////////////////////////////////////////////////////////////////////////
void CProceduralContextMovementControlMethod::CancelRequest( const uint32 cancelRequestId )
{
	m_requestList.RemoveRequest( cancelRequestId );
}


//////////////////////////////////////////////////////////////////////////
IAnimatedCharacter* CProceduralContextMovementControlMethod::GetAnimatedCharacter() const
{
	const EntityId entityId = m_entity->GetId();
	IActor* pActor = g_pGame->GetIGameFramework()->GetIActorSystem()->GetActor( entityId );
	IAnimatedCharacter* pAnimatedCharacter = ( pActor != NULL ) ? pActor->GetAnimatedCharacter() : NULL;
	return pAnimatedCharacter;
}
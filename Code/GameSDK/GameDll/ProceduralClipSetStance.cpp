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
#include "ICryMannequin.h"
#include <CryExtension/Impl/ClassWeaver.h>
#include <Mannequin/Serialization.h>
#include <IAgent.h>
#include "Player.h"

struct SSetStanceParams : public IProceduralParams
{
	virtual void Serialize(Serialization::IArchive& ar)
	{
		ar(stance, "Stance", "Stance");
	}

	TProcClipString stance;
};

class CProceduralClipSetStance : public TProceduralClip<SSetStanceParams>
{
protected:
	virtual void OnEnter( float blendTime, float duration, const SSetStanceParams& params )
	{
		const EntityId entityId = m_scope->GetEntityId();
		IEntity* entity = gEnv->pEntitySystem->GetEntity( entityId );
		IF_UNLIKELY( !entity )
			return;

		IAIObject* aiObject = entity->GetAI();
		IF_UNLIKELY( !aiObject )
			return;

		CPlayer* player = static_cast<CPlayer*>( g_pGame->GetIGameFramework()->GetIActorSystem()->GetActor( entityId ) );
		IF_UNLIKELY( !player )
			return;

		CAIAnimationComponent* aiAnimationComponent = player->GetAIAnimationComponent();
		IF_UNLIKELY( !aiAnimationComponent )
			return;

		const char *stanceName = params.stance.c_str();
		IF_UNLIKELY( !stanceName )
			return;

		int stance = STANCE_NULL;
		for(; stance < STANCE_LAST; ++stance)
		{
			if ( strcmpi( stanceName, GetStanceName( (EStance)stance) ) == 0 )
				break;
		}

		IF_UNLIKELY( (EStance)stance == STANCE_LAST )
			return;

		aiAnimationComponent->ForceStanceTo( *player, (EStance)stance );
		aiAnimationComponent->ForceStanceInAIActorTo( *player, (EStance)stance );
	}

	virtual void Update( float timePassed )
	{
	}

	virtual void OnExit( float blendTime )
	{
	}
};

REGISTER_PROCEDURAL_CLIP(CProceduralClipSetStance, "SetStance");

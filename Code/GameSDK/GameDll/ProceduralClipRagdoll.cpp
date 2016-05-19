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

// Description : ProceduralClip for Ragdolling from CryMannequin


#include "StdAfx.h"

#include "ICryMannequin.h"
#include <CryExtension/Impl/ClassWeaver.h>

#include "Player.h"

#include "ProceduralContextRagdoll.h"
#include "Serialization/IArchive.h"

struct SRagdollParams : public IProceduralParams
{
	SRagdollParams()
		: sleep(0.0f)
		, stiffness(500.0f)
	{
	}

	virtual void Serialize(Serialization::IArchive& ar)
	{
		ar(sleep, "Sleep", "Sleep");
		ar(stiffness, "Stiffness", "Stiffness");
	}
	float sleep;
	float stiffness;
};

class CProceduralClipRagdoll : public TProceduralContextualClip<CProceduralContextRagdoll, SRagdollParams>
{
public:
	CProceduralClipRagdoll()
		:
		m_randomTriggerTime(0.0f),
		m_totalTimePassed(0.0f)
	{
	}

protected:
	virtual void OnEnter(float blendTime, float duration, const SRagdollParams &params)
	{
		m_randomTriggerTime = cry_random(0.0f, blendTime);
		m_ragdollSleep = bool(params.sleep>0.0f);
		m_stiffness = params.stiffness;
	}
	virtual void Update(float timePassed)
	{
		m_totalTimePassed += timePassed;
		if( !m_context->IsInRagdoll() && m_totalTimePassed > m_randomTriggerTime ) 
		{
			m_context->EnableRagdoll( m_entity->GetId(), m_ragdollSleep, m_stiffness, true );
		}
	}
	virtual void OnExit(float blendTime)
	{
		m_totalTimePassed = 0.0f;
		m_context->DisableRagdoll( blendTime );
	}

private:
	float m_stiffness;
	float m_randomTriggerTime;
	float m_totalTimePassed;
	bool  m_ragdollSleep;
};

REGISTER_PROCEDURAL_CLIP(CProceduralClipRagdoll, "Ragdoll");

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
#include "Shake.h"
#include "../Game.h"
#include <IViewSystem.h>
#include <IActorSystem.h>
DECLARE_DEFAULT_COMPONENT_FACTORY(CShake, CShake)

CShake::CShake()
{
}

CShake::~CShake()
{
}

//------------------------------------------------------------------------
bool CShake::Init(IGameObject *pGameObject)
{
	SetGameObject(pGameObject);

	//Initialize default values before (in case ScriptTable fails)
	m_radius = 30.0f;
	m_shake = 0.05f;

	SmartScriptTable props;
	IScriptTable* pScriptTable = GetEntity()->GetScriptTable();
	if(!pScriptTable || !pScriptTable->GetValue("Properties", props))
		return false;

	props->GetValue("Radius", m_radius);
	props->GetValue("Shake", m_shake);

	return true;
}

//------------------------------------------------------------------------
void CShake::PostInit(IGameObject *pGameObject)
{
	GetGameObject()->EnableUpdateSlot(this, 0);
}

//------------------------------------------------------------------------
bool CShake::ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params )
{
	ResetGameObject();

	CRY_ASSERT_MESSAGE(false, "CShake::ReloadExtension not implemented");
	
	return false;
}

//------------------------------------------------------------------------
bool CShake::GetEntityPoolSignature( TSerialize signature )
{
	CRY_ASSERT_MESSAGE(false, "CShake::GetEntityPoolSignature not implemented");
	
	return true;
}

//------------------------------------------------------------------------
//void CShake::Release()
//{
//	delete this;
//}

//------------------------------------------------------------------------
void CShake::FullSerialize(TSerialize ser)
{
	ser.Value("Radius", m_radius);
	ser.Value("Shake", m_shake);
}

//------------------------------------------------------------------------
void CShake::Update(SEntityUpdateContext &ctx, int updateSlot)
{
	IActor *pClient = g_pGame->GetIGameFramework()->GetClientActor();
	if (pClient)
	{
		float dist2ToClient((pClient->GetEntity()->GetWorldPos() - GetEntity()->GetWorldPos()).len2());
		float maxRange(m_radius * m_radius);
		if (dist2ToClient<maxRange)
		{
			IView *pView = g_pGame->GetIGameFramework()->GetIViewSystem()->GetViewByEntityId(pClient->GetEntityId());
			if (pView)
			{
				float strength = (1.0f - (dist2ToClient/maxRange)) * 0.5f;
				pView->SetViewShake(ZERO,Vec3(m_shake*strength,0,m_shake*strength),0.1f,0.0225f,1.5f,1);
			}
		}
	}
}

//------------------------------------------------------------------------
void CShake::HandleEvent(const SGameObjectEvent &event)
{
}

//------------------------------------------------------------------------
void CShake::ProcessEvent(SEntityEvent &event)
{
}

//------------------------------------------------------------------------
void CShake::SetAuthority(bool auth)
{
}

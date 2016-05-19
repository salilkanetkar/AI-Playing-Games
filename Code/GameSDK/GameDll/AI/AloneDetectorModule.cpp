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

// Description : This is used for detecting the proximity of a specific 
//               set of AI agents to drive the selection of the behavior in
//               the tree without specific checks in the behavior itself

#include "StdAfx.h" 
#include "AloneDetectorModule.h"
#include "IAISystem.h"
#include "IAIObjectManager.h"
#include "Agent.h"


void AloneDetectorContainer::SetupDetector(const AloneDetectorSetup& setup)
{
	m_setup = setup;
} 

void AloneDetectorContainer::Update(float frameTime)
{
	FUNCTION_PROFILER(gEnv->pSystem, PROFILE_AI);

	if(m_entityClassNames.empty())
		return;

	Agent me(GetEntityID());
	const Vec3 entityPos = me.GetPos();	

	AutoAIObjectIter it(gEnv->pAISystem->GetAIObjectManager()->GetFirstAIObjectInRange(OBJFILTER_GROUP,me.GetGroupID(),entityPos,m_setup.range,false));

	AloneDetectorSetup::State newState = AloneDetectorSetup::Alone;

	for(;it->GetObject();it->Next())
	{
		IAIObject* pAIObject = it->GetObject();

		Agent agent(pAIObject->GetEntityID());

		if( !IsActorValid(agent) )
			continue;

		string sEntityClassName = GetActorClassName(agent);
		EntitiesList::const_iterator entityIt = std::find(m_entityClassNames.begin(),m_entityClassNames.end(), sEntityClassName);
		if(entityIt != m_entityClassNames.end())
		{
			newState = AloneDetectorSetup::EntitiesInRange;
			break;
		}
	}

	if(m_setup.state != newState)
	{
		m_setup.state = newState;
		SendCorrectSignal();
	}
}

void AloneDetectorContainer::SendCorrectSignal()
{
	switch(m_setup.state)
	{
	case AloneDetectorSetup::Alone :
		SendSignal(m_setup.aloneSignal.c_str());	
		break;
	case AloneDetectorSetup::EntitiesInRange :
		SendSignal(m_setup.notAloneSignal.c_str());
		break;
	default:
		assert(0);
		break;
	}
}

void AloneDetectorContainer::AddEntityClass(const char* entityClassName)
{
	if(std::find(m_entityClassNames.begin(),m_entityClassNames.end(),entityClassName) == m_entityClassNames.end())
		m_entityClassNames.push_back(entityClassName);
}

void AloneDetectorContainer::RemoveEntityClass(const char* entityClassName)
{
	EntitiesList::iterator it = std::find(m_entityClassNames.begin(),m_entityClassNames.end(),entityClassName);
	if(it != m_entityClassNames.end())
		m_entityClassNames.erase(it);
}

void AloneDetectorContainer::ResetDetector()
{
	m_setup.state = AloneDetectorSetup::Unkown;
	m_entityClassNames.clear();
}

bool AloneDetectorContainer::IsActorValid(const Agent& agent) const
{
	const bool isValid = agent.IsValid() && !agent.IsHidden() && agent.IsEnabled() && !agent.IsDead();
	return isValid;
}

const char* AloneDetectorContainer::GetActorClassName(const Agent& agent) const
{
	return (agent.GetEntity() && agent.GetEntity()->GetClass()) ? agent.GetEntity()->GetClass()->GetName() : "";
}

bool AloneDetectorContainer::IsAlone() const
{
	return m_setup.state == AloneDetectorSetup::EntitiesInRange;
}

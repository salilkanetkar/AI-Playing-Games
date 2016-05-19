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

#pragma once

#ifndef AIBattleFront_h
#define AIBattleFront_h

#include "IEntity.h"
#include "GameAIHelpers.h"

struct SBattleFrontMember
{
	SBattleFrontMember(EntityId _entityID);

	bool operator < (const SBattleFrontMember& rhs) const 
	{	
		return entityID < rhs.entityID;
	}

	EntityId entityID;
	mutable bool paused;
};

class CAIBattleFrontGroup
{
public:
	typedef int GroupID;

	CAIBattleFrontGroup();
	CAIBattleFrontGroup(GroupID groupID);
	void AddEntity(EntityId entityID);
	void RemoveEntity(EntityId entityID);
	void PauseEntity(EntityId entityID);
	void ResumeEntity(EntityId entityID);
	void Update();
	void SetDesignerControlledBattleFrontAt(const Vec3& position);
	void DisableDesignerControlledBattleFront();
	void DrawDebugInfo();

	const Vec3& GetBattleFrontPosition() const
	{
		return m_battleFrontPosition;
	}

	const Vec3& GetAveragePosition() const
	{
		return m_averagePosition;
	}

	unsigned int GetMemberCount() const
	{
		return m_members.size();
	}

	bool IsEmpty() const
	{
		return m_members.empty();
	}

private:
	enum BattleFrontMode
	{
		Dynamic,
		DesignerControlled
	};

	void CalculateAveragePositionOfGroupMembers();
	void SetPause(EntityId entityID, bool paused);

	std::set<SBattleFrontMember> m_members;
	GroupID m_groupID;
	Vec3 m_battleFrontPosition;
	Vec3 m_averagePosition;
	BattleFrontMode m_battleFrontMode;
};

class CAIBattleFrontModule : public IGameAIModule
{
public:
	virtual void EntityEnter(EntityId entityID);
	virtual void EntityLeave(EntityId entityID);
	virtual void EntityPause(EntityId entityID);
	virtual void EntityResume(EntityId entityID);
	virtual void Reset(bool bUnload);
	virtual void Update(float dt);
	virtual const char* GetName() const;
	CAIBattleFrontGroup* GetGroupForEntity(EntityId entityID);
	CAIBattleFrontGroup* GetGroupByID(CAIBattleFrontGroup::GroupID groupID);

private:
	std::map<CAIBattleFrontGroup::GroupID, CAIBattleFrontGroup> m_battleFrontGroups;
};

#endif // AIBattleFront_h

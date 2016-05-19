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

// Description : Handles entities being attached to paths in multiplayer


#ifndef __MPPATHFOLLOWINGMANAGER_H
#define __MPPATHFOLLOWINGMANAGER_H

#include "WaypointPath.h"
#include "IEntitySystem.h"

struct IMPPathFollowingListener
{
	virtual void OnPathCompleted(EntityId attachedEntityId) = 0;
	virtual ~IMPPathFollowingListener() {};
};

struct IMPPathFollower
{
	typedef uint8 MPPathIndex;

	virtual void OnAttachRequest(const struct SPathFollowingAttachToPathParameters& params, const CWaypointPath* pPath) = 0;
	virtual void OnUpdateSpeedRequest(EntityId attachEntityId, float speed) = 0;
	virtual ~IMPPathFollower() {};
};

class CMPPathFollowingManager : public IEntityEventListener
{
public:
	CMPPathFollowingManager();
	~CMPPathFollowingManager();

	//Note: Currently supports one listener per map entry.
	void RegisterClassFollower(uint16 classId, IMPPathFollower* pFollower);
	void UnregisterClassFollower(uint16 classId);

	bool RegisterPath(EntityId pathEntityId);
	void UnregisterPath(EntityId pathEntityId);

	void RegisterListener(EntityId listenToEntityId, IMPPathFollowingListener* pListener);
	void UnregisterListener(EntityId listenToEntityId);

	const CWaypointPath* GetPath(EntityId pathEntityId, IMPPathFollower::MPPathIndex& outIndex) const;

	void RequestAttachEntityToPath(const struct SPathFollowingAttachToPathParameters& params);

	void RequestUpdateSpeed(uint16 classId, EntityId attachEntityId, float newSpeed);

	void NotifyListenersOfPathCompletion(EntityId pathFollowingEntityId);

	// IEntityEventListener
	virtual void OnEntityEvent( IEntity *pEntity,SEntityEvent &event );
	// ~IEntityEventListener

#ifndef _RELEASE
	void Update();
#endif //_RELEASE

private:
	typedef std::map<uint16, IMPPathFollower*> PathFollowers;
	PathFollowers m_PathFollowers;

	struct SPathEntry
	{
		SPathEntry(EntityId pathEntityId) : pathId(pathEntityId)
		{
		}

		EntityId pathId;
		CWaypointPath path;
	};

	typedef std::vector<SPathEntry> Paths;
	Paths m_Paths;

	typedef std::map<EntityId, IMPPathFollowingListener*> PathListeners;
	PathListeners m_PathListeners;
};

#endif
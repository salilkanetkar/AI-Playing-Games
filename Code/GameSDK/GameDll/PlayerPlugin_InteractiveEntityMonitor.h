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

#ifndef __PLAYERPLUGIN_INTERACTIVE_ENTITY_MONITOR_H__
#define __PLAYERPLUGIN_INTERACTIVE_ENTITY_MONITOR_H__

#include "PlayerPlugin.h"

class CPlayerPlugin_InteractiveEntityMonitor : public CPlayerPlugin
{
public:
	SET_PLAYER_PLUGIN_NAME(CPlayerPlugin_InteractiveEntityMonitor);

	CPlayerPlugin_InteractiveEntityMonitor();
	~CPlayerPlugin_InteractiveEntityMonitor();

	static void PrecacheLevel();

private:
	enum EInteractiveEntityStatus
	{
		EIES_Highlighted			= BIT(0),
		EIES_ShootToInteract	= BIT(1),
	};

	typedef std::pair<EntityId, uint8> InteractiveEntityStatus;
	typedef std::list< InteractiveEntityStatus > InteractiveEntityList;

	virtual void Enter(CPlayerPluginEventDistributor* pEventDist);
	virtual void Update(const float dt);
	virtual void HandleEvent(EPlayerPlugInEvent theEvent, void * data);

	void Register(IEntity* pEntity, uint8 initialFlags);
	void Unregister(IEntity* pEntity);
	void EnableHighlighting(bool enable);

	bool m_bEnabled;

	InteractiveEntityList m_interactiveEntityList;

#ifndef _RELEASE
	typedef std::map<int, string> InteractiveEntityDebugMap;
	InteractiveEntityDebugMap m_debugMap;
#endif //_RELEASE
	
	static ColorF m_silhouetteInteractColor;
	static ColorF m_silhouetteShootColor;
	Vec3 m_playerPrevPos;
	float m_timeUntilRefresh;
};

#endif // __PLAYERPLUGIN_INTERACTIVE_ENTITY_MONITOR_H__


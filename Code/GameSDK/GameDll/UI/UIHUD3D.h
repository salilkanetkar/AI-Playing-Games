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

#ifndef __UIHUD3D_H__
#define __UIHUD3D_H__

#include "IUIGameEventSystem.h"
#include <IMovieSystem.h>
#include <IFlashUI.h>

class CUIHUD3D
	: public IUIGameEventSystem
	, public ISystemEventListener
	, public IEntityEventListener
	, public IMovieListener
	, public IUIModule
{
public:
	CUIHUD3D();
	~CUIHUD3D();
	// IUIGameEventSystem
	UIEVENTSYSTEM( "UIHUD3D" );
	virtual void InitEventSystem();
	virtual void UnloadEventSystem();
	virtual void UpdateView( const SViewParams &viewParams );

	// ISystemEventListener
	virtual void OnSystemEvent( ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam );
	// ~ISystemEventListener

	// IEntityEventListener
	virtual void OnEntityEvent( IEntity *pEntity,SEntityEvent &event );
	// ~IEntityEventListener

	// IMovieEventListener
	virtual void OnMovieEvent(IMovieListener::EMovieEvent event, IAnimSequence* pSequence);
	// ~IMovieEventListener

	// IUIModule
	void Reload();
	void Update(float fDeltaTime);
	// ~IUIModule

	void SetVisible(bool visible);
	bool IsVisible() const;

private:
	void SpawnHudEntities();
	void RemoveHudEntities();


	static void OnVisCVarChange( ICVar * );

private:
	IEntity* m_pHUDRootEntity;
	EntityId m_HUDRootEntityId;
	typedef std::vector< EntityId > THUDEntityList;
	THUDEntityList m_HUDEnties;
	bool m_bCutSceneNoHud;

	struct SHudOffset
	{
		SHudOffset(float aspect, float dist, float offset)
			: Aspect(aspect)
			, HudDist(dist)
			, HudZOffset(offset)
		{
		}

		float Aspect;
		float HudDist;
		float HudZOffset;
	};
	typedef std::vector< SHudOffset > THudOffset;
	THudOffset m_Offsets;

	float m_fHudDist;
	float m_fHudZOffset;
	//IAnimSequence* m_pSequence;
};

#endif // __UIHUD3D_H__


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

#ifndef __UIEntityDynTexTag_H__
#define __UIEntityDynTexTag_H__

#include "IUIGameEventSystem.h"
#include <IFlashUI.h>
#include <IEntitySystem.h>

class CUIEntityDynTexTag 
	: public IUIGameEventSystem
	, public IUIModule
	, public IUIElementEventListener
	, public IEntityEventListener
{
public:
	// IUIGameEventSystem
	UIEVENTSYSTEM( "UIEntityDynTexTag" );
	virtual void InitEventSystem();
	virtual void UnloadEventSystem();
	virtual void OnUpdate(float fDeltaTime);

	// IUIModule
	virtual void Reset();
	virtual void Reload();
	// ~IUIModule

	// IUIElementEventListener
	virtual void OnInstanceDestroyed( IUIElement* pSender, IUIElement* pDeletedInstance );
	// ~IUIElementEventListener

	// IEntityEventListener
	virtual void OnEntityEvent( IEntity *pEntity,SEntityEvent &event );
	// ~IEntityEventListener

private:
	void OnAddTaggedEntity( EntityId entityId, const char* uiElementName, const char* entityClass, const char* materialTemplate, const Vec3& offset, const char* idx);
	void OnUpdateTaggedEntity( EntityId entityId, const string& idx, const Vec3& offset, float speed );
	void OnRemoveTaggedEntity( EntityId entityId, const string& idx );
	void OnRemoveAllTaggedEntity( EntityId entityId );

	void RemoveAllEntityTags( EntityId entityId, bool bUnregisterListener = true );
	void ClearAllTags();
	inline bool HasEntityTag( EntityId entityId ) const;

private:
	SUIEventReceiverDispatcher<CUIEntityDynTexTag> s_EventDispatcher;
	IUIEventSystem* m_pUIOFct;

	struct STagInfo
	{
		STagInfo(EntityId ownerId, EntityId tagEntityId, const string& idx, const Vec3& offset, IUIElement* pInst) : OwnerId(ownerId), TagEntityId(tagEntityId), Idx(idx), vOffset(offset), vNewOffset(offset), pInstance(pInst), fLerp(2), fSpeed(0) {}

		EntityId OwnerId;
		EntityId TagEntityId;
		string Idx;
		Vec3 vOffset;
		Vec3 vNewOffset;
		IUIElement* pInstance;
		float fLerp;
		float fSpeed;
	};

	typedef std::vector< STagInfo > TTags;
	TTags m_Tags;
};

#endif // __UIEntityDynTexTag_H__


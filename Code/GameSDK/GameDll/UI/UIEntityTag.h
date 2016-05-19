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

#ifndef __UIEntityTag_H__
#define __UIEntityTag_H__

#include "IUIGameEventSystem.h"
#include <IFlashUI.h>
#include <IEntitySystem.h>

class CUIEntityTag 
	: public IUIGameEventSystem
	, public IUIModule
	, public IUIElementEventListener
	, public IEntityEventListener
{
public:
	// IUIGameEventSystem
	UIEVENTSYSTEM( "CUIEntityTag" );
	virtual void InitEventSystem();
	virtual void UnloadEventSystem();
	virtual void OnUpdate( float fDelta );

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

	struct STagInfo
	{
		STagInfo(EntityId ownerId, const string& idx, const Vec3& offset, const SUIMovieClipDesc* pDesc, IUIElement* pElement, IFlashVariableObject* pObj, bool scale, const Vec3& currPos, bool bCamAttached)
			: OwnerId(ownerId)
			, Idx(idx)
			, vOffset(offset)
			, pMCDesc(pDesc)
			, pUIElement(pElement)
			, pVarObj(pObj)
			, bScale(scale)
			, vCurrPos(currPos)
			, fLerp(1)
			, fLerpSpeed(0)
			, bAttachedToCam(bCamAttached)
		{
		}
		EntityId OwnerId;
		string Idx;
		Vec3 vOffset;
		Vec3 vCurrPos;
		bool bAttachedToCam;
		float fLerpSpeed;
		float fLerp;
		const SUIMovieClipDesc* pMCDesc;
		IFlashVariableObject* pVarObj;
		IUIElement* pUIElement;
		bool bScale;
	};

		const STagInfo* GetTagInfo(EntityId entityId, const string& tagIdx) const;

private:
	SUIArgumentsRet OnAddTaggedEntity( EntityId entityId, const char* uiTemplate, int instanceId, const Vec3& offset, const char* idx, bool scale, bool bCamAttached);
	void OnUpdateTaggedEntity( EntityId entityId, const string& idx, const Vec3& offset, bool bCamAttached, float speed );
	void OnRemoveTaggedEntity( EntityId entityId, const string& idx );
	void OnRemoveAllTaggedEntity( EntityId entityId );

	void RemoveAllEntityTags( EntityId entityId, bool bUnregisterListener = true );
	void ClearAllTags();
	inline bool HasEntityTag( EntityId entityId ) const;
	Vec3 AddOffset( const Matrix34& camMat, const Vec3& vPos, const Vec3 &offset, bool bRelToCam );

private:
	SUIEventReceiverDispatcher<CUIEntityTag> s_EventDispatcher;
	IUIEventSystem* m_pUIOFct;

	typedef std::vector< STagInfo > TTags;
	TTags m_Tags;
};

// --------------------------------------------------------------
#endif // __UIEntityTag_H__


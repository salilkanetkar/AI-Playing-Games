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
#include "UIEntityTag.h"
#include <IGame.h>
#include <IGameFramework.h>
#include <IViewSystem.h>
#include "Nodes/G2FlowBaseNode.h"
#include "UIManager.h"

extern IFlashUI *pFlashUI;

////////////////////////////////////////////////////////////////////////////
void CUIEntityTag::InitEventSystem()
{
#if !defined(EXCLUDE_SCALEFORM_SDK)
	//assert(pFlashUI);
#endif
	if (!pFlashUI)
		return;

	// event system to receive events from UI
	m_pUIOFct = pFlashUI->CreateEventSystem( "UIEntityTag", IUIEventSystem::eEST_UI_TO_SYSTEM );
	s_EventDispatcher.Init(m_pUIOFct, this, "UIEntityTag");

	{
		SUIEventDesc evtDesc( "AddEntityTag", "Adds a 3D entity Tag" );
		evtDesc.AddParam<SUIParameterDesc::eUIPT_Int>("EntityID", "Entity ID of tagged entity");
		evtDesc.AddParam<SUIParameterDesc::eUIPT_String>("uiTemplates_Template", "Movieclip Template");
		evtDesc.AddParam<SUIParameterDesc::eUIPT_Int>("InstanceID", "UIElement instance id");
		evtDesc.AddParam<SUIParameterDesc::eUIPT_Vec3>("Offset", "Offset in camera space relative to entity pos");
		evtDesc.AddParam<SUIParameterDesc::eUIPT_String>("TagIDX", "Custom IDX to identify entity tag.");
		evtDesc.AddParam<SUIParameterDesc::eUIPT_Bool>("ScaleMC", "If set to true it will scale the MC according to 3D pos");
		evtDesc.AddParam<SUIParameterDesc::eUIPT_Bool>("AttachedToCam", "If the pos will be \"Offset\" from camera otherwise offset from entity");
		evtDesc.OutputParams.AddParam<SUIParameterDesc::eUIPT_String>("MCInstanceName", "Name of the Movieclip instance for the tag");
		s_EventDispatcher.RegisterEvent( evtDesc, &CUIEntityTag::OnAddTaggedEntity );
	}

	{
		SUIEventDesc evtDesc( "UpdateEntityTag", "Updates a 3D entity Tag" );
		evtDesc.AddParam<SUIParameterDesc::eUIPT_Int>("EntityID", "Entity ID of tagged entity");
		evtDesc.AddParam<SUIParameterDesc::eUIPT_String>("TagIDX", "Custom IDX to identify entity tag.");
		evtDesc.AddParam<SUIParameterDesc::eUIPT_Vec3>("Offset", "Offset in camera space relative to entity pos");
		evtDesc.AddParam<SUIParameterDesc::eUIPT_Bool>("AttachedToCam", "If the pos will be \"Offset\" from camera otherwise offset from entity");
		evtDesc.AddParam<SUIParameterDesc::eUIPT_Float>("LerpSpeed", "Define speed of lerp between old and new pos, 0=instant");
		s_EventDispatcher.RegisterEvent( evtDesc, &CUIEntityTag::OnUpdateTaggedEntity );
	}

	{
		SUIEventDesc evtDesc( "RemoveEntityTag", "Removes a 3D entity Tag" );
		evtDesc.AddParam<SUIParameterDesc::eUIPT_Int>("EntityID", "Entity ID of tagged entity");
		evtDesc.AddParam<SUIParameterDesc::eUIPT_String>("TagIDX", "Custom IDX to identify entity tag.");
		s_EventDispatcher.RegisterEvent( evtDesc, &CUIEntityTag::OnRemoveTaggedEntity );
	}

	{
		SUIEventDesc evtDesc( "RemoveAllEntityTag", "Removes all 3D entity Tags for given entity" );
		evtDesc.AddParam<SUIParameterDesc::eUIPT_Int>("EntityID", "Entity ID of tagged entity");
		s_EventDispatcher.RegisterEvent( evtDesc, &CUIEntityTag::OnRemoveAllTaggedEntity );
	}

	pFlashUI->RegisterModule(this, "CUIEntityDynTexTag");
}

////////////////////////////////////////////////////////////////////////////
void CUIEntityTag::UnloadEventSystem()
{
	ClearAllTags();

	if (pFlashUI)
		pFlashUI->UnregisterModule(this);
}

////////////////////////////////////////////////////////////////////////////
void CUIEntityTag::OnUpdate( float fDelta )
{
	const CCamera& cam = GetISystem()->GetViewCamera();
	const Matrix34& camMat = cam.GetMatrix();

	std::multimap<float, STagInfo*> sortMap;
 	for (TTags::iterator it = m_Tags.begin(); it != m_Tags.end(); ++it)
 	{
 		IEntity* pOwner = gEnv->pEntitySystem->GetEntity(it->OwnerId);
		assert(pOwner);
 		if (pOwner)
 		{
			Vec3 vPos = AddOffset(camMat, it->bAttachedToCam ? camMat.GetTranslation() : pOwner->GetWorldPos(), it->vOffset, it->bAttachedToCam);;

			if (it->fLerp < 1)
			{
				vPos = Vec3::CreateLerp(it->vCurrPos, vPos, it->fLerp);
				it->fLerp += fDelta * it->fLerpSpeed;
			}
			it->vCurrPos = vPos;

			Vec3 vFlashPos;
			Vec2 borders;
			float scale;
			it->pUIElement->WorldToFlash(camMat, vPos, vFlashPos, borders, scale);

			SFlashDisplayInfo info;
			it->pVarObj->GetDisplayInfo(info);
			info.SetX(vFlashPos.x);
			info.SetY(vFlashPos.y);
			info.SetZ(vFlashPos.z);
			info.SetVisible(borders.x == 0 && borders.y == 0);
			scale *= 100.f;
			if (it->bScale)
				info.SetScale(scale, scale, scale);
			it->pVarObj->SetDisplayInfo(info);
			sortMap.insert(std::make_pair(vFlashPos.z, &(*it)));
		}
 	}
	int depth = 100;
	for (std::multimap<float, STagInfo*>::reverse_iterator it = sortMap.rbegin(); it != sortMap.rend(); ++it)
	{
		it->second->pVarObj->Invoke1("swapDepths", depth++);
	}
}

////////////////////////////////////////////////////////////////////////////
void CUIEntityTag::Reset()
{
	ClearAllTags();
}

////////////////////////////////////////////////////////////////////////////
void CUIEntityTag::Reload()
{
	if (gEnv->IsEditor())
	{
		ClearAllTags();
	}
}

////////////////////////////////////////////////////////////////////////////
void CUIEntityTag::OnInstanceDestroyed( IUIElement* pSender, IUIElement* pDeletedInstance )
{
	for (TTags::iterator it = m_Tags.begin(); it != m_Tags.end();)
	{
		if (it->pUIElement == pDeletedInstance)
			it = m_Tags.erase(it);
		else
			++it;
	}
}

////////////////////////////////////////////////////////////////////////////
const CUIEntityTag::STagInfo* CUIEntityTag::GetTagInfo(EntityId entityId, const string& tagIdx) const
{
	for (TTags::const_iterator it = m_Tags.begin(); it != m_Tags.end(); ++it)
	{
		if (it->OwnerId == entityId && it->Idx == tagIdx)
			return &(*it);
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////
void CUIEntityTag::OnEntityEvent( IEntity *pEntity,SEntityEvent &event )
{
	assert(event.event == ENTITY_EVENT_DONE);
	RemoveAllEntityTags( pEntity->GetId(), false );
}

////////////////////////////////////////////////////////////////////////////
SUIArgumentsRet CUIEntityTag::OnAddTaggedEntity( EntityId entityId, const char* uiTemplate, int instanceId, const Vec3& offset, const char* idx, bool scale, bool bCamAttached)
{
	OnRemoveTaggedEntity(entityId, idx);
	SUIArguments args;
	args.SetDelimiter(":");
	args.SetArguments(uiTemplate);
	assert(args.GetArgCount() == 2);
	string uielement;
	string tmpl;
	args.GetArg(0, uielement);
	args.GetArg(1, tmpl);

	IUIElement* pElement = pFlashUI->GetUIElement(uielement.c_str());
	if (pElement)
	{
		instanceId = max(0, instanceId);
		pElement = pElement->GetInstance(instanceId);
		assert(pElement);
		const SUIMovieClipDesc* pVarDesc = NULL;
		IFlashVariableObject* pNewMC = pElement->CreateMovieClip(pVarDesc, tmpl);
		IEntity* pOwner = gEnv->pEntitySystem->GetEntity(entityId);
		if (pNewMC && pOwner)
		{
			const CCamera& cam = GetISystem()->GetViewCamera();
			const Matrix34& camMat = cam.GetMatrix();
			Vec3 currPos = AddOffset(camMat, bCamAttached ? camMat.GetTranslation() : pOwner->GetWorldPos(), offset, bCamAttached);
			m_Tags.push_back( STagInfo(entityId, idx, offset, pVarDesc, pElement, pNewMC, scale, currPos, bCamAttached) );
			pNewMC->SetVisible(false);
			SUIArguments res;
			res.AddArgument(pVarDesc->sDisplayName);
			return res;
		}
	}

	SUIArguments res;
	res.AddArgument("UNDEFINED");
	return res;
}

////////////////////////////////////////////////////////////////////////////
void CUIEntityTag::OnUpdateTaggedEntity( EntityId entityId, const string& idx, const Vec3& offset, bool bCamAttached, float speed )
{
	for (TTags::iterator it = m_Tags.begin(); it != m_Tags.end(); ++it)
	{
		if (it->OwnerId == entityId && it->Idx == idx)
		{
			it->vOffset = offset;
			it->bAttachedToCam = bCamAttached;
			if (speed > 0)
			{
				it->fLerpSpeed = speed;
				it->fLerp = 0;
			}
			else
			{
				it->fLerp = 1;
			}
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////
void CUIEntityTag::OnRemoveTaggedEntity( EntityId entityId, const string& idx )
{
	for (TTags::iterator it = m_Tags.begin(); it != m_Tags.end(); ++it)
	{
		if (it->OwnerId == entityId && it->Idx == idx)
		{
			it->pUIElement->RemoveMovieClip(it->pMCDesc);
			m_Tags.erase(it);
			break;
		}
	}
	if (!HasEntityTag(entityId))
		gEnv->pEntitySystem->RemoveEntityEventListener(entityId, ENTITY_EVENT_DONE, this);
}

////////////////////////////////////////////////////////////////////////////
void CUIEntityTag::OnRemoveAllTaggedEntity( EntityId entityId )
{
	RemoveAllEntityTags(entityId);
}

////////////////////////////////////////////////////////////////////////////
void CUIEntityTag::RemoveAllEntityTags( EntityId entityId, bool bUnregisterListener )
{
	for (TTags::iterator it = m_Tags.begin(); it != m_Tags.end();)
	{
		if (it->OwnerId == entityId)
		{
			it->pUIElement->RemoveMovieClip(it->pMCDesc);
			it = m_Tags.erase(it);
		}
		else
		{
			++it;
		}
	}
	if (bUnregisterListener)
		gEnv->pEntitySystem->RemoveEntityEventListener(entityId, ENTITY_EVENT_DONE, this);
}

////////////////////////////////////////////////////////////////////////////
void CUIEntityTag::ClearAllTags()
{
	for (TTags::const_iterator it = m_Tags.begin(); it != m_Tags.end(); ++it)
	{
		it->pUIElement->RemoveMovieClip(it->pMCDesc);
		gEnv->pEntitySystem->RemoveEntityEventListener(it->OwnerId, ENTITY_EVENT_DONE, this);
	}
	m_Tags.clear();
}

////////////////////////////////////////////////////////////////////////////
bool CUIEntityTag::HasEntityTag( EntityId entityId ) const
{
	for (TTags::const_iterator it = m_Tags.begin(); it != m_Tags.end(); ++it)
	{
		if (it->OwnerId == entityId)
		{
			return true;
		}
	}
	return false;
}

Vec3 CUIEntityTag::AddOffset( const Matrix34& camMat, const Vec3& vPos, const Vec3 &offset, bool bRelToCam )
{
	const Vec3 vViewDir = camMat.GetColumn1();
	const Vec3 vFaceingPos = camMat.GetColumn3() - vViewDir * 1000.f;
	const Vec3 vDir = (vPos - vFaceingPos).GetNormalizedSafe(vViewDir);
	const Vec3 vOffsetX = vDir.Cross(Vec3Constants<float>::fVec3_OneZ).GetNormalizedFast() * offset.x;
	const Vec3 vOffsetY = vDir * offset.y;
	const Vec3 vOffsetZ = bRelToCam ? camMat.GetColumn2().GetNormalizedFast() * offset.z :  Vec3(0, 0, offset.z);
	return vPos + vOffsetX + vOffsetY + vOffsetZ;
}
////////////////////////////////////////////////////////////////////////////
REGISTER_UI_EVENTSYSTEM( CUIEntityTag );

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
class CGetEntityTagNode : public CFlowBaseNode<eNCT_Singleton>
{
public:
	CGetEntityTagNode(SActivationInfo* pActInfo) {};

	virtual void GetConfiguration(SFlowNodeConfig& config)
	{
		static const SInputPortConfig inputs[] = {
			InputPortConfig_AnyType("Get",_HELP("Trigger the nodes to get tag instance name")),
			InputPortConfig<string>("TagIdx",_HELP("The tag idx")),
			{0}
		};

		static const SOutputPortConfig outputs[] = {
			OutputPortConfig<string>("MCInstanceName", _HELP("Name of the movieclip instance name")),
			{0}
		};

		config.nFlags |= EFLN_TARGET_ENTITY;
		config.sDescription = _HELP("This node will return the Movieclip instance name for this entity");
		config.pInputPorts = inputs;
		config.pOutputPorts = outputs;
		config.SetCategory(EFLN_APPROVED);
	}

	virtual void ProcessEvent( EFlowEvent event, SActivationInfo* pActInfo)
	{
		if (event == eFE_Activate && IsPortActive(pActInfo, eI_Get))
		{
			string tagIdx = GetPortString(pActInfo, eI_TagIdx);
			EntityId id =  pActInfo->pEntity != 0 ? pActInfo->pEntity->GetId() : 0;
			CUIEntityTag* pEntityTagSystem = UIEvents::Get<CUIEntityTag>();
			assert(pEntityTagSystem);
			const CUIEntityTag::STagInfo* pInfo = pEntityTagSystem ? pEntityTagSystem->GetTagInfo(id, tagIdx) : NULL;
			ActivateOutput(pActInfo, eO_InstanceName, pInfo ? string(pInfo->pMCDesc->sDisplayName) : string(""));
		}
	}

	virtual void GetMemoryUsage(ICrySizer * s) const { s->Add(*this); }

private:
	enum EInputs
	{
		eI_Get = 0,
		eI_TagIdx
	};
	enum EOutputs
	{
		eO_InstanceName = 0,
	};
};
////////////////////////////////////////////////////////////////////////////
REGISTER_FLOW_NODE( "UI:Functions:UIEntityTag:GetEntityTag", CGetEntityTagNode );

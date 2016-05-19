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

// Description : Game effect - Ideal for handling a specific visual game feature


#include "StdAfx.h"
#include "GameEffect.h"
#include "Effects/GameEffectsSystem.h"
#include "ICryAnimation.h"
#include "Actor.h"

//--------------------------------------------------------------------------------------------------
// Name: GameSDKCGameEffect
// Desc: Constructor
//--------------------------------------------------------------------------------------------------
GameSDKCGameEffect::GameSDKCGameEffect()
{
	m_prev	= NULL;
	m_next	= NULL;
	m_flags = 0;
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: ~GameSDKCGameEffect
// Desc: Destructor
//--------------------------------------------------------------------------------------------------
GameSDKCGameEffect::~GameSDKCGameEffect()
{
#if DEBUG_GAME_FX_SYSTEM
	// Output message if effect hasn't been released before being deleted
	const bool bEffectIsReleased = (m_flags & GAME_EFFECT_RELEASED) ||			// -> Needs to be released before deleted
																 !(m_flags & GAME_EFFECT_INITIALISED) ||	// -> Except when not initialised
																 (gEnv->IsEditor());											// -> Or the editor (memory safely released by editor)
	if(!bEffectIsReleased)
	{
		string dbgMessage = m_debugName + " being destroyed without being released first";
		FX_ASSERT_MESSAGE(bEffectIsReleased,dbgMessage.c_str());
	}
#endif

    if (GameSDKCGameEffectsSystem::Exists())
	{
		GAME_FX_SYSTEM.UnRegisterEffect(this);	// -> Effect should have been released and been unregistered, but to avoid
																						//    crashes call unregister here too
	}
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: Initialise
// Desc: Initializes game effect
//--------------------------------------------------------------------------------------------------
void GameSDKCGameEffect::Initialise(const SGameEffectParams* gameEffectParams)
{
#if DEBUG_GAME_FX_SYSTEM
	m_debugName = GetName(); // Store name so it can be accessed in destructor and debugging
#endif

	if(!IsFlagSet(GAME_EFFECT_INITIALISED))
	{
		SGameEffectParams params;
		if(gameEffectParams)
		{
			params = *gameEffectParams;
		}

		SetFlag(GAME_EFFECT_AUTO_UPDATES_WHEN_ACTIVE,params.autoUpdatesWhenActive);
		SetFlag(GAME_EFFECT_AUTO_UPDATES_WHEN_NOT_ACTIVE,params.autoUpdatesWhenNotActive);
		SetFlag(GAME_EFFECT_AUTO_RELEASE,params.autoRelease);
		SetFlag(GAME_EFFECT_AUTO_DELETE,params.autoDelete);

		GAME_FX_SYSTEM.RegisterEffect(this);

		SetFlag(GAME_EFFECT_INITIALISED,true);
		SetFlag(GAME_EFFECT_RELEASED,false);
	}
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: Release
// Desc: Releases game effect
//--------------------------------------------------------------------------------------------------
void GameSDKCGameEffect::Release()
{
	SetFlag(GAME_EFFECT_RELEASING, true);
	if(IsFlagSet(GAME_EFFECT_ACTIVE))
	{
		SetActive(false);
	}
	GAME_FX_SYSTEM.UnRegisterEffect(this);
	SetFlag(GAME_EFFECT_INITIALISED,false);
	SetFlag(GAME_EFFECT_RELEASING, false);
	SetFlag(GAME_EFFECT_RELEASED,true);
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: SetActive
// Desc: Sets active status
//--------------------------------------------------------------------------------------------------
void GameSDKCGameEffect::SetActive(bool isActive)
{
	FX_ASSERT_MESSAGE(IsFlagSet(GAME_EFFECT_INITIALISED),"Effect changing active status without being initialised first");
	FX_ASSERT_MESSAGE((IsFlagSet(GAME_EFFECT_RELEASED)==false),"Effect changing active status after being released");

	SetFlag(GAME_EFFECT_ACTIVE,isActive);
	GAME_FX_SYSTEM.RegisterEffect(this); // Re-register effect with game effects system
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: Update
// Desc: Updates game effect
//--------------------------------------------------------------------------------------------------
void GameSDKCGameEffect::Update(float frameTime)
{
	FX_ASSERT_MESSAGE(IsFlagSet(GAME_EFFECT_INITIALISED),"Effect being updated without being initialised first");
	FX_ASSERT_MESSAGE((IsFlagSet(GAME_EFFECT_RELEASED)==false),"Effect being updated after being released");
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: Next
// Desc: Gets next effect
//--------------------------------------------------------------------------------------------------
GameSDKIGameEffect* GameSDKCGameEffect::Next() const
{
	return m_next;
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: Prev
// Desc: Gets previous effect
//--------------------------------------------------------------------------------------------------
GameSDKIGameEffect* GameSDKCGameEffect::Prev() const
{
	return m_prev;
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: SetNext
// Desc: Sets the next effect
//--------------------------------------------------------------------------------------------------
void GameSDKCGameEffect::SetNext(GameSDKIGameEffect* newNext)
{
	m_next = newNext;
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: SetPrev
// Desc: Sets the previous effect
//--------------------------------------------------------------------------------------------------
void GameSDKCGameEffect::SetPrev(GameSDKIGameEffect* newPrev)
{
	m_prev = newPrev;
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: SetFlag
// Desc: Sets a game effect flag
//--------------------------------------------------------------------------------------------------
void GameSDKCGameEffect::SetFlag(uint32 flag, bool state)
{
	SET_FLAG(m_flags,flag,state);
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: IsFlagSet
// Desc: Checks a game effect flag
//--------------------------------------------------------------------------------------------------
bool GameSDKCGameEffect::IsFlagSet(uint32 flag) const
{
	return IS_FLAG_SET(m_flags,flag);
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: GetFlags
// Desc: Gets effect's flags
//--------------------------------------------------------------------------------------------------
uint32 GameSDKCGameEffect::GetFlags() const
{ 
	return m_flags; 
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: SetFlags
// Desc: Sets effect's flags
//--------------------------------------------------------------------------------------------------
void GameSDKCGameEffect::SetFlags(uint32 flags)
{
	m_flags = flags;
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: SpawnParticlesOnSkeleton
// Desc: Spawn particles on Skeleton
//--------------------------------------------------------------------------------------------------
void GameSDKCGameEffect::SpawnParticlesOnSkeleton(IEntity* pEntity, IParticleEmitter* pParticleEmitter, uint32 numParticles, float maxHeightScale) const
{
	if((pEntity) && (numParticles>0) && (pParticleEmitter) && (maxHeightScale>0.0f))
	{
		ICharacterInstance* pCharacter = pEntity->GetCharacter(0);
		if(pCharacter)
		{
			IDefaultSkeleton& rIDefaultSkeleton = pCharacter->GetIDefaultSkeleton();
			ISkeletonPose* pPose = pCharacter->GetISkeletonPose();
			if(pPose)
			{
				Vec3 animPos;
				Quat animRot;

				IActor* pActor = gEnv->pGame->GetIGameFramework()->GetIActorSystem()->GetActor(pEntity->GetId());
				if(pActor) // First try to get animation data
				{
					QuatT animLoc = pActor->GetAnimatedCharacter()->GetAnimLocation();
					animPos = animLoc.t;
					animRot = animLoc.q;
				}
				else // If no actor, then use entity data
				{
					animPos = pEntity->GetWorldPos();
					animRot = pEntity->GetWorldRotation();
				}

				animRot.Invert();

				AABB bbox;
				pEntity->GetLocalBounds(bbox);
				float bbHeight = bbox.max.z - bbox.min.z;
				// Avoid division by 0
				if(bbHeight == 0)
				{
					bbHeight = 0.0001f;
				}

				const uint32 numJoints = rIDefaultSkeleton.GetJointCount();

				for (uint32 i = 0; i < numParticles; ++i)
				{
					int id = cry_random(0U, numJoints - 1);
					int parentId = rIDefaultSkeleton.GetJointParentIDByID(id);

					if(parentId>0)
					{
						QuatT boneQuat = pPose->GetAbsJointByID(id);
						QuatT parentBoneQuat= pPose->GetAbsJointByID(parentId);
						float lerpScale = cry_random(0.0f, 1.0f);

						QuatTS loc(IDENTITY);
						loc.t = LERP(boneQuat.t,parentBoneQuat.t,lerpScale);

						float heightScale = ((loc.t.z - bbox.min.z) / bbHeight);
						if(heightScale < maxHeightScale)
						{
							loc.t = loc.t * animRot;
							loc.t = loc.t + animPos;

							pParticleEmitter->EmitParticle(NULL, NULL, &loc);
						}
					}
				}
			}
		}
	}
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: SetMaterialOnEntity
// Desc: Sets material on entity
//--------------------------------------------------------------------------------------------------
void GameSDKCGameEffect::SetMaterialOnEntity(IMaterial* pMaterial, EntityId entityId, PodArray<int>*	pBodyAttachmentIndexArray)
{
	if(pMaterial && pBodyAttachmentIndexArray)
	{
		IEntity* pEntity = gEnv->pEntitySystem->GetEntity(entityId);
		if(pEntity)
		{
			SEntitySlotInfo slotInfo;
			bool gotSlotInfo = pEntity->GetSlotInfo(0, slotInfo);
			if(gotSlotInfo && slotInfo.pCharacter)
			{
				IAttachmentManager* pAttachmentManager = slotInfo.pCharacter->GetIAttachmentManager();
				if(pAttachmentManager)
				{
					int attachmentCount = pBodyAttachmentIndexArray->size();
					for(int i=0; i<attachmentCount; i++)
					{
						IAttachment* attachment = pAttachmentManager->GetInterfaceByIndex((*pBodyAttachmentIndexArray)[i]);

						if(attachment)
						{
							IAttachmentObject* attachmentObj = attachment->GetIAttachmentObject();
							if(attachmentObj)
							{
								attachmentObj->SetReplacementMaterial(pMaterial);
							}
						}
					}
				}
			}
		}
	}
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: SetMaterialOnEntity
// Desc: Sets material on entity
//--------------------------------------------------------------------------------------------------
void GameSDKCGameEffect::SetMaterialOnEntity(IMaterial* pMaterial, EntityId entityId, PodArray<ItemString>*	bodyAttachmentNameArray)
{
	if(pMaterial && bodyAttachmentNameArray)
	{
		IEntity* pEntity = gEnv->pEntitySystem->GetEntity(entityId);
		if(pEntity)
		{
			SEntitySlotInfo slotInfo;
			bool gotSlotInfo = pEntity->GetSlotInfo(0, slotInfo);
			if(gotSlotInfo && slotInfo.pCharacter)
			{
				IAttachmentManager* pAttachmentManager = slotInfo.pCharacter->GetIAttachmentManager();
				if(pAttachmentManager)
				{
					int attachmentCount = bodyAttachmentNameArray->size();
					for(int i=0; i<attachmentCount; i++)
					{
						IAttachment* attachment = pAttachmentManager->GetInterfaceByName(((*bodyAttachmentNameArray)[i]).c_str());

						if(attachment)
						{
							IAttachmentObject* attachmentObj = attachment->GetIAttachmentObject();
							if(attachmentObj)
							{
								attachmentObj->SetReplacementMaterial(pMaterial);
							}
						}
					}
				}
			}
		}
	}
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: ReadAttachmentNames
// Desc: Reads attachment names
//--------------------------------------------------------------------------------------------------
void GameSDKCGameEffect::ReadAttachmentNames(const IItemParamsNode* pParamNode, PodArray<ItemString>* pAttachmentNameArray)
{
	if(pParamNode && pAttachmentNameArray)
	{
		int attachmentCount = pParamNode->GetChildCount();
		pAttachmentNameArray->resize(attachmentCount);
		for(int i=0; i<attachmentCount; i++)
		{
			const IItemParamsNode* attachmentNode = pParamNode->GetChild(i);
			if(attachmentNode)
			{
				(*pAttachmentNameArray)[i] = attachmentNode->GetAttribute("name");
			}
		}
	}
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: InitAttachmentIndexArray
// Desc: Initialises attachment index array
//--------------------------------------------------------------------------------------------------
void GameSDKCGameEffect::InitAttachmentIndexArray(PodArray<int> *attachmentIndexArray, PodArray<ItemString>* pAttachmentNameArray, EntityId entityId) const
{
	if(attachmentIndexArray && pAttachmentNameArray && (entityId!=0))
	{
		if(attachmentIndexArray->size() == 0)
		{
			// Store attachment index array
			const int attachmentNameCount = pAttachmentNameArray->size();

			SEntitySlotInfo slotInfo;
			IEntity* pEntity = gEnv->pEntitySystem->GetEntity(entityId);
			if(pEntity)
			{
				bool gotEntitySlotInfo = pEntity->GetSlotInfo(0, slotInfo);
				if(gotEntitySlotInfo)
				{
					attachmentIndexArray->reserve(attachmentNameCount);

					if(slotInfo.pCharacter)
					{
						IAttachmentManager* attachmentManager = slotInfo.pCharacter->GetIAttachmentManager();
						if(attachmentManager)
						{
							const int attachmentCount = attachmentManager->GetAttachmentCount();

							for(int n=0; n<attachmentNameCount; n++)
							{
								for(int a=0; a<attachmentCount; a++)
								{
									IAttachment* attachment = attachmentManager->GetInterfaceByIndex(a);
									if(attachment)
									{
										const char* currentAttachmentName = attachment->GetName();
										if(strcmp(currentAttachmentName,(*pAttachmentNameArray)[n].c_str())==0)
										{
											attachmentIndexArray->push_back(a);
											break;
										}
									}
								}
							}
						}
					}
				}
			}	
		}
	}
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: LoadMaterial
// Desc: Loads and calls AddRef on material
//--------------------------------------------------------------------------------------------------
IMaterial* GameSDKCGameEffect::LoadMaterial(const char* pMaterialName)
{
	IMaterial* pMaterial = NULL;
	I3DEngine* p3DEngine = gEnv->p3DEngine;
	if(pMaterialName && p3DEngine)
	{
		IMaterialManager* pMaterialManager = p3DEngine->GetMaterialManager();
		if(pMaterialManager)
		{
			pMaterial = pMaterialManager->LoadMaterial(pMaterialName);
			if(pMaterial)
			{
				pMaterial->AddRef();
			}
		}
	}
	return pMaterial;
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: LoadParticleEffect
// Desc: Loads and calls AddRef on a particle effect
//--------------------------------------------------------------------------------------------------
IParticleEffect* GameSDKCGameEffect::LoadParticleEffect(const char* pParticleEffectName)
{
	IParticleEffect* pParticleEffect = NULL;
	IParticleManager* pParticleManager =  gEnv->pParticleManager;

	if(pParticleEffectName && pParticleManager)
	{
		pParticleEffect = gEnv->pParticleManager->FindEffect(pParticleEffectName);
		if(pParticleEffect)
		{
			pParticleEffect->AddRef();
		}
	}

	return pParticleEffect;
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: IsEntity3rdPerson
// Desc: Returns 3rd person state
//--------------------------------------------------------------------------------------------------
bool GameSDKCGameEffect::IsEntity3rdPerson(EntityId entityId)
{
	bool bIs3rdPerson = true;

	IGame* pGame = gEnv->pGame;
	if(pGame)
	{
		IGameFramework* pGameFramework = pGame->GetIGameFramework();
		if(pGameFramework)
		{
			EntityId clientEntityId = pGameFramework->GetClientActorId();
			if(clientEntityId == entityId)
			{
				bIs3rdPerson = pGameFramework->GetClientActor()->IsThirdPerson();
			}
		}
	}

	return bIs3rdPerson;
}//-------------------------------------------------------------------------------------------------
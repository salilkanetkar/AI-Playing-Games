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

#ifndef __STICKYPROJECTILE_H__
#define __STICKYPROJECTILE_H__

#if _MSC_VER > 1000
# pragma once
#endif

#include "Projectile.h"



class CStickyProjectile : public IEntityEventListener
{
public:

	static const NetworkAspectType ASPECT_STICK	= eEA_GameServerStatic;

	enum EStickFlags
	{
		eSF_IsStuck									= BIT(0),
		eSF_OrientateToCollNormal		= BIT(1),
		eSF_HandleLocally						= BIT(2),
		eSF_StuckToPlayer						= BIT(3),
		eSF_StuckToAI								= BIT(4),

		eSF_Reset										= (eSF_IsStuck|eSF_StuckToPlayer|eSF_StuckToAI)
	};
	typedef uint8 TFlags;

	enum EOrientation
	{
		eO_AlignToSurface = 0,
		eO_AlignToVelocity,
	};

	struct SStickParams
	{
		SStickParams(CProjectile* pProjectile, EventPhysCollision *pCollision, EOrientation orientation );
		SStickParams(CProjectile* pProjectile, const HitInfo& rHitInfo, EOrientation orientation );

		CProjectile* m_pProjectile;
		EntityId m_ownerId;
		IPhysicalEntity* m_pTarget;
		Vec3 m_stickPosition;
		Vec3 m_stickNormal;
		int m_targetPartId;
		int m_targetMatId;
		bool m_bStickToFriendlies; 
	};

public:
	CStickyProjectile(bool bOrientateToCollisionNormal, bool bHandleLocally = false);
	~CStickyProjectile();

	ILINE bool IsStuck() const { return (m_flags&eSF_IsStuck)!=0; }
	ILINE EntityId GetStuckEntityId() const { return m_parentId; }
	ILINE const Vec3& GetNormal() const { return m_stuckNormal; }
	bool IsStuckToPlayer() const;
	bool IsStuckToAI() const;
	ILINE int GetStuckJoint() const {return m_stuckJoint;}
	bool IsValid() const;

	void SwapToCorpse( const EntityId corpseId );

	void Reset();
	void Stick(const SStickParams& stickParams);
	void UnStick();
	void Serialize(TSerialize ser);
	void NetSerialize(CProjectile* pProjectile, TSerialize ser, EEntityAspects aspect);
	NetworkAspectType GetNetSerializeAspects();
	void NetSetStuck(CProjectile* pProjectile, bool stuck);

	// IEntityEventListener
	virtual void OnEntityEvent( IEntity *pEntity,SEntityEvent &event );
	//~IEntityEventListener

private:
	void AttachTo(CProjectile* pProjectile, IEntity * pTargetEntity);
	bool AttachToCharacter(CProjectile* pProjectile, IEntity& pEntity, ICharacterInstance& pCharacter, const char* boneName);
	void SetProjectilePhysics(CProjectile* pProjectile, EPhysicalizationType physics);
	void CalculateLocationForStick(const IEntity& projectile, const Vec3& collPos, const Vec3& collNormal, QuatT& outLocation) const;
	void SendHitInfo(const CProjectile* pProjectile, IEntity* pTargetEntity);

	bool StickToStatic( const SStickParams& stickParams );
	bool StickToEntity( const SStickParams& stickParams, IEntity* pTargetEntity );
	void SetParentId( const EntityId newParentId );

	uint32		m_characterAttachmentCrC;
	Vec3			m_stuckPos;
	Quat			m_stuckRot;
	Vec3			m_stuckNormal;
	EntityId	m_parentId;
	EntityId	m_childId;
	int				m_stuckJoint;
	int				m_stuckPartId;
	TFlags		m_flags;
};




#endif

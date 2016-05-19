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

#ifndef __TORNADO_H__
#define __TORNADO_H__
#pragma once

#include <IGameObject.h>

struct IGroundEffect;

namespace GameSDK
{
	class CFlowTornadoWander;

	class CTornado : public CGameObjectExtensionHelper<CTornado, IGameObjectExtension>
	{
	public:
		DECLARE_COMPONENT_TYPE("CTornado",0xB6B13D3DF2E44574,0xBA0BA77F5EEA5F2E)

		CTornado();
		virtual ~CTornado();

		// IGameObjectExtension
		virtual bool Init(IGameObject *pGameObject);
		virtual void InitClient (ChannelId channelId) {};
		virtual void PostInit(IGameObject *pGameObject);
		virtual void PostInitClient (ChannelId channelId) {};
		virtual bool ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params );
		virtual void PostReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params ) {}
		virtual bool GetEntityPoolSignature( TSerialize signature );
		//virtual void Release();
		virtual void FullSerialize( TSerialize ser );
		virtual bool NetSerialize( TSerialize ser, EEntityAspects aspect, uint8 profile, int flags );
		virtual void PostSerialize() {}
		virtual void SerializeSpawnInfo( TSerialize ser, IEntity * ) {}
		virtual ISerializableInfoPtr GetSpawnInfo() {return 0;}
		virtual void Update( SEntityUpdateContext &ctx, int updateSlot);
		virtual void PostUpdate(float frameTime ) {};
		virtual void PostRemoteSpawn() {};
		virtual void HandleEvent( const SGameObjectEvent &);
		virtual void ProcessEvent(SEntityEvent &);
		virtual void SetChannelId (ChannelId id) {}
		virtual void SetAuthority(bool auth);
		virtual void GetMemoryUsage(ICrySizer *pSizer) const;
	
		//~IGameObjectExtension

		void	SetTarget(IEntity *pTargetEntity, CFlowTornadoWander *pCallback);

		bool Reset();

	protected:

		bool	UseFunnelEffect(const char* effectName);
		void	UpdateParticleEmitters();
		void	UpdateTornadoSpline();
		void	UpdateFlow();
		void	OutputDistance();

	protected:
		static const NetworkAspectType POSITION_ASPECT = eEA_GameServerStatic;

		IPhysicalEntity*	m_pPhysicalEntity;

		// appearance of tornado
		IParticleEffect*	m_pFunnelEffect;
		IParticleEffect*	m_pCloudConnectEffect;
		IParticleEffect*	m_pTopEffect;
		IGroundEffect*		m_pGroundEffect;
		float							m_cloudHeight;
		bool							m_isOnWater;
		bool							m_isInAir;
		float							m_radius;
		int								m_curMatID;

		// spline
		Vec3							m_points[4];
		Vec3							m_oldPoints[4];

		// wandering
		Vec3							m_wanderDir;
		float							m_wanderSpeed;
		Vec3							m_currentPos;

		// target
		IEntity*						m_pTargetEntity;	// the tornado will try to reach this entity
		CFlowTornadoWander*	m_pTargetCallback;

		//
		float m_nextEntitiesCheck;

		float m_spinImpulse;
		float m_attractionImpulse;
		float m_upImpulse;

		std::vector<int> m_spinningEnts;
	};

	DECLARE_COMPONENT_POINTERS(CTornado)
}

#endif //__TORNADO_H__

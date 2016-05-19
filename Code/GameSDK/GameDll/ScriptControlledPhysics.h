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

// Description : Script Interface for controlling physics.
//               Neccessary when changing physics positions and velocities
//               while keeping visual physics in sync...


#ifndef __SCRIPTCONTROLLEDPHYSICS_H__
#define __SCRIPTCONTROLLEDPHYSICS_H__

#if _MSC_VER > 1000
# pragma once
#endif


#include "IGameObject.h"


class CScriptControlledPhysics: public CGameObjectExtensionHelper<CScriptControlledPhysics, IGameObjectExtension>,
	CScriptableBase
{
public:

	DECLARE_COMPONENT_TYPE("CScriptControlledPhysics",0xD89659D45606450C,0x87A0F9998E3E4AF1)
	CScriptControlledPhysics();
	virtual ~CScriptControlledPhysics();

	virtual void GetMemoryUsage(ICrySizer *pSizer) const;

	// IGameObjectExtension
	virtual bool Init( IGameObject * pGameObject );
	using CScriptableBase::Init;

	virtual void InitClient (ChannelId channelId) {};
	virtual void PostInit( IGameObject * pGameObject );
	virtual void PostInitClient (ChannelId channelId) {};
	virtual bool ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params );
	virtual void PostReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params ) {}
	virtual bool GetEntityPoolSignature( TSerialize signature );
	//virtual void Release();
	virtual void FullSerialize( TSerialize ser );
	virtual bool NetSerialize( TSerialize ser, EEntityAspects aspect, uint8 profile, int flags ) { return true; }
	virtual void PostSerialize() {}
	virtual void SerializeSpawnInfo( TSerialize ser, IEntity *) {}
	virtual ISerializableInfoPtr GetSpawnInfo() {return 0;}
	virtual void Update( SEntityUpdateContext& ctx, int slot ) {};
	virtual void HandleEvent( const SGameObjectEvent& );
	virtual void ProcessEvent(SEntityEvent& ) {};
	virtual void SetChannelId (ChannelId id) {};
	virtual void SetAuthority(bool auth) {}
	virtual void PostUpdate(float frameTime) { assert(false); }
	virtual void PostRemoteSpawn() {};

	//~IGameObjectExtension
	int Reset(IFunctionHandler *pH);
	int GetSpeed(IFunctionHandler *pH);
	int GetAcceleration(IFunctionHandler *pH);

	int GetAngularSpeed(IFunctionHandler *pH);
	int GetAngularAcceleration(IFunctionHandler *pH);

	int MoveTo(IFunctionHandler *pH, Vec3 point, float initialSpeed, float speed, float acceleration, float stopTime);
	int RotateTo(IFunctionHandler *pH, Vec3 dir, float roll, float initialSpeed, float speed, float acceleration, float stopSpeed);
	int RotateToAngles(IFunctionHandler *pH, Vec3 angles, float initialSpeed, float speed, float acceleration, float stopSpeed);

	int HasArrived(IFunctionHandler *pH);

	void OnPostStep(EventPhysPostStep *pPostStep);
private:
	void RegisterGlobals();
	void RegisterMethods();

	bool m_moving;
	Vec3  m_moveTarget;
	Vec3	m_lastVelocity;
	float m_speed;
	float m_maxSpeed;
	float m_acceleration;
	float m_stopTime;

	bool m_rotating;
	Quat m_rotationTarget;
	float m_rotationSpeed;
	float m_rotationMaxSpeed;
	float m_rotationAcceleration;
	float m_rotationStopTime;
};

DECLARE_COMPONENT_POINTERS(CScriptControlledPhysics)


#endif //__SCRIPTCONTROLLEDPHYSICS_H__

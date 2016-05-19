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

// Description : ProceduralContext for the ProceduralClipRagdoll from CryMannequin


#pragma once

#ifndef __ProceduralContextRagdoll_h__
#define __ProceduralContextRagdoll_h__

#include <ICryMannequin.h>

#include <ICryAnimation.h>
#include <IAnimationPoseModifier.h>

#include <CryExtension/CryCreateClassInstance.h>
#include <CryExtension/Impl/ClassWeaver.h>
#include <CryExtension/Impl/ICryFactoryRegistryImpl.h>
#include <CryExtension/Impl/RegFactoryNode.h>


#define PROCEDURAL_CONTEXT_RAGDOLL_NAME "ProceduralContextRagdoll"

class CProceduralContextRagdoll
	: public IProceduralContext
{
public:
	PROCEDURAL_CONTEXT( CProceduralContextRagdoll, PROCEDURAL_CONTEXT_RAGDOLL_NAME, 0x37856d62bd5f42f0, 0xad8a4314a0de6dd2 );

	ILINE EntityId GetEntityTarget() const { return m_targetEntityId; }
	ILINE void SetEntityTarget( const EntityId entityID ) { m_targetEntityId = entityID; }
	ILINE void SetAspectProfileScope( bool bScope ) { m_bDispatchedAspectProfile = bScope; }
	ILINE bool GetAspectProfileScope() const { return m_bDispatchedAspectProfile; }
	ILINE bool IsInRagdoll() const{ return m_bInRagdoll; }
	ILINE void SetBlendOut( float blendOutTime )
	{
		m_blendOutTime = blendOutTime;
		m_bInBlendOut = true;
	}
	void EnableRagdoll( const EntityId entityID, const bool bAlive, const float stiffness, const bool bFromProcClip = false );
	void DisableRagdoll( float blendOutTime );
	void QueueRagdoll( bool bAlive );
	void ForceRagdollFinish(IActor* piActor, bool bForceDead);

protected:
	// IProceduralContext
	virtual void Update( float timePassedSeconds );
	// ~IProceduralContext

	void Reset();

private:
	EntityId m_targetEntityId;
	float m_stiffness;
	float m_blendOutTime;
	float m_blendOutTimeCurrent;
	bool m_bInRagdoll;
	bool m_bInBlendOut;
	bool m_bEntityAlive;
	bool m_bDispatchedAspectProfile;
	bool m_bForceRagdollFinish;
	bool m_bFromProcClip;
};

#endif //__ProceduralContextRagdoll_h__
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

#ifndef __PROCEDURAL_CONTEXT_LOOK__H__
#define __PROCEDURAL_CONTEXT_LOOK__H__

#include <ICryMannequin.h>

#include <ICryAnimation.h>
#include <IAnimationPoseModifier.h>

#include <CryExtension/CryCreateClassInstance.h>
#include <CryExtension/Impl/ClassWeaver.h>
#include <CryExtension/Impl/ICryFactoryRegistryImpl.h>
#include <CryExtension/Impl/RegFactoryNode.h>


#define PROCEDURAL_CONTEXT_LOOK_NAME "ProceduralContextLook"

class CProceduralContextLook
	: public IProceduralContext
{
public:
	PROCEDURAL_CONTEXT( CProceduralContextLook, PROCEDURAL_CONTEXT_LOOK_NAME, 0x0928592BD91648A5, 0x9024C8221945BB17 );

	// IProceduralContext
	virtual void Initialise( IEntity& entity, IActionController& actionController );
	virtual void Update( float timePassedSeconds );
	// ~IProceduralContext

	void UpdateGameLookingRequest( const bool lookRequest );
	void UpdateProcClipLookingRequest( const bool lookRequest );

	void UpdateGameLookTarget( const Vec3& lookTarget );

	void SetBlendInTime( const float blendInTime );
	void SetBlendOutTime( const float blendOutTime );
	void SetFovRadians( const float fovRadians );

private:
	void InitialisePoseBlenderLook();
	void InitialiseGameLookTarget();

private:
	IAnimationPoseBlenderDir* m_pPoseBlenderLook;

	bool m_gameRequestsLooking;
	bool m_procClipRequestsLooking;
	Vec3 m_gameLookTarget;
};


#endif

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

#ifndef __PROCEDURAL_CONTEXT_COLLIDER_MODE__H__
#define __PROCEDURAL_CONTEXT_COLLIDER_MODE__H__

#include <ICryMannequin.h>

#include <CryExtension/CryCreateClassInstance.h>
#include <CryExtension/Impl/ClassWeaver.h>
#include <CryExtension/Impl/ICryFactoryRegistryImpl.h>
#include <CryExtension/Impl/RegFactoryNode.h>

#include <IAnimatedCharacter.h>

#include "ProceduralContextHelpers.h"


#define PROCEDURAL_CONTEXT_COLLIDER_MODE_NAME "ProceduralContextColliderMode"


class CProceduralContextColliderMode
	: public IProceduralContext
{
public:
	PROCEDURAL_CONTEXT( CProceduralContextColliderMode, PROCEDURAL_CONTEXT_COLLIDER_MODE_NAME, 0x2857e483964b45e4, 0x8e9e6a481db8c166 );

	// IProceduralContext
	virtual void Update( float timePassedSeconds );
	// ~IProceduralContext

	uint32 RequestColliderMode( const EColliderMode colliderMode );
	void CancelRequest( const uint32 requestId );

private:
	IAnimatedCharacter* GetAnimatedCharacter() const;

private:
	struct SColliderModeRequest
	{
		uint32 id;
		EColliderMode mode;
	};

	typedef ProceduralContextHelpers::CRequestList< SColliderModeRequest > TColliderModeRequestList;
	TColliderModeRequestList m_requestList;
};


#endif

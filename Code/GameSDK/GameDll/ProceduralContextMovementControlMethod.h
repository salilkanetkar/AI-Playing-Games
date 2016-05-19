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

#ifndef __PROCEDURAL_CONTEXT_MOVEMENT_CONTROL_METHOD__H__
#define __PROCEDURAL_CONTEXT_MOVEMENT_CONTROL_METHOD__H__

#include <ICryMannequin.h>

#include <CryExtension/CryCreateClassInstance.h>
#include <CryExtension/Impl/ClassWeaver.h>
#include <CryExtension/Impl/ICryFactoryRegistryImpl.h>
#include <CryExtension/Impl/RegFactoryNode.h>

#include <IAnimatedCharacter.h>

#include "ProceduralContextHelpers.h"


#define PROCEDURAL_CONTEXT_MOVEMENT_CONTROL_METHOD_NAME "ProceduralContextMCM"


class CProceduralContextMovementControlMethod
	: public IProceduralContext
{
public:
	PROCEDURAL_CONTEXT( CProceduralContextMovementControlMethod, PROCEDURAL_CONTEXT_MOVEMENT_CONTROL_METHOD_NAME, 0x80140507bdc64be4, 0xa24190f322270e82 );

	// IProceduralContext
	virtual void Update( float timePassedSeconds );
	// ~IProceduralContext

	uint32 RequestMovementControlMethod( const EMovementControlMethod horizontal, const EMovementControlMethod vertical );
	void CancelRequest( const uint32 requestId );

private:
	IAnimatedCharacter* GetAnimatedCharacter() const;

private:
	struct SMCMRequest
	{
		uint32 id;
		EMovementControlMethod horizontal;
		EMovementControlMethod vertical;
	};

	typedef ProceduralContextHelpers::CRequestList< SMCMRequest > TMCMRequestList;
	TMCMRequestList m_requestList;
};


#endif

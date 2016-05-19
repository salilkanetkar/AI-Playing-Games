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

#include "ICryMannequin.h"
#include <ICryAnimation.h>
#include <IAnimationPoseModifier.h>
#include <CryExtension/Impl/ClassWeaver.h>
#include "Serialization/IArchive.h"

#include "ProceduralContextAim.h"


struct SAimSmoothingParams 
	: public IProceduralParams
{
	SAimSmoothingParams()
		: smoothTimeSeconds(0.1f)
		, maxYawDegreesPerSecond(360.0f)
		, maxPitchDegreesPerSecond(360.0f)
	{
	}

	virtual void Serialize(Serialization::IArchive& ar)
	{
		ar(smoothTimeSeconds, "SmoothTimeSeconds", "Smooth Time Seconds");
		ar(maxYawDegreesPerSecond, "MaxYawDegreesPerSecond", "Max Yaw Degrees Per Second");
		ar(maxPitchDegreesPerSecond, "MaxPitchDegreesPerSecond", "Max Pitch Degrees Per Second");
	}

	float smoothTimeSeconds;
	float maxYawDegreesPerSecond;
	float maxPitchDegreesPerSecond;
};

class CProceduralClipAimSmoothing
	: public TProceduralContextualClip<CProceduralContextAim, SAimSmoothingParams>
{
public:
	CProceduralClipAimSmoothing()
		: m_requestId( 0 )
	{
	}
	
	virtual void OnEnter( float blendTime, float duration, const SAimSmoothingParams& params )
	{
		m_requestId = m_context->RequestPolarCoordinatesSmoothingParameters( Vec2( DEG2RAD( params.maxYawDegreesPerSecond ), DEG2RAD( params.maxPitchDegreesPerSecond ) ), params.smoothTimeSeconds );
	}

	virtual void OnExit( float blendTime )
	{
		m_context->CancelPolarCoordinatesSmoothingParameters( m_requestId );
	}

	virtual void Update( float timePassed )
	{
	}

private:
	uint32 m_requestId;
};

REGISTER_PROCEDURAL_CLIP(CProceduralClipAimSmoothing, "AimSmoothing");
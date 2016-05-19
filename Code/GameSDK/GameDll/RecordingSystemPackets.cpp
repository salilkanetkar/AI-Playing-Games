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
#include "RecordingSystemPackets.h"
#include "RecordingSystem.h"
#include "Utility/BufferUtil.h"

void SRecording_FrameData::Serialise( CBufferUtil &buffer )
{
	size = sizeof(SRecording_FrameData);

	buffer.Serialise(frametime);
}

void SRecording_FPChar::Serialise( CBufferUtil &buffer )
{
	size = sizeof(SRecording_FPChar);

	buffer.Serialise(camlocation);
	buffer.Serialise(relativePosition);
	buffer.Serialise(fov);
	buffer.Serialise(frametime);
	buffer.Serialise(playerFlags);
}

void SRecording_Flashed::Serialise( CBufferUtil &buffer )
{
	size = sizeof(SRecording_Flashed);

	buffer.Serialise(frametime);
	buffer.Serialise(duration);
	buffer.Serialise(blindAmount);
}

void SRecording_RenderNearest::Serialise( CBufferUtil &buffer )
{
	size = sizeof(SRecording_RenderNearest);

	buffer.Serialise(frametime);
	buffer.Serialise(renderNearest);
}

void SRecording_VictimPosition::Serialise( CBufferUtil &buffer )
{
	size = sizeof(SRecording_VictimPosition);

	buffer.Serialise(frametime);
	buffer.Serialise(victimPosition);
}

void SRecording_KillHitPosition::Serialise( CBufferUtil &buffer )
{
	size = sizeof(SRecording_KillHitPosition);

	buffer.Serialise(hitRelativePos);
	buffer.Serialise(victimId);
	buffer.Serialise(fRemoteKillTime);
}

void SRecording_PlayerHealthEffect::Serialise( CBufferUtil &buffer )
{
	size = sizeof(SRecording_PlayerHealthEffect);

	buffer.Serialise(hitDirection);
	buffer.Serialise(frametime);
	buffer.Serialise(hitStrength);
	buffer.Serialise(hitSpeed);
}

void SRecording_PlaybackTimeOffset::Serialise( CBufferUtil &buffer )
{
	size = sizeof(SRecording_PlaybackTimeOffset);

	buffer.Serialise(timeOffset);
}


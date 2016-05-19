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

#ifndef __RECORDINGSYSTEMDEBUG_H__
#define __RECORDINGSYSTEMDEBUG_H__
#include "RecordingSystemDefines.h"

#ifdef RECSYS_DEBUG


class CRecordingSystemDebug : public IRecordingSystemListener
{
public:
	CRecordingSystemDebug(CRecordingSystem& system);
	virtual ~CRecordingSystemDebug();

	//IRecordingSystemListener
	virtual void OnPlaybackRequested( const SPlaybackRequest& info ) {}
	virtual void OnPlaybackStarted( const SPlaybackInfo& info ) {}
	virtual void OnPlaybackEnd( const SPlaybackInfo& info ) {}
	//~IRecordingSystemListener

	void PrintFirstPersonPacketData ( const SRecording_Packet& packet ) const;
	void PrintThirdPersonPacketData ( const SRecording_Packet& packet, float& frameTime ) const;
	void PrintFirstPersonPacketData ( uint8* data, size_t size, const char* const msg ) const;
	void PrintThirdPersonPacketData ( uint8* data, size_t size, const char* const msg ) const;
	void PrintFirstPersonPacketData ( CRecordingBuffer& buffer, const char* const msg ) const;
	void PrintThirdPersonPacketData ( CRecordingBuffer& buffer, const char* const msg ) const;

private:
	CRecordingSystem& m_system;
};


#endif //RECSYS_DEBUG
#endif // __RECORDINGSYSTEMDEBUG_H__
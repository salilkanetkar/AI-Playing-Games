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

#ifndef __RECORDINGSYSTEMSERVERFORWARDER_H__
#define __RECORDINGSYSTEMSERVERFORWARDER_H__

#include "RecordingSystemCircularBuffer.h"

#define KILLCAM_FORWARDING_BUFFER_SIZE	(16*1024)

class CServerKillCamForwarder
{
	typedef CCircularBuffer<KILLCAM_FORWARDING_BUFFER_SIZE> BufferType;
	struct SForwardingPacket;

public:
	void Reset();
	void ReceivePacket(IActor *pActor, const CActor::KillCamFPData &packet);
	void Update();
	void GetMemoryUsage(ICrySizer *pSizer) const
	{
		pSizer->AddContainer(m_forwarding);
	}

private:
	void ForwardPacket(SForwardingPacket &forward, CActor::KillCamFPData *pPacket);
	void DropOldestPacket();
	void AddDataAndErase(const void *data, size_t size);
	void GetFirstPacket(BufferType::iterator &first, IActor *pActor, int packetId);
	CActor::KillCamFPData* FindPacket(BufferType::iterator &it, IActor *pActor, int packetId);
	
	struct SForwardingPacket
	{
		SForwardingPacket() { m_sent=0; }
		EntityId victim;
		IActor *pActor;
		int packetID;
		int m_sent;
		int m_numPackets;
		CTimeValue m_lastPacketTime;
		BufferType::iterator iterator;
	};

	std::deque<SForwardingPacket> m_forwarding;
	BufferType m_history;
};

#endif // __RECORDINGSYSTEMSERVERFORWARDER_H__
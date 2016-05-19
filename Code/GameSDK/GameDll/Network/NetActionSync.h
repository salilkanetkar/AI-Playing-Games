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

// Description : Helper template to provide correct action synchronization
//               for actors and vehicles

#ifndef __NETACTIONSYNC_H__
#define __NETACTIONSYNC_H__

#pragma once

#ifdef __GNUC__
// GCC requires a full decl of TSerialize, not just a fwd decl.
#include <ISerialize.h>
#endif

template <class ActionRep>
class CNetActionSync
{
public:
	CNetActionSync() : m_havePublished(false), m_lastReceived(0), m_lastCancelation(1) {}

	static const NetworkAspectType CONTROLLED_ASPECT = ActionRep::CONTROLLED_ASPECT;

	// publish current state of actions - returns true if net-sync required
	bool PublishActions( ActionRep rep )
	{
		bool changed = false;
		if (m_lastReceived > m_lastCancelation)
		{
			rep = m_received;
		}
		if (!m_havePublished || m_published != rep)
		{
			m_published = rep;
			changed = true;
		}
		m_havePublished = true;
		return changed;
	}
	void Serialize( TSerialize ser, EEntityAspects aspects )
	{
		// ensure CONTROLLED_ASPECT only has one bit set
		CRY_ASSERT((CONTROLLED_ASPECT & (CONTROLLED_ASPECT-1)) == 0);
		if ((aspects & CONTROLLED_ASPECT) == 0)
			return;
		if (ser.IsReading())
		{
			m_received.Serialize(ser, aspects);
			m_lastReceived = gEnv->pRenderer->GetFrameID();
		}
		else // writing
		{
			CRY_ASSERT(m_havePublished);
			m_published.Serialize(ser, aspects);
		}
	}
	void CancelReceived()
	{
		m_lastCancelation = gEnv->pRenderer->GetFrameID();
	}
	void UpdateObject( typename ActionRep::UpdateObjectSink obj )
	{
		if (m_lastReceived > m_lastCancelation)
			m_received.UpdateObject( obj );
	}

private:
	ActionRep m_published;
	ActionRep m_received;
	bool m_havePublished;
	uint32 m_lastCancelation;
	uint32 m_lastReceived;
};

#endif

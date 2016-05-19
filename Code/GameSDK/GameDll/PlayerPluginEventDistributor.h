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

#include "EventDistributor.h"
#include "PlayerPlugin.h"

#ifndef __PLAYER_PLUGIN_EVENT_DISTRIBUTOR_H__
#define __PLAYER_PLUGIN_EVENT_DISTRIBUTOR_H__

class CPlayerPluginEventDistributor: public CEventDistributor<CPlayerPlugin, EPlayerPlugInEvent, uint64>
{
public:
	void HandleEvent(EPlayerPlugInEvent theEvent, void * data)
	{
#if !defined(_RELEASE)
		const size_t previousSize = m_pReceivers.size();
		CRY_ASSERT(m_pReceivers.size() == m_flags.size());
		m_debugSendingEvents = true;	//base call will assert if register or unregister happens during handleEvent
#endif //#if !defined(_RELEASE)
		
		if( !m_flags.empty() )
		{
			PrefetchLine(&m_flags[0], 0);
			PrefetchLine(&m_pReceivers[0], 0);

			const size_t size = m_flags.size();

			PrefetchLine(&m_flags[size-1], 0);
			PrefetchLine(&m_pReceivers[size-1], 0);

			uint64 flag = EventTypeToFlag(theEvent);

			for(size_t i = 0; i < size; i++)
			{
				if(IsFlagSet(m_flags[i], flag))
				{
					m_pReceivers[i]->HandleEvent(theEvent, data);
				}
			}
		}

		//Assert if unregister (or register) happens during HandleEvent
#if !defined(_RELEASE)
		CRY_ASSERT(previousSize == m_pReceivers.size());
		CRY_ASSERT(m_pReceivers.size() == m_flags.size());
		m_debugSendingEvents = false;
#endif //#if !defined(_RELEASE)
	}
};

#endif //#ifndef __PLAYER_PLUGIN_EVENT_DISTRIBUTOR_H__
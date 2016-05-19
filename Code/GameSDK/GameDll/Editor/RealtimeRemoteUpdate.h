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

// Description : This is the header file for the module Realtime remote
//               update  The purpose of this module is to allow data update to happen
//               remotely so that you can  for example  edit the terrain and see the changes
//               in the console


#ifndef RealtimeRemoteUpdate_h__
#define RealtimeRemoteUpdate_h__

#pragma once

#include "INotificationNetwork.h"
#include "IRealtimeRemoteUpdate.h"

class CRealtimeRemoteUpdateListener:public INotificationNetworkListener,public IRealtimeRemoteUpdate
{
	//////////////////////////////////////////////////////////////////////////
	// Types & typedefs.
	public:
	protected:
	private:
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Methods
	public:
		// From IRealtimeRemoteUpdate
		bool	Enable(bool boEnable=true);
		bool	IsEnabled();

		// From INotificationNetworkListener and from IRealtimeRemoteUpdate
		void	OnNotificationNetworkReceive(const void *pBuffer, size_t length);

		// Singleton management
		static CRealtimeRemoteUpdateListener&	GetRealtimeRemoteUpdateListener();
protected:
		CRealtimeRemoteUpdateListener();
		virtual ~CRealtimeRemoteUpdateListener();

		void	LoadArchetypes(XmlNodeRef &root);
		void  LoadEntities( XmlNodeRef &root );
		void  LoadTimeOfDay( XmlNodeRef &root );
		void  LoadMaterials( XmlNodeRef &root );

		void  LoadConsoleVariables(XmlNodeRef &root );

		void  LoadParticles(XmlNodeRef &root );

		void  LoadTerrainLayer(XmlNodeRef &root, unsigned char*	uchData);
	private:
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Data
	public:
	protected:
		// As currently you can't query if the currently listener is registered
		// the control has to be done here.
		bool m_boIsEnabled;

		int  m_nPreviousFlyMode;
		bool m_boIsSyncingCamera;
	private:
	//////////////////////////////////////////////////////////////////////////
};

#endif // RealtimeRemoteUpdate_h__

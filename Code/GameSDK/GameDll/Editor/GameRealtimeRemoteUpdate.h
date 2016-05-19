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

// Description : This is the header file for the game module specific Realtime remote update.
//               The purpose of this module is to allow data update to happen remotely inside
//               the game layer so that you can  for example  edit the terrain and see
//               the changes in the console


#ifndef GameRealtimeRemoteUpdate_h__
#define GameRealtimeRemoteUpdate_h__

#pragma once

#include "IRealtimeRemoteUpdate.h"

class CGameRealtimeRemoteUpdateListener : public IRealtimeUpdateGameHandler
{
protected:
	CGameRealtimeRemoteUpdateListener();
	virtual ~CGameRealtimeRemoteUpdateListener();

public:
	static CGameRealtimeRemoteUpdateListener& GetGameRealtimeRemoteUpdateListener();
	bool Enable(bool boEnable);

	bool Update();
protected:
	
	virtual bool UpdateGameData(XmlNodeRef oXmlNode, unsigned char * auchBinaryData);
	virtual void UpdateCamera(XmlNodeRef oXmlNode);
	virtual void CloseLevel();
	virtual void CameraSync();
	virtual void EndCameraSync();
private:
	bool m_bCameraSync;
	int  m_nPreviousFlyMode;
	Vec3 m_Position;
	Vec3 m_ViewDirection;
	Vec3 m_headPositionDelta;


	XmlNodeRef	m_CameraUpdateInfo;
};

#endif //GameRealtimeRemoteUpdate_h__


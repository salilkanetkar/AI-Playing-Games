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

// Description : Central storage and processing of all gamecode client side
//               monitoring


#ifndef ___CLIENT_CHEAT_MONITOR_H___
#define ___CLIENT_CHEAT_MONITOR_H___

#include "AntiCheat/AnticheatDefines.h"
#include "Utility/MaskedVar.h"


#if CLIENT_CHEAT_MONITOR_ENABLED
#include <IGameFramework.h>


class CClientCheatMonitor : public IGameFrameworkListener
{
public:
	CClientCheatMonitor();
	~CClientCheatMonitor();
		
					void	Init(IGameFramework *pFramework);
					 
	// IGameFrameworkListener
	virtual void	OnPostUpdate(float fDeltaTime);
	virtual void	OnSaveGame(ISaveGame* pSaveGame);
	virtual void	OnLoadGame(ILoadGame* pLoadGame);
	virtual void	OnLevelEnd(const char* nextLevel);
	virtual void	OnActionEvent(const SActionEvent& event);
	// ~IGameFrameworkListener

	void UploadTelemetry();
	
private:
	IGameFramework* m_pFramework;
};
#else
class CClientCheatMonitor
{
public:
	ILINE void UploadTelemetry() {}
};
#endif //CLIENT_CHEAT_MONITOR_ENABLED
#endif // ___CLIENT_CHEAT_MONITOR_H___

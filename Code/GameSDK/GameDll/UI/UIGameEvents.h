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

#ifndef __UIGameEvents_H__
#define __UIGameEvents_H__

#include "IUIGameEventSystem.h"
#include <IFlashUI.h>
#include <ILevelSystem.h>

class CUIGameEvents 
	: public IUIGameEventSystem
{
public:
	CUIGameEvents();

	// IUIGameEventSystem
	UIEVENTSYSTEM( "UIGameEvents" );
	virtual void InitEventSystem();
	virtual void UnloadEventSystem();

private:
	// UI events
	void OnLoadLevel( const char* mapname, bool isServer, const char* gamerules );
	void OnReloadLevel();
	void OnSaveGame( bool shouldResume );
	void OnLoadGame( bool shouldResume );
	void OnPauseGame();
	void OnResumeGame();
	void OnExitGame();
	void OnStartGame();

private:
	IUIEventSystem* m_pUIEvents;
	SUIEventReceiverDispatcher<CUIGameEvents> m_eventDispatcher;

	IGameFramework* m_pGameFramework;
	ILevelSystem* m_pLevelSystem;
};


#endif // __UIGameEvents_H__

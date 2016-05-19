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

#ifndef __UIMenuEvents_H__
#define __UIMenuEvents_H__

#include "IUIGameEventSystem.h"
#include <IFlashUI.h>
#include <IGameFramework.h>

class CUIMenuEvents
	: public IUIGameEventSystem
	, public IUIModule
{
public:
	CUIMenuEvents();

	// IUIGameEventSystem
	UIEVENTSYSTEM( "UIMenuEvents" );
	virtual void InitEventSystem();
	virtual void UnloadEventSystem();

	//IUIModule
	virtual void Reset();

	void DisplayIngameMenu(bool bDisplay);
	bool IsIngameMenuStarted() const { return m_bIsIngameMenuStarted; }

private:
	void StartIngameMenu();
	void StopIngameMenu();

private:
	enum EUIEvent
	{
		eUIE_StartIngameMenu,
		eUIE_StopIngameMenu,
	};

	SUIEventReceiverDispatcher<CUIMenuEvents> m_eventDispatcher;
	SUIEventSenderDispatcher<EUIEvent> m_eventSender;
	IUIEventSystem* m_pUIEvents;
	IUIEventSystem* m_pUIFunctions;

	bool m_bIsIngameMenuStarted;
};


#endif // __UISettings_H__
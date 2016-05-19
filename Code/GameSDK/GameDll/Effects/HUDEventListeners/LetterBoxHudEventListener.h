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

#ifndef _LETTER_BOX_HUD_EVENT_LISTENER_
#define _LETTER_BOX_HUD_EVENT_LISTENER_

#pragma once

// Includes
#include "UI/HUD/HUDEventDispatcher.h"

//==================================================================================================
// Name: SLetterBoxParams
// Desc: Parameters for CLetterBoxHudEventListener
// Author: James Chilvers
//==================================================================================================
struct SLetterBoxParams
{
	SLetterBoxParams()
	{
		color.set(0.0f,0.0f,0.0f,1.0f);
		scale = 0.11f;
	}

	ColorF color;
	float scale;
};//------------------------------------------------------------------------------------------------

//==================================================================================================
// Name: CLetterBoxHudEventListener
// Desc: Renders Letter box bars
// Author: James Chilvers
//==================================================================================================
class CLetterBoxHudEventListener : public IHUDEventListener
{
public:
	CLetterBoxHudEventListener() {}
	SC_API virtual ~CLetterBoxHudEventListener();

	SC_API void Initialise(const SLetterBoxParams* params);

	SC_API void Register();
	SC_API void UnRegister();

	SC_API virtual void OnHUDEvent(const SHUDEvent& event);

private:

	void Draw();

	SLetterBoxParams	m_params;

};//------------------------------------------------------------------------------------------------

#endif // _LETTER_BOX_HUD_EVENT_LISTENER_

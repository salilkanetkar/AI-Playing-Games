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

// Description : Renders Letter box bars


#include "StdAfx.h"
#include "LetterBoxHudEventListener.h"
#include "UI/UIManager.h"
#include "Graphics/2DRenderUtils.h"
#include "UI/Utils/ScreenLayoutManager.h"

//--------------------------------------------------------------------------------------------------
// Name: ~CLetterBoxHudEventListener
// Desc: Destructor
//--------------------------------------------------------------------------------------------------
CLetterBoxHudEventListener::~CLetterBoxHudEventListener()
{
	UnRegister();
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: Initialise
// Desc: Initializes HUD event listener
//--------------------------------------------------------------------------------------------------
void CLetterBoxHudEventListener::Initialise(const SLetterBoxParams* params)
{
	if(params)
	{
		m_params = *params;
	}
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: Register
// Desc: Registers HUD event listener with HUD
//--------------------------------------------------------------------------------------------------
void CLetterBoxHudEventListener::Register()
{
	CHUDEventDispatcher::AddHUDEventListener(this, "OnPostHUDDraw");
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: UnRegister
// Desc: UnRegisters HUD event listener with HUD
//--------------------------------------------------------------------------------------------------
void CLetterBoxHudEventListener::UnRegister()
{
	CHUDEventDispatcher::RemoveHUDEventListener(this);
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: OnHUDEvent
// Desc: Called on the event this listener is registered with
//--------------------------------------------------------------------------------------------------
void CLetterBoxHudEventListener::OnHUDEvent(const SHUDEvent& event)
{
	switch(event.eventType)
	{
		case eHUDEvent_OnPostHUDDraw:
		{
			Draw();
			break;
		}
	}
}//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Name: Draw
// Desc: Draws HUD item
//--------------------------------------------------------------------------------------------------
void CLetterBoxHudEventListener::Draw()
{
	C2DRenderUtils* pRenderUtils = g_pGame->GetUI()->Get2DRenderUtils();
	ScreenLayoutManager* pLayoutManager = g_pGame->GetUI()->GetLayoutManager();

	ScreenLayoutStates prevLayoutState = pLayoutManager->GetState();
	pLayoutManager->SetState(eSLO_DoNotAdaptToSafeArea|eSLO_ScaleMethod_None);

	gEnv->pRenderer->SetState(GS_NODEPTHTEST);

	// Apply overscan borders to bars
	Vec2 overscanBorders = Vec2(0.0f,0.0f);
	gEnv->pRenderer->EF_Query(EFQ_OverscanBorders, overscanBorders);
	const float overscanBorderHeight = overscanBorders.y * VIRTUAL_SCREEN_HEIGHT;
	float barHeight = (VIRTUAL_SCREEN_HEIGHT * m_params.scale * (1.0f - overscanBorders.y)) + overscanBorderHeight; 

	pRenderUtils->DrawQuad(0, 0, VIRTUAL_SCREEN_WIDTH, barHeight, m_params.color);
	pRenderUtils->DrawQuad(0, VIRTUAL_SCREEN_HEIGHT - barHeight, VIRTUAL_SCREEN_WIDTH, barHeight, m_params.color);

	pLayoutManager->SetState(prevLayoutState);
}//-------------------------------------------------------------------------------------------------

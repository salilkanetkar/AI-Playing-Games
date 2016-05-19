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

#pragma once

#ifndef SCREEN_FADER_H
#define SCREEN_FADER_H

#include "EngineFacade/Renderer.h"

namespace EngineFacade
{
	struct IEngineFacade;
}

namespace Graphics
{
	class CScreenFader
	{
	public:
		CScreenFader(EngineFacade::IEngineFacade& engineFacade);

		void FadeIn(const string& texturePath, const ColorF& targetColor, float fadeTime, bool useCurrentColor);
		void FadeOut(const string& texturePath, const ColorF& targetColor, float fadeTime, bool useCurrentColor);

		bool IsFadingIn() const;
		bool IsFadingOut() const;

		void Update(float frameTime);
		void Reset();

	protected:

		void Render();
		void SetTexture(const string& textureName);
		ColorF GetDrawColor() const;
		bool ShouldUpdate() const;

	private:

		ColorF         m_currentColor;
		ColorF         m_targetColor;
		
		float          m_fadeTime;
		float          m_currentTime;
		
		bool	m_fadingIn;
		bool	m_fadingOut;					

		EngineFacade::IEngineFacade& m_engineFacade;
		EngineFacade::IEngineTexture::Ptr m_texture;
	};
}

#endif
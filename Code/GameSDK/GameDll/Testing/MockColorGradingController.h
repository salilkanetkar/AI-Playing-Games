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

#ifndef MOCK_COLOR_GRADING_CONTROLLER_H_INCLUDED
#define MOCK_COLOR_GRADING_CONTROLLER_H_INCLUDED

#include "EngineFacade/3DEngine.h"

namespace GameTesting
{
	class CMockEngineColorGradingController : public EngineFacade::CNullEngineColorGradingController
	{
	public:
		CMockEngineColorGradingController();

		virtual int LoadColorChart(const char* colorChartFilePath) const;

		virtual void UnloadColorChart(int textureID) const;

		void SetLayers(const SColorChartLayer* layers, uint32 numLayers);

		bool AnyChartsWereLoaded() const;

		int GetLastUnloadedTextureID() const;

		void ClearLoadedCharts();

		const string& GetPathOfLastLoadedColorChart() const;

		const string& GetPathOfLoadedColorChart(const unsigned int index) const;

		bool LayersHaveBeenSet() const;

		uint32 GetLayerCount() const;

		size_t GetNumberOfLayersSet() const;

		const SColorChartLayer& GetCurrentlySetLayerByIndex(const uint32 index) const;

		void SetFakeIDForLoadedTexture(const int id);

		bool WasNullPointerSetOnLayers() const;

	private:
		mutable std::vector<string> m_loadedChartsPaths;
		bool m_wasNullPointerSetOnLayers;
		std::vector<SColorChartLayer> m_currentLayers;
		int m_fakeIDForLoadedTexture;
		mutable int m_lastUnloadedTextureID;
	};
}

#endif

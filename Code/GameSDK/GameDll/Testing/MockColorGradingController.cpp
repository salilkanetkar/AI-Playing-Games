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

#include "StdAfx.h"

#include "MockColorGradingController.h"

#include "IColorGradingController.h"

namespace GameTesting
{
	CMockEngineColorGradingController::CMockEngineColorGradingController() : m_wasNullPointerSetOnLayers(false)
		, m_fakeIDForLoadedTexture(0)
		, m_lastUnloadedTextureID(-1)
	{

	}

	int CMockEngineColorGradingController::LoadColorChart( const char* colorChartFilePath ) const
	{
		m_loadedChartsPaths.push_back(colorChartFilePath);

		return m_fakeIDForLoadedTexture;
	}

	void CMockEngineColorGradingController::UnloadColorChart( int textureID ) const
	{
		m_lastUnloadedTextureID = textureID;
	}

	void CMockEngineColorGradingController::SetLayers( const SColorChartLayer* layers, uint32 numLayers )
	{
		if (layers == 0)
		{
			m_wasNullPointerSetOnLayers = true;
		}

		m_currentLayers.clear();

		for (uint32 layerIndex = 0; layerIndex < numLayers; ++layerIndex)
		{
			m_currentLayers.push_back(layers[layerIndex]);
		}
	}

	bool CMockEngineColorGradingController::AnyChartsWereLoaded() const
	{
		return !m_loadedChartsPaths.empty();
	}

	int CMockEngineColorGradingController::GetLastUnloadedTextureID() const
	{
		return m_lastUnloadedTextureID;
	}

	void CMockEngineColorGradingController::ClearLoadedCharts()
	{
		m_loadedChartsPaths.clear();
	}

	const string& CMockEngineColorGradingController::GetPathOfLastLoadedColorChart() const
	{
		if (!AnyChartsWereLoaded())
		{
			static const string emptyString("");
			return emptyString;
		}

		return m_loadedChartsPaths.back();
	}

	const string& CMockEngineColorGradingController::GetPathOfLoadedColorChart( const unsigned int index ) const
	{
		if (index >= m_loadedChartsPaths.size())
		{
			static const string emptyString("");
			return emptyString;
		}
		return m_loadedChartsPaths[index];
	}

	bool CMockEngineColorGradingController::LayersHaveBeenSet() const
	{
		return !m_currentLayers.empty();
	}

	uint32 CMockEngineColorGradingController::GetLayerCount() const
	{
		return m_currentLayers.size();
	}

	size_t CMockEngineColorGradingController::GetNumberOfLayersSet() const
	{
		return m_currentLayers.size();
	}

	const SColorChartLayer& CMockEngineColorGradingController::GetCurrentlySetLayerByIndex( const uint32 index ) const
	{
		return m_currentLayers[index];
	}

	void CMockEngineColorGradingController::SetFakeIDForLoadedTexture( const int id )
	{
		m_fakeIDForLoadedTexture = id;
	}

	bool CMockEngineColorGradingController::WasNullPointerSetOnLayers() const
	{
		return m_wasNullPointerSetOnLayers;
	}
}

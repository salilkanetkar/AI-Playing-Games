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

#ifndef POST_EFFECT_BLENDER_H
#define POST_EFFECT_BLENDER_H

namespace EngineFacade
{
	struct IEngineFacade;
};

namespace Graphics
{

#define INVALID_BLEND_EFFECT_INITIAL_VALUE -1000.0f

	struct SBlendEffectParams
	{
		SBlendEffectParams()
			: m_initialValue(INVALID_BLEND_EFFECT_INITIAL_VALUE)
			, m_endValue(0.0f) 
			, m_blendTime(1.0f)
		{

		}
		string m_postEffectName;
		float  m_initialValue;
		float  m_endValue;
		float  m_blendTime;
	};

	class CPostEffectBlender
	{
	public:

		CPostEffectBlender(EngineFacade::IEngineFacade& engine);

		void AddBlendedEffect(const SBlendEffectParams& effectParams);
		void Update(float frameTime);
		void Reset();

		int GetRunningBlendsCount() const { return m_activeBlends.size(); }

	private:

		struct SInternalBlendParams
		{
			SInternalBlendParams()
				: m_runningTime(0.0f)
			{

			}

			SBlendEffectParams m_blendParams;
			float m_runningTime;
		};

		typedef std::vector<SInternalBlendParams> TActiveBlendsVector;

		TActiveBlendsVector m_activeBlends;

		EngineFacade::IEngineFacade& m_engine;
	};

}


#endif
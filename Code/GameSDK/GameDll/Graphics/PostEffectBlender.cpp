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

#include "Stdafx.h"
#include "PostEffectBlender.h"
#include "EngineFacade/EngineFacade.h"

namespace Graphics
{

	CPostEffectBlender::CPostEffectBlender( EngineFacade::IEngineFacade& engine )
		: m_engine(engine)
	{
		m_activeBlends.reserve(8);
	}


	void CPostEffectBlender::AddBlendedEffect( const SBlendEffectParams& effectParams )
	{
		SInternalBlendParams internalParams;
		internalParams.m_blendParams = effectParams;

		if (internalParams.m_blendParams.m_initialValue == INVALID_BLEND_EFFECT_INITIAL_VALUE)
			internalParams.m_blendParams.m_initialValue = m_engine.GetEngine3DEngine().GetPostEffectParameter(internalParams.m_blendParams.m_postEffectName.c_str());

		m_activeBlends.push_back(internalParams);
	}


	void CPostEffectBlender::Update( float frameTime )
	{
		TActiveBlendsVector updatingBlends;
		updatingBlends.swap(m_activeBlends);

		const int updateCount = updatingBlends.size();

		for (int i = 0; i < updateCount; ++i)
		{
			SInternalBlendParams& blendParams = updatingBlends[i];
			blendParams.m_runningTime += frameTime;

			if (blendParams.m_runningTime >= blendParams.m_blendParams.m_blendTime)
			{
				m_engine.GetEngine3DEngine().SetPostProcessEffectParameter(blendParams.m_blendParams.m_postEffectName.c_str(), blendParams.m_blendParams.m_endValue);
			}
			else
			{
				const float effectTime = CLAMP(blendParams.m_blendParams.m_blendTime / blendParams.m_runningTime, 0.0f, 1.0f);
				const float diff = blendParams.m_blendParams.m_endValue - blendParams.m_blendParams.m_initialValue;
				const float postEffectValue = blendParams.m_blendParams.m_initialValue + (diff * effectTime);

				m_engine.GetEngine3DEngine().SetPostProcessEffectParameter(blendParams.m_blendParams.m_postEffectName.c_str(), postEffectValue);
				m_activeBlends.push_back(blendParams);
			}
		}
	}

	void CPostEffectBlender::Reset()
	{
		m_engine.GetEngine3DEngine().ResetPostEffects();
		m_activeBlends.clear();
	}

}

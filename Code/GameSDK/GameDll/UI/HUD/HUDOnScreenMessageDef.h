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

#ifndef __HUD_ONSCREENMESSAGEDEF_H__
#define __HUD_ONSCREENMESSAGEDEF_H__

struct CControllerInputRenderInfo;

struct SOnScreenMessageDef
{
	public:
	SOnScreenMessageDef();
	SOnScreenMessageDef(const SOnScreenMessageDef& _in);
	~SOnScreenMessageDef();
	void Read(const XmlNodeRef xml);
	void operator=(const SOnScreenMessageDef & fromHere);

	ILINE const bool empty() const
	{
		return m_onScreenMessageText.empty();
	}

	ILINE const char * GetDisplayText() const
	{
		return m_onScreenMessageText.c_str();
	}

	ILINE const CControllerInputRenderInfo * GetInputRenderInfo() const
	{
		return m_pInputRenderInfo;
	}

	ILINE const float GetLifespan() const
	{
		return m_lifespan;
	}

	private:
	string                          m_onScreenMessageText;
	CControllerInputRenderInfo*     m_pInputRenderInfo;
	float                           m_lifespan;
};

#endif	// __HUD_ONSCREENMESSAGEDEF_H__

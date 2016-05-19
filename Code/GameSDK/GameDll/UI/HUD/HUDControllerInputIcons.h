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

#ifndef __HUD_CONTROLLER_INPUT_ICONS_H__
#define __HUD_CONTROLLER_INPUT_ICONS_H__

enum eControllerInputTypeVisualization
{
	kCITV_none,
	kCITV_icon,
	kCITV_text
};

struct CControllerInputRenderInfo
{
	public:
	CControllerInputRenderInfo()
	{
		Clear();
	}

	void Clear();
	bool SetIcon(const char * text);
	bool SetText(const char * text);
	bool CreateForInput(const char * mapName, const char * inputName);
	void operator=(const CControllerInputRenderInfo & fromThis);
	
	ILINE eControllerInputTypeVisualization			GetType() const { return m_type; }
	ILINE const char *													GetText() const { return m_text; }
	ILINE const ITexture *											GetTexture() const { return m_texture; }

	private:
	eControllerInputTypeVisualization			m_type;
	char																	m_text[32];
	ITexture *                            m_texture;

	static ITexture* GetTexture(const char* name);
};

#endif	// __HUD_CONTROLLER_INPUT_ICONS_H__
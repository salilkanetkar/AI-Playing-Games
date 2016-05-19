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

// Description : Screen Utilities such as safearea rendering.

#ifndef __ScreenLayoutUtils_H__
#define __ScreenLayoutUtils_H__

class C2DRenderUtils;
class ScreenLayoutManager;

#if ENABLE_HUD_EXTRA_DEBUG
class SafeAreaResizer;
#endif

class SafeAreaRenderer
{
public :
	SafeAreaRenderer( C2DRenderUtils* p2dRenderUtils, ScreenLayoutManager* pScreenLayout );
	~SafeAreaRenderer( );

	void DrawSafeAreas( void );

private :

	void  DrawSafeArea( const char* text, const Vec2& border_pecentage );

	C2DRenderUtils* m_p2dRenderUtils;
	ScreenLayoutManager* m_pScreenLayout;

#if ENABLE_HUD_EXTRA_DEBUG
	SafeAreaResizer* m_pResizer;

	int m_interactiveResize;
#endif
};

#endif // __ScreenLayoutUtils_H__
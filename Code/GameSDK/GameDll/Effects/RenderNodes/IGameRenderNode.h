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

#ifndef _IGAME_RENDERNODE_
#define _IGAME_RENDERNODE_

#pragma once

#include "Effects/RenderElements/GameRenderElement.h"
#include "Effects/GameEffectsSystem.h"

// Forward declares
struct IGameRenderNodeParams;

//==================================================================================================
// Name: GameSDKIGameRenderNode
// Desc: Base interface for all game render nodes
// Author: James Chilvers
//==================================================================================================
// Renamed to avoid conflict with GameEffectSystem Gem.
struct GameSDKIGameRenderNode : public IRenderNode, public _i_reference_target_t
{
    DECLARE_TYPELIB(GameSDKIGameRenderNode); // Allow soft coding on this interface

    virtual ~GameSDKIGameRenderNode() {}

	virtual bool InitialiseGameRenderNode() = 0;
	virtual void ReleaseGameRenderNode() = 0;

	virtual void SetParams(const IGameRenderNodeParams* pParams = NULL) = 0;

};//------------------------------------------------------------------------------------------------

//==================================================================================================
// Name: IGameRenderNodeParams
// Desc: Game render node params
// Author: James Chilvers
//==================================================================================================
struct IGameRenderNodeParams
{
	virtual ~IGameRenderNodeParams() {}
};//------------------------------------------------------------------------------------------------

#endif // _IGAME_RENDERNODE_

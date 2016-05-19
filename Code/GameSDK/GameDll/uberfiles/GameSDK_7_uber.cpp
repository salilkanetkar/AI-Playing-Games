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

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_devirt_defines.h>
#endif

#include "../Utility/AttachmentUtils.cpp"
#include "../PlayerAnimation.cpp"
#include "../StickyProjectile.cpp"
#include "../UI/HUD/HUDControllerInputIcons.cpp"
#include "../UI/HUD/HUDEventDispatcher.cpp"
#include "../UI/HUD/HUDEventTranslator.cpp"
#include "../UI/HUD/HUDEventWrapper.cpp"
#include "../UI/HUD/HUDMissionObjectiveSystem.cpp"
#include "../UI/HUD/HUDOnScreenMessageDef.cpp"
#include "../UI/HUD/HUDSilhouettes.cpp"
#include "../UI/HUD/HUDUtils.cpp"
#include "../UI/HUD/ScriptBind_HUD.cpp"
#include "../UI/HUD/TacticalOverrideEntity.cpp"
#include "../UI/Menu3dModels/FrontEndModelCache.cpp"
#include "../UI/Menu3dModels/MenuRender3DModelMgr.cpp"
#include "../UI/Option.cpp"
#include "../UI/ProfileOptions.cpp"
#include "../UI/UICVars.cpp"
#include "../UI/UIDialogs.cpp"
#include "../UI/UIEntityDynTexTag.cpp"
#include "../UI/UIEntityTag.cpp"
#include "../UI/UIGameEvents.cpp"
#include "../UI/UIHUD3D.cpp"
#include "../UI/UIInput.cpp"
#include "../UI/UILobbyMP.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif

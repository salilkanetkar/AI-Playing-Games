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

#include "../Utility/CryWatch.cpp"
#include "../Utility/DesignerWarning.cpp"
#include "../Utility/SingleAllocTextBlock.cpp"
#include "../SShootHelper.cpp"
#include "../Utility/StringUtils.cpp"
#include "../Effects/GameEffectsSystem.cpp"
#include "../Effects/GameEffects/ExplosionGameEffect.cpp"
#include "../Effects/GameEffects/GameEffect.cpp"
#include "../Effects/GameEffects/HitRecoilGameEffect.cpp"
#include "../Effects/GameEffects/HudInterferenceGameEffect.cpp"
#include "../Effects/GameEffects/KillCamGameEffect.cpp"
#include "../Effects/GameEffects/PlayerHealthEffect.cpp"
#include "../Effects/HUDEventListeners/LetterBoxHudEventListener.cpp"
#include "../Effects/Tools/CVarActivationSystem.cpp"
#include "../Effects/Tools/PostEffectActivationSystem.cpp"
#include "../GameCodeCoverage/GameCodeCoverageGUI.cpp"
#include "../GameCodeCoverage/GameCodeCoverageManager.cpp"
#include "../GameCodeCoverage/GameCodeCoverageTracker.cpp"
#include "../GameCodeCoverage/IGameCodeCoverageListener.cpp"
#include "../Audio/Announcer.cpp"
#include "../Audio/AreaAnnouncer.cpp"
#include "../Audio/MiscAnnouncer.cpp"
#include "../Graphics/2DRenderUtils.cpp"
#include "../Network/GameNetworkUtils.cpp"
#include "../Network/Lobby/GameAchievements.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif

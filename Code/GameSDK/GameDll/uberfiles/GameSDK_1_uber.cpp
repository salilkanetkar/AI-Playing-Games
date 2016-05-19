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

#include "../DoubleMagazine.cpp"
#include "../Effects/GameEffects/LightningGameEffect.cpp"
#include "../Effects/GameEffects/ParameterGameEffect.cpp"
#include "../Effects/GameEffects/WaterEffects.cpp"
#include "../Effects/GameEffects/PlayerMindGameBeamEffect.cpp"
#include "../Effects/RenderNodes/LightningNode.cpp"
#include "../EMPGrenade.cpp"
#include "../Environment/DoorPanel.cpp"
#include "../Environment/DoorPanelBehavior.cpp"
#include "../Environment/Ledge.cpp"
#include "../Environment/LightningArc.cpp"
#include "../Environment/MineField.cpp"
#include "../Environment/ScriptBind_LightningArc.cpp"
#include "../Environment/ScriptBind_TowerSearchLight.cpp"
#include "../Environment/SmartMine.cpp"
#include "../Environment/SmartMineBehavior.cpp"
#include "../Environment/TowerSearchLight.cpp"
#include "../Environment/VicinityDependentObjectMover.cpp"
#include "../Environment/WaterPuddle.cpp"
#include "../Environment/WaterRipplesGenerator.cpp"
#include "../ExactPositioning.cpp"
#include "../ExactPositioningTrigger.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif

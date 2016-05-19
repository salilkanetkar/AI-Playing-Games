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

#include "../ItemScheduler.cpp"
#include "../ItemView.cpp"
#include "../ScopeReticule.cpp"
#include "../ScriptBind_Item.cpp"
#include "../AmmoParams.cpp"
#include "../FireModeParams.cpp"
#include "../FireModePluginParams.cpp"
#include "../MuzzleEffect.cpp"
#include "../PickAndThrowProxy.cpp"
#include "../Projectile.cpp"
#include "../Recoil.cpp"
#include "../ScriptBind_Weapon.cpp"
#include "../TracerManager.cpp"
#include "../Weapon.cpp"
#include "../WeaponAlias.cpp"
#include "../WeaponClientServer.cpp"
#include "../WeaponEvent.cpp"
#include "../WeaponInput.cpp"
#include "../WeaponSystem.cpp"
#include "../Automatic.cpp"
#include "../AutomaticShotgun.cpp"
#include "../Burst.cpp"
#include "../Charge.cpp"
#include "../Detonate.cpp"
#include "../FireMode.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif

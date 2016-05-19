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

#include "../ProceduralClipAiming.cpp"
#include "../ProceduralClipAimSmoothing.cpp"
#include "../ProceduralClipColliderMode.cpp"
#include "../ProceduralClipCompromiseCover.cpp"
#include "../ProceduralClipCopyNormalizedTime.cpp"
#include "../ProceduralClipFacialSequence.cpp"
#include "../ProceduralClipLooking.cpp"
#include "../ProceduralClipMovementControlMethod.cpp"
#include "../ProceduralClipRagdoll.cpp"
#include "../ProceduralClipSetStance.cpp"
#include "../ProceduralContextAim.cpp"
#include "../ProceduralContextColliderMode.cpp"
#include "../ProceduralContextLook.cpp"
#include "../ProceduralContextMovementControlMethod.cpp"
#include "../ProceduralContextRagdoll.cpp"
#include "../ProceduralWeaponAnimation.cpp"
#include "../ProceduralWeaponClip.cpp"
#include "../PlayerStateEvents.cpp"
#include "../PlayerStateMovement.cpp"
#include "../ProceduralWeaponContext.cpp"
#include "../ProgressBar3D.cpp"
#include "../ProjectileAutoAimHelper.cpp"
#include "../RandomDeck.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif

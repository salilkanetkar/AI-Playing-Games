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

// Description : Controls player movement when using a mounted gun


#pragma once

#ifndef _MOUNTED_GUN_CONTROLLER_H_
#define _MOUNTED_GUN_CONTROLLER_H_

#include "PlayerAnimation.h"

class CPlayer;
class CItem;


class CMountedGunController
{
public:
	CMountedGunController()
		: m_pControlledPlayer(NULL)
		, m_pMovementAction(NULL)
		, m_pMannequinParams(NULL)
	{
	}

	~CMountedGunController() { SAFE_RELEASE(m_pMovementAction); }

	ILINE void InitWithPlayer(CPlayer* pPlayer){ assert(m_pControlledPlayer == NULL); m_pControlledPlayer = pPlayer; }
	void InitMannequinParams();

	void OnEnter(EntityId mountedGunID);
	void OnLeave();
	void Update(EntityId mountedGunID, float frameTime);

	static float CalculateAnimationTime(float aimRad);

	static void ReplayStartThirdPersonAnimations(ICharacterInstance* pCharacter, int upAnimId, int downAnimId);
	static void ReplayStopThirdPersonAnimations(ICharacterInstance* pCharacter);
	static void ReplayUpdateThirdPersonAnimations(ICharacterInstance* pCharacter, float aimRad, float aimUp, float aimDown, bool firstPerson = false);

private:

	void UpdateGunnerLocation(CItem* pMountedGun, IEntity* pParent, const Vec3& bodyDirection);
	void UpdateFirstPersonAnimations(CItem* pMountedGun, const Vec3 &aimDirection);
	void UpdateIKMounted(CItem* pMountedGun);
	Vec3 GetMountDirection(CItem* pMountedGun, IEntity* pParent) const;
	Vec3 GetMountedGunPosition(CItem* pMountedGun, IEntity* pParent) const;

	CPlayer*		m_pControlledPlayer;
	TPlayerAction* m_pMovementAction;
	const struct SMannequinMountedGunParams* m_pMannequinParams;
};

#endif

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

#ifndef __SKILLKILL_H__
#define __SKILLKILL_H__

#include "GameRulesTypes.h"

struct IActor;
class CPlayer;
class CGameRules;

class SkillKill
{
public:
	static bool IsHeadshot(CPlayer* pTargetPlayer, int hit_joint, int material);
	static bool IsAirDeath(CPlayer* pTargetPlayer);
	static bool IsStealthKill(CPlayer* pTargetPlayer);
	static bool IsMeleeTakedown(CGameRules* pGameRules, int hit_type);
	static bool IsBlindKill(CPlayer* pShooterPlayer);
	static bool IsFirstBlood(IActor *pShooter, IActor *pVictim);
	static bool IsRumbled(CPlayer* pShooterPlayer, CPlayer* pTargetPlayer);
	static bool IsDefiantKill(CPlayer* pShooterPlayer);
	static bool IsKillJoy(CPlayer* pTargetPlayer);
	static EPPType IsMultiKill(CPlayer* pShooterPlayer);
	static bool IsRecoveryKill(CPlayer* pShooterPlayer);
	static bool IsRetaliationKill(CPlayer* pShooterPlayer, CPlayer* pTargetPlayer);
	static bool IsGotYourBackKill(CPlayer* pShooterPlayer, CPlayer* pTargetPlayer);
	static bool IsGuardianKill(CPlayer* pShooterPlayer, CPlayer* pTargetPlayer);
	static bool IsInterventionKill(CPlayer* pShooterPlayer, CPlayer* pTargetPlayer);
	static bool IsPiercing(int penetration);
	static bool IsBlinding(CPlayer* pShooterPlayer, CPlayer* pTargetPlayer, uint16 weaponClassId);
	static bool IsFlushed(CPlayer* pShooterPlayer, CPlayer* pTargetPlayer, CGameRules* pGameRules, int hit_type);
	static bool IsDualWeapon(CPlayer* pShooterPlayer, CPlayer* pTargetPlayer);
	static void	SetFirstBlood(bool firstBlood);
	static bool GetFirstBlood();
	static bool IsKickedCarKill(CPlayer* pKicker, CPlayer* pTargetPlayer, EntityId vehicleId);
	static bool IsSuperChargedKill(CPlayer* pShooter);
	static bool IsIncomingKill(int hit_type);
	static bool IsPangKill(int hit_type);
	static bool IsAntiAirSupportKill(int hit_type);

	static void Reset();

private:
	static bool s_firstBlood;
	static uint16 s_flashBangGrenadesClassId;
};

#endif

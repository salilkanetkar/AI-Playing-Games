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

#pragma once

#ifndef _HEAVY_WEAPON_H_
#define _HEAVY_WEAPON_H_

#include "Weapon.h"
#include "GameRulesModules/IGameRulesClientConnectionListener.h"

class CActor;

class CHeavyWeapon : public CWeapon, public IGameRulesClientConnectionListener
{
private:
	struct StopUseAction;
	struct DetachItemAction;
	typedef CWeapon BaseClass;

public:
	DECLARE_COMPONENT_TYPE("CHeavyWeapon", 0x358C1487EE954673,0x96BBA4C5C197EAA7)
	CHeavyWeapon();
	virtual ~CHeavyWeapon();

	virtual bool CanPickUp(EntityId userId) const;
	virtual bool CanUse(EntityId userId) const;
	virtual void Use(EntityId userId);
	virtual void StartUse(EntityId userId);
	virtual void StopUse(EntityId  userId);
	virtual bool IsPickable() const;
	virtual bool IsHeavyWeapon() const;
	virtual bool IsRippedOff() const;
	virtual void GetAngleLimits(EStance stance, float& minAngle, float& maxAngle);
	virtual bool CanSelect() const;
	virtual bool AllowInteraction(EntityId interactionEntity, EInteractionType interactionType);

	virtual void PostSerialize();
	virtual void InitClient (ChannelId channelId);

	using CWeapon::StartFire;
	virtual void StartFire(const SProjectileLaunchParams& launchParams);

	// IGameRulesClientConnectionListener
	virtual void OnClientConnect(ChannelId channelId, bool isReset, EntityId playerId) {};
	virtual void OnClientDisconnect(ChannelId channelId, EntityId playerId) {};
	virtual void OnClientEnteredGame(ChannelId channelId, bool isReset, EntityId playerId) {}
	virtual void OnOwnClientEnteredGame();
	// ~IGameRulesClientConnectionListener

	struct SHeavyWeaponUserParams
	{
		SHeavyWeaponUserParams(): ownerId(0) {};
		SHeavyWeaponUserParams(EntityId owner): ownerId(owner) {};
		void SerializeWith(TSerialize ser)
		{
			ser.Value("ownerId", ownerId, 'eid');
		}
		EntityId ownerId;
	};

	struct SNoParams
	{
		SNoParams() {}
		void SerializeWith(TSerialize ser) {}
	};

	DECLARE_CLIENT_RMI_NOATTACH(ClDeselectAndDrop, SHeavyWeaponUserParams, eNRT_ReliableUnordered);
	DECLARE_CLIENT_RMI_NOATTACH(ClHeavyWeaponUsed, SHeavyWeaponUserParams, eNRT_ReliableUnordered);
	DECLARE_CLIENT_RMI_NOATTACH(ClHeavyWeaponHighlighted, SNoParams, eNRT_ReliableUnordered);

protected:
	void HandleHeavyWeaponPro(CActor& rOwner);

	FragmentID GetSelectAction() const;
	virtual void DeselectAndDrop(EntityId userId);
};


#endif

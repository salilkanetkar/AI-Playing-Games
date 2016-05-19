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

#ifndef __PLAYER_ENTITY_INTERACTION_H__
#define __PLAYER_ENTITY_INTERACTION_H__

#if _MSC_VER > 1000
# pragma once
#endif



class CPlayerEntityInteraction
{
	struct SLastInteraction
	{
		SLastInteraction()
		{
			Reset();
		}

		void Reset()
		{
			m_frameId = 0;
		}
		 
		bool CanInteractThisFrame( const int frameId ) const
		{
			return (m_frameId != frameId);
		}

		void Update( const int frameId )
		{
			m_frameId = frameId;
		}

	private:
		int      m_frameId;
	};

public:
	CPlayerEntityInteraction();

	void ItemPickUpMechanic(CPlayer* pPlayer, const ActionId& actionId, int activationMode);
	void UseEntityUnderPlayer(CPlayer* pPlayer);

	void JustInteracted( );

	void Update(CPlayer* pPlayer, float frameTime);

private:
	void ReleaseHeavyWeapon(CPlayer* pPlayer);

	SLastInteraction m_lastUsedEntity;

	float m_autoPickupDeactivatedTime;

	bool m_useHoldFiredAlready;
	bool m_usePressFiredForUse;
	bool m_usePressFiredForPickup;
	bool m_useButtonPressed;
};



#endif

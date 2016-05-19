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

// Description : Utility functions related to cloaking effect

#pragma once

#ifndef __ENTITY_EFFECTS_CLOAK_H__
#define __ENTITY_EFFECTS_CLOAK_H__

namespace EntityEffects
{
	namespace Cloak
	{
		enum ECloakColorChannels
		{
			eCCC_Friendly=0,
			eCCC_Hostile
		};

		struct CloakSyncParams
		{
			CloakSyncParams(const EntityId _masterId, const EntityId _slaveId, const bool _fadeToDesiredCloakTarget = false, const bool _forceDecloakOfSlave = false)
				: cloakMasterId(_masterId)
				, cloakSlaveId(_slaveId)
				, fadeToDesiredCloakTarget(_fadeToDesiredCloakTarget)	// Snap if false
				, forceDecloakOfSlave(_forceDecloakOfSlave)            // Handy override for when weapon dropped
			{

			}

			EntityId cloakMasterId;
			EntityId cloakSlaveId; 
			bool fadeToDesiredCloakTarget;
			bool forceDecloakOfSlave; 
		};

		void CloakEntity(IEntity *pEntity, bool bEnable, bool bFade, float blendSpeedScale, bool bCloakFadeByDistance, uint8 cloakPaletteColorChannel,bool bIgnoreCloakRefractionColor);
		void CloakEntity(EntityId entityId, bool bEnable, bool bFade, float blendSpeedScale, bool bCloakFadeByDistance, uint8 cloakPaletteColorChannel,bool bIgnoreCloakRefractionColor);
		bool CloakSyncEntities(const CloakSyncParams& params);

		bool DoesCloakFadeByDistance(EntityId ownerEntityId);
		uint8 GetCloakColorChannel(EntityId ownerEntityId);
		ILINE uint8 GetCloakColorChannel ( const bool bIsFriendly ) { return bIsFriendly ? eCCC_Friendly : eCCC_Hostile; }
		bool IgnoreRefractionColor(EntityId ownerEntityId);
	};
};

#endif // __ENTITY_CLOAK_H__
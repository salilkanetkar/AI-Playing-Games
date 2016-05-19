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

// Description : Manager to handle loading team specific player materials and
//               apply them to players + replay entities


#ifndef __TEAM_VISUALIZATION_MANAGER__
#define __TEAM_VISUALIZATION_MANAGER__

#if _MSC_VER > 1000
# pragma once
#endif

#include "ItemString.h"
struct IMaterial;

class CTeamVisualizationManager 
{
private:
	enum EMaterialIndex
	{
		eMI_AliveFriendly = 0,
		eMI_AliveHostile,
		eMI_DeadFriendly,
		eMI_DeadHostile,

		eMI_Total
	};

	typedef std::vector<uint32> TCrcList;

	struct SModelMaterialSetup
	{
		SModelMaterialSetup();
		~SModelMaterialSetup();
		void SetMaterial(const EMaterialIndex idx, IMaterial* pMaterial);
		void ApplyMaterial(ICharacterInstance* pCharInst, const EMaterialIndex materialIdx) const;

		IMaterial* m_materials[eMI_Total]; 
		TCrcList m_attachments;
	};

	typedef unsigned int TModelNameCRC;  
	typedef std::map<TModelNameCRC, SModelMaterialSetup> TModelPartsMap;

public:
	CTeamVisualizationManager();
	~CTeamVisualizationManager();

	void Init(); 

	void OnPlayerTeamChange(const EntityId playerId) const; 
	void RefreshPlayerTeamMaterial(const EntityId playerId) const;
	void RefreshTeamMaterial( IEntity* pEntity, const bool isAlive, const bool isFriendly ) const;
	void ProcessTeamChangeVisualization(EntityId entityId) const;

private:

	ILINE EMaterialIndex GetMaterialIndex ( const bool isAlive, const bool isFriendly ) const { return (EMaterialIndex)((isAlive?0:2) + (isFriendly?0:1)); }
	void InitTeamVisualizationData(XmlNodeRef xmlNode); 

	TModelPartsMap m_teamVisualizationPartsMap;

};


#endif // __TEAM_VISUALIZATION_MANAGER__
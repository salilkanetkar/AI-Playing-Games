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

#include "CryFixedString.h"

struct IEntityClass;

class CStatsEntityIdRegistry
{
public:
	CStatsEntityIdRegistry();

	uint16 GetGameModeId(const char *pModeName) const;
	uint16 GetGameModeId(const IEntityClass *pClass) const;

	uint16 GetMapId(const char *pMapName) const;
	
	uint16 GetWeaponId(const char *pWeaponName) const;
	uint16 GetWeaponId(const IEntityClass *pClass) const;

	uint16 GetHitTypeId(const char* pHitTypeName) const; 
	uint16 GetDefaultWeapon() const { return m_defaultWeapon; }

	const char* GetGameMode(uint16 id) const;
	const char* GetMap(uint16 id) const;
	const char* GetWeapon(uint16 id) const;
	const char* GetHitType(uint16 id) const; 
	
private:
	typedef CryFixedStringT<32> TFixedString;

	struct SClassId
	{
		const IEntityClass *m_pClass;
		uint16 m_id;
	};

	struct SStringId
	{
		TFixedString m_name;
		uint16 m_id;
	};

	typedef std::vector<SClassId> TClassIdVec;
	typedef std::vector<SStringId> TStringIdVec;

	static void ReadClassIds(XmlNodeRef xmlNode, uint16 &defaultId, TClassIdVec &vec );
	static void ReadStringIds(XmlNodeRef xmlNode, uint16 &defaultId, TStringIdVec &vec );
	
	TClassIdVec m_gameModes;
	TClassIdVec m_weapons;
	TStringIdVec m_weaponExtensions;
	TStringIdVec m_maps;
	TStringIdVec	m_hitTypes;
	
	uint16 m_defaultGameMode;
	uint16 m_defaultWeapon;
	uint16 m_defaultMap;
	uint16 m_defaultHitType;
};

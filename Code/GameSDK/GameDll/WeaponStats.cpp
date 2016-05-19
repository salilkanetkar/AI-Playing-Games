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

#include "StdAfx.h"

#include "WeaponStats.h"
#include "ItemSharedParams.h"
#include "GameXmlParamReader.h"

#define MAX_STAT_VALUE 10

//////////////////////////////////////////////////////////////////////////


SWeaponStatsData::SWeaponStatsData()
{
	const int numStats = eWeaponStat_NumStats;
	for(int i=0; i<numStats; ++i)
	{
		stats.push_back(0);
	}
}

void SWeaponStatsData::ReadStats(const XmlNodeRef& paramsNode, bool defaultInit /*= false*/)
{	
	if (defaultInit)
	{
		const int numStats = eWeaponStat_NumStats;
		for(int i=0; i<numStats; ++i)
		{
			stats[i] = 0;
		}
	}

	if (paramsNode == NULL)
		return;

	CGameXmlParamReader reader(paramsNode);

	for (int i  = 0; i < eWeaponStat_NumStats; i++)
	{
		reader.ReadParamValue<int>(s_weaponStatNames[i], stats[i]);
	}

}

void SWeaponStatsData::ReadStatsByAttribute(const XmlNodeRef& paramsNode, bool defaultInit /*= false*/)
{	
	if (defaultInit)
	{
		const int numStats = eWeaponStat_NumStats;
		for(int i=0; i<numStats; ++i)
		{
			stats[i] = 0;
		}
	}

	if (paramsNode == NULL)
		return;

	int iReadValue; // Can't use int directly in the vector, somehow will get translated to an unsigned int
	for (int i  = 0; i < eWeaponStat_NumStats; i++)
	{
		if (paramsNode->getAttr(s_weaponStatNames[i], iReadValue))
		{
			stats[i] = iReadValue;
		}		
	}
}

IMPLEMENT_OPERATORS_WITH_VECTORS(WEAPON_STATSDATA_PARAMS, WEAPON_STATSDATA_PARAM_VECTORS, SWeaponStatsData)

//////////////////////////////////////////////////////////////////////////


void SWeaponStatStoredData::UpdateTotalValue()
{
	totalValue = baseValue + accessoryModifier + firemodeModifier;
}


//////////////////////////////////////////////////////////////////////////


CWeaponStats::CWeaponStats()
{
	const int numStats = eWeaponStat_NumStats;
	for(int i=0; i<numStats; ++i)
	{
		SWeaponStatStoredData weaponStoredData;
		CRY_TODO(25,08,2010, "Dean - Remove setting weapon stat default value to 5 when all designer data is in");
		weaponStoredData.baseValue = MAX_STAT_VALUE / 2;
		weaponStoredData.totalValue = weaponStoredData.baseValue;
		m_weaponStats.push_back(weaponStoredData);
	}
}



CWeaponStats::~CWeaponStats()
{

}



void CWeaponStats::SetBaseStats(const CItemSharedParams* params)
{
	CRY_ASSERT(m_weaponStats.size() == params->params.weaponStats.stats.size() && m_weaponStats.size() == eWeaponStat_NumStats);
	const int numStats = eWeaponStat_NumStats;
	for (int i = 0; i < numStats; i++)
	{
		m_weaponStats[i].baseValue = params->params.weaponStats.stats[i];
	}	

	UpdateTotalValue();
}



void CWeaponStats::SetStatsFromAccessory(const SAccessoryParams *params, const bool attach)
{

	CRY_ASSERT(m_weaponStats.size() == params->weaponStats.stats.size() && m_weaponStats.size() == eWeaponStat_NumStats);

	// Safeguard against this being called more than once on the same accessory which happens for some weapons
	const IEntityClass* pAccessoryClass = params->pAccessoryClass;
	if (pAccessoryClass)
	{
		const int numStats = eWeaponStat_NumStats;
		if(attach)
		{
			if (m_attachments.find(pAccessoryClass) != m_attachments.end()) // Don't add stats if already added
			{
				return;
			}
			m_attachments.insert(pAccessoryClass);

			for (int i = 0; i < numStats; i++)
			{
				m_weaponStats[i].accessoryModifier += params->weaponStats.stats[i];
			}
		}
		else
		{
			const TWeaponStatsAttachments::iterator iter = m_attachments.find(pAccessoryClass);
			if (iter == m_attachments.end()) // Don't remove stats if already removed
			{
				return;
			}
			m_attachments.erase(iter);

			for (int i = 0; i < numStats; i++)
			{
				m_weaponStats[i].accessoryModifier -= params->weaponStats.stats[i];
			}
		}

		UpdateTotalValue();
	}
}



void CWeaponStats::SetStatsFromFiremode(const SWeaponStatsData *pStats)
{
	const int numStats = eWeaponStat_NumStats;

	if (!pStats) // Valid, notifies clear
	{
		for (int i = 0; i < numStats; i++)
		{
			m_weaponStats[i].firemodeModifier = 0;
		}
	}
	else
	{
		CRY_ASSERT(m_weaponStats.size() == pStats->stats.size() && m_weaponStats.size() == eWeaponStat_NumStats);
		for (int i = 0; i < numStats; i++)
		{
			m_weaponStats[i].firemodeModifier = pStats->stats[i];
		}
	}

	UpdateTotalValue();
}



const int CWeaponStats::GetStat(const EWeaponStat stat) const
{
	CRY_ASSERT(stat >= 0 && stat < eWeaponStat_NumStats);
	return m_weaponStats[stat].totalValue;
}


const SWeaponStatStoredData& CWeaponStats::GetStatData(const EWeaponStat stat) const
{
	CRY_ASSERT(stat >= 0 && stat < eWeaponStat_NumStats);
	return m_weaponStats[stat];
}


void CWeaponStats::SetStat(const EWeaponStat stat, const SWeaponStatStoredData& statData)
{
	CRY_ASSERT(stat >= 0 && stat < eWeaponStat_NumStats);
	m_weaponStats[stat] = statData;
}


void CWeaponStats::UpdateTotalValue()
{
	const int numStats = eWeaponStat_NumStats;
	for (int i = 0; i < numStats; i++)
	{
		SWeaponStatStoredData& weaponStat = m_weaponStats[i];
		weaponStat.UpdateTotalValue();
	}	

}


//////////////////////////////////////////////////////////////////////////
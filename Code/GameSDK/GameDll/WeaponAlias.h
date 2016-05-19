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

#ifndef __WEAPONALIAS_H__
#define __WEAPONALIAS_H__

struct IEntityClass;

class CWeaponAlias
{
public:
	CWeaponAlias();
	virtual ~CWeaponAlias();

	void AddAlias(const char* pParentName, const char* pChildName);
	void Reset();

	//Will update pClass if they have a parent
	void UpdateClass(IEntityClass** ppClass) const;

	//Return pParentClass (or NULL if they don't have one)
	const IEntityClass* GetParentClass(const IEntityClass* pClass) const;
	const IEntityClass* GetParentClass(const char* pClassName) const;

	bool IsAlias(const char* pAliasName) const;

protected:
	struct SWeaponAlias
	{
		SWeaponAlias(const char* pParentName, const char* pName);

		IEntityClass* m_pParentClass;
		IEntityClass* m_pClass;
	};

	typedef std::vector<SWeaponAlias> TWeaponAliasVec;
	TWeaponAliasVec m_aliases;
};

#endif // __WEAPONALIAS_H__

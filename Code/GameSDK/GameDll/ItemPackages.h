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

#ifndef __ITEM_PACKAGES_H__
#define __ITEM_PACKAGES_H__

#if _MSC_VER > 1000
# pragma once
#endif



class CItemPackages
{
public:

	typedef std::vector<IEntityClass*> TSetup;

	struct SPackage
	{
		ItemString m_displayName;
		IEntityClass* m_pItemClass;
		TSetup m_setup;
	};

	typedef std::vector<SPackage> TPackages;

public:
	void Load();
	const char* GetFullItemName(const CItem* pItem) const;

private:
	TPackages m_packages;
};


#endif

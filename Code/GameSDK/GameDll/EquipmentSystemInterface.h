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

// Description : Interface for Editor to access CryAction/Game specific equipments


#ifndef __EQUIPMENTSYSTEMINTERFACE_H__
#define __EQUIPMENTSYSTEMINTERFACE_H__

#if _MSC_VER > 1000
# pragma once
#endif

#include <IEditorGame.h>

// some forward decls
class CEditorGame;
struct IItemSystem;
struct IEquipmentManager;

class CEquipmentSystemInterface : public IEquipmentSystemInterface
{
public:
	CEquipmentSystemInterface(CEditorGame* pEditorGame, IGameToEditorInterface* pGTE);
	~CEquipmentSystemInterface();

	// return iterator with all available equipment items
	virtual IEquipmentItemIteratorPtr CreateEquipmentItemIterator(const char* type="");
	virtual IEquipmentItemIteratorPtr CreateEquipmentAccessoryIterator(const char* type);

	// delete all equipment packs
	virtual void DeleteAllEquipmentPacks();

	// load a single equipment pack from an XmlNode
	// Equipment Pack is basically
	// <EquipPack name="BasicPack">
	//   <Items>
	//      <Scar type="Weapon" />
	//      <SOCOM type="Weapon" />
	//   </Items>
	//   <Ammo Scar="50" SOCOM="70" />
	// </EquipPack>

	virtual bool LoadEquipmentPack(const XmlNodeRef& rootNode);	

	// set the players equipment pack. maybe we enable this, but normally via FG only
	// virtual void SetPlayerEquipmentPackName(const char *packName);
protected:
	void InitItems(IGameToEditorInterface* pGTE);

protected:
	class CIterator;

	CEditorGame* m_pEditorGame;
	IItemSystem* m_pIItemSystem;
	IEquipmentManager* m_pIEquipmentManager;

	typedef std::vector<string> TNameArray;
	typedef std::map<string, TNameArray> TItemMap;
	typedef std::map<string, TItemMap> TAccessoryMap;
	// maybe make it a multimap, or contain real item desc instead of only name
	TItemMap m_itemMap;
	TAccessoryMap m_accessoryMap;
};

#endif

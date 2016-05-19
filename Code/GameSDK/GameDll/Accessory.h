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

// Description : Item/weapon accessories

#ifndef _ACCESSORY_H_
#define _ACCESSORY_H_

#include "Item.h"

class CAccessory: public CItem
{
	typedef CItem BaseClass;

public:
	DECLARE_COMPONENT_TYPE("CAccessory", 0xBB61816FCD7F40F8, 0x85BC717167D3C35F);

	CAccessory()  {};

	virtual			~CAccessory() {};
	
	virtual void PickUp(EntityId pickerId, bool sound, bool select/* =true */, bool keepHistory/* =true */, const char *setup = NULL);
	virtual bool IsAccessory() { return true; };

	virtual void OnEnterFirstPerson();
	virtual void OnEnterThirdPerson();

	virtual void SetParentId(EntityId parentId);
	virtual void Physicalize(bool enable, bool rigid);
	virtual ePhysicalization	FindPhysicalisationType(bool enable, bool rigid);

	void GetMemoryUsage(ICrySizer *pSizer )const
	{
		pSizer->AddObject(this, sizeof(*this));
		CItem::GetInternalMemoryUsage(pSizer); // collect memory of parent class
	}

};

#endif

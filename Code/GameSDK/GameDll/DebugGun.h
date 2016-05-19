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

// Description : DebugGun Implementation


#ifndef __DebugGun_H__
#define __DebugGun_H__

#if _MSC_VER > 1000
# pragma once
#endif


#include <IItemSystem.h>
#include "Weapon.h"


class CDebugGun :
  public CWeapon
{
public:
	DECLARE_COMPONENT_TYPE("CDebugGun", 0x49F9DC64CDBB4C08,0x92A962CC05F02E1B)
  CDebugGun();
  void OnAction(EntityId actorId, const ActionId& actionId, int activationMode, float value);
  void Update(SEntityUpdateContext& ctx, int update);
  void Shoot( bool bPrimary);
	virtual void GetMemoryUsage(ICrySizer * s) const
	{
		s->AddObject(this, sizeof(*this));		
		s->AddContainer(m_fireModes);
		CWeapon::GetInternalMemoryUsage(s); // collect memory of parent class
	}

  virtual void Select(bool select);

private:
  ICVar* m_pAIDebugDraw;
  int m_aiDebugDrawPrev;
  
  typedef std::pair<string, float> TFmPair;
  std::vector<TFmPair> m_fireModes;    
  int m_fireMode;
};

#endif // __DebugGun_H__
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

// Description : Parachute Item implementation

#ifndef __PARACHUTE_H__
#define __PARACHUTE_H__

#include <IItemSystem.h>
#include "Item.h"
#include "VehicleMovementAerodynamic.h"

class CParachute : public CItem, public CVehicleMovementAerodynamic
{
public:
  CParachute();
  virtual ~CParachute();

  // IItem, IGameObjectExtension
  virtual bool Init(IGameObject * pGameObject) override;      
  virtual void Update(SEntityUpdateContext& ctx, int) override;    
  virtual void OnAction(EntityId actorId, const char *actionName, int activationMode, float value) override;
  virtual void UpdateFPView(float frameTime) override;
  virtual void OnReset() override;
  // No longer used
  //virtual void Release() override;
  // ~IItem

  // IGameObjectPhysics
  virtual bool SetProfile( uint8 profile );
  // ~IGameObjectPhysics

private:
  void ProcessMovement(const float deltatime);
  int AddCel(IPhysicalEntity* pPhysics,int,SWing *);
    
  inline bool IsOpened(){ return m_isOpened; }
  void Open();
  void Close(bool drop=false);
  void PhysicalizeCanvas(bool enable);

  TPointsMap m_LiftPointsMap;
  TPointsMap m_DragPointsMap;
  SWing m_aCels[7];
  std::vector<int> m_paraPhysIds;
  
  EntityId m_actorId;
  bool m_isOpened;  
  float m_inAir;

  EntityId m_canvasId;
};


#endif //__PARACHUTE_H__

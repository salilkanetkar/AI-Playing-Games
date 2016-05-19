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

#ifndef STEREOFRAMEWORK_H
#define STEREOFRAMEWORK_H

#include "Stereo3D/StereoZoom.h"

namespace Stereo3D
{	
  void Update(float deltaTime);

  namespace Zoom
  {
    void SetFinalPlaneDist(float planeDist, float transitionTime);
    void SetFinalEyeDist(float eyeDist, float transitionTime);
    void ReturnToNormalSetting(float);
  } // namespace zoom

  namespace Weapon{
    const int MAX_RAY_IDS = 5;
    const QueuedRayID INVALID_RAY_ID = 0;

    class CWeaponCheck
    {
    public:
      CWeaponCheck() : m_closestCastDist(1000.f) {}
      ~CWeaponCheck();
      void Update(float deltaTime);
      void OnRayCastResult(const QueuedRayID &rayID, const RayCastResult &result);
      float GetCurrentPlaneDist();

    private:
      void CastRays();

      float  m_closestDist;
      float  m_closestCastDist;
      QueuedRayID m_rayIDs[MAX_RAY_IDS];
      uint8  m_numFramesWaiting;
      uint8  m_numResults;
    };
  } // 
} // namespace Stereo3D

#endif

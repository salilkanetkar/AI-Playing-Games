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

#ifndef PLAYERSTUMBLE_H
#define PLAYERSTUMBLE_H

#pragma once

namespace PlayerActor
{
  namespace Stumble
  {
    struct StumbleParameters
    {
      float minDamping;
      float maxDamping;
      float periodicTime;
      float strengthX;
      float strengthY;
      float randomness;
    };

    class CPlayerStumble
    {
    public:
      CPlayerStumble();
      void Disable();
      bool Update(float deltaTime, const pe_status_dynamics &dynamics);
      void Start(StumbleParameters* stumbleParameters);

      inline const Vec3& GetCurrentActionImpulse() const { return m_finalActionImpulse; }
    protected:
    private:
    public:
    protected:
    private:
      StumbleParameters m_stumbleParameter;
      Vec3	m_finalActionImpulse;
      float m_currentPeriodicScaleX;
      float m_currentPeriodicScaleY;
      float m_currentPastTime;
    };
  } // namespace Stumble
} // namespace Player















#endif


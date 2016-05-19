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

// Description : Automatic shotgun firemode. It works like the shotgun one, spawning
//               several pellets on a single shot, but doesn't require 'pump' action
//               and it has a 'single' magazine reload


#pragma once

#ifndef _AUTOMATIC_SHOTGUN_H_
#define _AUTOMATIC_SHOTGUN_H_

#include "Shotgun.h"

class CAutomaticShotgun : public CShotgun
{
public:
	CRY_DECLARE_GTI(CAutomaticShotgun);

	CAutomaticShotgun();
	virtual ~CAutomaticShotgun();

	virtual void Update(float frameTime, uint32 frameId);
	virtual void StartFire();
	virtual void StopFire();
	virtual void Activate(bool activate);
	virtual void StartReload(int zoomed);
	virtual void EndReload(int zoomed);

	virtual void CancelReload();
	virtual bool CanCancelReload();

	void GetMemoryUsage(ICrySizer * s) const
	{
		s->AddObject(this, sizeof(*this));	
		CShotgun::GetInternalMemoryUsage(s);		// collect memory of parent class
	}

private:
	float m_rapidFireCountdown;
	bool m_firing;
};

#endif
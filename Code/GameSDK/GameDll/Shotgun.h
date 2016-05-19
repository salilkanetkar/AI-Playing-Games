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

#pragma once

#ifndef _SHOTGUN_H_
#define _SHOTGUN_H_

#include "Single.h"

class CShotgun :
	public CSingle
{
	struct BeginReloadLoop;
	class PartialReloadAction;
	class ReloadEndAction;
	class ScheduleReload;

public:
	CRY_DECLARE_GTI(CShotgun);

	virtual void GetMemoryUsage(ICrySizer * s) const;
	void GetInternalMemoryUsage(ICrySizer * s) const;
	virtual void Activate(bool activate);
	virtual void StartReload(int zoomed);
	void ReloadShell(int zoomed);
	virtual void EndReload(int zoomed);
	using CSingle::EndReload;
	
	virtual void CancelReload();

#ifdef SERVER_CHECKS
	virtual float GetDamageAmountAtXMeters(float x);
#endif

	virtual bool CanFire(bool considerAmmo) const;

	virtual bool Shoot(bool resetAnimation, bool autoreload = true , bool isRemote=false );
	virtual void NetShootEx(const Vec3 &pos, const Vec3 &dir, const Vec3 &vel, const Vec3 &hit, float extra, int ph);

	virtual float GetSpreadForHUD() const;

	virtual uint8 GetShotIncrementAmount()
	{
		return (uint8)m_fireParams->shotgunparams.pellets;
	}

private:

	int   m_max_shells;
	uint8 m_shotIndex;

	bool	m_reload_pump;
	bool	m_load_shell_on_end;				
	bool	m_break_reload;
	bool	m_reload_was_broken;

};

#endif

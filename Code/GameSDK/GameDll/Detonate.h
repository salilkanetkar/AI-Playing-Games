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

// Description : Detonation Fire Mode Implementation


#ifndef __DETONATE_H__
#define __DETONATE_H__

#if _MSC_VER > 1000
# pragma once
#endif


#include "Single.h"

class CDetonate :
	public CSingle
{
private:
	
	typedef CSingle BaseClass;
	struct ExplodeAction;
	struct DropRemoveAction;

public:
	CRY_DECLARE_GTI(CDetonate);

	CDetonate();
	virtual ~CDetonate();

	//IFireMode
	virtual void Update(float frameTime, uint32 frameId);
	virtual void GetMemoryUsage(ICrySizer * s) const
	{ 
		s->AddObject(this, sizeof(*this));	
		CSingle::GetInternalMemoryUsage(s);		// collect memory of parent class
	}

	virtual void Activate(bool activate);

	virtual bool CanReload() const;

	virtual bool CanFire(bool considerAmmo = true) const;
	virtual void StartFire();

	virtual void NetShoot(const Vec3 &hit, int ph);
	//~IFireMode

#ifdef SERVER_CHECKS
	virtual float GetDamageAmountAtXMeters(float x);
#endif

	virtual void SetCanDetonate(bool canDet);
	virtual const char *GetCrosshair() const;

	bool ClientCanDetonate() { return m_canDetonate; }

	void OutOfAmmoExplode();
	void DropRemoveItem();

protected:
	bool Detonate(bool net=false);
	void SelectLast();

	float	m_detonationTimer;
	bool	m_canDetonate;
};


#endif //__DETONATE_H__
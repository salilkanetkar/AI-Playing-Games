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

// Description : A dummy player used to simulate a client player for profiling purposes


#ifndef __DUMMYPLAYER_H__
#define __DUMMYPLAYER_H__

#if (USE_DEDICATED_INPUT)

#include "Player.h"
#include "AIDemoInput.h"

class CDummyPlayer : public CPlayer
{
public:
	DECLARE_COMPONENT_TYPE("CDummyPlayer", 0x24F9B3D7DB074882, 0x8D239F5C2B1E66E2)
	CDummyPlayer();
	virtual ~CDummyPlayer();

	virtual bool IsPlayer() const { return true; }
	
	virtual bool Init( IGameObject * pGameObject );
	virtual void Update(SEntityUpdateContext& ctx, int updateSlot);

	EDefaultableBool GetFire();
	void SetFire(EDefaultableBool value);
	EDefaultableBool GetMove();
	void SetMove(EDefaultableBool value);

	void GetMemoryUsage(ICrySizer *pSizer) const
	{
		pSizer->AddObject(this, sizeof(*this));
		CPlayer::GetInternalMemoryUsage(pSizer); // collect memory of parent class
	}

protected:
	virtual void OnChangeTeam();

private:
};

#endif //USE_DEDICATED_INPUT

#endif //!__DUMMYPLAYER_H__

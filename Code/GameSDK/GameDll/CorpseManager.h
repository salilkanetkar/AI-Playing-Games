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

// Description : 'Corpse Manager' used to control number of corpses in a level


#ifndef __CORPSEMANAGER_H__
#define __CORPSEMANAGER_H__

#if _MSC_VER > 1000
# pragma once
#endif

#define MAX_CORPSES (24)

#include <CryFixedArray.h>
#include "GameRulesModules/IGameRulesRoundsListener.h"

class CCorpseManager : IGameRulesRoundsListener
{
	enum ECorpseFlags
	{
		eCF_NeverSleep		=BIT(0),
	};

	struct SCorpseInfo
	{
		SCorpseInfo(EntityId _id, Vec3 _pos, float _thermalVisionHeat)
			:	corpseId(_id)
			, corpsePos(_pos)
			, age(0.0f)
			, awakeTime(0.f)
			, thermalVisionHeat(_thermalVisionHeat)
			, flags(0)
		{}
		
		Vec3 corpsePos;
		float age;
		float awakeTime;
		float thermalVisionHeat;
		EntityId corpseId;
		uint8 flags;
	};

public:
	CCorpseManager(); 
	~CCorpseManager(); 

	void RegisterCorpse(EntityId corpseId, Vec3 corpsePos, float thermalVisionHeat);
	void RemoveACorpse();
	void Update(float frameTime);
	void KeepAwake(const EntityId corpseId, IPhysicalEntity* pCorpsePhys);
	void ClearCorpses();

	// IGameRulesRoundsListener
	virtual void OnRoundStart() { ClearCorpses(); }
	virtual void OnRoundEnd() {}
	virtual void OnSuddenDeath() {}
	virtual void ClRoundsNetSerializeReadState(int newState, int curState) {}
	virtual void OnRoundAboutToStart() {};
	//~IGameRulesRoundsListener

private:

	void UpdateCorpses(float frameTime);
	void OnRemovedCorpse(const EntityId corpseId);

	CryFixedArray<SCorpseInfo, MAX_CORPSES>  m_activeCorpses;

	bool m_bThermalVisionOn;
};


#endif // __CORPSEMANAGER_H__

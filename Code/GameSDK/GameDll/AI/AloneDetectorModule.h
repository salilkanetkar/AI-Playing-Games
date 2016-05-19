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

// Description : This is used for detecting the proximity of a specific 
//               set of AI agents to drive the selection of the behavior in
//               the tree without specific checks in the behavior itself

#ifndef __AloneDetectorModule_h__
#define __AloneDetectorModule_h__

#pragma once

#include "GameAIHelpers.h"

class Agent;

class AloneDetectorContainer : public CGameAIInstanceBase
{
public:
	typedef uint8 FactionID;

	struct AloneDetectorSetup
	{
		enum State
		{
			Alone,
			EntitiesInRange,
			Unkown,
		};

		AloneDetectorSetup(
			const float _rangeSq, 
			const char* _aloneSignal, 
			const char* _notAloneSignal
			)
			:range(_rangeSq)
			,aloneSignal(_aloneSignal)
			,notAloneSignal(_notAloneSignal)
			,state(Unkown)
		{
		}

		AloneDetectorSetup():state(Unkown)
		{
		}

		float		range;
		string		aloneSignal;
		string		notAloneSignal;
		State		state;
	};

	void		Update(float frameTime);
	void		SetupDetector(const AloneDetectorSetup& setup);
	void		AddEntityClass(const char* const entityClassName);
	void		RemoveEntityClass(const char* const entityClassName);
	void		ResetDetector();
	bool		IsAlone() const;

private:
	float		GetSqDistanceFromLocation(const Vec3& location) const;
	void		SendCorrectSignal();

	const char* GetActorClassName(const Agent& agent) const;
	bool		IsActorValid(const Agent& agent) const;

	AloneDetectorSetup	m_setup;
	typedef std::vector<string> EntitiesList;
	EntitiesList		m_entityClassNames;
};

class AloneDetectorModule : public AIModuleWithInstanceUpdate<AloneDetectorModule, AloneDetectorContainer, 16, 8>
{
public:
	virtual const char* GetName() const { return "AloneDetector"; }
};

#endif // __AloneDetectorModule_h__
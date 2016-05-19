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

// Description : Holds a CMovementTransitions object for each entity class
#pragma once
#ifndef __MOVEMENT_TRANSITIONS_SYSTEM_H
#define __MOVEMENT_TRANSITIONS_SYSTEM_H

class CMovementTransitions;
class CMovementTransitionsSystem
{
public:
	// public methods
	CMovementTransitionsSystem();
	~CMovementTransitionsSystem();

	CMovementTransitions*const GetMovementTransitions(IEntity* pEntity);
	CMovementTransitions*const GetMovementTransitions(IEntityClass* pEntityClass, SmartScriptTable pEntityScript);

	void GetMemoryUsage(ICrySizer* s) const;
	void Reload() const;
	void Flush();

private:
	// private types
	typedef std::vector<CMovementTransitions*> MovementTransitionsVector;

	// private methods
	CMovementTransitionsSystem(const CMovementTransitionsSystem&) {}
	CMovementTransitionsSystem& operator=(const CMovementTransitionsSystem&) { return *this; }

	// private fields
	MovementTransitionsVector m_entityTransitions;
};

#endif // __MOVEMENT_TRANSITIONS_SYSTEM_H
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

// Description : Various definitions that are shared between the mastermind module and
//               depended systems.


#pragma once

#ifndef MastermindModuleShared_h
#define MastermindModuleShared_h


namespace Mastermind
{


// Just a helper container in which to store the configuration for the mastermind
// module instance.
class MastermindModuleInstanceConfig
{
public:

	// The search radius (from the pivot of the owner agent) (>= 0.0f) 
	// (in meters).
	float								m_SearchRadius;

	// Setup: The resurrection radius (from the pivot of the owner agent) (>= 0.0f)
	// (in meters). So this is actually the area to resurrect entities in.
	float								m_ResurrectionRadius;

	// The name of the signal that should be send to the owner when resurrectable
	// targets are within the search range.
	string								m_ResurrectablesAvailableSignal;

	// The name of the signal that should be send to the owner when resurrectable
	// targets are not within the search range.
	string								m_ResurrectablesUnavailableSignal;

	// The shield entity forward offset distance (in meters).
	float								m_ShieldForwardOffset;

	// The shield entity upwards offset distance (in meters).
	float								m_ShieldUpwardOffset;

	// The name of the signal that should be send to the owner when husks
	// have been spawned.
	string								m_HusksSpawnedSignal;

	// The name of the signal that should be send to the owner when all
	// spawned husks have been destroyed.
	string								m_HusksAllDestroyedSignal;

	// The delay before the Mastermind and the other Husks will be reported
	// of the sighting of an enemy by one of the Husks (>= 0.0f) (in seconds).
	// This setting is mostly relevant for when the Mastermind is in defensive 
	// mode and the player has managed to sneak up behind him.
	float								m_EnemySpottedByHuskNotifyDelay;


public:
	MastermindModuleInstanceConfig();
};


}; // namespace Mastermind


#endif // MastermindModuleShared_h
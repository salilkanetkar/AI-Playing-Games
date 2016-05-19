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

#ifndef Assignments_h
#define Assignments_h

struct Assignment
{
	// When changing this enum please maintain the same values for the types 
	// (so that validity of the saved games is kept) and the corresponding references to 
	// the global lua values set in ScriptBind_GameAI.cpp /Mario 08-12-2011
	enum Type
	{
		NoAssignment        = 0,
		DefendArea          = 1,
		HoldPosition        = 2,
		CombatMove          = 3,
		ScanSpot            = 4,
		ScorchSpot          = 5,
		PsychoCombatAllowed = 6,
	};

	Assignment()
		: type(NoAssignment)
	{}

	Assignment(Type type_, SmartScriptTable data_)
		: type(type_)
		, data(data_)
	{}

	Type type;
	SmartScriptTable data;
};

#endif //Assignments_h
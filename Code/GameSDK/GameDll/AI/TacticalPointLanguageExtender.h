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

#ifndef TACTICAL_POINT_LANGUAGE_EXTENDER_H
#define TACTICAL_POINT_LANGUAGE_EXTENDER_H

#include "ITacticalPointSystem.h"

class CAIBattleFrontModule;

namespace FlankCalculator
{
	bool IsPointOnMyFlank(EntityId actorEntityID, const Vec3& actorPos, const Vec3& targetPos, const Vec3& pointPos);
}

class CTacticalPointLanguageExtender : public ITacticalPointLanguageExtender
{
public:
	CTacticalPointLanguageExtender();

	void Reset();
	void FullSerialize(TSerialize ser);

	void Initialize();
	void Deinitialize();
	virtual bool GeneratePoints(TGenerateParameters& parameters, SGenerateDetails& details, TObjectType object, const Vec3& objectPos, TObjectType auxObject, const Vec3& auxObjectPos) const;
	virtual bool GetObject(TObjectParameters& parameters) const;
	virtual bool BoolTest(TBoolParameters& params, TObjectType pObject, const Vec3& objPos, TPointType point) const;

private:
	void RegisterWithTacticalPointSystem();
	void RegisterQueries();
	void UnregisterFromTacticalPointSystem();
	void UnregisterQueries();
	IAIObject* GetBattleFrontObject() const;
	void ReleaseBattleFrontObject();

	mutable tAIObjectID m_battlefrontAIObject;
};

#endif // TACTICAL_POINT_LANGUAGE_EXTENDER_H

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

#ifndef MOCKENTITYSYSTEM_H
#define MOCKENTITYSYSTEM_H


#include <EngineFacade/EngineFacade.h>


class CMockEnginePhysicalEntity: public EngineFacade::CNullEnginePhysicalEntity
{
public:
	CMockEnginePhysicalEntity();

	virtual void SetParamsResult(int result);
	virtual int SetParams(pe_params* params);

	virtual void SetReturnParams(pe_player_dynamics params);
	virtual int GetParams(pe_params* params);

	virtual void Action(pe_action* action);
	int GetActionCount();

private:
	int setParamsResult;
	pe_player_dynamics setReturnParams;
	int m_actionCounter;
};


class CMockEngineEntity: public EngineFacade::CNullEngineEntity
{
public:
	CMockEngineEntity();

	virtual EngineFacade::IEnginePhysicalEntity& GetPhysicalEntity();

	virtual const Matrix34& GetSlotWorldTM( int nSlot ) const;
	virtual const Matrix34& GetWorldTM() const;
	virtual Ang3 GetWorldAngles() const;
	virtual	Vec3 GetWorldPos() const;
	virtual void SetWorldPos(Vec3 worldPos);

	virtual Quat GetWorldRotation() const;
	virtual void SetWorldRotation(Quat rotation);

private:
	CMockEnginePhysicalEntity m_mockedPhysicalEntity;

	Vec3 m_worldPos;
	Quat m_worldRotation;
	Ang3 m_worldAngles;
	Matrix34 m_WorldMatrix;
};


class CMockEntitySystem: public EngineFacade::CEngineEntitySystem
{
public:
	CMockEntitySystem();

	virtual EngineFacade::IEngineEntity::Ptr GetEntityByID(EntityId id);

    void Use(EngineFacade::IEngineEntity::Ptr entity);

private:
	EngineFacade::IEngineEntity::Ptr mockedEntity;
};


#endif 

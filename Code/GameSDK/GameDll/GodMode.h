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

#ifndef GOD_MODE_H
#define GOD_MODE_H

class CActor;

enum EGodModeState
{
	eGMS_None,
	eGMS_GodMode,
	eGMS_TeamGodMode,
	eGMS_DemiGodMode,
	eGMS_NearDeathExperience,
	eGMS_LAST
};

class CGodMode
{
public:
	static CGodMode& GetInstance();

	void RegisterConsoleVars(IConsole* pConsole);
	void UnregisterConsoleVars(IConsole* pConsole) const;

	void MoveToNextState();
	bool RespawnIfDead(CActor* actor) const;
	bool RespawnPlayerIfDead() const;

	EGodModeState GetCurrentState() const;
	const char* GetCurrentStateString() const;

	void Update(float frameTime);
	void DemiGodDeath();

	bool IsGod() const;
	bool IsDemiGod() const;
	bool IsGodModeActive() const;

	void ClearCheckpointData();
	void SetNewCheckpoint(const Matrix34& rWorldMat);

private:
	CGodMode();
	CGodMode(const CGodMode&);
	CGodMode& operator=(const CGodMode&);

	static const float m_timeToWaitBeforeRespawn;
	static const char* m_godModeCVarName;
	static const char* m_demiGodRevivesAtCheckpointCVarName;

	float m_elapsedTime;
	int m_godMode;
	int m_demiGodRevivesAtCheckpoint;

	bool m_hasHitCheckpoint;
	bool m_respawningFromDemiGodDeath;
	Matrix34	m_lastCheckpointWorldTM;
};

#endif

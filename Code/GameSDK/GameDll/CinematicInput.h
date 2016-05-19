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

// Description : Controls script variables coming from track view to add some
//               control feedback during cutscenes


#pragma once

#ifndef _CINEMATIC_INPUT_H_
#define _CINEMATIC_INPUT_H_

#define CINEMATIC_INPUT_PC_MOUSE 1


class CWeapon;

class CCinematicInput
{
	struct SUpdateContext
	{
		SUpdateContext()
			: m_frameTime(0.0333f)
			, m_lookUpLimit(0.0f)
			, m_lookDownLimit(0.0f)
			, m_lookLeftLimit(0.0f)
			, m_lookRightLimit(0.0f)
			, m_recenter(true)
		{

		}

		float m_frameTime;
		float m_lookUpLimit;
		float m_lookDownLimit;
		float m_lookLeftLimit;
		float m_lookRightLimit;
		bool  m_recenter;
	};

	struct SCinematicWeapon
	{
		SCinematicWeapon()
		{
			Reset();
		}

		void Reset()
		{
			m_weaponId = 0;
			m_parentId = 0;
		}

		EntityId	m_weaponId;
		EntityId	m_parentId;
	};

public:

	enum Weapon
	{
		eWeapon_Primary = 0,
		eWeapon_Secondary,
		eWeapon_ClassCount,
	};

	CCinematicInput();
	~CCinematicInput();

	void OnBeginCutScene(int cutSceneFlags);
	void OnEndCutScene(int cutSceneFlags);

	void Update(float frameTime);

	void SetUpWeapon( const CCinematicInput::Weapon& weaponClass, const IEntity* pEntity );
	void OnAction( const EntityId actorId, const ActionId& actionId, int activationMode, float value);

	ILINE bool IsAnyCutSceneRunning() const 
	{ 
		return (m_cutsceneRunningCount > 0); 
	}

	ILINE bool IsPlayerNotActive() const
	{
		return (m_cutscenesNoPlayerRunningCount > 0);
	}

	void OnRayCastDataReceived(const QueuedRayID& rayID, const RayCastResult& result);

private:

	void UpdateForceFeedback(IScriptSystem* pScriptSystem, float frameTime);
	void UpdateAdditiveCameraInput(IScriptSystem* pScriptSystem, float frameTime);

	void UpdateWeapons();
	void UpdateWeaponOrientation( IEntity* pWeaponEntity, const Vec3& targetPosition );

	Ang3 UpdateAdditiveCameraInputWithMouse(const CCinematicInput::SUpdateContext& updateCtx, const Ang3& rawMouseInput);
	Ang3 UpdateAdditiveCameraInputWithController(const CCinematicInput::SUpdateContext& updateCtx, const Ang3& rawMouseInput);

	void RefreshInputMethod(const bool isMouseInput);

	void ClearCutSceneVariables();
	void DisablePlayerForCutscenes();
	void ReEnablePlayerAfterCutscenes();
	void TogglePlayerThirdPerson(bool bEnable);

	CWeapon* GetWeapon(const CCinematicInput::Weapon& weaponClass) const;

	Ang3	m_controllerAccumulatedAngles;
	int		m_cutsceneRunningCount;
	int		m_cutscenesNoPlayerRunningCount;
	bool	m_bPlayerIsThirdPerson;
	int		m_iHudState;

	SCinematicWeapon m_weapons[eWeapon_ClassCount];
	QueuedRayID m_aimingRayID;
	float				m_aimingDistance;

#if CINEMATIC_INPUT_PC_MOUSE
	Ang3	m_mouseAccumulatedAngles;
	Ang3	m_mouseAccumulatedInput;
	float m_mouseRecenterTimeOut;
	bool	m_lastUpdateWithMouse;
#endif
};

#endif
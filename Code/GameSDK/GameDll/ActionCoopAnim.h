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

// Description : Implements Coop Anim.


#pragma once

#ifndef __ActionCoopAnim_h__
#define __ActionCoopAnim_h__

#include "ICryMannequin.h"
#include "PlayerAnimation.h"
#include "IEntityPoolManager.h"

class CPlayer;
class CActor;

class CActionCoopAnimation : public TPlayerAction, public IEntityPoolListener, public IEntityEventListener
{
public:

	DEFINE_ACTION( "CoopAnim" )

	struct SActionCoopParams
	{
		SActionCoopParams( CPlayer &player, CActor &target, FragmentID fragID, TagState tagState, TagID targetTagID, const IAnimationDatabase* piOptionalDatabase )
			:
		m_player(player),
		m_target(target),
		m_fragID(fragID),
		m_tagState(tagState),
		m_targetTagID(targetTagID),
		m_piOptionalTargetDatabase(piOptionalDatabase)
		{
		}

		CPlayer& m_player;
		CActor& m_target;
		FragmentID m_fragID;
		TagState m_tagState;
		TagID m_targetTagID;
		const IAnimationDatabase* m_piOptionalTargetDatabase;
	};

	explicit CActionCoopAnimation( const SActionCoopParams& params );
	~CActionCoopAnimation();


protected:

	virtual void Install();
	virtual void Enter();
	virtual void Exit();

	// IEntityPoolListener
	virtual void OnEntityReturningToPool(EntityId entityId, IEntity *pEntity);
	// ~IEntityPoolListener

	// IEntityEventListener
	virtual void OnEntityEvent( IEntity *pEntity,SEntityEvent &event );
	// ~IEntityEventListener

	void RemoveTargetFromSlaveContext();
	void SendStateEventCoopAnim();

	CPlayer &m_player;
	CActor  &m_target;
	EntityId m_targetEntityID;
	TagID m_targetTagID;
	const IAnimationDatabase* m_piOptionalTargetDatabase;

private:
	CActionCoopAnimation(); // DO NOT IMPLEMENT!!!
};


#endif// __ActionCoopAnim_h__

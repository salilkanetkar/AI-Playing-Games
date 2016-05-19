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

#ifndef Agent_inl
#define Agent_inl


// =======================================================================
//	Query if the agent is dead.
//
//	Returns:	True if dead; otherwise false.
//
inline bool Agent::IsDead() const
{
	const IActor* actor = GetActor();
	assert(actor);

	if (actor)
		return actor->IsDead();
	else
		return true;
}


// =======================================================================
//	Query if the agent is hidden.
//
//	Also see IEntity::IsHidden()
//
//	Returns:	True if the agent is hidden; otherwise false.
//
inline bool Agent::IsHidden() const
{
	assert(GetEntity() != NULL);
	return GetEntity()->IsHidden();
}


// =======================================================================
//	Get the actor interface.
//
//	Returns:	The actor interface (or NULL if it could not be obtained).
//
inline const IActor* Agent::GetActor() const
{
	return g_pGame->GetIGameFramework()->GetIActorSystem()->GetActor(GetEntityID());
}


#endif // Agent_inl

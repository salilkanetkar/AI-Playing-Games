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

// Description : Interactive objects are registered here with required params


#pragma once

#ifndef __INTERACTIVEOBJECT_REGISTRY_H__
#define __INTERACTIVEOBJECT_REGISTRY_H__

#include "../Utility/CryHash.h"
#include "ItemString.h"

#include <ICryMannequinDefs.h>
#include "InteractiveObjectEnums.h"
#include "ICryMannequinProceduralClipFactory.h"

class IActionController;
class IAnimationDatabase;
struct SControllerDef;

class CInteractiveObjectRegistry
{
public : 

	struct SInteraction
	{
		const char *helper;
		TagID			  targetStateTagID;
	};

	struct SMannequinParams
	{
		TagID interactionTagID;
		TagID stateTagID;

		SMannequinParams()
			: interactionTagID(TAG_ID_INVALID)
			, stateTagID(TAG_ID_INVALID)
		{

		}

		void GetMemoryUsage(ICrySizer *pSizer) const
		{

		}
	};

private:

	typedef std::map< EntityId, SMannequinParams > TEntityToTagMap;

public:

	void Init();
	void Shutdown();

	void OnInteractiveObjectSutdown(const EntityId entityId);

	TagID GetInteractionTag(const char* interactionName) const;
	const SMannequinParams GetInteractionTagForEntity(const EntityId entityId, const int interactionIndex) const;

	void QueryInteractiveActionOptions( const EntityId entityId, const TagID interactionTag, const TagID stateTagId, std::vector<SInteraction> &options);
	void ApplyInteractionToObject(IEntity *pEntity, const TagID interactionTypeTag, const int interactionIndex) const;

	void GetMemoryUsage(ICrySizer *pSizer) const
	{
		pSizer->AddContainer(m_entityToTag);
	}

private:

	TEntityToTagMap			m_entityToTag;
	IProceduralClipFactory::THash m_clipLocatorHash;

	FragmentID m_interactFragID;
	const IAnimationDatabase *m_pDatabasePlayer;
	const IAnimationDatabase *m_pDatabaseObject;
	const SControllerDef *m_pControllerDef;
};

#endif

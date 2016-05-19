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

#ifndef __CGAMEMECHANISMBASE_H__
#define __CGAMEMECHANISMBASE_H__

#include "GameMechanismEvents.h"

#if defined(_RELEASE)
#define INCLUDE_NAME_IN_GAME_MECHANISMS 0 // Do not switch this on! [TF]
#else
#define INCLUDE_NAME_IN_GAME_MECHANISMS 1
#endif

#if INCLUDE_NAME_IN_GAME_MECHANISMS
// NB: Specifying the wrong class name in the REGISTER_GAME_MECHANISM macro will now fail to compile, so it should be
// impossible (or trickier at least) to accidentally register your game mechanism instance with the wrong name. [TF]
#define REGISTER_GAME_MECHANISM(classType) CGameMechanismBase((GetConstSelf() == (classType *) NULL) ? NULL : (# classType))
#else
#define REGISTER_GAME_MECHANISM(classType) CGameMechanismBase(NULL)
#endif

class CGameMechanismBase
{
	public:
	struct SLinkedListPointers
	{
		CGameMechanismBase * m_nextMechanism;
		CGameMechanismBase * m_prevMechanism;
	};

	CGameMechanismBase(const char * className);
	virtual ~CGameMechanismBase();
	virtual void Update(float dt) = 0;
	virtual void Inform(EGameMechanismEvent gmEvent, const SGameMechanismEventData * data) {}

	ILINE SLinkedListPointers * GetLinkedListPointers()
	{
		return & m_linkedListPointers;
	}

#if INCLUDE_NAME_IN_GAME_MECHANISMS
	ILINE const char * GetName()
	{
		return m_className;
	}
#else
	ILINE const char * GetName()
	{
		return "?";
	}
#endif

	protected:
	// Get a const 'this' pointer which we're allowed to use during subclass initialization without disabling warning C4355
	inline const CGameMechanismBase * GetConstSelf() const { return this; }

	private:
	SLinkedListPointers m_linkedListPointers;

#if INCLUDE_NAME_IN_GAME_MECHANISMS
	const char * m_className;
#endif
};

#endif //__CGAMEMECHANISMBASE_H__
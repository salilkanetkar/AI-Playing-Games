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

#ifndef __CRY_HASH_UTIL_H__
#define __CRY_HASH_UTIL_H__

#include <StringUtils.h>

//-----------------------------------------------------------------------------------
// HASH Tools.
// from Frd's code-base courtesy of AW. /FH
typedef uint32 CryHash;

struct CryHashStringId
{
	CryHashStringId()
		: id (0)
	{

	}

	CryHashStringId(CryHash _id)
		: id (_id)
	{

	}

	CryHashStringId( const char* _name )
	{
		Set(_name);
	}

	CryHashStringId(const CryHashStringId& _otherId)
	{
#if defined(_DEBUG)
		debugName = _otherId.debugName;
#endif
		id = _otherId.id;
	}

	void Set( const char* _name )
	{
		CRY_ASSERT(_name);
#if defined(_DEBUG)
		debugName = _name;
#endif
		id = CryStringUtils::HashString(_name);
	}

	ILINE bool operator == (const CryHashStringId& rhs) const
	{
		return (id == rhs.id);
	}

	ILINE bool operator != (const CryHashStringId& rhs) const
	{
		return (id != rhs.id);
	}

	ILINE bool operator <= (const CryHashStringId& rhs) const
	{
		return (id <= rhs.id);
	}

	ILINE bool operator < (const CryHashStringId& rhs) const
	{
		return (id < rhs.id);
	}

	ILINE bool operator >= (const CryHashStringId& rhs) const
	{
		return (id >= rhs.id);
	}

	ILINE bool operator > (const CryHashStringId& rhs) const
	{
		return (id > rhs.id);
	}

	void GetMemoryUsage(ICrySizer* pSizer) const
	{
#if defined(_DEBUG)
		pSizer->AddObject(debugName);
#endif
	}

	const char* GetDebugName() const
	{
#if defined(_DEBUG)
		return debugName.c_str();
#else
		return "";
#endif
	}

	//This is useful for look ups in debug, so we don't allocate strings
	static CryHashStringId GetIdForName(const char* _name);

#if defined(_DEBUG)
	string debugName;
#endif
	CryHash id;
};

#endif // __CRY_HASH_UTIL_H__

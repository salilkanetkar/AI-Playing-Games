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

// Description : Class for returning a fake session list to session searches.
//               Aim is to use this to test match making performance
//               The fake session lists are loaded from XML files


#ifndef __SESSIONSEARCHSIMULATOR_H__
#define __SESSIONSEARCHSIMULATOR_H__

//For SCrySessionID and CRYSESSIONID_STRINGLEN
#include "ICryLobby.h"
//For CryMatchmakingSessionSearchCallback
#include "ICryMatchMaking.h"


//////////////////////////////////////////////////////////////////////////
//The session search simulator class
class CSessionSearchSimulator
{
public:
	CSessionSearchSimulator();
	~CSessionSearchSimulator();

	bool OpenSessionListXML( const char* filepath );
	bool OutputSessionListBlock( CryLobbyTaskID& taskID, CryMatchmakingSessionSearchCallback cb, void* cbArg );

	//Inlines
	const char* GetCurrentFilepath() { return m_currentFilepath.c_str(); }

private:
	CryFixedStringT< ICryPak::g_nMaxPath >	m_currentFilepath;

	XmlNodeRef	m_sessionListXML;
	int	m_currentNode;
};

//////////////////////////////////////////////////////////////////////////
// Fake Session IDs used by Session Search Simulator.
// They are only required to display session IDs read in as strings
struct SCryFakeSessionID : public SCrySessionID
{
	char m_idStr[CRYSESSIONID_STRINGLEN];
	
	bool operator == (const SCrySessionID &other)
	{
		char otherIdStr[CRYSESSIONID_STRINGLEN];
		other.AsCStr( otherIdStr, CRYSESSIONID_STRINGLEN );
		return ( strcmpi( m_idStr, otherIdStr ) == 0 );
	}
	
	bool operator < (const SCrySessionID &other)
	{
		char otherIdStr[CRYSESSIONID_STRINGLEN];
		other.AsCStr( otherIdStr, CRYSESSIONID_STRINGLEN );
		return ( strcmpi( m_idStr, otherIdStr ) < 0 );
	}
	
	bool IsFromInvite() const
	{
		return false;
	}

	void AsCStr( char* pOutString, int inBufferSize ) const
	{
		if (pOutString && inBufferSize > 0)
		{
			size_t len = inBufferSize > sizeof(m_idStr) ? sizeof(m_idStr) : inBufferSize;
			memcpy( pOutString, m_idStr, len);
			pOutString[len-1]=0;
		}
	}
};


#endif	//__SESSIONSEARCHSIMULATOR_H__


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

#if defined(SERVER_CHECKS)

#ifndef __PLAYERPOSITIONCHECKER_H__
#define __PLAYERPOSITIONCHECKER_H__

class CPlayer;

class CPlayerPositionChecker
{
public:
	CPlayerPositionChecker(void);
	~CPlayerPositionChecker(void);

	void Update(float fFrameTime);

private:
	struct SPlayerRayCast
	{
		int nLastPlayerTested;
		EntityId lastPlayerTested;
		QueuedRayID rayId;
	};

	struct SHeightCheck : public SPlayerRayCast
	{
		float fStartTimeInAir;
		bool	bHighFrequencyChecks;
	} m_HeightCheck;

	void OnHeightCheckRayCastDataReceived( const QueuedRayID& rayID, const RayCastResult& result );
	void CancelRayCastRequest( SPlayerRayCast& rPlayerRayCast );
	void QueueNextPlayerHeightCheckRayCast( );
	void QueueHeightCheckRayCast( EntityId playerId );

	bool ShouldCheckPlayer( CPlayer * pPlayer );
};

#endif //__PLAYERPOSITIONCHECKER_H__

#endif //SERVER_CHECKS
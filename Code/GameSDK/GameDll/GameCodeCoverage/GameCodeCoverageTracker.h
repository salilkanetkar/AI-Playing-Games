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

// Description : Defines code coverage check points
//               and a central class to track their registration

/**
* Design notes:
*   See the CGameCodeCoverageManager class that acts as the high-level API to the system
*   A (separate) tracking GUI is crucial to this system - an efficient interface to service this is not trivial
*
* Technical notes:
*   The manager would appear to lend itself to a map of names to checkpoint pointers for quick lookup
*   However I really want to keep overhead to a minimum even in registering and I guess we might have 1000 CCCPoints
*   A vector, with some sorting or heapifying might be better when the code matures
*/


#ifndef __GAME_CODE_COVERAGE_TRACKER_H_
#define __GAME_CODE_COVERAGE_TRACKER_H_

#pragma once

#include "GameCodeCoverage/GameCodeCoverageEnabled.h"

#if ENABLE_SHARED_CODE_COVERAGE

#define CCCPOINT(x) CODECHECKPOINT(x)
#define CCCPOINT_IF(check, x) if(check) CCCPOINT(x)

#elif ENABLE_GAME_CODE_COVERAGE

#define CCCPOINT(x) do { static CGameCodeCoverageCheckPoint autoReg##x(#x); autoReg##x.Touch(); } while(0)
#define CCCPOINT_IF(check, x) if(check) CCCPOINT(x)

class CGameCodeCoverageCheckPoint
{
	public:
	CGameCodeCoverageCheckPoint( const char * label );

	void Touch();
	ILINE int GetCount() const { return m_nCount; }
	ILINE const char * GetLabel() const { return m_psLabel; }

	protected:
	int m_nCount;
	const char * m_psLabel;
};

#else

#define CCCPOINT(x) (void)(0)
#define CCCPOINT_IF(check, x) (void)(0)

#endif // ENABLE_GAME_CODE_COVERAGE

#endif // __GAME_CODE_COVERAGE_TRACKER_H_
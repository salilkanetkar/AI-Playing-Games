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
#if !defined(__ICRYREWARD_H__)
#define __ICRYREWARD_H__

enum ECryRewardError
{
	eCRE_Queued = 0,		// Reward successfully queued
	eCRE_Busy,					// Reward queue full - try again later
	eCRE_Failed					// Reward process failed
};


// CryRewardCallback
// taskID		-	Task ID allocated when the function was executed
// error		- Error code - eCLE_Success if the function succeeded or an error that occurred while processing the function
// pArg			- Pointer to application-specified data
typedef void (*CryRewardCallback)(CryLobbyTaskID taskID, uint32 playerID, uint32 awardID, ECryLobbyError error, bool alreadyAwarded, void* pArg);



struct ICryReward
{
	// <interfuscator:shuffle>
	virtual ~ICryReward(){}
	// Award
	// Awards an achievement/trophy/reward to the specified player
	// playerID	- player ID
	// awardID	- award ID (probably implemented as an enumerated type)
	// return		- informs the caller that the award was added to the pending queue or not
	virtual ECryRewardError		Award(uint32 playerID, uint32 awardID, CryLobbyTaskID* pTaskID, CryRewardCallback cb, void* pCbArg) = 0;
	// </interfuscator:shuffle>
};

#endif // End [!defined(__ICRYREWARD_H__)]
// [EOF]
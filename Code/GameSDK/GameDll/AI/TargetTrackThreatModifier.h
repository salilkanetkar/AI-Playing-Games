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

// Description : Game-side logic for controlling the threat level of an AI
//               agent's current target


#ifndef __TARGET_TRACK_THREAT_MODIFIER_H__
#define __TARGET_TRACK_THREAT_MODIFIER_H__

#include "ITargetTrackManager.h"

class CTargetTrackThreatModifier : public ITargetTrackThreatModifier
{
public:
	CTargetTrackThreatModifier();
	virtual ~CTargetTrackThreatModifier();
	
	virtual void ModifyTargetThreat(IAIObject &ownerAI, IAIObject &targetAI, const ITargetTrack &track, float &outThreatRatio, EAITargetThreat &outThreat) const;

private:
	// TODO Can these CVars be handled in some other way? Currently live in CryAISystem where they are used for other things as well
	const ICVar *m_pCVar_CloakMinDist;
	const ICVar *m_pCVar_CloakMaxDist;
	const ICVar *m_pCVar_SOMSpeedRelaxed;
	const ICVar *m_pCVar_SOMSpeedCombat;
};

#endif //__TARGET_TRACK_THREAT_MODIFIER_H__

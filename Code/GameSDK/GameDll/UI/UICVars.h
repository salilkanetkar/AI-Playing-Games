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

#ifndef __HUDCVARS_H__
#define __HUDCVARS_H__

//////////////////////////////////////////////////////////////////////////
	
class CUICVars
{

public:

	CUICVars();
	~CUICVars();

	void RegisterConsoleCommandsAndVars( void );
	void UnregisterConsoleCommandsAndVars( void );

	void GetMemoryUsage(ICrySizer *pSizer) const
	{	
		pSizer->AddObject(this, sizeof(*this));
	}

	int					hud_hide;

	int					hud_detach;
	float				hud_bobHud;
	int					hud_debug3dpos;

	int					hud_cameraOverride;
	float				hud_cameraDistance;
	float				hud_cameraOffsetZ;

	float				hud_overscanBorder_depthScale;

	float				hud_cgf_positionScaleFOV;
	float				hud_cgf_positionRightScale;

	int					hud_tagging_enabled;
	float				hud_tagging_duration_assaultDefenders;

	float				hud_warningDisplayTimeSP;
	float				hud_warningDisplayTimeMP;

	float				hud_inputprompts_dropPromptTime;

	float				hud_Crosshair_shotgun_spreadMultiplier;
	float				hud_tagging_duration;
	float				hud_double_taptime;
	float				hud_tagnames_EnemyTimeUntilLockObtained;
	float				hud_InterestPointsAtActorsHeads;

	float				hud_Crosshair_ironsight_fadeInDelay;
	float				hud_Crosshair_ironsight_fadeInTime;
	float				hud_Crosshair_ironsight_fadeOutTime;

	float				hud_Crosshair_laser_fadeInTime;
	float				hud_Crosshair_laser_fadeOutTime;

	float				hud_stereo_icon_depth_multiplier;
	float				hud_stereo_minDist;

	ICVar*      hud_colour_enemy;
	ICVar*      hud_colour_friend;
	ICVar*      hud_colour_squaddie;
	ICVar*      hud_colour_localclient;
};

//////////////////////////////////////////////////////////////////////////

#endif



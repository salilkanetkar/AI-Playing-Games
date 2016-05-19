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

// Description : Collects together all the anticheat defines used in the game
//               project


#ifndef __ANTICHEAT_DEFINES_H___
#define __ANTICHEAT_DEFINES_H___

//========================================================================
// ------------------------------ OVERRIDES ------------------------------
// Set these to 1 if you want to force an anticheat system to be enabled
//========================================================================
#define		FORCE__SERVER_CHEAT_MONITOR_ENABLED		0
#define		FORCE__CLIENT_CHEAT_MONITOR_ENABLED		0

//========================================================================
//
// SERVER_CHEAT_MONITOR_ENABLED - Enables server anticheat monitoring code
//
//========================================================================
#ifdef SERVER_CHECKS
#define SERVER_CHEAT_MONITOR_ENABLED		1
#elif FORCE__SERVER_CHEAT_MONITOR_ENABLED
#define SERVER_CHEAT_MONITOR_ENABLED		1
#else
#define SERVER_CHEAT_MONITOR_ENABLED		0
#endif

//========================================================================
//
// CLIENT_CHEAT_MONITOR_ENABLED - Enables client anticheat monitoring code
//
//========================================================================
#if (defined(WIN32) || defined(WIN64)) && !PC_CONSOLE_NET_COMPATIBLE
#define CLIENT_CHEAT_MONITOR_ENABLED		1
#elif FORCE__CLIENT_CHEAT_MONITOR_ENABLED
#define CLIENT_CHEAT_MONITOR_ENABLED		1
#else
#define CLIENT_CHEAT_MONITOR_ENABLED		0
#endif

#endif //__ANTICHEAT_DEFINES_H___ 

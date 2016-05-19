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

// Description : Utilities for debugging input synchronization problems


#ifndef __NETINPUTCHAINDEBUG_H__
#define __NETINPUTCHAINDEBUG_H__

#if !defined(LINUX) && !defined(ORBIS) && !defined(_RELEASE)
	#define ENABLE_NETINPUTCHAINDEBUG 1
#endif

void NetInputChainInitCVars();

#if ENABLE_NETINPUTCHAINDEBUG
void NetInputChainPrint( const char * name, float val );
void NetInputChainPrint( const char * name, const Vec3& val );

extern EntityId _netinputchain_debugentity;

#define NETINPUT_TRACE(ent, val) if (ent != _netinputchain_debugentity); else NetInputChainPrint(#val, val)
#else
#define NETINPUT_TRACE(ent, val) ((void*)0)
#endif

#endif

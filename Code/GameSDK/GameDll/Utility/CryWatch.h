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

// Description : basic onscreen watch
//               in game dll till it matures and can be moved into the engine


#ifndef __CRYWATCH_H__
#define __CRYWATCH_H__

#if !defined(_RELEASE)
#define CRY_WATCH_ENABLED			 (1)
#else
#define CRY_WATCH_ENABLED			 (0)
#endif

#define CryWatch(...) CryWatchFunc(string().Format(__VA_ARGS__))
#define CryWatchLog(...) CryWatchLogFunc(string().Format(__VA_ARGS__))

#if CRY_WATCH_ENABLED

SC_API int CryWatchFunc(const char * message);
SC_API int CryWatchLogFunc(const char * message);
void CryWatch3DAdd(const char * text, const Vec3 & posIn, float lifetime = 2.f, const Vec3 * velocity = NULL, float gravity = 3.f);
void CryWatch3DReset();
void CryWatch3DTick(float dt);

#else

#define CryWatchFunc(message)          (0)
#define CryWatchLogFunc(message)          (0)
#define CryWatch3DAdd(...)             ((void)0)
#define CryWatch3DReset()              ((void)0)
#define CryWatch3DTick(dt)             ((void)0)

#endif // CRY_WATCH_ENABLED

#endif // __CRYWATCH_H__
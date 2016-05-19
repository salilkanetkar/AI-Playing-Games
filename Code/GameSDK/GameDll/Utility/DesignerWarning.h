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

// Description : basic message box in windows to allow designers to be told something is 
//               wrong with their setup

#ifndef __DESIGNER_WARNING_H__
#define __DESIGNER_WARNING_H__

//#define DESIGNER_WARNING_ENABLED (1 && (defined(WIN32) || defined(WIN64)))		
#if defined(WIN32) 
#define DESIGNER_WARNING_ENABLED 1  // needs a release build define to hook in here 
#elif defined(WIN64)
#define DESIGNER_WARNING_ENABLED 1  // needs a release build define to hook in here 
#else
#define DESIGNER_WARNING_ENABLED 0
#endif

#if defined(_RELEASE)
	#undef DESIGNER_WARNING_ENABLED
	#define DESIGNER_WARNING_ENABLED 0
#endif

#if DESIGNER_WARNING_ENABLED

#define DesignerWarning(cond, ...) ((!(cond)) && DesignerWarningFail(#cond, string().Format(__VA_ARGS__).c_str()))
#define DesignerWarningFail(condText, messageText) DesignerWarningFunc(string().Format("CONDITION:\n%s\n\nMESSAGE:\n%s", condText, messageText))
int DesignerWarningFunc(const char * message);
int GetNumDesignerWarningsHit();

#else // DESIGNER_WARNING_ENABLED

#define DesignerWarning(cond, ...) (0)
#define DesignerWarningFail(condText, messageText) (0)
#define GetNumDesignerWarningsHit() (0)

#endif // DESIGNER_WARNING_ENABLED

#endif // __DESIGNER_WARNING_H__

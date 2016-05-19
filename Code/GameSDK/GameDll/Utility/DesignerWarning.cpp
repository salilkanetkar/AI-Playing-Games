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

// Description : basic message box in windows to allow designers to be told something is wrong with their setup

#include "StdAfx.h"
#include "DesignerWarning.h"
#include "GameCVars.h"
#include "Testing/FeatureTester.h"
#include "Testing/AutoTester.h"

#if DESIGNER_WARNING_ENABLED

static int s_numDesignerWarningsHit=0;

#ifdef WIN32
#include "CryWindows.h"
#endif

int DesignerWarningFunc(const char * message)
{
	if (g_pGameCVars->designer_warning_enabled && (!gEnv->IsDedicated()))
	{
		GameWarning("!DESIGNER WARNING\n%s", message);
	}

	// kept because autotests gather all designer warnings out of logs with this form
	CryLogAlways("---DESIGNER_WARNING: %s", message);
	CryLogAlways("----------------------------------------");

#if ENABLE_FEATURE_TESTER
	// If feature testing is in progress, write each designer warning out as a failed feature test

	CFeatureTester * featureTester = CFeatureTester::GetInstance();
	if (featureTester)
	{
		CAutoTester * autoTestResultWriter = featureTester->GetAutoTesterIfActive();
		if (autoTestResultWriter)
		{
			CryFixedStringT<32> warningName;
			warningName.Format("DesignerWarning%04u", s_numDesignerWarningsHit);
			autoTestResultWriter->AddSimpleTestCase("DesignerWarnings", warningName.c_str(), 0.1f, message);
		}
	}
#endif

	s_numDesignerWarningsHit++;
	return 0;
}

int GetNumDesignerWarningsHit()
{
	return s_numDesignerWarningsHit;
}

#endif // DESIGNER_WARNING_ENABLED
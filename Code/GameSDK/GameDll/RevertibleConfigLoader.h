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

// Description : Class that loads a config file with the ability to restore the
//               cvars to the values they were before loading them


#ifndef __REVERTIBLE_CONFIG_LOADER_H__
#define __REVERTIBLE_CONFIG_LOADER_H__

#pragma once

#include "Utility/SingleAllocTextBlock.h"

class CRevertibleConfigLoader : public ILoadConfigurationEntrySink
{
public:
	CRevertibleConfigLoader(int maxCvars, int maxTextBufferSize);
	~CRevertibleConfigLoader() {}

	/* ILoadConfigurationEntrySink */
	virtual void OnLoadConfigurationEntry( const char *szKey, const char *szValue, const char *szGroup );
	/* ILoadConfigurationEntrySink */

	void LoadConfiguration(const char *szConfig);
	void ApplyAndStoreCVar(const char *szKey, const char *szValue);
	void RevertCVarChanges();

	void SetAllowCheatCVars(bool allow) { m_allowCheatCVars = allow; }

protected:
	struct SSavedCVar
	{
		const char * m_name;
		const char * m_value;
	};

	std::vector<SSavedCVar> m_savedCVars;
	CSingleAllocTextBlock m_cvarsTextBlock;
	bool m_allowCheatCVars;
};

#endif // ~__REVERTIBLE_CONFIG_LOADER_H__

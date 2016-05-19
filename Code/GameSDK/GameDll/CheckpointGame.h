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

// Description : Checkpoint Save/Load system for Game03


#ifndef __CHECKPOINTGAME_H__
#define __CHECKPOINTGAME_H__

#include <ICheckPointSystem.h>

class CCheckpointGame : public ICheckpointGameHandler
{
private:
	CCheckpointGame();
	static CCheckpointGame m_Instance;

public:
	static CCheckpointGame* GetInstance() { return &m_Instance; }
	virtual ~CCheckpointGame();

	void Init();

	// Writing game-specific data
	virtual void OnWriteData(XmlNodeRef parentNode);

	// Reading game-specific data
	virtual void OnReadData(XmlNodeRef parentNode);

	// Engine reset control
	virtual void OnPreResetEngine();
	virtual void OnPostResetEngine();

	// Restart
	virtual void OnRestartGameplay();

protected:
	//player data
	void WritePlayerData(XmlNodeRef parentNode);
	void ReadPlayerData(XmlNodeRef data);

	//player inventory
	void WritePlayerInventory(XmlNodeRef parentNode);
	void ReadPlayerInventory(XmlNodeRef parentNode);

	//get data or log warning
	template<class T>
	bool GetAttrSave(XmlNodeRef source, const char *name, T &data);
};

template<class T>
ILINE bool CCheckpointGame::GetAttrSave(XmlNodeRef source, const char *name, T &data)
{
	CRY_ASSERT(source != NULL);
	CRY_ASSERT(name);
	bool found = source->getAttr(name, data);
	if(!found)
		CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "Failed reading %s from checkpoint node %s.", name, source->getTag());
	return found;
}

#endif //__CHECKPOINTGAME_H__

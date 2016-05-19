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

// Description : Helper for Game-specific items dealing with AI Recorder


#ifndef __GAMEAIRECORDER_H__
#define __GAMEAIRECORDER_H__

class Agent;


// INCLUDE_GAME_AI_RECORDER - Define to include the game-specific utilities for AI recorder
// INCLUDE_GAME_AI_RECORDER_NET - Define to include the network portion of the Game AI Recorder

#if !defined(_RELEASE) && !defined(DEDICATED_SERVER)
	#define INCLUDE_GAME_AI_RECORDER 1
	// #define INCLUDE_GAME_AI_RECORDER_NET 1
#endif // _RELEASE


// Helper to record a comment inside the AI's recorder
// In:
//	entityId - EntityId of AI whose recorder receives the comment
//	szComment - Comment to add, with additional arguments
void RecordAIComment(EntityId entityId, const char* szComment, ...) PRINTF_PARAMS(2,3);


#ifdef INCLUDE_GAME_AI_RECORDER

#include "IAIRecorder.h"

class CGameAIRecorder : public IAIRecorderListener
{
	// For network RMI usage
	friend class CGameRules;

public:
	CGameAIRecorder();

	void Init();
	void Shutdown();
	bool IsRecording() const { return m_bIsRecording; }

	// Use these methods to add bookmarks/comments to AI recorder
	void RequestAIRecordBookmark();
	void RequestAIRecordComment(const char* szComment);

	void RecordLuaComment(const Agent &agent, const char* szComment, ...) const PRINTF_PARAMS(3,4);

	// IAIRecorderListener
	virtual void OnRecordingStart(EAIRecorderMode mode, const char *filename);
	virtual void OnRecordingStop(const char *filename);
	virtual void OnRecordingSaved(const char *filename);
	//~IAIRecorderListener

private:
	void AddRecordBookmark(EntityId requesterId);
	void AddRecordComment(EntityId requesterId, const char* szComment);

	// Remote recording copy
	void OnAddBookmark(const string& sScreenShotPath);
	void CleanupRemoteArchive();
	bool FinalizeRemoteArchive(const char* szRecordingFile);
	bool SendRemoteArchive(const char* szRecordingFile);
	bool AddFileToRemoteArchive(const char* szFile);

private:
	bool m_bIsRecording;
	bool m_bBookmarkAdded;
	ICryArchive_AutoPtr m_pRemoteArchive;
};

class CGameAIRecorderCVars
{
	friend class CGameAIRecorder;

public:
	static void RegisterCommands();
	static void RegisterVariables();
	static void UnregisterCommands(IConsole* pConsole);
	static void UnregisterVariables(IConsole* pConsole);

	// Console command
	static void CmdAIRecorderAddComment(IConsoleCmdArgs* cmdArgs);

public:
	static const char *ai_remoteRecorder_serverDir;
	static int ai_remoteRecorder_enabled;
	static int ai_remoteRecorder_onlyBookmarked;
};

#endif //INCLUDE_GAME_AI_RECORDER


#endif //__GAMEAIRECORDER_H__

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

#ifndef __WarningsManager_H__
#define __WarningsManager_H__

#include "UIDialogs.h"

#define INVALID_HUDWARNING_ID ((THUDWarningId)~0)


struct SWarningDefinition
{
	SWarningDefinition(const char* msgId, EDialogType type, const char* title, const char* message, const char* param, const char* positiveResonse, const char* negativeResponse, THUDWarningId id)
		: messageId(msgId)
		, diagType(type)
		, diagTitle(title)
		, diagMessage(message)
		, diagParam(param)
		, warningId(id)
	{
		response[0] = positiveResonse;
		response[1] = negativeResponse;
	}
	const char* messageId;
	EDialogType diagType;
	const char* diagTitle;
	const char* diagMessage;
	const char* diagParam;
	const char* response[2];
	THUDWarningId warningId;
};

class CWarningsManager : public IDialogCallback
{
public:
	CWarningsManager();
	~CWarningsManager();

	THUDWarningId AddGameWarning(const char* stringId, const char* paramMessage = NULL, IGameWarningsListener* pListener = NULL);
	void AddGameWarning(THUDWarningId id, const char* paramMessage = NULL, IGameWarningsListener* pListener = NULL);
	void RemoveGameWarning(THUDWarningId Id);
	void RemoveGameWarning(const char* stringId);
	void CancelCallbacks(IGameWarningsListener* pListener);
	void CancelWarnings();

	THUDWarningId GetWarningId(const char* stringId) const;
	bool IsWarningActive(const char* stringId) const;
	bool IsWarningActive(THUDWarningId Id) const;

	//IDialogCallback
	virtual void DialogCallback(uint32 dialogId, EDialogResponse response, const char* param);
	//~IDialogCallback

private:
	struct SGameWarning
	{
		SGameWarning() 
			: pWarningDef(NULL)
			, pListener(NULL)
			, DialogId(~0)
		{}

		const SWarningDefinition* pWarningDef;
		IGameWarningsListener *pListener;
		uint32 DialogId;
	};

	SGameWarning* GetWarningForDialog(uint32 dialogId);

	const SWarningDefinition* GetWarningDefinition(THUDWarningId id) const;
	const SWarningDefinition* GetWarningDefinition(const char* stringId) const;

	void AddGameWarning(const SWarningDefinition* pWarningDef, const char* paramMessage = NULL, IGameWarningsListener* pListener = NULL);
	void RemoveGameWarning(const SWarningDefinition* pWarningDef);

	CUIDialogs* GetDialogs();
private:
	typedef std::map<THUDWarningId, SGameWarning> TWarningMap;
	typedef std::vector<SWarningDefinition> TWarningDefMap;

	TWarningDefMap m_WarningDefinitions;
	TWarningMap m_Warnings;
};


#endif // #ifndef __WarningsManager_H__


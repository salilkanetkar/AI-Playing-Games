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

#ifndef __PROFILEOPTIONS_H__
#define __PROFILEOPTIONS_H__

#include "IGameFramework.h"
#include "Option.h"

//////////////////////////////////////////////////////////////////////////
#include <IPlayerProfiles.h>

class CProfileOptions : public IPlayerProfileListener
{
public:

	CProfileOptions();
	virtual		~CProfileOptions();

	struct SPendingOption
	{
		CryFixedStringT<64> command;
		CryFixedStringT<512> param;
		CryFixedStringT<512> original;
		bool								preview;
		bool								confirmation;
		bool								restart;
		bool								writeToConfig;

		SPendingOption(const char* _command, const char* _param, const char* _original, bool _preview, bool _confirmation, bool _restart, bool _write):command(_command), param(_param), original(_original), preview(_preview), confirmation(_confirmation), restart(_restart), writeToConfig(_write)
		{}
	};

	void			Init();
	void			InitializeFromCVar();

	void			SaveProfile(unsigned int reason = ePR_Options);
	COption*		GetOption(const char* option) const;
	COption*		GetOptionByCVar(const char* cvar) const;
	bool			IsOption(const char* option);

	string			GetOptionValue(const char* command, bool getDefault=false);
	string			GetOptionValueOrCreate(const char* command, bool getDefault=false);
	void			SetOptionValue(const char* command, const char* param, bool toPendingOptions = false);
	void			SetOptionValue(const char* command, int value, bool toPendingOptions = false);
	void			SetOptionValue(const char* command, float value, bool toPendingOptions = false);

	int				GetOptionValueAsInt(const char* command, bool getDefault=false);
	float			GetOptionValueAsFloat(const char* command, bool getDefault=false);

	string			GetPendingOptionValue(const char* command);
	bool			HasPendingOptionValues()const;
	bool			HasPendingOptionValue(const char* option)const;
	bool			HasPendingOptionValuesWithConfirmation()const;
	bool			HasPendingOptionValuesWithRequiresRestart() const;
	void			ApplyPendingOptionsValuesForConfirmation();
	void			FlushPendingOptionValues();
	void			ClearPendingOptionValues();
	void			ClearPendingOptionValuesFromConfirmation();

	void			ResetToDefault();

	const std::vector<SPendingOption>& GetPendingOptions() { return m_pendingOptions; }

	//IOnlinePlayerProfileListener
	void			SaveToProfile(IPlayerProfile* pProfile, bool online, unsigned int reason);
	void			LoadFromProfile(IPlayerProfile* pProfile, bool online, unsigned int reason);
	//~IOnlinePlayerProfileListener

	bool			ShouldDeferredMPSave() const { return m_bDeferredSaveMP; }
	void			SetDeferredMPSave(const bool deferredSave) { m_bDeferredSaveMP = deferredSave; }

	void			ResetOverscanBorders();

	void			SetInitialProfileLoaded(const bool bLoaded) { m_bInitialProfileLoaded = bLoaded; }
	ILINE bool		IsInitialProfileLoaded() const { return m_bInitialProfileLoaded; }

private:

	struct CCVarSink : public ICVarDumpSink
	{
		CCVarSink(CProfileOptions* pOptions, AZ::IO::HandleType fileHandle)
		{
			m_pOptions = pOptions;
			m_fileHandle = fileHandle;
		}

		void OnElementFound(ICVar *pCVar);
		CProfileOptions* m_pOptions;
		AZ::IO::HandleType m_fileHandle;
	};

	bool IsCVar(const char* cVarName);
	void AddOption(const XmlNodeRef node);
	void AddOption(const char* name, const char* value, const char* cvar = NULL, const bool preview = false, const bool confirmation = false, const bool restart = false, const bool writeToConfig = false);

	bool IsAdvancedOption(const char* command)const;
	void AddOrReplacePendingOption(const char* command, const char* option);

	bool WriteGameCfg();

	std::vector<SPendingOption> m_pendingOptions;
	std::vector<COption*> m_allOptions;

	bool m_bDeferredSaveMP;
	bool m_bInitialProfileLoaded;
	bool m_bLoadingProfile;
};


//////////////////////////////////////////////////////////////////////////

#endif


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

#ifndef __UISettings_H__
#define __UISettings_H__

#include "IUIGameEventSystem.h"
#include <IFlashUI.h>
#include <IGameFramework.h>
#include <IAudioSystem.h>
#include <SFunctor.h>
using namespace Audio;

struct SNullCVar : public ICVar
{
	virtual ~SNullCVar() {}
	virtual void Release() { return; }
	virtual int GetIVal() const { return 0; }
	virtual int64 GetI64Val() const { return 0; }
	virtual float GetFVal() const { return 0; }
	virtual const char *GetString() const { return "NULL"; }
#if defined( DEDICATED_SERVER )
	virtual void SetDataProbeString( const char* pDataProbeString )  { return; }
#endif
	virtual const char *GetDataProbeString() const { return "NULL"; }
	virtual void Set(const char* s) { return; }
	virtual void ForceSet(const char* s) { return; }
	virtual void Set(const float f) { return; }
	virtual void Set(const int i) { return; }
	virtual void ClearFlags (int flags) { return; }
	virtual int GetFlags() const { return 0; }
	virtual int SetFlags( int flags ) { return 0; }
	virtual int GetType() { return 0; }
	virtual const char* GetName() const { return "NULL"; }
	virtual const char* GetHelp() { return "NULL"; }
	virtual bool IsConstCVar() const { return 0; }

	virtual void SetOnChangeCallback( ConsoleVarFunc pChangeFunc ){return;}
	virtual uint64 AddOnChangeFunctor( const SFunctor& pChangeFunctor) {return 0;}
	virtual bool RemoveOnChangeFunctor(const uint64 nElement) {return true;}
	virtual uint64 GetNumberOfOnChangeFunctors()const {return 0;}
	virtual const SFunctor& GetOnChangeFunctor(uint64 nFunctorIndex)const {static SFunctor oDummy;return oDummy;};
	virtual ConsoleVarFunc GetOnChangeCallback() const {return NULL;}

	virtual void GetMemoryUsage( class ICrySizer* pSizer ) const { return; }
	virtual int GetRealIVal() const { return 0; }
	virtual void DebugLog( const int iExpectedValue, const EConsoleLogMode mode ) const {}

	static SNullCVar* Get()
	{
		static SNullCVar inst;
		return &inst;
	}

private:
	SNullCVar() {}
};

class CUISettings
	: public IUIGameEventSystem
	, public IUIModule
{
public:
	CUISettings();

	// IUIGameEventSystem
	UIEVENTSYSTEM( "UISettings" );
	virtual void InitEventSystem();
	virtual void UnloadEventSystem();

	//IUIModule
	virtual void Init();
	virtual void Update(float fDelta);

private:
	// ui functions
	void SendResolutions();
	void SendGraphicSettingsChange();
	void SendSoundSettingsChange();
	void SendGameSettingsChange();

	// ui events
	void OnSetGraphicSettings( int resIndex, int graphicsQuality, bool fullscreen );
	void OnSetResolution( int resX, int resY, bool fullscreen );
	void OnSetSoundSettings( float music, float sfx, float video );
	void OnSetGameSettings( float sensitivity, bool invertMouse, bool invertController );

	void OnGetResolutions();
	void OnGetCurrGraphicsSettings();
	void OnGetCurrSoundSettings();
	void OnGetCurrGameSettings();

	void OnGetLevels( string levelPathFilter );

	void OnLogoutUser();

private:
	enum EUIEvent
	{
		eUIE_GraphicSettingsChanged,
		eUIE_SoundSettingsChanged,
		eUIE_GameSettingsChanged,

		eUIE_OnGetResolutions,
		eUIE_OnGetResolutionItems,
		eUIE_OnGetLevelItems,
	};

	SUIEventReceiverDispatcher<CUISettings> m_eventDispatcher;
	SUIEventSenderDispatcher<EUIEvent> m_eventSender;
	IUIEventSystem* m_pUIEvents;
	IUIEventSystem* m_pUIFunctions;

	ICVar* m_pRXVar;
	ICVar* m_pRYVar;
 	ICVar* m_pFSVar;
	ICVar* m_pGQVar;


	TAudioControlID m_musicVolumeId;
	TAudioControlID m_sfxVolumeId;

	ICVar* m_pVideoVar;

	ICVar* m_pMouseSensitivity;
	ICVar* m_pInvertMouse;
	ICVar* m_pInvertController;

	int m_currResId;

	typedef std::vector< std::pair<int,int> > TResolutions;
	TResolutions m_Resolutions;
};


#endif // __UISettings_H__

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

#ifndef _GAME_EFFECTS_SYSTEM_
#define _GAME_EFFECTS_SYSTEM_

#pragma once

// Includes
#include "GameEffectsSystemDefines.h"
#include "GameRulesTypes.h"

//==================================================================================================
// Name: CGameEffectsSystem
// Desc: System to handle game effects, game render nodes and game render elements
//			 Game effect: separates out effect logic from game logic
//			 Game render node: handles the render object in 3d space
//			 Game render element: handles the rendering of the object
//			 CVar activation system: system used to have data driven cvars activated in game effects
//			 Post effect activation system: system used to have data driven post effects activated in game effects
// Author: James Chilvers
//==================================================================================================
class GameSDKCGameEffectsSystem : public IInputEventListener, public ISoftCodeListener, public SGameRulesListener
{
	friend struct SGameEffectSystemStaticData;

public:
	// ---------- Singleton static functions ----------
    SC_API static inline GameSDKCGameEffectsSystem&		Instance()
	{
		if(s_singletonInstance == NULL)
		{
            s_singletonInstance = new GameSDKCGameEffectsSystem;
		}
		return *s_singletonInstance;
	}

	static void							Destroy();
	SC_API static ILINE bool				Exists()
	{
		return (s_singletonInstance) ? true : false;
	}
	//-------------------------------------------------

	void										Initialise();
	void										LoadData();
	void										ReleaseData();

	template<class T>
	T*											CreateEffect()  // Use if dynamic memory allocation is required for the game effect
	{																				// Using this function then allows easy changing of memory allocator for all dynamically created effects
		T* newEffect = new T;
		return newEffect;
	}

    SC_API void							RegisterEffect(GameSDKIGameEffect* effect); // Each effect automatically registers and unregisters itself
    SC_API void							UnRegisterEffect(GameSDKIGameEffect* effect);

	void										Update(float frameTime);

	SC_API void							RegisterGameRenderNode(IGameRenderNodePtr& pGameRenderNode);
	SC_API void							UnregisterGameRenderNode(IGameRenderNodePtr& pGameRenderNode);

    SC_API void							RegisterGameRenderElement(GameSDKIGameRenderElementPtr& pGameRenderElement);
    SC_API void							UnregisterGameRenderElement(GameSDKIGameRenderElementPtr& pGameRenderElement);

#ifdef SOFTCODE_ENABLED
	SC_API void*						CreateSoftCodeInstance(const char* pTypeName); // Create soft code instance using libs
	SC_API void							RegisterSoftCodeLib(ITypeLibrary* pLib); // Register soft code lib for creation of instances
#endif

	bool										OnInputEvent(const SInputEvent& inputEvent);

#if DEBUG_GAME_FX_SYSTEM
	// Creating a static version of SRegisterEffectDebugData inside an effect cpp registers the effect's debug data with the game effects system
	struct SRegisterEffectDebugData
	{
		SRegisterEffectDebugData(DebugOnInputEventCallback inputEventCallback,DebugDisplayCallback debugDisplayCallback, const char* effectName)
		{
            GameSDKCGameEffectsSystem::RegisterEffectDebugData(inputEventCallback,debugDisplayCallback,effectName);
		}
	};

	int											GetDebugView() const { return m_debugView; }
    SC_API GameSDKIGameEffect*			GetDebugEffect(const char* pEffectName) const;
#endif

	// Creating a static version of SRegisterDataCallbacks inside an effect cpp registers the effect's data callback functions with the game effects system
	struct SRegisterDataCallbacks
	{
		SRegisterDataCallbacks(DataLoadCallback dataLoadingCallback,DataReleaseCallback dataReleaseCallback,DataReloadCallback dataReloadCallback)
		{
            GameSDKCGameEffectsSystem::RegisterDataLoadCallback(dataLoadingCallback);
            GameSDKCGameEffectsSystem::RegisterDataReleaseCallback(dataReleaseCallback);
            GameSDKCGameEffectsSystem::RegisterDataReloadCallback(dataReloadCallback);
		}
	};

	// Creating a static version of SRegisterGameCallbacks inside an effect cpp registers the effect's game callback functions with the game effects system
	struct SRegisterGameCallbacks
	{
		SRegisterGameCallbacks(EnteredGameCallback enteredGameCallback)
		{
            GameSDKCGameEffectsSystem::RegisterEnteredGameCallback(enteredGameCallback);
		}
	};

	// ISoftCodeListener implementation
	virtual void InstanceReplaced(void* pOldInstance, void* pNewInstance);
	virtual void GameRenderNodeInstanceReplaced(void* pOldInstance, void* pNewInstance);
	virtual void GameRenderElementInstanceReplaced(void* pOldInstance, void* pNewInstance);

	// SGameRulesListener implementation
	void GameRulesInitialise();
	virtual void EnteredGame();

	void ReloadData();

protected:
    GameSDKCGameEffectsSystem();
    virtual ~GameSDKCGameEffectsSystem();

private:

	void										Reset();
    void										AutoReleaseAndDeleteFlaggedEffects(GameSDKIGameEffect* effectList);
    void										AutoDeleteEffects(GameSDKIGameEffect* effectList);
	void										SetPostEffectCVarCallbacks();
	static void							PostEffectCVarCallback(ICVar* cvar);

	SC_API static void			RegisterDataLoadCallback(DataLoadCallback dataLoadCallback);
	SC_API static void			RegisterDataReleaseCallback(DataReleaseCallback dataReleaseCallback);
	SC_API static void			RegisterDataReloadCallback(DataReloadCallback dataReloadCallback);

	SC_API static void			RegisterEnteredGameCallback(EnteredGameCallback enteredGameCallback);

#if DEBUG_GAME_FX_SYSTEM
	void										DrawDebugDisplay();
	void										OnActivateDebugView(int debugView);
	void										OnDeActivateDebugView(int debugView);
	SC_API static void			RegisterEffectDebugData(	DebugOnInputEventCallback inputEventCallback,
																										DebugDisplayCallback displayCallback,
																										const char* effectName);

	struct SEffectDebugData
	{
		SEffectDebugData(	DebugOnInputEventCallback paramInputCallback,
											DebugDisplayCallback paramDisplayCallback,
											const char* paramEffectName)
		{
			inputCallback = paramInputCallback;
			displayCallback = paramDisplayCallback;
			effectName = paramEffectName;
		}
		DebugOnInputEventCallback inputCallback;
		DebugDisplayCallback			displayCallback;
		const char*								effectName;
	};

	static int												s_currentDebugEffectId;

	int																m_debugView;
#endif

    static GameSDKCGameEffectsSystem*	s_singletonInstance;
	static int									s_postEffectCVarNameOffset;

#ifdef SOFTCODE_ENABLED
	std::vector<ITypeLibrary*>				m_softCodeTypeLibs;

	typedef std::vector<IGameRenderNodePtr*> TGameRenderNodeVec;
	TGameRenderNodeVec								m_gameRenderNodes;
	CGameRenderNodeSoftCodeListener*	m_gameRenderNodeSoftCodeListener;

    typedef std::vector<GameSDKIGameRenderElementPtr* > TGameRenderElementVec;
	TGameRenderElementVec								m_gameRenderElements;
	CGameRenderElementSoftCodeListener*	m_gameRenderElementSoftCodeListener;
#endif

    GameSDKIGameEffect*								m_effectsToUpdate;
    GameSDKIGameEffect*								m_effectsNotToUpdate;
    GameSDKIGameEffect*								m_nextEffectToUpdate; // -> If in update loop, this is the next effect to be updated
																										//    this will get changed if the effect is unregistered
	bool												m_isInitialised;
	static bool									s_hasLoadedData;
};//------------------------------------------------------------------------------------------------

#endif // _GAME_EFFECTS_SYSTEM_

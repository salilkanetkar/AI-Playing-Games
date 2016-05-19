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

#ifndef GAME_AUDIO_UTILS_H
#define GAME_AUDIO_UTILS_H

#pragma once

#include "Audio/AudioSignalPlayer.h"

class CGameAudioUtils
{
public:
	//typedef Functor3<const bool&, const float&, ISound*> LengthCallback;

	CGameAudioUtils();
	virtual ~CGameAudioUtils();
	void Reset();

	void UnregisterSignal(const CAudioSignalPlayer signalPlayer);
	//bool GetPlayingSignalLength(const CAudioSignalPlayer signalPlayer, LengthCallback callback, EntityId entityID = 0);
	
	//static ISound* GetSoundFromProxy(tSoundID soundID, EntityId entityID);
	static IComponentAudio* GetEntityAudioProxy( EntityId entityID );

	//ISoundEventListener
	//void OnSoundEvent( ESoundCallbackEvent event, ISound *pSound );
	//~ISoundEventListener

protected:
	/*typedef std::map<tSoundID, LengthCallback> TSoundIDCallback;
	TSoundIDCallback m_soundCallbacksMap;

	void ProcessEvent(ISound* pSound, const bool success, const float length = 0.0f);*/
};
#endif //#ifndef GAME_AUDIO_UTILS_H
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

#pragma once

#ifndef MOCK_SOUND_SYSTEM_WRAPPER_H
#define MOCK_SOUND_SYSTEM_WRAPPER_H

#include "EngineFacade/CryEngineWrappers/SoundSystemWrapper.h"
#include "Actor2\\ComponentEntityID.h"

namespace GameTesting
{
	class CMockSoundSystemWrapper : public EngineFacade::ISoundSystemWrapper
	{
	public:
		CMockSoundSystemWrapper();

		virtual tSoundID Play(const string& soundName, const ESoundSemantic semantic, const ComponentEntityID& entityID);
		virtual void Stop(const tSoundID soundID, const ComponentEntityID& entityID);

		virtual void AddSoundMood(const string& name, const uint32 fadeInTimeMSecs);
		virtual void RemoveSoundMood(const string& name, const uint32 fadeOutTimeMSecs);

		void AddReturnedSoundIDAfterPlay(const tSoundID soundID);

		bool WasAddSoundMoodCalledOnceWith(const string& name, const uint32 fadeInTimeMSecs) const;

		bool WasRemoveSoundMoodCalledOnceWith(const string& name, const uint32 fadeOutTimeMSecs) const;

		bool WasAddSoundMoodCalled() const;

		bool WasRemoveSoundMoodCalled() const;

		bool WasSoundPlayedOnceWith(const string& soundName) const;
		
		bool WasSoundStoppedOnceWith(const tSoundID soundID) const;
		bool WasSoundStoppedOnceWith(const tSoundID soundID, const ComponentEntityID& entityID) const;

		bool WasSoundPlayedOnceWithSpecificSemantic( const string& soundName, const ESoundSemantic semantic ) const;
		bool WasSoundPlayedOnceWithSpecificEntityID( const string& soundName, const ComponentEntityID& entityID ) const;

	private:
		struct SPlayParameters
		{
			string soundName;
			ESoundSemantic semantic;
			ComponentEntityID entityID;
		};

		struct SStopParameters
		{
			tSoundID soundID;
			ComponentEntityID entityID;
		};

		struct SAddRemoveMoodParameters
		{
			SAddRemoveMoodParameters( const string& _moodName, const uint32 _fadeTime )
				: moodName( _moodName )
				, fadeTime( _fadeTime )
			{}

			bool operator == ( const SAddRemoveMoodParameters& other ) const { return moodName==other.moodName && fadeTime==other.fadeTime; }

			string moodName;
			uint32 fadeTime;
		};

		std::vector<tSoundID> m_soundIDsToReturnOnNextPlay;

		std::vector<SPlayParameters> m_playCalls;
		std::vector<SStopParameters> m_stopCalls;

		std::vector<SAddRemoveMoodParameters> m_addSoundMoodCalls;
		std::vector<SAddRemoveMoodParameters> m_removeSoundMoodCalls;
	};
}

#endif




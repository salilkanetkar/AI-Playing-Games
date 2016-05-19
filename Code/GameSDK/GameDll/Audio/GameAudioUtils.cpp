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

#include "StdAfx.h"
#include "Audio/GameAudioUtils.h"

//---------------------------------------
CGameAudioUtils::CGameAudioUtils()
{
}

//---------------------------------------
CGameAudioUtils::~CGameAudioUtils()
{
	Reset();
}

//---------------------------------------
void CGameAudioUtils::Reset()
{
	/*ISoundSystem *pSoundSystem = gEnv->pSoundSystem;

	TSoundIDCallback::const_iterator end = m_soundCallbacksMap.end();
	for(TSoundIDCallback::const_iterator it = m_soundCallbacksMap.begin(); it != end; ++it)
	{
		_smart_ptr<ISound> pSound = pSoundSystem->GetSound(it->first);
		if(pSound)
		{
			pSound->RemoveEventListener((ISoundEventListener*) this);
		}
	}

	m_soundCallbacksMap.clear();*/
}

//---------------------------------------
void CGameAudioUtils::UnregisterSignal(const CAudioSignalPlayer signalPlayer)
{
	/*size_t numPlayingSounds = signalPlayer.m_playingSoundIDs.size();
	for (size_t i = 0; i < numPlayingSounds; ++i)
	{
		tSoundID soundID = signalPlayer.m_playingSoundIDs[i];
		if (soundID != INVALID_SOUNDID)
		{
			TSoundIDCallback::iterator it = m_soundCallbacksMap.find(soundID);
			if(it != m_soundCallbacksMap.end())
			{
				m_soundCallbacksMap.erase(it);
			}

			ISound* pSound = gEnv->pSoundSystem->GetSound( soundID );
			if(pSound)
			{
				pSound->RemoveEventListener((ISoundEventListener*) this);		
			}
		}
	}*/
}

//---------------------------------------
//bool CGameAudioUtils::GetPlayingSignalLength( const CAudioSignalPlayer signalPlayer, LengthCallback callback, EntityId entityID )
//{
//	size_t numPlayingSounds = signalPlayer.m_playingSoundIDs.size();
//	for (size_t i = 0; i < numPlayingSounds; ++i)
//	{
//		tSoundID soundID = signalPlayer.m_playingSoundIDs[i];
//		if (soundID != INVALID_SOUNDID)
//		{
//			ISound* pSound = GetSoundFromProxy(soundID, entityID);
//			if(pSound)
//			{
//				pSound->AddEventListener((ISoundEventListener*) this, "CGameAudioUtils");
//				m_soundCallbacksMap[soundID] = callback;
//				return true;
//			}
//		}
//	}
//
//	return false;
//}

//---------------------------------------
//void CGameAudioUtils::OnSoundEvent( ESoundCallbackEvent event, ISound *pSound )
//{
//	switch(event)
//	{
//	case SOUND_EVENT_ON_LOADED:
//		{
//			const int lengthMs = pSound->GetLengthMs();
//			CRY_ASSERT(lengthMs != 0);
//
//			const float length = (float) lengthMs/1000.0f;
//			ProcessEvent(pSound, true, length);
//		}
//		break;
//	case SOUND_EVENT_ON_LOAD_FAILED:
//	case SOUND_EVENT_ON_STOP: //processing stop as this will be called in the sound is reset
//		{
//			ProcessEvent(pSound, false);
//		}
//		break;
//	}
//}

//---------------------------------------
//void CGameAudioUtils::ProcessEvent(ISound* pSound, const bool success, const float length)
//{
//	pSound->RemoveEventListener((ISoundEventListener*) this);
//
//	TSoundIDCallback::iterator it = m_soundCallbacksMap.find(pSound->GetId());
//	if(it != m_soundCallbacksMap.end())
//	{
//		it->second(true, length, pSound);
//		m_soundCallbacksMap.erase(it);
//	}
//	else
//	{
//		CRY_ASSERT_MESSAGE(0, "CGameAudioUtils::OnSoundEvent failed to find a sound.");
//	}
//}


//---------------------------------------
IComponentAudio* CGameAudioUtils::GetEntityAudioProxy( EntityId entityID )
{
	IComponentAudio* pProxy = NULL;
	if (entityID != 0)
	{
		IEntity* pEntity = gEnv->pEntitySystem->GetEntity(entityID);
		if (pEntity)
		{
			pProxy = static_cast<IComponentAudio*>(pEntity->GetComponent<IComponentAudio>().get());
		}
	}

	return pProxy;
}


//---------------------------------------
//ISound* CGameAudioUtils::GetSoundFromProxy(tSoundID soundID, EntityId entityID)
//{
//	IComponentAudio* pProxy = GetEntityAudioProxy( entityID );
//	if (pProxy)
//	{
//		return pProxy->GetSound(soundID);
//	}
//	else
//	{
//		ISound* pSound = gEnv->pSoundSystem->GetSound( soundID );
//		return pSound;
//	}
//}

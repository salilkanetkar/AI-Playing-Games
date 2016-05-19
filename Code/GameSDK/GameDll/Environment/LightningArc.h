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

#ifndef _LIGHTNING_ARC_H_
#define _LIGHTNING_ARC_H_

#pragma once


#include "Effects/GameEffects/LightningGameEffect.h"

namespace GameSDK
{

    class CLightningArc : public CGameObjectExtensionHelper < CLightningArc, IGameObjectExtension >
    {
    public:
        DECLARE_COMPONENT_TYPE("CLightningArc", 0x42F13A45E4704ED2, 0x8168F67D36127A03)
        CLightningArc();

        virtual void GetMemoryUsage(ICrySizer *pSizer) const;
        virtual bool Init(IGameObject* pGameObject);
        virtual void PostInit(IGameObject * pGameObject);
        virtual void InitClient(ChannelId channelId);
        virtual void PostInitClient(ChannelId channelId);
        virtual bool ReloadExtension(IGameObject * pGameObject, const SEntitySpawnParams &params);
        virtual void PostReloadExtension(IGameObject * pGameObject, const SEntitySpawnParams &params);
        virtual bool GetEntityPoolSignature(TSerialize signature);
        //virtual void Release();
        virtual void FullSerialize(TSerialize ser);
        virtual bool NetSerialize(TSerialize ser, EEntityAspects aspect, uint8 profile, int pflags);
        virtual void PostSerialize();
        virtual void SerializeSpawnInfo(TSerialize ser, IEntity *);
        virtual ISerializableInfoPtr GetSpawnInfo();
        virtual void Update(SEntityUpdateContext& ctx, int updateSlot);
        virtual void HandleEvent(const SGameObjectEvent& event);
        virtual void ProcessEvent(SEntityEvent& event);
        virtual void SetChannelId(ChannelId id);
        virtual void SetAuthority(bool auth);
        virtual const void * GetRMIBase() const;
        virtual void PostUpdate(float frameTime);
        virtual void PostRemoteSpawn();

        void TriggerSpark();
        void Enable(bool enable);
        void ReadLuaParameters();

    private:
        void Reset(bool jumpingIntoGame);

        const char* m_lightningPreset;
        float m_delay;
        float m_delayVariation;
        float m_timer;
        bool m_enabled;
        bool m_inGameMode;
    };

    DECLARE_COMPONENT_POINTERS(CLightningArc)

}

#endif

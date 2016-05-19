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

// Description : Logs data about client latency

#ifndef __LAGOMETER_H__
#define __LAGOMETER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if USE_LAGOMETER



#include "Actor.h"
#include "ITelemetryCollector.h"
#include "IInput.h"
#include "ItemString.h"

struct HitInfo;
class CItem;
struct IDebugHistoryManager;
struct IDebugHistory;


class CLagOMeter : public IInputEventListener
{
public:
	enum EBandwidthGraph
	{
		eBG_None = 0,
		eBG_Upload = BIT(0),
		eBG_Download = BIT(1),
		eBG_Both = eBG_Upload|eBG_Download,
	};


	CLagOMeter();
	~CLagOMeter();

	void OnClientRequestHit(HitInfo &hitInfo);
	void OnClientReceivedKill(const CActor::KillParams &killParams);
	void OnClientRequestPurchase(int purchaseSlot);
	void OnClientPickupItem(CItem* pItem);
	void Update();
	void UpdateBandwidthGraphVisibility();
	
	// IInputEventListener
	bool OnInputEvent( const SInputEvent &event );

protected:
	struct SHitRequestHistory
	{
		SHitRequestHistory() {}
		CTimeValue requestTime;
	};

	enum { HIT_HISTORY_COUNT = 16 };		// Note this should match up with serialization policy in HitInfo & KillParams
	typedef std::map<ItemString, CTimeValue> TStringTimeMap;

	IDebugHistoryManager* m_pDebugHistoryManager;
	IDebugHistory* m_pUploadGraph;
	IDebugHistory* m_pDownloadGraph;
	SHitRequestHistory m_hitHistory[HIT_HISTORY_COUNT];
	int m_rollingHitId;
	TStringTimeMap m_purchaseRequests;
	CTimeValue m_prevTime;

	bool m_buttonHeld;
	bool m_perceivedLagEventRecorded;
	float m_timeSinceLastPerceivedLagEvent;
};

#endif // USE_LAGOMETER

#endif // __LAGOMETER_H__


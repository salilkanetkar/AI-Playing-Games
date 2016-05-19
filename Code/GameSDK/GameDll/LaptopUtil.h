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

// Description : Intel Laptop Gaming TDK support.
//               Battery and wireless signal status


#ifndef __LAPTOPUTIL_H__
#define __LAPTOPUTIL_H__

#pragma once

class CLaptopUtil //: public IGameFrameworkListener
{
public:
	CLaptopUtil();
	~CLaptopUtil();

	// Call before getting params. You can call not in each frames
	void Update();

	bool IsLaptop() {return m_isLaptop;}

	// Is Battery like power source
	bool IsBattteryPowerSrc() {return m_isBattery;}
	// Get Battery Life in percent
	int GetBatteryLife() {return m_percentBatLife;}
	// Get Battery Life in second
	unsigned long GetBattteryLifeTime() {return m_secBatLife;}

	bool IsWLan() {return m_isWLan;}
	// Get WLan Signal Strength in percent
	int GetWLanSignalStrength() {return m_signalStrength;}

	/* 
	// IGameFrameworkListener
	virtual void OnPostUpdate(float fDeltaTime);
	virtual void OnSaveGame(ISaveGame* pSaveGame) {};
	virtual void OnLoadGame(ILoadGame* pLoadGame) {};
	virtual void OnLevelEnd(const char* nextLevel) {};
	virtual void OnActionEvent(const SActionEvent& event) {};
	/* */

	static int g_show_laptop_status_test;
	static int g_show_laptop_status;

private:
	void Init();

private:
	bool m_isLaptop;
	unsigned long m_secBatLife;
	int m_percentBatLife;
	bool m_isWLan;
	int m_signalStrength;
	bool m_isBattery;
};



#endif // __LAPTOPUTIL_H__
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

// Description : Iron Sight


#pragma once

#ifndef __SCOPE_H__
#define __SCOPE_H__

#include "IronSight.h"

class CScope : public CIronSight
{
	public:
		CRY_DECLARE_GTI(CScope);

	CScope();

	// IZoomMode
	virtual void Update(float frameTime, uint32 frameId);

	virtual void GetMemoryUsage(ICrySizer * s) const;

	virtual void UpdateFPView(float frameTime) {};
	// ~IZoomMode

	// CIronSight
	virtual void OnEnterZoom();
	virtual void OnLeaveZoom();
	virtual void OnZoomStep(bool zoomingIn, float t);
	virtual void OnZoomedOut();
	virtual void Activate(bool activate);
	virtual bool IsScope() const { return true; }
	// ~CIronSight

protected:
	float					m_showTimer;
	float					m_hideTimer;
	bool					m_musicLogicEventEnterTriggered;
	
private:
	void InformActorOfScope(bool active);
	void ToggleScopeVisionMode(bool enabled, bool toggleOffscreen);
};

#endif // __SCOPE_H__
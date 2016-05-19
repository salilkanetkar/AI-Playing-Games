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

#ifndef __THROWINDICATOR_H__
#define __THROWINDICATOR_H__

#include "IronSight.h"

class CThrowIndicator : public CIronSight
{

public:
	CRY_DECLARE_GTI(CThrowIndicator);

	CThrowIndicator();
	virtual ~CThrowIndicator();

	virtual bool StartZoom(bool stayZoomed = false, bool fullZoomout = true, int zoomStep = 1);
	virtual void StopZoom();
	virtual void ExitZoom(bool force);

	virtual bool IsZoomed() const { return m_indicatorShowing; }

private:

	bool m_indicatorShowing;
};

#endif // __THROWINDICATOR_H__

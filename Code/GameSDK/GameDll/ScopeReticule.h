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

#ifndef __SCOPE_RETICULE_H__
#define __SCOPE_RETICULE_H__


struct SScopeParams;
class CWeapon;



class CScopeReticule
{
private:
	typedef _smart_ptr<IMaterial> TMaterialPtr;

public:
	CScopeReticule();

	void SetMaterial(IMaterial* pMaterial);
	void SetBlinkFrequency(float blink);

	void Disable(float time);
	void Update(CWeapon* pWeapon);

private:
	TMaterialPtr m_scopeReticuleMaterial;
	float m_blinkFrequency;
	float m_disabledTimeOut;
};


#endif

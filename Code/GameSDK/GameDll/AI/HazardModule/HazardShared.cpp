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

//    Various class and types that are shared between the various hazard 
//    module classes.

#include "StdAfx.h"

#include "HazardShared.h"


using namespace HazardSystem;


// ============================================================================
// ============================================================================
// ============================================================================
//
// -- HazardProjectileID -- HazardProjectileID -- HazardProjectileID --
//
// ============================================================================
// ============================================================================
// ============================================================================


void HazardProjectileID::Serialize(TSerialize ser)
{
	ser.BeginGroup("HazardProjectileID");

	ser.Value("ID", m_ID);

	ser.EndGroup();
}


// ============================================================================
// ============================================================================
// ============================================================================
//
// -- HazardSphereID -- HazardSphereID -- HazardSphereID -- HazardSphereID --
//
// ============================================================================
// ============================================================================
// ============================================================================


void HazardSphereID::Serialize(TSerialize ser)
{
	ser.BeginGroup("HazardSphereID");

	ser.Value("ID", m_ID);

	ser.EndGroup();
}

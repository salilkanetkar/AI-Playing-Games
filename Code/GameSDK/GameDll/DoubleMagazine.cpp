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
#include "DoubleMagazine.h"
#include "ICryMannequin.h"



DECLARE_DEFAULT_COMPONENT_FACTORY(CDoubleMagazine, CDoubleMagazine)

CDoubleMagazine::CDoubleMagazine()
	:	m_reloadFaster(true)
{
}



void CDoubleMagazine::OnAttach(bool attach)
{
	m_reloadFaster = true;
}



void CDoubleMagazine::OnParentReloaded()
{
	m_reloadFaster = !m_reloadFaster;
}



void CDoubleMagazine::SetAccessoryReloadTags(CTagState& fragTags)
{
	if (m_reloadFaster)
	{
		TagID clipRemaining = fragTags.GetDef().Find(CItem::sFragmentTagCRCs.doubleclip_fast);
		if(clipRemaining != TAG_ID_INVALID)
			fragTags.Set(clipRemaining, true);
	}
}

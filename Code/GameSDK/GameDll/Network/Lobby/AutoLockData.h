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

// Description : Gameside struct for locking when accessing data that is access from a thread


#include "CryThread.h"

#pragma once

template <class T, class D>
struct SAutoLockData
{
	SAutoLockData(T* pClass, bool tryLock = false)
	{
		if(tryLock)
		{
			if(pClass->___m_mutex.TryLock())
			{
				m_pData = &pClass->___m_private;
				m_pClass = pClass;
			}
			else
			{
				m_pData = NULL;
			}
		}
		else
		{
			pClass->___m_mutex.Lock();
			m_pData = &pClass->___m_private;
			m_pClass = pClass;
		}
	}

	~SAutoLockData()
	{
		if(m_pData)
		{
			m_pClass->___m_mutex.Unlock();
		}
	}

	ILINE bool IsValid()
	{
		return m_pData != NULL;
	}

	ILINE D* Get()
	{
		CRY_ASSERT(m_pData);
		return m_pData;
	}

	ILINE const D* Get() const
	{
		CRY_ASSERT(m_pData);
		return m_pData;
	}

	D* m_pData;
	T* m_pClass;
};


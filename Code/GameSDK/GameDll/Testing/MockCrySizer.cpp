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
#include "MockCrySizer.h"

CMockCrySizer::CMockCrySizer()
: m_totalSize(0)
{

}

void CMockCrySizer::Release()
{

}

size_t CMockCrySizer::GetTotalSize()
{
    return m_totalSize;
}

bool CMockCrySizer::AddObject(const void* identifier, size_t sizeInBytes, int count)
{
    m_totalSize += sizeInBytes;

    return true;
}

IResourceCollector& CMockCrySizer::GetResourceCollector()
{
    CRY_TODO(12, 5, 2009, "We might eventually implement this as a Mock");

    IResourceCollector* nullCollector = 0;

    return *nullCollector;
}

void CMockCrySizer::Push(const char* componentName)
{

}

void CMockCrySizer::PushSubcomponent(const char* subcomponentName)
{

}

void CMockCrySizer::Pop()
{

}

void CMockCrySizer::Reset()
{

}

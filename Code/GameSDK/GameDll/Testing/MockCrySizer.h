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

#ifndef MOCK_CRY_SIZER_H_INCLUDED
#define MOCK_CRY_SIZER_H_INCLUDED

class CMockCrySizer : public ICrySizer
{
public:
    CMockCrySizer();

    virtual void Release();

    virtual size_t GetTotalSize();

    virtual bool AddObject(const void* identifier, size_t sizeInBytes, int count);

    virtual IResourceCollector& GetResourceCollector();

    virtual void Push(const char* componentName);

    virtual void PushSubcomponent(const char* subcomponentName);

    virtual void Pop();

		virtual void Reset();

private:
    size_t m_totalSize;
};

#endif //MOCK_CRY_SIZER_H_INCLUDED

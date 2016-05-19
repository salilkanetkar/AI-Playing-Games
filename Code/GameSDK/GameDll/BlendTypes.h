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

// Description : BlendType interface for ScreenEffects and some implementations
//               Includes also a wrapper implementation (based on ItemScheduler) that 
//               we should use when creating new blends


#ifndef _BLEND_TYPES_H_
#define _BLEND_TYPES_H_

#include "PoolAllocator.h"

//-BlendTypes---------------------------
// Defines a curve to be used by the effect
// Progress is between 0 and 1. Consider it the X, and return the Y.
// The return should also be between 0 and 1.
struct IBlendType
{
	virtual ~IBlendType(){}
	virtual float Blend(float progress) = 0;
	virtual void Release() = 0;
};

// Use this template to create new blends when needed
// class YourBlend { void Blend(float progress) { ... } };
// and use a pBlend = CBlendType<YourBlend>::Create(YourBlend(...));
template <class T>
class CBlendType : public IBlendType
{
	typedef stl::PoolAllocator<sizeof(T) + sizeof(void*), stl::PoolAllocatorSynchronizationSinglethreaded> Alloc;
	static Alloc m_alloc;

public:
	static void FreePool()
	{
		m_alloc.FreeMemory();
	}

public:
	static CBlendType * Create()
	{
		return new (m_alloc.Allocate()) CBlendType();
	}
	static CBlendType * Create( const T& from )
	{
		return new (m_alloc.Allocate()) CBlendType(from);
	}

	float Blend(float progress) { return m_impl.Blend(progress); }
	void Release() 
	{ 
		this->~CBlendType();
		m_alloc.Deallocate(this);
	}
	void GetMemoryStatistics(ICrySizer * s) { s->Add(*this); }

private:
	T m_impl;

	CBlendType() {}
	CBlendType( const T& from ) : m_impl(from) {}
	~CBlendType() {}

};

template <class T>
typename CBlendType<T>::Alloc CBlendType<T>::m_alloc;

//-------------------BLEND TYPES (add here new ones)--------------------------

// Standard linear blend --------------------------------------
class CLinearBlend
{
public:
	
	CLinearBlend(float slope) { m_slope = slope; };
	CLinearBlend()						{ m_slope = 1.0f; };
	virtual ~CLinearBlend()		{};

	virtual float Blend(float progress) 
	{
		return (m_slope * progress);
	}

private:
	
	float m_slope;
};

// A cosin-based curve blend ---------------------------------
class CWaveBlend
{

public:
	
	CWaveBlend() {};
	virtual ~CWaveBlend() {};

	virtual float Blend(float progress) 
	{
		return ((cosf((progress * gf_PI) - gf_PI) + 1.0f)/2.0f);
	}
};

#endif
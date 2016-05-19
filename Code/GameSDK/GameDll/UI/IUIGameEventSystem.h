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

#ifndef __IGameUIEventSystem__
#define __IGameUIEventSystem__

#include <IViewSystem.h>
#include <IPlayerProfiles.h>

struct IUIPseudoRTTI
{
	virtual ~IUIPseudoRTTI() {}
	// do not override this function,
	// use UIEVENTSYSTEM( name ) instead
	virtual const char* GetTypeName() const = 0;
};

struct IUIGameEventSystem : public IUIPseudoRTTI
{
	virtual ~IUIGameEventSystem() {}
	
	virtual void InitEventSystem() = 0;
	virtual void UnloadEventSystem() = 0;

	virtual void UpdateView( const SViewParams &viewParams ) {}
	virtual void OnUpdate( float fDelta ) {}
};
typedef boost::shared_ptr<IUIGameEventSystem> TUIEventSystemPtr;

struct IUIEventSystemFactory
{
	IUIEventSystemFactory()
	{
		m_pNext = 0;
		if (!s_pLast)
			s_pFirst = this;
		else
			s_pLast->m_pNext = this;
		s_pLast = this;
	}

	virtual ~IUIEventSystemFactory(){}
	virtual TUIEventSystemPtr Create() = 0;

	static IUIEventSystemFactory* GetFirst() { return s_pFirst; }
	IUIEventSystemFactory* GetNext() const { return m_pNext; }

private:
	IUIEventSystemFactory* m_pNext;
	static IUIEventSystemFactory* s_pFirst;
	static IUIEventSystemFactory* s_pLast;
};

template <class T>
struct SAutoRegUIEventSystem : public IUIEventSystemFactory
{
	virtual TUIEventSystemPtr Create() { return TUIEventSystemPtr(new T); }
};

#define UIEVENTSYSTEM(name) \
virtual const char* GetTypeName() const { return GetTypeNameS(); } \
static const char* GetTypeNameS() { return name; }


#if defined(WIN32) && defined(_LIB)
#define CRY_EXPORT_STATIC_LINK_VARIABLE( Var ) \
	extern "C" { int lib_func_##Var() { return (int)&Var; } } \
	__pragma( message("#pragma comment(linker,\"/include:_lib_func_"#Var"\")") )
#else
#define CRY_EXPORT_STATIC_LINK_VARIABLE( Var )
#endif

#define REGISTER_UI_EVENTSYSTEM( UIEventSystemClass ) \
	SAutoRegUIEventSystem<UIEventSystemClass> g_AutoRegUIEvent##UIEventSystemClass; \
	CRY_EXPORT_STATIC_LINK_VARIABLE( g_AutoRegUIEvent##UIEventSystemClass );

#endif
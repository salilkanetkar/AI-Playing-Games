#include "StdAfx.h"

#include "CounterTerroristFriend.h"

DECLARE_DEFAULT_COMPONENT_FACTORY(CCounterTerroristFriend, CCounterTerroristFriend)

CCounterTerroristFriend::CCounterTerroristFriend()
{
}

CCounterTerroristFriend::~CCounterTerroristFriend()
{
}

bool CCounterTerroristFriend::Init(IGameObject *pGameObject)
{
	if (!CPlayer::Init(pGameObject))
		return false;

	SetGameObject(pGameObject);

	return true;
}

void CCounterTerroristFriend::PostInit(IGameObject *pGameObject)
{
	CPlayer::PostInit(pGameObject);

	// Enable update function
	pGameObject->EnableUpdateSlot(this, 0);

	// Initialize other components here
}

void CCounterTerroristFriend::Update(SEntityUpdateContext& ctx, int updateSlot)
{
	CPlayer::Update(ctx, updateSlot);

	//gEnv->pLog->Log("Medic Update C++");
}
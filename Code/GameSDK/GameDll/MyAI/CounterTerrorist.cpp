#include "StdAfx.h"

#include "CounterTerrorist.h"

DECLARE_DEFAULT_COMPONENT_FACTORY(CCounterTerrorist, CCounterTerrorist)

CCounterTerrorist::CCounterTerrorist()
{
}

CCounterTerrorist::~CCounterTerrorist()
{
}

bool CCounterTerrorist::Init(IGameObject *pGameObject)
{
	if (!CPlayer::Init(pGameObject))
		return false;

	SetGameObject(pGameObject);

	return true;
}

void CCounterTerrorist::PostInit(IGameObject *pGameObject)
{
	CPlayer::PostInit(pGameObject);

	// Enable update function
	pGameObject->EnableUpdateSlot(this, 0);

	// Initialize other components here
}

void CCounterTerrorist::Update(SEntityUpdateContext& ctx, int updateSlot)
{
	CPlayer::Update(ctx, updateSlot);

	//gEnv->pLog->Log("Medic Update C++");
}
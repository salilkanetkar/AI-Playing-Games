#include "StdAfx.h"

#include "Medic.h"

DECLARE_DEFAULT_COMPONENT_FACTORY(CMedic, CMedic)

CMedic::CMedic()
{
}

CMedic::~CMedic()
{
}

bool CMedic::Init(IGameObject *pGameObject)
{
	if (!CPlayer::Init(pGameObject))
		return false;

	SetGameObject(pGameObject);

	return true;
}

void CMedic::PostInit(IGameObject *pGameObject)
{
	CPlayer::PostInit(pGameObject);

	// Enable update function
	pGameObject->EnableUpdateSlot(this, 0);

	// Initialize other components here
}

void CMedic::Update(SEntityUpdateContext& ctx, int updateSlot)
{
	CPlayer::Update(ctx, updateSlot);

	//gEnv->pLog->Log("Medic Update C++");
}
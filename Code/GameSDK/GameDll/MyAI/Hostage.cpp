#include "StdAfx.h"

#include "Hostage.h"

DECLARE_DEFAULT_COMPONENT_FACTORY(CHostage, CHostage)

CHostage::CHostage()
{
}

CHostage::~CHostage()
{
}

bool CHostage::Init(IGameObject *pGameObject)
{
	if (!CPlayer::Init(pGameObject))
		return false;

	SetGameObject(pGameObject);

	return true;
}

void CHostage::PostInit(IGameObject *pGameObject)
{
	CPlayer::PostInit(pGameObject);

	// Enable update function
	pGameObject->EnableUpdateSlot(this, 0);

	// Initialize other components here
}

void CHostage::Update(SEntityUpdateContext& ctx, int updateSlot)
{
	CPlayer::Update(ctx, updateSlot);

	//gEnv->pLog->Log("Medic Update C++");
}

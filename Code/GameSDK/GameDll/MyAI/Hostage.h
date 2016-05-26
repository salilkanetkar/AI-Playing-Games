
#ifndef __Hostage_H__
#define __Hostage_H__
#include "Player.h"

class CHostage : public CPlayer
{
public:
	DECLARE_COMPONENT_TYPE("CHostage", 0xc19ef39f5f90656a, 0x74af37e73d376278);

	CHostage();
	virtual ~CHostage();

	virtual bool Init(IGameObject *pGameObject);

	virtual void PostInit(IGameObject *pGameObject);

	virtual void Update(SEntityUpdateContext& ctx, int updateSlot);

	void GetMemoryUsage(ICrySizer *pSizer) const{
		pSizer->AddObject(this, sizeof(*this));
		CPlayer::GetInternalMemoryUsage(pSizer);
	}
};

#endif

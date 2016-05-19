
#ifndef __COUNTERTERRORIST_H__
#define __COUNTERTERRORIST_H__
#include "Player.h"

class CCounterTerrorist : public CPlayer
{
public:
	DECLARE_COMPONENT_TYPE("CCounterTerrorist", 0xc585c534bc6dd247, 0xfded033135fc034b);

	CCounterTerrorist();
	virtual ~CCounterTerrorist();

	virtual bool Init(IGameObject *pGameObject);

	virtual void PostInit(IGameObject *pGameObject);

	virtual void Update(SEntityUpdateContext& ctx, int updateSlot);

	void GetMemoryUsage(ICrySizer *pSizer) const{
		pSizer->AddObject(this, sizeof(*this));
		CPlayer::GetInternalMemoryUsage(pSizer);
	}
};

#endif
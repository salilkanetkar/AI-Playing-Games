#ifndef __COUNTERTERRORISTFRIEND_H__
#define __COUNTERTERRORISTFRIEND_H__
#include "Player.h"

class CCounterTerroristFriend : public CPlayer
{
public:
	DECLARE_COMPONENT_TYPE("CCounterTerroristFriend", 0xc585c534bc6dd456, 0xfded033135fc095b);

	CCounterTerroristFriend();
	virtual ~CCounterTerroristFriend();

	virtual bool Init(IGameObject *pGameObject);

	virtual void PostInit(IGameObject *pGameObject);

	virtual void Update(SEntityUpdateContext& ctx, int updateSlot);

	void GetMemoryUsage(ICrySizer *pSizer) const{
		pSizer->AddObject(this, sizeof(*this));
		CPlayer::GetInternalMemoryUsage(pSizer);
	}
};

#endif
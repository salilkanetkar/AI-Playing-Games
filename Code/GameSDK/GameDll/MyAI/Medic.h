#ifndef __MEDIC_H__
#define __MEDIC_H__

#include "Player.h"

class CMedic : public CPlayer
{
public:
	DECLARE_COMPONENT_TYPE("CMedic", 0xe646be4075e41351, 0xb54c0b774b5d88d9)

	CMedic();
	virtual ~CMedic();

	/* Override member functions */

	// Called when entity is placed in the editor
	virtual bool Init(IGameObject * pGameObject);

	// Called once entity is first ready
	virtual void PostInit(IGameObject * pGameObject);

	// Called on every frame
	virtual void Update(SEntityUpdateContext& ctx, int updateSlot);

	void GetMemoryUsage(ICrySizer *pSizer) const
	{
		pSizer->AddObject(this, sizeof(*this));
		CPlayer::GetInternalMemoryUsage(pSizer); // collect memory of parent class
	}
};

#endif //__MEDIC_H__
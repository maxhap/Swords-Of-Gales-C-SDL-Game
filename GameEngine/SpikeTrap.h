#ifndef _SPIKETRAP_
#define _SPIKETRAP_

#include "stdafx.h"

class SpikeTrap : public Trap
{

public:

	SpikeTrap( int objectID, int damage, int activationPeriod, int x, int y, int width, int height, string spriteLocation, int startingAngle, int movementSpeed, bool hittable );
	~SpikeTrap();

	inline bool HasColided( GameObject* otherItem );

	bool Update( bool nocollision, bool includeAI = false  );

private:

	int _ActivationPeriod;

	bool _HitPlayer;

	void BuildSpriteMap();

	void SetSprite();
};



#endif
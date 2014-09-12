#ifndef _TRAPS_
#define _TRAPS_

#include "stdafx.h" 

class Trap : public GameObject
{

public:

	Trap( int objectID, int damage, int x, int y, int width, int height, string spriteLocation, int startingAngle, int movementSpeed, bool hittable );
	~Trap();

	virtual bool Update( bool nocollision, bool includeAI = false );

	bool GetIsActive();

	void SetIsActive( bool active );


protected:

	int _Damage;
	int _State;

	bool _Active;

	virtual void Animate();

};

#endif
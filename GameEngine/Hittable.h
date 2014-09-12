#ifndef _HITTABLE_
#define _HITTABLE_

#include "stdafx.h"

class Hittable
{

public: 

	Hittable( bool isHittable );
	~Hittable();

	bool GetIsHittable();
	void virtual TakeHit( int dmg );

private:

	bool _IsHittable;

};

#endif
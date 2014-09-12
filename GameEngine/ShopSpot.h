#ifndef _SHOPSPOT_
#define _SHOPSPOT_

#include "stdafx.h"

class ShopSpot : public InteractableGameObject
{

public:

	ShopSpot( int objectID, int x, int y, int width, int height, int startingAngle, int movementSpeed, string spriteLocation, bool isHittable );
	~ShopSpot();
	
	bool HasColided( GameObject* otherItem );

	void Interact();

private:



};

#endif
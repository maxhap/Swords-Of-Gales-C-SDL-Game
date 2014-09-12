#include "stdafx.h"

House::House( int objectType, int x, int y, int width, int height, int startingAngle, int movementSpeed, string spriteLocation, bool isHittable, int doorX, int doorY, int doorWidth, int doorHeight , string forwardLevel, string entryPointID ) : GameObject( objectType, x, y, width, height, startingAngle, 0, spriteLocation, false ), ExitPoint( forwardLevel, entryPointID )
{
	_ObjectType = Initialize::House;
	_pDoor = new SDL_Rect();
	_pDoor->x = doorX + x;
	_pDoor->y = doorY + y;
	_pDoor->w = doorWidth;
	_pDoor->h = doorHeight;
}

House::~House()
{
	delete _pDoor;
}

bool House::HasColided( GameObject* otherItem )
{
	bool collision = Object::HasColided( otherItem );

	if( collision && otherItem != NULL )
	{
		if( otherItem->GetObjectType() == Initialize::Player )
		{
			bool colidedWithDoor = otherItem->HasColidedRect( _pDoor );

			if( colidedWithDoor )
			{
				Activate();
			}
		}
	}

	return collision;
}
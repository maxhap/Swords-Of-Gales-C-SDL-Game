#include "stdafx.h"

Grass::Grass( int objectID, int x, int y, int width, int height, int startingAngle, int movementSpeed, string spriteLocation, bool isHittable ): GameObject( objectID, x, y, width, height, startingAngle, movementSpeed, spriteLocation, isHittable )
{
	_ObjectType = Initialize::Grass;
}

Grass::~Grass()
{
}

bool Grass::HasColided( GameObject* otherItem )
{
	bool colided = Object::HasColided( otherItem );

	if( colided )
	{
		if( WithinToCropSprite( otherItem->Container() )== true )
		{
			otherItem->SetMovingOnThickTorain( true );
		}
		else
		{
			otherItem->SetMovingOnThickTorain( false );
		}
	}
	else
	{
		otherItem->SetMovingOnThickTorain( false );
	}

	return false;
}

bool Grass::WithinToCropSprite( SDL_Rect* otherObject )
{
	if( _Container->x <= otherObject->x  && ( _Container->x + _Container->w ) > ( otherObject->x + otherObject->w ) )
	{
		if(_Container->y <= otherObject->y  && ( _Container->y + _Container->h ) > ( otherObject->y + otherObject->h ) )
		{
			return true;
		}	
	}

	return false;
}
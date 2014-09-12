#include "stdafx.h"

Heart::Heart( int objectID, int x, int y, int width, int height, string spriteLocation ) : Item( objectID, x, y, width, height, spriteLocation )
{

}

Heart::~Heart()
{

}

bool Heart::Aquire()
{
	GameObjectHolder::instance().GetPlayer()->RestoreHealth( 4 );

	return false;
}
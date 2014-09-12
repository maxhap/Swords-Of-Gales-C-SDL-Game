#include "stdafx.h"

GreenRupee::GreenRupee( int objectID, int x, int y, int width, int height, string spriteLocation ) : Item( objectID, x, y, width, height, spriteLocation )
{

}

GreenRupee::~GreenRupee()
{

}

bool GreenRupee::Aquire()
{
	GameObjectHolder::instance().GetPlayer()->ChangeRupeeAmount( 1 );

	return false;
}
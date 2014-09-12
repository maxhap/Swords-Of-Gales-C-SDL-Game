#include "stdafx.h"

Door::Door( int objectType, int x, int y, int width, int height, int startingAngle, string spriteLocation, string forwardLevel, string entryPointID ) : GameObject( objectType, x, y, width, height, startingAngle, 0, spriteLocation, false ), ExitPoint( forwardLevel, entryPointID )
{
	_ObjectType = Initialize::Door;
}

Door::~Door()
{

}

bool Door::HasColided( GameObject* otherItem )
{
	bool collision = Object::HasColided( otherItem );
	
	if( otherItem != NULL )
	{
		if( collision )
		{
			if( otherItem->GetObjectType() == Initialize::Player )
			{
				Activate();
			}
		}
	}

	return collision;
}
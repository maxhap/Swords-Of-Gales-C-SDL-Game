#include "stdafx.h"

Hagle::Hagle( int objectType, int x, int y, int width, int height, int startinAngle, int movementSpeed, string spriteLocation, int healthAmount, bool isHittable, int areaOfSight ) : MeeleEnemy ( objectType, x, y, width, height, startinAngle, movementSpeed, spriteLocation, healthAmount, isHittable, areaOfSight )
{
	BuildSpriteMap();
	_ObjectType = Initialize::Hagle;
}

Hagle::~Hagle()
{

}

//overrides
void Hagle::BuildSpriteMap()
{
	//build down
	vector<Point> up;
	up.insert( up.end(), 1, Point( 2, 0, 38, 34 ) );
	up.insert( up.end(), 1, Point( 47, 0, 38, 34 ) );

	_SpriteMap->insert( _SpriteMap ->end(), 1, up );

	//build up
	vector<Point> down;
	down.insert( down.end(), 1, Point( 2, 56, 41, 34 ) );
	down.insert( down.end(), 1, Point( 49, 56 , 41, 34 ) );

	_SpriteMap->insert( _SpriteMap ->end(), 1, down );

	//build left
	vector<Point> left;
	left.insert( left.end(), 1, Point( 2, 96, 38, 34 ) );
	left.insert( left.end(), 1, Point( 47, 96, 38, 34 ) );

	_SpriteMap->insert( _SpriteMap ->end(), 1, left );

	//build right
	vector<Point> right;
	right.insert( right.end(), 1, Point( 2, 145, 38, 34 ) );
	right.insert( right.end(), 1, Point( 47, 145, 48, 34 ) );

	_SpriteMap->insert( _SpriteMap ->end(), 1, right );
}
#include "stdafx.h"

Player::Player( int objectType, int x, int y, int width, int height, int startinAngle, int movementSpeed, string spriteLocation, int maxHealth, int healthAmount, bool isHittable, int RupeeAmount, int arrowAmount, int interactionX, int interactionY, int interactionWidth, int interactionHeight ) : AttackModuleHolder(), InventoryItemHolder(), Health( maxHealth, healthAmount ), Character( objectType, x, y, width, height, startinAngle, movementSpeed, spriteLocation, isHittable ,interactionX, interactionY, interactionWidth, interactionHeight )
{
	_RupeeAmount = RupeeAmount;
	_ArrowAmount = arrowAmount;

	_IsInteractable = true;

	_ObjectType = Initialize::Player;

	BuildSpriteMap();
}

Player::~Player()
{

}

bool Player::ChangeRupeeAmount( int amount ) 
{
	int amountToBe = _RupeeAmount + amount;

	if( amountToBe >= 0 )
	{
		_RupeeAmount += amount;
		return true;
	}

	return false;
}

int Player::GetRupeeAmount()
{
	return _RupeeAmount;
}

int Player::GetArrowAmount()
{
	return _ArrowAmount;
}

void Player::ChangeArrowAmount( int amount )
{
	_ArrowAmount += amount;
}

void Player::BuildSpriteMap()
{
	//build down
	vector<Point> up;
	up.insert( up.end(), 1, Point( 10, 0, 48, 48 ) );
	up.insert( up.end(), 1, Point( 70, 0, 48, 48) );
	up.insert( up.end(), 1, Point( 130, 0, 48, 48 ) );
	up.insert( up.end(), 1, Point( 190, 0, 48, 48 ) );
	up.insert( up.end(), 1, Point( 250, 0, 48, 48 ) );
	up.insert( up.end(), 1, Point( 310, 0, 48, 48 ) );
	up.insert( up.end(), 1, Point( 370, 0, 48, 48 ) );
	up.insert( up.end(), 1, Point( 430, 0, 48, 48 ) );
	up.insert( up.end(), 1, Point( 490, 0, 48, 48 ) );
	up.insert( up.end(), 1, Point( 550, 0, 48, 48 ) );

	_SpriteMap->insert( _SpriteMap ->end(), 1, up );

	//build up
	vector<Point> down;
	down.insert( down.end(), 1, Point( 10, 55, 48, 48 ) );
	down.insert( down.end(), 1, Point( 70, 55 , 48, 48) );
	down.insert( down.end(), 1, Point( 130, 55, 48, 48 ) );
	down.insert( down.end(), 1, Point( 190, 55, 48, 48 ) );
	down.insert( down.end(), 1, Point( 250, 55, 48, 48 ) );
	down.insert( down.end(), 1, Point( 310, 55, 48, 48 ) );
	down.insert( down.end(), 1, Point( 370, 55, 48, 48 ) );
	down.insert( down.end(), 1, Point( 430, 55, 48, 48 ) );
	down.insert( down.end(), 1, Point( 490, 55, 48, 48 ) );
	down.insert( down.end(), 1, Point( 550, 55, 48, 48 ) );

	_SpriteMap->insert( _SpriteMap ->end(), 1, down );

	//build left
	vector<Point> left;
	left.insert( left.end(), 1, Point( 10, 106, 48, 48 ) );
	left.insert( left.end(), 1, Point( 70, 106, 48, 48 ) );
	left.insert( left.end(), 1, Point( 130, 106, 48, 48 ) );
	left.insert( left.end(), 1, Point( 190, 106, 48, 48) );
	left.insert( left.end(), 1, Point( 250, 106, 48, 48 ) );
	left.insert( left.end(), 1, Point( 310, 106, 48, 48 ) );
	left.insert( left.end(), 1, Point( 370, 106, 48, 48 ) );
	left.insert( left.end(), 1, Point( 430, 106, 48, 48 ) );
	left.insert( left.end(), 1, Point( 490, 106, 48, 48) );
	left.insert( left.end(), 1, Point( 550, 106, 48, 48 ) );

	_SpriteMap->insert( _SpriteMap ->end(), 1, left );

	//build right
	vector<Point> right;
	right.insert( right.end(), 1, Point( 10, 160, 48, 48 ) );
	right.insert( right.end(), 1, Point( 70, 160, 48, 48 ) );
	right.insert( right.end(), 1, Point( 130, 160, 48, 48 ) );
	right.insert( right.end(), 1, Point( 190, 160, 48, 48 ) );
	right.insert( right.end(), 1, Point( 250, 160, 48, 48 ) );
	right.insert( right.end(), 1, Point( 310, 160, 48, 48 ) );
	right.insert( right.end(), 1, Point( 370, 160, 48, 48 ) );
	right.insert( right.end(), 1, Point( 430, 160, 48, 48 ) );
	right.insert( right.end(), 1, Point( 490, 160, 48, 48 ) );
	right.insert( right.end(), 1, Point( 550, 160, 48, 48 ) );

	_SpriteMap->insert( _SpriteMap ->end(), 1, right );

	//build sword down	
	vector<Point> sdown;
	sdown.insert( sdown.end(), 1, Point( 3, 208, 57, 55 ) );
	sdown.insert( sdown.end(), 1, Point( 88, 208, 57, 55 ) );
	sdown.insert( sdown.end(), 1, Point( 165, 208, 57, 70 ) );
	sdown.insert( sdown.end(), 1, Point( 254, 208, 57, 70 ) );
	sdown.insert( sdown.end(), 1, Point( 332, 208, 57, 70 ) );
	sdown.insert( sdown.end(), 1, Point( 412, 208, 57, 70 ) );
	sdown.insert( sdown.end(), 1, Point( 482, 208, 63, 55 ) );

	_SpriteMap->insert( _SpriteMap ->end(), 1,sdown );

	//build sword up
	vector<Point> sup;
	sup.insert( sup.end(), 1, Point( 12, 286, 54, 72 ) );
	sup.insert( sup.end(), 1, Point( 87, 286, 54, 72 ) );
	sup.insert( sup.end(), 1, Point( 166, 286, 54, 72 ) );
	sup.insert( sup.end(), 1, Point( 255, 286, 54, 72 ) );
	sup.insert( sup.end(), 1, Point( 340, 286, 58, 72 ) );
	sup.insert( sup.end(), 1, Point( 420, 286, 58, 72 ) );
	sup.insert( sup.end(), 1, Point( 484, 286, 60, 72 ) );

	_SpriteMap->insert( _SpriteMap ->end(), 1, sup );

	//build sword left
	vector<Point> sleft;
	sleft.insert( sleft.end(), 1, Point( 4, 374, 65, 48 ) );
	sleft.insert( sleft.end(), 1, Point( 79, 374, 65, 48 ) );
	sleft.insert( sleft.end(), 1, Point( 159, 374, 65, 48 ) );
	sleft.insert( sleft.end(), 1, Point( 239, 374, 65, 48 ) );
	sleft.insert( sleft.end(), 1, Point( 325, 374, 65, 48 ) );

	_SpriteMap->insert( _SpriteMap ->end(), 1, sleft );

	//build sword right
	vector<Point> sright;
	sright.insert( sright.end(), 1, Point( 6, 438, 72, 54 ) );
	sright.insert( sright.end(), 1, Point( 72, 438, 72, 54 ) );
	sright.insert( sright.end(), 1, Point( 235, 438, 72, 54 ) );
	sright.insert( sright.end(), 1, Point( 322, 438, 72, 54 ) );

	_SpriteMap->insert( _SpriteMap ->end(), 1, sright );

	//build bow down	
	vector<Point> rdown;
	rdown.insert( rdown.end(), 1, Point( 8, 528, 42, 52 ) );
	rdown.insert( rdown.end(), 1, Point( 66, 528, 42, 52 ) );
	rdown.insert( rdown.end(), 1, Point( 125, 528, 42, 52 ) );
	rdown.insert( rdown.end(), 1, Point( 182, 528, 42, 52 ) );
	rdown.insert( rdown.end(), 1, Point( 241, 528, 42, 52 ) );
	rdown.insert( rdown.end(), 1, Point( 300, 528, 45, 52 ) );	

	_SpriteMap->insert( _SpriteMap ->end(), 1,rdown );

	//build bow up
	vector<Point> bup;
	bup.insert( bup.end(), 1, Point( 8, 592, 42, 52 ) );
	bup.insert( bup.end(), 1, Point( 66, 592, 42, 52 ) );
	bup.insert( bup.end(), 1, Point( 125, 592, 24, 52 ) );
	bup.insert( bup.end(), 1, Point( 182, 592, 42, 52 ) );
	bup.insert( bup.end(), 1, Point( 241, 592, 42, 52 ) );
	bup.insert( bup.end(), 1, Point( 300, 592, 42, 52 ) );	

	_SpriteMap->insert( _SpriteMap ->end(), 1, bup );

	//build bow left
	vector<Point> bleft;
	bleft.insert( bleft.end(), 1, Point( 8, 652, 42, 52 ) );
	bleft.insert( bleft.end(), 1, Point( 66, 652, 42, 52 ) );
	bleft.insert( bleft.end(), 1, Point( 125, 652, 42, 52 ) );
	bleft.insert( bleft.end(), 1, Point( 182, 652, 42, 52 ) );
	bleft.insert( bleft.end(), 1, Point( 241, 652, 42, 52 ) );
	bleft.insert( bleft.end(), 1, Point( 300, 652, 42, 52 ) );

	_SpriteMap->insert( _SpriteMap ->end(), 1, bleft );

	//build bow right
	vector<Point> bright;
	bright.insert( bright.end(), 1, Point( 8, 711, 42, 52 ) );
	bright.insert( bright.end(), 1, Point( 66, 711, 42, 52 ) );
	bright.insert( bright.end(), 1, Point( 125, 711, 42, 52 ) );
	bright.insert( bright.end(), 1, Point( 182, 711, 42, 52 ) );
	bright.insert( bright.end(), 1, Point( 242, 711, 42, 52 ) );
	bright.insert( bright.end(), 1, Point( 307, 711, 42, 52 ) );
	
	_SpriteMap->insert( _SpriteMap ->end(), 1, bright );
}


void Player::TakeHit( int Damage )
{
	ReduceHealth( Damage );
}
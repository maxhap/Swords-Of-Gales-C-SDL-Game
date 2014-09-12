#include "stdafx.h"

SpikeTrap::SpikeTrap( int objectID, int damage, int activationPeriod, int x, int y, int width, int height, string spriteLocation, int startingAngle, int movementSpeed, bool hittable ) : Trap( objectID, damage, x, y, width, height, spriteLocation, startingAngle, movementSpeed, hittable )		
{
	_ActivationPeriod = activationPeriod;	

	_ObjectType = Initialize::SpikeTrap;	
	
	_HitPlayer = false;

	BuildSpriteMap();
}

SpikeTrap::~SpikeTrap()
{

}

bool SpikeTrap::Update( bool nocollision, bool includeAI )
{
	if( _State < _ActivationPeriod )
	{
		_State++;
	}
	else
	{		
		_Active = ( _Active == true ) ? false : true;
		_State = 0;
		SetSprite();
		_HitPlayer = false;
	}

	return true;
}

void SpikeTrap::SetSprite()
{
	for( vector< vector<Point> >::iterator i = _SpriteMap->begin(); i < _SpriteMap->end(); i++ )
	{
		bool set = false;
		
		int pos = abs( ( _SpriteMap->begin() - i ) );

		if( pos == _CurrentSpritePossitionY )
		{
			vector<Point> pointvect = ( *i );

			int location = ( _Active == true ) ? 1 : 0;

			int possition = 0;

			for( vector<Point>::iterator z = pointvect.begin(); z < pointvect.end(); z++, possition++ )
			{
				if( possition == location )
				{					
					Point point = ( *z );

					_pSpriteClip->x = point.X;
					_pSpriteClip->y = point.Y;
					_pSpriteClip->w = point.Width;
					_pSpriteClip->h = point.Height;

					set = true;
					break;
				}
			}

			if( set )
			{
				break;
			}
		}
	}
}

void SpikeTrap::BuildSpriteMap()
{
	vector<Point> up;
	up.insert( up.end(), 1, Point( 0, 0, 60, 60 ) );
	up.insert( up.end(), 1, Point( 70, 0, 60, 60 ) );
	
	_SpriteMap->insert( _SpriteMap ->end(), 1, up );
}

bool SpikeTrap::HasColided( GameObject* otherItem )
{
	if( otherItem->GetObjectType() == Initialize::Player )
	{
		if( _Active && !_HitPlayer )
		{
			bool colided = Object::HasColided( otherItem );

			if( colided )
			{
				GameObjectHolder::instance().GetPlayer()->TakeHit( _Damage );
				_HitPlayer = true;
			}
		}
	}

	return false;
}
#include "stdafx.h"

Object::Object( int objectID, int x, int y, int width, int height, string spriteLocation )
{
	_ObjectID = objectID;

	_Container = new SDL_Rect();
	_Container->x = x;
	_Container->y = y;
	_Container->w = width;
	_Container->h = height;

	_pSprite = NULL;

	_ObjectSpriteLocation = spriteLocation;

	_pSpriteClip = new SDL_Rect();
	_pSpriteClip->h = height;
	_pSpriteClip->w = width;
	_pSpriteClip->x = 0;
	_pSpriteClip->y = 0;

	_CurrentSpritePossitionX = 0;
	_CurrentSpritePossitionY = 0;

	_SpriteMap = new vector< vector<Point> >();

	_WalkingOnThickTorrain = false;

	_pCollisionBox = new SDL_Rect();
	_pCollisionBox->x = x;
	_pCollisionBox->y = y + ( height / 2 );
	_pCollisionBox->h = height /2;
	_pCollisionBox->w = width;

	_DrawAfterMark = NOMARK;
	_AlwaysDrawBefore = false;
}

Object::~Object()
{
	delete _Container;
	delete _pCollisionBox;
	delete _pSpriteClip;
	delete _SpriteMap;	
	delete _pSprite;
}

SDL_Rect* Object::Container() const
{
	return _Container;
}

bool Object::LoadItemImage()
{
	_pSprite = ImageLoader::instance().Load( _ObjectSpriteLocation );

	if( _pSprite == NULL )
	{
		return false;
	}

	return true;
}

void Object::SetAbsolutePosition( int x, int y )
{
	_Container->x = x;
	_Container->y = y;

	_pCollisionBox->x = x;
	_pCollisionBox->y = y + ( _Container->h / 2 );
}

bool Object::HasColided( GameObject* otherItem )
{
	int thisItemL = _pCollisionBox->x;
	int thisItemT = _pCollisionBox->y;
	int thisItemR = _pCollisionBox->x + _pCollisionBox->w;
	int thisItemB = _pCollisionBox->y + _pCollisionBox->h;

	//detect from other game item
	if( otherItem != NULL )
	{
		int otherItemL = otherItem->CollisionBox()->x;
		int otherItemT = otherItem->CollisionBox()->y;
		int otherItemR = otherItem->CollisionBox()->x + otherItem->CollisionBox()->w;
		int otherItemB = otherItem->CollisionBox()->y + otherItem->CollisionBox()->h;

		if( thisItemL > otherItemR )
		{
			return false;
		}

		if( thisItemR < otherItemL )
		{
			return false;
		}

		if( thisItemT > otherItemB )
		{
			return false;
		}

		if( thisItemB < otherItemT )
		{
			return false;
		}
	}
	//detect from level boundories 
	else
	{
		if( thisItemL < 0 )
		{
			return false;
		}

		if( thisItemR > LevelSystem::instance().GetCurrentLevel()->GetContainer()->w )
		{
			return false;
		}

		if( thisItemT < 0 )
		{
			return false;
		}

		if( thisItemB > LevelSystem::instance().GetCurrentLevel()->GetContainer()->h )
		{
			return false;
		}
	}

	return true;
}

bool Object::HasColidedRect( SDL_Rect* otherItemRect )
{
	int thisItemL = _Container->x;
	int thisItemT = _Container->y;
	int thisItemR = _Container->x + _Container->w;
	int thisItemB = _Container->y + _Container->h;

	//detect from other game item
	if( otherItemRect != NULL )
	{
		int otherItemL = otherItemRect->x;
		int otherItemT = otherItemRect->y;
		int otherItemR = otherItemRect->x + otherItemRect->w;
		int otherItemB = otherItemRect->y + otherItemRect->h;

		if( thisItemL > otherItemR )
		{
			return false;
		}

		if( thisItemR < otherItemL )
		{
			return false;
		}

		if( thisItemT > otherItemB )
		{
			return false;
		}

		if( thisItemB < otherItemT )
		{
			return false;
		}
	}
	//detect from level boundories 
	else
	{
		if( thisItemL < 0 )
		{
			return false;
		}

		if( thisItemR > LevelSystem::instance().GetCurrentLevel()->GetContainer()->w )
		{
			return false;
		}

		if( thisItemT < 0 )
		{
			return false;
		}

		if( thisItemB > LevelSystem::instance().GetCurrentLevel()->GetContainer()->h )
		{
			return false;
		}
	}

	return true;
}

SDL_Rect* Object::CollisionBox() const
{
	return _pCollisionBox;
}

void Object::Draw( MainWnd* window, Camora* camora )
{
	if( _pSprite != NULL && _ObjectSpriteLocation != "" )
	{
		SDL_Rect location;
		location.x = _Container->x - camora->GetRect()->x ;
		location.y = _Container->y - camora->GetRect()->y;
		
		//only draw if in viewing range
		if( _Container->x  <= ( camora->GetRect()->x + camora->GetRect()->w ) && 
			_Container->y  <= ( camora->GetRect()->y + camora->GetRect()->h ) &&
			( _Container->x + _Container->w ) >= camora->GetRect()->x &&
			( _Container->y + _Container->h ) >= camora->GetRect()->y )
		{
			
			SDL_Rect ultraClip;
			ultraClip.x = 0;
			ultraClip.y = 0;
			ultraClip.h = 0;
			ultraClip.w = 0;

			//clip if need be
		    if( ( _Container->x + _Container->w ) <= ( camora->GetRect()->x + camora->GetRect()->w ) &&  
				( _Container->y + _Container->h ) <= ( camora->GetRect()->y + camora->GetRect()->h ) &&
				( _Container->x ) >= ( camora->GetRect()->x ) &&
				( _Container->y ) >= ( camora->GetRect()->y ) )
			{
				//image in viewing space, blot without problem
				if( _WalkingOnThickTorrain )
				{
					ultraClip.x = _pSpriteClip->x;
					ultraClip.y = _pSpriteClip->y;
					ultraClip.h =  _pSpriteClip->h / 2 + 3;
					ultraClip.w = _pSpriteClip->w;

					window->RenderToScreen( _pSprite, &location,  &ultraClip );
				}
				else
				{
					window->RenderToScreen( _pSprite, &location,  _pSpriteClip );
				}

				return;

			}
			else if( ( _Container->x + _Container->w ) >= ( camora->GetRect()->x + camora->GetRect()->w ) && 
				_Container->x <= ( camora->GetRect()->x + camora->GetRect()->w ) && 
				_Container->y >= camora->GetRect()->y &&
				( _Container->y + _Container->h ) <= ( camora->GetRect()->y + camora->GetRect()->h) )
			{
				//clip right side
				
				ultraClip.x = _pSpriteClip->x;
				ultraClip.y = _pSpriteClip->y;

				ultraClip.h =  _pSpriteClip->h;
				ultraClip.w =  ( camora->GetRect()->x + camora->GetRect()->w ) - _Container->x;

				//image in viewing space, blot with new clipping space
			}
			else if( ( _Container->x + _Container->w ) >= ( camora->GetRect()->x ) && 
				_Container->x <= ( camora->GetRect()->x ) &&
				_Container->y >= camora->GetRect()->y &&
				( _Container->y + _Container->h ) <= ( camora->GetRect()->y + camora->GetRect()->h) )
			{
				//clip left of camora	

				ultraClip.x = _pSpriteClip->x + ( camora->GetRect()->x - _Container->x );
				ultraClip.y = _pSpriteClip->y;

				ultraClip.h =  _pSpriteClip->h;
				ultraClip.w =  ( _Container->x + _Container->w ) - camora->GetRect()->x;

				location.x = 0;

				//image in viewing space, blot with new clipping space				
			}
			else if ( ( _Container->y + _Container->h ) >= ( camora->GetRect()->y ) && 
				_Container->y <= ( camora->GetRect()->y ) &&
				( _Container->x ) >= camora->GetRect()->x &&
				( _Container->x + _Container->w) <= ( camora->GetRect()->x + camora->GetRect()->w ) )
			{

				//clip above of camora
				ultraClip.x = _pSpriteClip->x;
				ultraClip.y = _pSpriteClip->y + ( camora->GetRect()->y - _Container->y );

				ultraClip.h =  ( _Container->y + _Container->h ) - camora->GetRect()->y;
				ultraClip.w =  _pSpriteClip->w;

				location.y = 0;

				//image in viewing space, blot with new clipping space
			}
			else if ( ( _Container->y + _Container->h ) >= ( camora->GetRect()->y + camora->GetRect()->h ) && 
				_Container->y <= ( camora->GetRect()->y + camora->GetRect()->h ) &&
				( _Container->x ) >= camora->GetRect()->x &&
				( _Container->x + _Container->w) <= ( camora->GetRect()->x + camora->GetRect()->w) )
			{
				//clip bleow camora							

				ultraClip.x = _pSpriteClip->x;
				ultraClip.y = _pSpriteClip->y;

				ultraClip.h =  ( camora->GetRect()->y + camora->GetRect()->h  ) - _Container->y;
				ultraClip.w =  _pSpriteClip->w;

				//image in viewing space, blot with new clipping space
			}
			else if ( _Container->x < camora->GetRect()->x && 
				    ( _Container->x + _Container->w ) > camora->GetRect()->x &&
					_Container->y < camora->GetRect()->y &&
					( _Container->y + _Container->h ) > camora->GetRect()->y )
			{
				//clip top left corner		

				ultraClip.x = _pSpriteClip->x + ( camora->GetRect()->x - _Container->x );
				ultraClip.y = _pSpriteClip->y + ( camora->GetRect()->y - _Container->y );

				ultraClip.h =  ( _Container->y + _Container->h ) - camora->GetRect()->y;
				ultraClip.w =  ( _Container->x + _Container->w ) - camora->GetRect()->x;

				location.y = 0;
				location.x = 0;

				//image in viewing space, blot with new clipping space
			}
			else if ( ( _Container->x + _Container->w ) > ( camora->GetRect()->x + camora->GetRect()->w ) && 
				    _Container->x  < ( camora->GetRect()->x + camora->GetRect()->w ) &&
					_Container->y < camora->GetRect()->y &&
					( _Container->y + _Container->h ) > camora->GetRect()->y )
			{

				//clip top right corner						
				ultraClip.x = _pSpriteClip->x;
				ultraClip.y = _pSpriteClip->y + ( camora->GetRect()->y - _Container->y );

				ultraClip.h =  ( _Container->y + _Container->h ) - camora->GetRect()->y ;
				ultraClip.w =   ( camora->GetRect()->x + camora->GetRect()->w ) - _Container->x;

				location.y = 0;

				//image in viewing space, blot with new clipping space
			}
			else if ( ( _Container->x + _Container->w ) > ( camora->GetRect()->x + camora->GetRect()->w ) && 
				    _Container->x  < ( camora->GetRect()->x + camora->GetRect()->w ) &&
					_Container->y < ( camora->GetRect()->y + camora->GetRect()->h ) &&
					( _Container->y + _Container->h ) > ( camora->GetRect()->y + camora->GetRect()->h ) )
			{
				//clip bottom right corner							

				ultraClip.x = _pSpriteClip->x;
				ultraClip.y = _pSpriteClip->y;

				ultraClip.h =  ( camora->GetRect()->y + camora->GetRect()->h ) - _Container->y;
				ultraClip.w =  ( camora->GetRect()->x + camora->GetRect()->w ) - _Container->x;

				//image in viewing space, blot with new clipping 				
			}
			else if ( _Container->x < camora->GetRect()->x && 
				    ( _Container->x + _Container->w ) > camora->GetRect()->x &&
					( _Container->y + _Container->h ) > ( camora->GetRect()->y + camora->GetRect()->h ) &&
					( _Container->y ) < ( camora->GetRect()->y + camora->GetRect()->h ) )
			{
				//clip bottom left corner							
				ultraClip.x = _pSpriteClip->x + ( camora->GetRect()->x - _Container->x );
				ultraClip.y = _pSpriteClip->y;

				ultraClip.h =  ( camora->GetRect()->y + camora->GetRect()->h ) - _Container->y;
				ultraClip.w =  ( _Container->x + _Container->w ) - camora->GetRect()->x;

				location.x = 0;

				//image in viewing space, blot with new clipping space					
			}

			window->RenderToScreen( _pSprite, &location,  &ultraClip );

		}
	}
}

void Object::BuildSpriteMap()
{
	//error message
	ErrorSystem::instance().WriteObjectError( _ObjectID, "No sprite map implemented" );
}

int Object::GetID()
{
	return _ObjectID;
}

void Object::SetMovingOnThickTorain( bool thick )
{
	_WalkingOnThickTorrain = thick;
}

bool Object::CheckIsAbove( SDL_Rect* otherItemRect )
{
	if( _Container->y < otherItemRect->y )
	{
		return true;
	}
	else if( _Container->y > otherItemRect->y && ( _Container->y + _Container->h ) < ( otherItemRect->y + otherItemRect->h ) )
	{
		return true;
	}

	return false;
}

void Object::SetDrawMark( int set )
{
	_DrawAfterMark = set;
}

int Object::GetDrawMark()
{
	return _DrawAfterMark;
}

bool Object::GetAlwaysDrawBefore()
{
	return _AlwaysDrawBefore;
}

void Object::SetAlwaysDrawBefore( bool val )
{
	_AlwaysDrawBefore = val;
}
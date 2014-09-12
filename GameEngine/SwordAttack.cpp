#include "stdafx.h"

SwordAttack::SwordAttack( int identity, int width, int height, int damage, int reach, GameObject* objectAttachedTo, bool isTogle, string backgroundImageLocation, string activeImageLocation ) : Attack( identity, width, height, damage, reach,  objectAttachedTo, isTogle, backgroundImageLocation, activeImageLocation ) 
{
}

SwordAttack::~SwordAttack()
{
	
}

bool SwordAttack::HasColided( GameObject* otherObject )
{
	int thisItemL = _pVirtualContainer->x;
	int thisItemT = _pVirtualContainer->y;
	int thisItemR = _pVirtualContainer->x + _pVirtualContainer->w;
	int thisItemB = _pVirtualContainer->y + _pVirtualContainer->h;

	//detect from other game item
	if( otherObject != NULL )
	{
		int otherItemL = otherObject->Container()->x;
		int otherItemT = otherObject->Container()->y;
		int otherItemR = otherObject->Container()->x + otherObject->Container()->w;
		int otherItemB = otherObject->Container()->y + otherObject->Container()->h;

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

	return true;
}

bool SwordAttack::CheckHit( GameObject* otherObject )
{
	//create and check collision on virtual rect
	int thisMiddleX = _pObjectAttachedTo->Container()->x + ( _pObjectAttachedTo->Container()->w / 2 );		
	int thisMiddleY = _pObjectAttachedTo->Container()->y + ( _pObjectAttachedTo->Container()->h / 2 );

	//triganomatry maths
	int attackMiddleX = int ( cos( ( _pObjectAttachedTo->GetDirection() + 0.0 ) * M_PI / 180.0 ) * _Reach );
	int attackMiddleY = int ( sin( ( _pObjectAttachedTo->GetDirection() + 0.0 ) * M_PI / 180.0 ) * _Reach );

	attackMiddleX = attackMiddleX + thisMiddleX;
	attackMiddleY = attackMiddleY + thisMiddleY;

	_pVirtualContainer->x = attackMiddleX - ( _pVirtualContainer->w / 2 );
	_pVirtualContainer->y = attackMiddleY - ( _pVirtualContainer->h / 2 );

	return HasColided( otherObject );
}

void SwordAttack::UseAttack( CombatSystem* combatSystem )
{

	vector<GameObject*>* hitList = combatSystem->GetHitList( this );

	//hit logic
	for( vector<GameObject*>::iterator i = hitList->begin(); i < hitList->end(); i++ )
	{
		//use attack on following items
		( *i )->TakeHit( _Damage );
	}

	MemoryManagement<GameObject>::instance().CleanVector( hitList, false );

	//animation
	_pObjectAttachedTo->SwordAttackAnimation();
}

void SwordAttack::DrawTestRect( MainWnd* window, Camora* camora )
{
	//create and check collision on virtual rect
	int thisMiddleX = _pObjectAttachedTo->Container()->x + ( _pObjectAttachedTo->Container()->w / 2 );		
	int thisMiddleY = _pObjectAttachedTo->Container()->y + ( _pObjectAttachedTo->Container()->h / 2 );

	//triganomatry maths
	int attackMiddleX = int ( cos( ( _pObjectAttachedTo->GetDirection() + 0.0 ) * M_PI / 180.0 ) * _Reach );
	int attackMiddleY = int ( sin( ( _pObjectAttachedTo->GetDirection() + 0.0 ) * M_PI / 180.0 ) * _Reach );

	attackMiddleX = attackMiddleX + thisMiddleX;
	attackMiddleY = attackMiddleY + thisMiddleY;

	_pVirtualContainer->x = attackMiddleX - ( _pVirtualContainer->w / 2 );
	_pVirtualContainer->y = attackMiddleY - ( _pVirtualContainer->h / 2 );

	int dx = _pVirtualContainer->x - camora->GetRect()->x;
	int dy = _pVirtualContainer->y - camora->GetRect()->y;

	if( Initialize::TestMode )
	{
		if( window->GetRenderMode() == MainWnd::SDL_RENDER )
		{
			//only draw if in viewing range
			if( _pVirtualContainer->x + _pVirtualContainer->w  < ( camora->GetRect()->x + camora->GetRect()->w ) && 
					_pVirtualContainer->y + _pVirtualContainer->h < ( camora->GetRect()->y + camora->GetRect()->h ) &&
					( _pVirtualContainer->x ) > camora->GetRect()->x &&
					( _pVirtualContainer->y ) > camora->GetRect()->y )
			{
				Draw_Rect( window->GetSurface(), dx, dy, _pVirtualContainer->w, _pVirtualContainer->h, SDL_MapRGB( window->GetSurface()->format, 0, 246, 255 ) );
			}
		}
	}
}
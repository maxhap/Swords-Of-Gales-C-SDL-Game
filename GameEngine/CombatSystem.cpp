#include "stdafx.h"

CombatSystem::CombatSystem()
{
	_pProjectileHolder = new vector<Projectile*>;
}

CombatSystem::~CombatSystem()
{
	MemoryManagement<Projectile>::instance().CleanVector( _pProjectileHolder, true );
}

void CombatSystem::AddInventorySystem( InventorySystem* inventorySystem )
{
		_InventorySystem = inventorySystem;
}

void CombatSystem::HandleEvent( SDL_Event event )
{
	if( event.type == SDL_KEYUP )
	{
		if( event.key.keysym.sym == SDLK_SPACE )
		{
			ProcessAttack();
		}
	}
}

void CombatSystem::ProcessAttack()
{
	Attack* attack = GameObjectHolder::instance().GetPlayer()->GetActiveAttack();

	if( attack != NULL )
	{
		attack->UseAttack( this );
	}
}

vector<GameObject*>* CombatSystem::GetHitList( Attack* attack )
{
	if( attack != NULL )
	{
		vector<GameObject*>* hitList = new vector<GameObject*>;

		vector<GameSector*>* sectorList = GameObjectHolder::instance().GetSectorsContaining( attack->GetVirtualRect() );

		for( vector<GameSector*>::iterator i = sectorList->begin(); i < sectorList->end(); i++ )
		{
			vector<GameObject*>* objectList = ( *i )->GetAll();
		
			for( vector<GameObject*>::iterator z = objectList->begin(); z < objectList->end(); z++ )
			{
				if( ( *z )->GetIsHittable() == true && attack->CheckHit ( ( *z ) ) == true && ( *z ) != attack->GetObjectAttachedTo() )
				{
					hitList->insert( hitList->end(), 1, ( *z ) );
			
				}
			}
		}

		MemoryManagement<GameSector>::instance().CleanVector( sectorList, false );
		
		return hitList;
	}

	return NULL;		
}

vector<GameObject*>* CombatSystem::GetHitList( Projectile* projectile )
{
	if( projectile != NULL )
	{
		vector<GameObject*>* hitList = new vector<GameObject*>;

		vector<GameSector*>* sectorList = GameObjectHolder::instance().GetSectorsContaining( projectile->Container() );

		for( vector<GameSector*>::iterator i = sectorList->begin(); i < sectorList->end(); i++ )
		{
			vector<GameObject*>* objectList = ( *i )->GetAll();
		
			for( vector<GameObject*>::iterator z = objectList->begin(); z < objectList->end(); z++ )
			{
				if( ( *z )->GetIsHittable() == true && projectile->HasColidedRect( ( *z )->Container() ) == true )
				{
					hitList->insert( hitList->end(), 1, ( *z ) );
			
				}
			}
		}

		MemoryManagement<GameSector>::instance().CleanVector( sectorList, false );
		
		return hitList;
	}

	return NULL;		
}


void CombatSystem::DrawTestAreas( MainWnd* window, Camora* camora )
{
	Attack* attack = GameObjectHolder::instance().GetPlayer()->GetActiveAttack();

	if ( attack != NULL )
	{
		attack->DrawTestRect( window, camora );
	}
}

void CombatSystem::CreateArrow( Attack* attack )
{
	//factory to create arrow
	Arrow* arrow = GameObjectFactory::instance().GetArrow( attack->GetDamage(), attack->GetObjectAttachedTo()->GetDirection(), attack->GetObjectAttachedTo() );

	SDL_Rect* objectPosition = attack->GetObjectAttachedTo()->Container();

	int attackMiddleX = objectPosition->x + ( objectPosition->w / 2 );		
	int attackMiddleY = objectPosition->y + ( objectPosition->h / 2 );

	//triganomatry maths
	int arrowMiddleX = int ( cos( ( attack->GetObjectAttachedTo()->GetDirection() + 0.0 ) * M_PI / 180.0 ) * 50 ) + attackMiddleX;
	int arrowMiddleY = int ( sin( ( attack->GetObjectAttachedTo()->GetDirection() + 0.0 ) * M_PI / 180.0 ) * 50 ) + attackMiddleY;

	int x = arrowMiddleX - ( arrow->Container()->w / 2 );
	int y = attackMiddleY - ( arrow->Container()->h / 2 );

	arrow->SetAbsolutePosition( x, y );

	_pProjectileHolder->insert( _pProjectileHolder->end(), 1, arrow );
}

void CombatSystem::Update()
{
	EventManager::instance().OnIdle();
	UpdateProjectiles();
}

void CombatSystem::UpdateProjectiles()
{

	vector<Projectile*>* removeList = new vector<Projectile*>;

	for( vector<Projectile*>::iterator i = _pProjectileHolder->begin(); i < _pProjectileHolder->end(); i++ )
	{
		( *i )->Update( true );

		//logic for colision and damage and deletion

		vector<GameObject*>* hitList = GetHitList( ( *i ) ); 
		bool hasHit = false;

		for( vector<GameObject*>::iterator z = hitList->begin(); z < hitList->end(); z++ )
		{
			if( ( *z ) != ( *i )->GetObjectAttachedTo() )
			{
				( *z )->TakeHit( ( *i )->GetDamage() );
				hasHit = true;
			}
		}

		if( ( *i )->TimeToDestroy() || hasHit )
		{
			removeList->insert( removeList->end(), 1, ( *i ) );
		}

		MemoryManagement<GameObject>::instance().CleanVector( hitList, false );
	}

	//clean up
	for( std::vector<Projectile*>::iterator i = removeList->begin(); i < removeList->end(); i++ )
	{
		for( std::vector<Projectile*>::iterator z = _pProjectileHolder->begin(); z < _pProjectileHolder->end(); z++ )
		{
			if( ( *i ) == ( *z ))
			{
				delete ( *z );
				_pProjectileHolder->erase( z );
				break;
			}
		}
	}

	MemoryManagement<Projectile>::instance().CleanVector(removeList, false );
}

void CombatSystem::DrawProjectiles( MainWnd* window, Camora* camora )
{
	for( vector<Projectile*>::iterator i = _pProjectileHolder->begin(); i < _pProjectileHolder->end(); i++ )
	{
		( *i )->Draw( window, camora );

		if( Initialize::TestMode )
		{
			( *i )->DrawTestRect( window, camora );
		}
	}
}

void CombatSystem::ProcessAttackOnPlayer( Attack* attack )
{
	Character* player = GameObjectHolder::instance().GetPlayer();
	
	if( attack->CheckHit( player ) )
	{
		player->TakeHit( attack->GetDamage() );
	}
}
#include "stdafx.h"

GameSector::GameSector( int x, int y, int width, int height )
{
	_pContainer = new SDL_Rect();

	_pContainer->x = x;
	_pContainer->y = y;
	_pContainer->w = width;
	_pContainer->h = height;

	_pObjectEntityList = new vector<GameObject*>;
	_pObjectBlockerList = new vector<GameObject*>;
	_pObjectListAll = new vector<GameObject*>;
}

GameSector::~GameSector()
{
	//already cleared by holder
	delete _pObjectEntityList;
	delete _pObjectBlockerList;
	delete _pObjectListAll;
}

void GameSector::Add( GameObject* object )
{
	_pObjectListAll->insert( _pObjectListAll->end(), 1 , object );

	int type = object->GetEntityType();

	if ( type == Initialize::Blocker )
	{
		_pObjectBlockerList->insert( _pObjectBlockerList->end(), 1 , object );
	}
	else if ( type == Initialize::Entity )
	{
		_pObjectEntityList->insert( _pObjectEntityList->end(), 1 , object );
	}
}

void GameSector::Remove( GameObject* object )
{
	bool removed = false;

	for( vector<GameObject*>::iterator i = _pObjectListAll->begin(); i < _pObjectListAll->end(); i++ )
	{
		if( ( *i ) == object )
		{
			_pObjectListAll->erase( i );
			break;
		}
	}

	for( vector<GameObject*>::iterator i = _pObjectEntityList->begin(); i < _pObjectEntityList->end(); i++ )
	{
		if( ( *i ) == object )
		{
			removed = true;
			_pObjectEntityList->erase( i );
			break;
		}
	}

	if( !removed ) 
	{
		for( vector<GameObject*>::iterator i = _pObjectBlockerList ->begin(); i < _pObjectBlockerList->end(); i++ )
		{
			if( ( *i ) == object )
			{
				removed = true;
				_pObjectBlockerList->erase( i );
				break;
			}
		}
	}
}

void GameSector::Delete( GameObject* object )
{
	bool removed = false;
	GameObject* tmp = NULL;

	for( vector<GameObject*>::iterator i = _pObjectListAll->begin(); i < _pObjectListAll->end(); i++ )
	{
		if( ( *i ) == object )
		{
			_pObjectEntityList->erase( i );
			tmp = ( *i );
			break;
		}
	}

	for( vector<GameObject*>::iterator i = _pObjectEntityList->begin(); i < _pObjectEntityList->end(); i++ )
	{
		if( ( *i ) == object )
		{
			removed = true;
			_pObjectEntityList->erase( i );
			break;
		}
	}

	if( !removed ) 
	{
		for( vector<GameObject*>::iterator i = _pObjectBlockerList ->begin(); i < _pObjectBlockerList->end(); i++ )
		{
			if( ( *i ) == object )
			{
				removed = true;
				_pObjectEntityList->erase( i );
				break;
			}
		}
	}

	if( tmp != NULL )
	{
		delete tmp;
	}
}

vector<GameObject*>* GameSector::GetAll()
{
	return _pObjectListAll;
}

vector<GameObject*>* GameSector::GetBlockers()
{
	return _pObjectBlockerList;
}

vector<GameObject*>* GameSector::GetEntities()
{
	return _pObjectEntityList;
}

bool GameSector::CheckSectorCollision( SDL_Rect* otherRect )
{
	int thisItemL = _pContainer->x;
	int thisItemT = _pContainer->y;
	int thisItemR = _pContainer->x + _pContainer->w;
	int thisItemB = _pContainer->y + _pContainer->h;

	//detect from other game item
	if( otherRect != NULL )
	{
		int otherItemL = otherRect->x;
		int otherItemT = otherRect->y;
		int otherItemR = otherRect->x + otherRect->w;
		int otherItemB = otherRect->y + otherRect->h;

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

GameObject* GameSector::CheckObjectCollision( GameObject* otherObject )
{
	for( vector<GameObject*>::iterator i = _pObjectEntityList->begin(); i < _pObjectEntityList->end(); i++ )
	{
		if( ( *i )->HasColided( otherObject ) )
		{
			return ( *i );
		}
	}

	return NULL;
}

bool GameSector::ObjectIsContained( GameObject* object )
{
	for( vector<GameObject*>::iterator i = _pObjectEntityList->begin(); i < _pObjectEntityList->end(); i++ )
	{
		if( ( *i ) == object )
		{
			return true;
		}
	}

	return false;
}

#ifndef _GAMESECTOR_
#define _GAMESECTOR_

#include "stdafx.h"
#include "MemoryManagement.h"

class GameObject;

class GameSector
{

public:

	GameSector( int x, int y, int width, int height );
	~GameSector();

	void Add( GameObject* object );
	void Remove( GameObject* object );
	void Delete( GameObject* object );

	bool CheckSectorCollision( SDL_Rect* otherRect );
	bool ObjectIsContained( GameObject* object );
	GameObject* CheckObjectCollision( GameObject* otherObject );

	vector<GameObject*>* GetAll();
	vector<GameObject*>* GetBlockers();
	vector<GameObject*>* GetEntities();

private:

	SDL_Rect* _pContainer;

	vector<GameObject*>* _pObjectEntityList;
	vector<GameObject*>* _pObjectBlockerList;
	vector<GameObject*>* _pObjectListAll;

};

#endif
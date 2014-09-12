#ifndef _LEVEL_
#define _LEVEL_

#include "stdafx.h"
#include "Shop.h"

class GameObjectHolder;

class Level
{
public:

	Level( string levelfile );
	~Level();

	bool LoadProperties();
	bool LoadTiles();
	bool LoadEnemies();
	bool LoadObjects();
	bool NextLevel();
	bool LoadShop();
	bool LoadAsStartScreen();

	void PaintBackground( MainWnd* window, SDL_Rect* camora );

	SDL_Rect* GetContainer() const;
	SDL_Rect* GetTileDimentions() const;

	Shop* GetShop();

private:

	SDL_Rect* _pContainer;
	SDL_Rect* _pTileDimentions;
	GraphicsTexture* _pBackground;
	
	string _LevelFile;
	string _BackgroundFileLocation;
	string _BlockTileTestImageLocation;
	string _TileTestImageLocation;

	string _levelID;
	int _TotalTiles;

	bool _ShopLevel;

	Shop* _pShop; 

};


#endif
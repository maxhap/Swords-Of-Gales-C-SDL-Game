#ifndef _TILE_
#define _TILE_

#include "stdafx.h"

class Tile : public GameObject
{
public:

	Tile( int objectType, int number, int x, int y, int width, int height, int tileType, string spriteLocation );
	~Tile();
	int GetType() const;

private:

	int _TileType;
	int _TileNumber;
};

#endif
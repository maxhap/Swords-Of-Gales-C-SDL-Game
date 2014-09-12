#include "stdafx.h"

Camora::Camora( int x, int y, int width, int height )
{
	_pRect = new SDL_Rect();
	_pVirtRect = new SDL_Rect();

	_pRect->x = x;
	_pRect->y = y;
	_pRect->w = width;
	_pRect->h = height;
}

Camora::~Camora()
{
	delete _pRect;
	delete _pVirtRect;
}

void Camora::Update(int x, int y)
{
	_pRect->x = x;
	_pRect->y = y;
}

SDL_Rect* Camora::GetRect() const
{
	return _pRect;
}
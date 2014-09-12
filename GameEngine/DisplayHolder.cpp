#include "stdafx.h"

DisplayHolder::DisplayHolder( int x, int y, int width, int height, string backgroundImageLocation )
{
	_pDisplayContainer = new SDL_Rect();
	_pDisplayContainer->x = x;
	_pDisplayContainer->y = y;
	_pDisplayContainer->w = width;
	_pDisplayContainer->h = height;

	_DisplayBackgroundImageLocation = backgroundImageLocation; 
	_pDisplaySurface = NULL;
	_pDisplaySurfaceActive = NULL;

}

DisplayHolder::~DisplayHolder()
{
	delete _pDisplayContainer;
	delete _pDisplaySurface;
	delete _pDisplaySurfaceActive;
}

bool DisplayHolder::LoadDisplayImage()
{
	_pDisplaySurface = ImageLoader::instance().Load( _DisplayBackgroundImageLocation );

	if( _pDisplaySurface == NULL )
	{
		return false;
	}

	return true;
}

void DisplayHolder::DrawDisplay( MainWnd* window )
{
	if( _pDisplaySurface != NULL && _DisplayBackgroundImageLocation != "" )
	{
		//image in viewing space, blot without problem
		window->RenderToScreen( _pDisplaySurface, _pDisplayContainer, NULL );		
	}
}


SDL_Rect* DisplayHolder::GetContainer() const
{
	return _pDisplayContainer;
}


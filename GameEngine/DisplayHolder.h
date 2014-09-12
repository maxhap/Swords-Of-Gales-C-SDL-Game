#ifndef _DISPLAYHOLDER_
#define _DISPLAYHOLDER_

#include "stdafx.h"

class DisplayHolder
{

public:

	DisplayHolder( int x, int y, int width, int height, string backgroundImageLocation );
	~DisplayHolder();

	SDL_Rect* GetContainer() const;

	bool LoadDisplayImage();
	virtual void DrawDisplay( MainWnd* window );

protected:
	
	SDL_Rect* _pDisplayContainer;
	GraphicsTexture* _pDisplaySurface;
	GraphicsTexture* _pDisplaySurfaceActive;

	string _DisplayBackgroundImageLocation;

};

#endif
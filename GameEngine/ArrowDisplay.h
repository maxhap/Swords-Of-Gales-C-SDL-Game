#ifndef _ARROWDISPLAY_
#define _ARROWDISPLAY_

#include "DisplayHolder.h"
#include"stdafx.h"

class ArrowDisplay : public DisplayHolder
{

public:

	ArrowDisplay( int x, int y, int width, int height, string backgroundImageLocation );
	~ArrowDisplay();

	void DrawDisplay( MainWnd* window );

private:

	TTF_Font* _Font;
	SDL_Color* _TextColor;
	GraphicsTexture* _Text;

};

#endif

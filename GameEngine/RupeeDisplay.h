#ifndef _RupeeDISPLAY_
#define _RupeeDISPLAY_

#include"stdafx.h"

class RupeeDisplay : public DisplayHolder
{

public:

	RupeeDisplay( int x, int y, int width, int height, string backgroundImageLocation );
	~RupeeDisplay();

	void DrawDisplay( MainWnd* window );

private:

	TTF_Font* _Font;
	SDL_Color* _TextColor;
	GraphicsTexture* _Text;

};

#endif

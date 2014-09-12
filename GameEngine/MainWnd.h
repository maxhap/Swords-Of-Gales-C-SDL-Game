#include "stdafx.h"

#ifndef _MAINWND_
#define _MAINWND_

class MainWnd
{
public:

	static const int SDL_RENDER = 0;
	static const int OPENGL_RENDER = 1;

	MainWnd();
	~MainWnd();

	bool IsInitialize() const;
	bool RefreshSurface();
	bool Init();
	bool InitGL();
	bool CleanUp();
	
	void FillSurface();

	void RenderToScreen( GraphicsTexture* graphic, SDL_Rect* position, SDL_Rect* clipping  );

	void ClearScreen();
	void SetRenderMode( int mode );

	int GetRenderMode();

	SDL_Surface* GetSurface();



private:

	int _RenderMode;
	
	bool _initializedOK;
	bool _cleanOK;
	
	SDL_Surface* _pScreen;

	float GetClippingPercentage( int inner, int outer );

	void Render( GraphicsTexture* graphic, SDL_Rect* position, SDL_Rect* clipping );
	void Blit( int x, int y, SDL_Surface* source, SDL_Rect* clip );
};

#endif
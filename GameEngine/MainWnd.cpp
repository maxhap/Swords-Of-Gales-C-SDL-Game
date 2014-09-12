#include "stdafx.h"


//surface
using namespace std;

MainWnd::MainWnd()
{
}

MainWnd::~MainWnd()
{
}

bool MainWnd::RefreshSurface()
{
	//Update the _pScreen
	if( _RenderMode == SDL_RENDER )
	{
		if( SDL_Flip( _pScreen ) == -1 )
		{
			return false;    
		}
	}
	else
	{
		SDL_GL_SwapBuffers();
	}

	return true;
}

bool MainWnd::Init()
{
	_initializedOK = false;

	//initialise everthing
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		return _initializedOK;
	}
	//set up the _pScreen 
	if( _RenderMode == SDL_RENDER )
	{																															//SDL_HWSURFACE    SDL_FULLSCREEN
		_pScreen = SDL_SetVideoMode( Initialize::SCREEN_WIDTH, Initialize::SCREEN_HEIGHT, Initialize::SCREEN_BPP, SDL_DOUBLEBUF|SDL_HWSURFACE );
	}
	else
	{
		_pScreen = SDL_SetVideoMode( Initialize::SCREEN_WIDTH, Initialize::SCREEN_HEIGHT, Initialize::SCREEN_BPP, SDL_OPENGL );
	}
	
	if( _pScreen == NULL )
	{
		return false;
	}

	if( _RenderMode == OPENGL_RENDER )
	{
		//Initialize OpenGL
		if( InitGL() == false )
		{
			return false;
		}
	}

	//Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;    
    }

	ClearScreen();

	_initializedOK = true;

	return _initializedOK;
}

bool MainWnd::IsInitialize() const
{
	return _initializedOK;
}

bool MainWnd::InitGL()
{
    //Set clear color
    glClearColor( 0, 0, 0, 0 );
	glViewport( 0, 0, Initialize::SCREEN_WIDTH, Initialize::SCREEN_HEIGHT );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    //Set projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
	glOrtho( 0, Initialize::SCREEN_WIDTH, Initialize::SCREEN_HEIGHT, 0, -1, 1 );

	glEnable( GL_BLEND );
	glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );

    glDisable( GL_LIGHTING );
	glDisable( GL_DEPTH_TEST );

    //Initialize modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
	
    //If there was any errors
    if( glGetError() != GL_NO_ERROR )
    {
		ErrorSystem::instance().WriteError( "MainWnd GL load Fail" );
        return false;
    }

    //If everything initialized
    return true;
}

bool MainWnd::CleanUp()
{
	//free the _pScreen sufrace
	if( _pScreen != NULL )
	{
		SDL_FreeSurface( _pScreen );
	}
	
	//quit sql
	SDL_Quit();

	return true;
}

SDL_Surface* MainWnd::GetSurface()
{
	return _pScreen;
}

void MainWnd::ClearScreen()
{
	if( _RenderMode == SDL_RENDER )
	{
		SDL_FillRect( _pScreen, &_pScreen->clip_rect, SDL_MapRGB( _pScreen->format,000, 000, 000 ) );
	}
	else
	{
		glClear( GL_COLOR_BUFFER_BIT );
	}
}

void MainWnd::SetRenderMode( int mode )
{
	_RenderMode = mode;
	ImageLoader::instance().SetLoadMode( mode );
}

int MainWnd::GetRenderMode()
{
	return _RenderMode;
}

void MainWnd::RenderToScreen( GraphicsTexture* graphic, SDL_Rect* position, SDL_Rect* clipping  )
{
	if( _RenderMode == SDL_RENDER )
	{
		Blit( position->x, position->y, graphic->GetSDLSurface(), clipping );
	}
	else
	{
		bool deleteFlag = false;

		if( clipping == NULL )
		{
			deleteFlag = true;

			clipping = new SDL_Rect();
			clipping->x = 0;
			clipping->y = 0;
			clipping->w = position->w;
			clipping->h = position->h;
		}

		Render( graphic, position, clipping );

		if( deleteFlag )
		{
			delete clipping;
		}
	}
}

void MainWnd::Blit( int x, int y, SDL_Surface* source, SDL_Rect* clip = NULL )
{
	//hold offsets
	SDL_Rect offset;

	//get offsets
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface( source, clip, _pScreen, &offset );
}

void MainWnd::Render( GraphicsTexture* graphic, SDL_Rect* position, SDL_Rect* clipping )
{
	// Enable 2D rendering
    glColor4ub( 255,255,255,255 );

	glEnable( GL_TEXTURE_2D );
    
	glBindTexture( GL_TEXTURE_2D, graphic->GetTexture() );

	glTranslatef( position->x, position->y, 0 );

	float x = 0;
	float y = 0;

    glBegin( GL_QUADS ); 
		
		x = GetClippingPercentage( clipping->x , graphic->_TextureDimentions.width );
		y = GetClippingPercentage( clipping->y, graphic->_TextureDimentions.height );

		glTexCoord2f( x, y );
		glVertex3f( 0.0f, 0.0f, 0.0f );//top left
	
		x = GetClippingPercentage( ( clipping->x + clipping->w ), graphic->_TextureDimentions.width );
		y = GetClippingPercentage( clipping->y, graphic->_TextureDimentions.height );

		glTexCoord2f( x, y );		
		glVertex3f( ( clipping->w ), 0.0f, 0.0f );//top right
			
		x = GetClippingPercentage( clipping->x  + clipping->w, graphic->_TextureDimentions.width );
		y = GetClippingPercentage( ( clipping->y + clipping->h ), ( graphic->_TextureDimentions.height + 0.0 ) );

		glTexCoord2f( x, y );		
		glVertex3f( ( clipping->w ), ( clipping->h ), 0.0f );//bottom right

		x = GetClippingPercentage( clipping->x, graphic->_TextureDimentions.width );
		y = GetClippingPercentage( clipping->y + clipping->h, graphic->_TextureDimentions.height );

		glTexCoord2f( x, y );		
		glVertex3f( 0.0f, ( clipping->h + 0.0f ), 0.0f );//bottom left

	glEnd(); 
	
	glDisable( GL_TEXTURE_2D );	

	glDisable( GL_BLEND );

	//Reset
    glLoadIdentity();
}

float MainWnd::GetClippingPercentage( int inner, int outer )
{
	float value = ( float ) ( inner ) / ( float ) ( outer + 0.0 );
	return value;
}
#include "stdafx.h"

RupeeDisplay::RupeeDisplay( int x, int y, int width, int height, string backgroundImageLocation ) : DisplayHolder( x, y, width, height, backgroundImageLocation )
{	
	_Text = new GraphicsTexture( NULL, width, height, width, height );

	_TextColor = new SDL_Color();
	_TextColor->b = 255;
	_TextColor->g = 255;
	_TextColor->r = 255;
}

RupeeDisplay::~RupeeDisplay()
{	
	delete _TextColor;
	delete _Text;
}

void RupeeDisplay::DrawDisplay( MainWnd* window )
{
	if( window->GetRenderMode() == MainWnd::SDL_RENDER )
	{
		_Font = TTF_OpenFont( "Fonts\\acmesai.TTF", 16 );

		if( _Font != NULL )
		{

			int amount = GameObjectHolder::instance().GetPlayer()->GetRupeeAmount();
			string sAmount;

			stringstream out;
			out << amount;
	
			sAmount = out.str();

			//Render the text
			_Text->SetSDLSurface( TTF_RenderText_Solid( _Font, sAmount.c_str(), *_TextColor ) );

			if( _pDisplaySurface != NULL && _DisplayBackgroundImageLocation != "" )
			{
				window->RenderToScreen( _pDisplaySurface, _pDisplayContainer, NULL ); 

				if( _Text != NULL )
				{
					SDL_Rect* textRect = new SDL_Rect();
					textRect->x = _pDisplayContainer->x + 10;
					textRect->y = _pDisplayContainer->y + 20;

					window->RenderToScreen( _Text, textRect, NULL ); 

					delete textRect;
				}
			}
		}

		TTF_CloseFont( _Font );
	}
}

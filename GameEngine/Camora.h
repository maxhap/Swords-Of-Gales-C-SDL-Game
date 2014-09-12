#ifndef _CAMORA_
#define _CAMORA_

class Camora
{
public:

	Camora( int x, int y, int width, int height );
	~Camora();

	SDL_Rect* GetRect() const;
	void Update( int x, int y );

private:

	SDL_Rect* _pRect;
	SDL_Rect* _pVirtRect;

};



#endif
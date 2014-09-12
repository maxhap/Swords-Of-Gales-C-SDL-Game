#ifndef _OBJECT_
#define _OBJECT_

#include "stdafx.h"

class GameObject;

class Object
{

public:

	int const static NOMARK = 0;
	int const static COLIDEDMARK = 1;
	int const static DRAWMARK = 2;
	
	Object( int objectID, int x, int y, int width, int height, string spriteLocation );
	~Object();

	SDL_Rect* Container() const;
	SDL_Rect* CollisionBox() const;
	
	void SetAbsolutePosition( int x, int y );
	void SetMovingOnThickTorain( bool thick );
	void SetDrawMark( int set );
	void SetAlwaysDrawBefore( bool val );

	virtual void Draw( MainWnd* window, Camora* camora );

	virtual bool HasColided( GameObject* otherItem );
	virtual bool HasColidedRect( SDL_Rect* otherItemRect );
	
	bool LoadItemImage();
	bool CheckIsAbove( SDL_Rect* otherItemRect );
	bool GetAlwaysDrawBefore();

	int GetDrawMark();
	int GetID();

protected:

	vector< vector<Point> >* _SpriteMap;

	int _CurrentSpritePossitionX;
	int _CurrentSpritePossitionY;
	int _ObjectID;
	int _ObjectType;
	int _DrawAfterMark;

	bool _WalkingOnThickTorrain;
	bool _AlwaysDrawBefore;

	string _ObjectSpriteLocation;

	SDL_Rect* _Container;
	SDL_Rect* _pCollisionBox;
	SDL_Rect* _pSpriteClip;
	
	GraphicsTexture* _pSprite;

	virtual void BuildSpriteMap();
};

#endif
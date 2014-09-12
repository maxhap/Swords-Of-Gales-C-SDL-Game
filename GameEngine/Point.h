#ifndef _POINT_
#define _POINT_

#include "stdafx.h"

class Point
{

public :

	Point( int x, int y, int width, int height );
	~Point();
	
	int X;
	int Y;
	int Width;
	int Height;

private:

};

#endif
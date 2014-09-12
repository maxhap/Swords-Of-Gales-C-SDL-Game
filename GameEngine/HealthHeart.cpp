#include "stdafx.h"

HealthHeart::HealthHeart( int x, int y, int width, int height, string backgroundImageLocation  ) : DisplayHolder( x, y, width, height, backgroundImageLocation )
{

}

HealthHeart::~HealthHeart()
{

}

void HealthHeart::SetPosition( int x, int y )
{
	_pDisplayContainer->x = x;
	_pDisplayContainer->y = y;
}
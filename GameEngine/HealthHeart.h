#ifndef _HEALTHHEART_
#define _HEALTHHEART_

#include "stdafx.h"

class HealthHeart : public DisplayHolder
{

public:

	HealthHeart( int x, int y, int width, int height, string backgroundImageLocation  );
	~HealthHeart();

	void SetPosition( int x, int y );

private:

};

#endif
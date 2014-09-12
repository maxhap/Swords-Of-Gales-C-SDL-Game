#ifndef _ENTRYPOINT_
#define _ENTRYPOINT_

#include "stdafx.h"

class EntryPoint
{

public:

	EntryPoint( string entryPointID, int x, int y );
	~EntryPoint();

	Point* GetEntryLocation() const;
	string GetEntryPointID();

private:

	string _EntryPointID; 
	Point* _EntryLocation;

};

#endif
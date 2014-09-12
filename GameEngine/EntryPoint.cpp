#include "stdafx.h"

EntryPoint::EntryPoint( string entryPointID, int x, int y )
{
	_EntryPointID = entryPointID;
	_EntryLocation = new Point( x, y, 0, 0 );
}

EntryPoint::~EntryPoint()
{
	delete _EntryLocation;
}

Point* EntryPoint::GetEntryLocation() const
{
	return _EntryLocation;
}

string EntryPoint::GetEntryPointID()
{
	return _EntryPointID;
}




	
	
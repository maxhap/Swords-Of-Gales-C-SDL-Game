#ifndef _EXITPOINT_
#define _EXITPOINT_

#include "stdafx.h"

class ExitPoint
{

public:

	ExitPoint( string forwardLevel, string entryPointID );
	~ExitPoint();

	string GetForwardLevel() const;

	string GetEntryPointID();

public:

	string _ForwardLevel;
	string _EntryPointID;

	void Activate();

};

#endif



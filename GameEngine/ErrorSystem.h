#ifndef _ERRORSYSTEM_
#define _ERRORSYSTEM_

#include "stdafx.h"

class ErrorSystem : public Singleton<ErrorSystem>
{

public:

	~ErrorSystem();

	void WriteError( string text );
	void WriteEvent( string text );
	void WriteObjectError( int objectID, string text );

private:

	friend Singleton<ErrorSystem>;
	ErrorSystem();

	string _ErrorLogLocation;
	string _EventLogLocation;

	void RecreateFiles();


};


#endif
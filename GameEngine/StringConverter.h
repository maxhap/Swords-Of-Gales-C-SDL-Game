#ifndef _STRINGCONVERTER_
#define _STRINGCONVERTER_

#include "stdafx.h"

using namespace std;

class StringConverter
{

public:

	StringConverter();
	~StringConverter();

	static int StringToInt( string sValue, string errorCode );

private:

};

#endif
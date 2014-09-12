#include "stdafx.h"

int StringConverter::StringToInt( string sValue, string errorCode )
{
	int newInt = -1;
	
	newInt = atoi( sValue.c_str() );

	return newInt;
}
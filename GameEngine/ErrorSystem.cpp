#include "stdafx.h"

ErrorSystem::ErrorSystem()
{
	_ErrorLogLocation = Initialize::ErrorLogLocation;
	_EventLogLocation = Initialize::EventLogLocation;

	RecreateFiles();
}

ErrorSystem::~ErrorSystem()
{

}

void ErrorSystem::WriteError( string text )
{
	ofstream file;
	file.open( _ErrorLogLocation, fstream::in | fstream::out | fstream::app );

	if ( file.is_open() )
	{
		file << "\n";
		file << "------------------------------------------------------------------------------------------------";
		file << "\n" << text << "\n";
		file << "------------------------------------------------------------------------------------------------";
		file.close();
	}
	else
	{
		cout << "Unable to open error file";
	}

}

void ErrorSystem::WriteEvent( string text )
{
	ofstream file;
	file.open( _EventLogLocation, fstream::in | fstream::out | fstream::app );
	
	if ( file.is_open() )
	{
		file << "\n";
		file << "------------------------------------------------------------------------------------------------";
		file << "\n" << text << "\n";
		file << "------------------------------------------------------------------------------------------------";
		file.close();
	}
	else
	{
		cout << "Unable to open event file";
	}
}

void ErrorSystem::WriteObjectError( int objectID, string text )
{
	ofstream file;
	file.open( _EventLogLocation, fstream::in | fstream::out | fstream::app );
	
	if ( file.is_open() )
	{
		stringstream number;
		number << objectID;

		file << "\n";
		file << "------------------------------------------------------------------------------------------------";
		file << "\n ObjectID - " << objectID << "\n";
		file << "\n Error - " << text << "\n";
		file << "------------------------------------------------------------------------------------------------";
		file.close();
	}
	else
	{
		cout << "Unable to open event file";
	}
}

void ErrorSystem::RecreateFiles()
{
	if( remove( _ErrorLogLocation.c_str() ) != 0 )
	{
		cout << "Error deleting file";
	}

	if( remove( _EventLogLocation.c_str() ) != 0 )
	{
		cout << "Error deleting file";
	}
}
#include "stdafx.h"

ExitPoint::ExitPoint( string forwardLevel, string entryPointID )
{
	_ForwardLevel = forwardLevel;
	_EntryPointID = entryPointID;
}

ExitPoint::~ExitPoint()
{
}

string ExitPoint::GetForwardLevel() const
{
	return _ForwardLevel;
}

string ExitPoint::GetEntryPointID()
{
	return _EntryPointID;
}

void ExitPoint::Activate()
{
	LevelSystem::instance().SetNextLevelFileLocation( _ForwardLevel );
	LevelSystem::instance().SetNextLevelEntryPointID( _EntryPointID );

	LevelSystem::instance().SetLevelToSwitch( true );
}
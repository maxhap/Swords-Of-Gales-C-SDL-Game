#ifndef _MemoryManagement_
#define _MemoryManagement_

#include "stdafx.h"
#include "GameObjectHolder.h"
#include "TileObjectHolder.h"

template<class T> class MemoryManagement
{
	MemoryManagement( const MemoryManagement& );
	MemoryManagement& operator=( const MemoryManagement& );

public:

	static MemoryManagement& instance()
	{
		static MemoryManagement instance;
		return instance;
	}

	void CleanVector( vector<T*>* vectorList, bool deleteObjects )
	{
	    if( deleteObjects == true )
		{
			for( vector<T*>::iterator i = vectorList->begin(); i < vectorList->end(); i++ )
			{
				delete ( *i );
			}
		}

		vectorList->erase( vectorList->begin(), vectorList->end() );
		
		delete vectorList;
	};

	void EmptyVector( vector<T*>* vectorList, bool deleteObjects )
	{
		if( deleteObjects == true )
		{
			for( vector<T*>::iterator i = vectorList->begin(); i < vectorList->end(); i++ )
			{
				delete ( *i );
			}
		}

		vectorList->erase( vectorList->begin(), vectorList->end() );
	};

	void AddToDumpList( GameObject* object )
	{
		_ObjectDumpList->insert( _ObjectDumpList->end(), 1, object );
	}

	void RemoveDumpListFromGamePlay()
	{
		for( vector<GameObject*>::iterator i = _ObjectDumpList->begin(); i < _ObjectDumpList->end(); i++ )
		{
			GameObjectHolder::instance().RemoveObjectFromReleventSectors( *i );			
		}

	}

	void FlushDumpList()
	{
		for( vector<GameObject*>::iterator i = _ObjectDumpList->begin(); i < _ObjectDumpList->end(); i++ )
		{
			GameObjectHolder::instance().RemoveFromGameContainer( *i );
			delete ( *i );
		}

		_ObjectDumpList->erase( _ObjectDumpList->begin(), _ObjectDumpList->end() );
	};

	

private:

	MemoryManagement() 
	{
		_ObjectDumpList = new vector<GameObject*>;
	};

	~MemoryManagement() 
	{
		FlushDumpList();
		delete _ObjectDumpList;
	};

	vector<GameObject*>* _ObjectDumpList;


};

#endif
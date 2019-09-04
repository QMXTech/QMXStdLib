////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ThreadManager.cpp
// Robert M. Baker | Created : 24FEB16 | Last Modified : 03SEP19 by Robert M. Baker
// Version : 2.1.1
// This is a source file for 'QMXStdLib'; it defines the implementation for a thread manager class.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2011-2019 QuantuMatriX Software, a QuantuMatriX Technologies Cooperative Partnership
//
// This file is part of 'QMXStdLib'.
//
// 'QMXStdLib' is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// 'QMXStdLib' is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with 'QMXStdLib'.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 24FEB16
  * @date    Last Modified : 03SEP19 by Robert M. Baker
  * @version 2.1.1
  *
  * @brief This is a source file for 'QMXStdLib'; it defines the implementation for a thread manager class.
  *
  * @section ThreadManagerS0000 Description
  *
  * This is a source file for 'QMXStdLib'; it defines the implementation for a thread manager class.
  *
  * @section ThreadManagerS0001 License
  *
  * Copyright (C) 2011-2019 QuantuMatriX Software, a QuantuMatriX Technologies Cooperative Partnership
  *
  * This file is part of 'QMXStdLib'.
  *
  * 'QMXStdLib' is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free
  * Software Foundation, either version 3 of the License, or (at your option) any later version.
  *
  * 'QMXStdLib' is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  * A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public License along with 'QMXStdLib'.  If not, see <http://www.gnu.org/licenses/>.
  */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../include/ThreadManager.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Methods for the 'ThreadManager' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ThreadManager::~ThreadManager()
{
	try
	{
		// Perform necessary cleanup.

			if( initialized )
				deallocate();
	}
	catch( const exception& except )
	{
		// Do nothing.
	}
}

void ThreadManager::createGroup( const string& groupID )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ThreadManager::createGroup", 0000 );

	// Create specified group, if it does not already exist.

		QMX_ASSERT(
			groups.insert( GroupMap::value_type( groupID, { ThreadPtrMap(), BarrierPtr() } ) ).second,
			"QMXStdLib",
			"ThreadManager::createGroup",
			"00000017",
			groupID
		);
}

void ThreadManager::destroyGroup( const string& groupID, const bool doDestroyThreads, const bool doInterrupt )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ThreadManager::destroyGroup", 0000 );

	// Create local variables.

		auto groupMapIterator = groups.find( groupID );

	// Destroy specified group, with optional thread destruction/interruption, if it exists.

		QMX_ASSERT(
			( groupMapIterator != groups.end() ),
			"QMXStdLib",
			"ThreadManager::destroyGroup",
			"00000018",
			groupID << ", " << boolalpha << doDestroyThreads << ", " << doInterrupt
		);

		if( doDestroyThreads )
		{
			for( auto& index : groupMapIterator->second.threads )
			{
				if( doInterrupt )
					index.second->interrupt();
				else if( index.second->joinable() )
					index.second->detach();
			}
		}
		else
			QMX_ASSERT(
				groupMapIterator->second.threads.empty(),
				"QMXStdLib",
				"ThreadManager::destroyGroup",
				"00000019",
				groupID << ", " << boolalpha << doDestroyThreads << ", " << doInterrupt
			);

		groups.erase( groupMapIterator );
}

void ThreadManager::getGroupIDs( StringVector& target ) const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Retrieve all group IDs, if any exist.

		for( const auto& index : groups )
			target.push_back( index.first );
}

void ThreadManager::setBarrierSize( const string& groupID, const size_t newSize )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ThreadManager::setBarrierSize", 0000 );

	// Create local variables.

		auto groupMapIterator = groups.find( groupID );

	// Set barrier to specified size for specified group, if it exists.

		QMX_ASSERT( ( groupMapIterator != groups.end() ), "QMXStdLib", "ThreadManager::setBarrierSize", "0000001A", groupID << ", " << newSize );

		if( newSize )
			groupMapIterator->second.groupBarrier = make_shared< Barrier >( newSize );
		else
			groupMapIterator->second.groupBarrier = nullptr;
}

void ThreadManager::destroyThread( const string& groupID, const string& threadID, const bool doInterrupt )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ThreadManager::destroyThread", 0000 );

	// Create local variables.

		auto groupMapIterator = groups.find( groupID );
		ThreadPtrMap::iterator threadPtrMapIterator;

	// Destroy specified thread in specified group, with optional interruption, if both group and thread exist.

		QMX_ASSERT(
			( groupMapIterator != groups.end() ),
			"QMXStdLib",
			"ThreadManager::destroyThread",
			"0000001B",
			groupID << ", " << threadID << ", " << boolalpha << doInterrupt
		);

		threadPtrMapIterator = groupMapIterator->second.threads.find( threadID );

		QMX_ASSERT(
			( threadPtrMapIterator != groupMapIterator->second.threads.end() ),
			"QMXStdLib",
			"ThreadManager::destroyThread",
			"0000001C",
			groupID << ", " << threadID << ", " << boolalpha << doInterrupt
		);

		if( doInterrupt )
			threadPtrMapIterator->second->interrupt();
		else if( threadPtrMapIterator->second->joinable() )
			threadPtrMapIterator->second->detach();

		groupMapIterator->second.threads.erase( threadPtrMapIterator );
}

void ThreadManager::getThreadIDs( const string& groupID, StringVector& target ) const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ThreadManager::getThreadIDs", 0000 );

	// Create local variables.

		const auto groupMapIterator = groups.find( groupID );

	// Retrieve all thread IDs, if any exist.

		QMX_ASSERT( ( groupMapIterator != groups.end() ), "QMXStdLib", "ThreadManager::getThreadIDs", "0000001D", groupID );

		for( const auto& Index : groupMapIterator->second.threads )
			target.push_back( Index.first );
}

void ThreadManager::wait( const string& groupID )
{
	// Create local variables.

		BarrierPtr targetBarrier;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ThreadManager::wait", 0000 );

	// Read Scope
	{
		// Obtain locks.

			SCOPED_READ_LOCK;

		// Create scope variables.

			auto groupMapIterator = groups.find( groupID );

		// Obtain the specified group's thread barrier, if it exists.

			QMX_ASSERT( ( groupMapIterator != groups.end() ), "QMXStdLib", "ThreadManager::wait", "0000001E", groupID );
			targetBarrier = groupMapIterator->second.groupBarrier;
	}

	// Call 'wait' on thread barrier, if valid.

		if( targetBarrier )
			targetBarrier->wait();
}

void ThreadManager::join( const string& groupID, const string& threadID )
{
	// Create local variables.

		ThreadPtr targetThread;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ThreadManager::join", 0000 );

	// Read Scope
	{
		// Obtain locks.

			SCOPED_READ_LOCK;

		// Create local variables.

			auto groupMapIterator = groups.find( groupID );
			ThreadPtrMap::iterator threadPtrMapIterator;

		// Obtain specified thread in specified group, if both group and thread exist.

			QMX_ASSERT( ( groupMapIterator != groups.end() ), "QMXStdLib", "ThreadManager::join", "0000001F", groupID << ", " << threadID );
			threadPtrMapIterator = groupMapIterator->second.threads.find( threadID );

			QMX_ASSERT(
				( threadPtrMapIterator != groupMapIterator->second.threads.end() ),
				"QMXStdLib",
				"ThreadManager::join",
				"00000020",
				groupID << ", " << threadID
			);

			targetThread = threadPtrMapIterator->second;
	}

	// Join thread, if possible.

		if( targetThread->joinable() )
			targetThread->join();
}

void ThreadManager::joinAll( const string& groupID )
{
	// Create local variables.

		ThreadPtrMap targetThreads;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ThreadManager::joinAll", 0000 );

	// Read Scope
	{
		// Obtain locks.

			SCOPED_READ_LOCK;

		// Create local variables.

			auto groupMapIterator = groups.find( groupID );

		// Obtain all spawned threads for specified group, if it exists.

			QMX_ASSERT( ( groupMapIterator != groups.end() ), "QMXStdLib", "ThreadManager::joinAll", "00000021", groupID );
			targetThreads = groupMapIterator->second.threads;
	}

	// Join threads, if possible.

		for( auto& index : targetThreads )
		{
			if( index.second->joinable() )
				index.second->join();
		}
}

void ThreadManager::interrupt( const string& groupID, const string& threadID )
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ThreadManager::interrupt", 0000 );

	// Create local variables.

		auto groupMapIterator = groups.find( groupID );
		ThreadPtrMap::iterator threadPtrMapIterator;

	// Interrupt specified thread in specified group, if both group and thread exist.

		QMX_ASSERT( ( groupMapIterator != groups.end() ), "QMXStdLib", "ThreadManager::interrupt", "00000022", groupID << ", " << threadID );
		threadPtrMapIterator = groupMapIterator->second.threads.find( threadID );

		QMX_ASSERT(
			( threadPtrMapIterator != groupMapIterator->second.threads.end() ),
			"QMXStdLib",
			"ThreadManager::interrupt",
			"00000023",
			groupID << ", " << threadID
		);

		threadPtrMapIterator->second->interrupt();
}

void ThreadManager::interruptAll( const string& groupID )
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ThreadManager::interruptAll", 0000 );

	// Create local variables.

		auto groupMapIterator = groups.find( groupID );

	// Interrupt all spawned threads for specified group, if it exists.

		QMX_ASSERT( ( groupMapIterator != groups.end() ), "QMXStdLib", "ThreadManager::interruptAll", "00000024", groupID );

		for( auto& index : groupMapIterator->second.threads )
			index.second->interrupt();
}

bool ThreadManager::interruptionRequested() const
{
	// Report wether or not a request has been made to interrupt the current thread to calling routine.

		return boost::this_thread::interruption_requested();
}

void ThreadManager::interruptionPoint() const
{
	// Throw an exception if the current thread has been interrupted.

		boost::this_thread::interruption_point();
}

uint32_t ThreadManager::getLogicalCoreCount() const
{
	// Report the number of logical cores available on the current system to calling routine.

		return boost::thread::hardware_concurrency();
}

uint32_t ThreadManager::getPhysicalCoreCount() const
{
	// Report the number of physical cores available on the current system to calling routine.

		return boost::thread::physical_concurrency();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods for the 'ThreadManager' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ThreadManager::ThreadManager()
{
	// Do nothing.
}

void ThreadManager::deallocateImp()
{
	// Perform necessary cleanup.

		if( !groups.empty() )
		{
			for( auto& indexA : groups )
			{
				for( auto& indexB : indexA.second.threads )
				{
					if( indexB.second->joinable() )
						indexB.second->detach();
				}
			}

			groups.clear();
		}
}

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ThreadManager.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

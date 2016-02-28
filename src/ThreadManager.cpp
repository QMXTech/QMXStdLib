////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ThreadManager.cpp
// Robert M. Baker | Created : 24FEB16 | Last Modified : 28FEB16 by Robert M. Baker
// Version : 1.1.2
// This is a source file for 'QMXStdLib'; it defines the implementation for a thread manager class.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2011-2016 QuantuMatriX Software, LLP.
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
  * @date    Last Modified : 28FEB16 by Robert M. Baker
  * @version 1.1.2
  *
  * @brief This is a source file for 'QMXStdLib'; it defines the implementation for a thread manager class.
  *
  * @section Description
  *
  * This is a source file for 'QMXStdLib'; it defines the implementation for a thread manager class.
  *
  * @section License
  *
  * Copyright (C) 2011-2016 QuantuMatriX Software, LLP.
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
// Static Field Initializers for the 'ThreadManager' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<> ThreadManager* Singleton< ThreadManager >::SingletonInstance = nullptr;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Methods for the 'ThreadManager' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ThreadManager::~ThreadManager()
{
	// Perform necessary cleanup.

		if( Initialized )
			Deallocate();
}

void ThreadManager::CreateGroup( const string& GroupID )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ThreadManager::CreateGroup", 0000 );

	// Create specified group, if it does not already exist.

		QMX_ASSERT( Groups.insert( GroupMap::value_type( GroupID, { ThreadPtrMap(), BarrierPtr() } ) ).second,
		            "QMXStdLib",
		            "ThreadManager::CreateGroup",
		            "00000026",
		            GroupID );
}

void ThreadManager::DestroyGroup( const string& GroupID, const bool DoDestroyThreads, const bool DoInterrupt )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ThreadManager::DestroyGroup", 0000 );

	// Create local variables.

		auto GroupMapIterator = Groups.find( GroupID );

	// Destroy specified group, with optional thread destruction/interruption, if it exists.

		QMX_ASSERT( ( GroupMapIterator != Groups.end() ),
		            "QMXStdLib",
		            "ThreadManager::DestroyGroup",
		            "00000027",
		            GroupID << ", " << DoDestroyThreads << ", " << DoInterrupt );

		if( DoDestroyThreads )
		{
			for( auto& Index : GroupMapIterator->second.Threads )
			{
				if( DoInterrupt )
					Index.second->interrupt();
				else if( Index.second->joinable() )
					Index.second->detach();
			}
		}
		else
			QMX_ASSERT( GroupMapIterator->second.Threads.empty(),
			            "QMXStdLib",
			            "ThreadManager::DestroyGroup",
			            "00000028",
			            GroupID << ", " << DoDestroyThreads << ", " << DoInterrupt );

		Groups.erase( GroupMapIterator );
}

void ThreadManager::SetBarrierSize( const string& GroupID, const size_t TargetSize )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ThreadManager::SetBarrierSize", 0000 );

	// Create local variables.

		auto GroupMapIterator = Groups.find( GroupID );

	// Set barrier to specified size for specified group, if it exists.

		QMX_ASSERT( ( GroupMapIterator != Groups.end() ), "QMXStdLib", "ThreadManager::SetBarrierSize", "00000029", GroupID << ", " << TargetSize );

		if( TargetSize )
			GroupMapIterator->second.GroupBarrier = make_shared< Barrier >( TargetSize );
		else
			GroupMapIterator->second.GroupBarrier = nullptr;
}

void ThreadManager::DestroyThread( const string& GroupID, const string& ThreadID, const bool DoInterrupt )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ThreadManager::DestroyThread", 0000 );

	// Create local variables.

		auto GroupMapIterator = Groups.find( GroupID );
		ThreadPtrMap::iterator ThreadPtrMapIterator;

	// Destroy specified thread in specified group, with optional interruption, if both group and thread exist.

		QMX_ASSERT( ( GroupMapIterator != Groups.end() ),
		            "QMXStdLib",
		            "ThreadManager::DestroyThread",
		            "0000002A",
		            GroupID << ", " << ThreadID << ", " << DoInterrupt );
		ThreadPtrMapIterator = GroupMapIterator->second.Threads.find( ThreadID );
		QMX_ASSERT( ( ThreadPtrMapIterator != GroupMapIterator->second.Threads.end() ),
		            "QMXStdLib",
		            "ThreadManager::DestroyThread",
		            "0000002B",
		            GroupID << ", " << ThreadID << ", " << DoInterrupt );

		if( DoInterrupt )
			ThreadPtrMapIterator->second->interrupt();
		else if( ThreadPtrMapIterator->second->joinable() )
			ThreadPtrMapIterator->second->detach();

		GroupMapIterator->second.Threads.erase( ThreadPtrMapIterator );
}

void ThreadManager::Wait( const string& GroupID )
{
	// Create local variables.

		BarrierPtr TargetBarrier;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ThreadManager::Wait", 0000 );

	// Read Scope
	{
		// Obtain locks.

			SCOPED_READ_LOCK;

		// Create scope variables.

			auto GroupMapIterator = Groups.find( GroupID );

		// Obtain the specified group's thread barrier, if it exists.

			QMX_ASSERT( ( GroupMapIterator != Groups.end() ), "QMXStdLib", "ThreadManager::Wait", "0000002C", GroupID );
			TargetBarrier = GroupMapIterator->second.GroupBarrier;
	}

	// Call 'wait' on thread barrier, if valid.

		if( TargetBarrier )
			TargetBarrier->wait();
}

void ThreadManager::Join( const string& GroupID, const string& ThreadID )
{
	// Create local variables.

		ThreadPtr TargetThread;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ThreadManager::Join", 0000 );

	// Read Scope
	{
		// Obtain locks.

			SCOPED_READ_LOCK;

		// Create local variables.

			auto GroupMapIterator = Groups.find( GroupID );
			ThreadPtrMap::iterator ThreadPtrMapIterator;

		// Obtain specified thread in specified group, if both group and thread exist.

			QMX_ASSERT( ( GroupMapIterator != Groups.end() ), "QMXStdLib", "ThreadManager::Join", "0000002D", GroupID << ", " << ThreadID );
			ThreadPtrMapIterator = GroupMapIterator->second.Threads.find( ThreadID );
			QMX_ASSERT( ( ThreadPtrMapIterator != GroupMapIterator->second.Threads.end() ),
		               "QMXStdLib",
		               "ThreadManager::Join",
		               "0000002E",
		               GroupID << ", " << ThreadID );
			TargetThread = ThreadPtrMapIterator->second;
	}

	// Join thread, if possible.

		if( TargetThread->joinable() )
			TargetThread->join();
}

void ThreadManager::JoinAll( const string& GroupID )
{
	// Create local variables.

		ThreadPtrMap TargetThreads;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ThreadManager::JoinAll", 0000 );

	// Read Scope
	{
		// Obtain locks.

			SCOPED_READ_LOCK;

		// Create local variables.

			auto GroupMapIterator = Groups.find( GroupID );

		// Obtain all spawned threads for specified group, if it exists.

			QMX_ASSERT( ( GroupMapIterator != Groups.end() ), "QMXStdLib", "ThreadManager::JoinAll", "0000002F", GroupID );
			TargetThreads = GroupMapIterator->second.Threads;
	}

	// Join threads, if possible.

		for( auto& Index : TargetThreads )
		{
			if( Index.second->joinable() )
				Index.second->join();
		}
}

void ThreadManager::Interrupt( const string& GroupID, const string& ThreadID )
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ThreadManager::Interrupt", 0000 );

	// Create local variables.

		auto GroupMapIterator = Groups.find( GroupID );
		ThreadPtrMap::iterator ThreadPtrMapIterator;

	// Interrupt specified thread in specified group, if both group and thread exist.

		QMX_ASSERT( ( GroupMapIterator != Groups.end() ), "QMXStdLib", "ThreadManager::Interrupt", "00000030", GroupID << ", " << ThreadID );
		ThreadPtrMapIterator = GroupMapIterator->second.Threads.find( ThreadID );
		QMX_ASSERT( ( ThreadPtrMapIterator != GroupMapIterator->second.Threads.end() ),
		            "QMXStdLib",
		            "ThreadManager::Interrupt",
		            "00000031",
		            GroupID << ", " << ThreadID );
		ThreadPtrMapIterator->second->interrupt();
}

void ThreadManager::InterruptAll( const string& GroupID )
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ThreadManager::InterruptAll", 0000 );

	// Create local variables.

		auto GroupMapIterator = Groups.find( GroupID );

	// Interrupt all spawned threads for specified group, if it exists.

		QMX_ASSERT( ( GroupMapIterator != Groups.end() ), "QMXStdLib", "ThreadManager::InterruptAll", "00000032", GroupID );

		for( auto& Index : GroupMapIterator->second.Threads )
			Index.second->interrupt();
}

bool ThreadManager::InterruptionRequested()
{
	// Report wether or not a request has been made to interrupt the current thread to calling routine.

		return boost::this_thread::interruption_requested();
}

void ThreadManager::InterruptionPoint()
{
	// Throw an exception if the current thread has been interrupted.

		boost::this_thread::interruption_point();
}

uint32_t ThreadManager::GetLogicalCoreCount()
{
	// Report the number of logical cores available on the current system to calling routine.

		return boost::thread::hardware_concurrency();
}

uint32_t ThreadManager::GetPhysicalCoreCount()
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

void ThreadManager::DeallocateImp()
{
	// Perform necessary cleanup.

		if( !Groups.empty() )
		{
			for( auto& IndexA : Groups )
			{
				for( auto& IndexB : IndexA.second.Threads )
				{
					if( IndexB.second->joinable() )
						IndexB.second->detach();
				}
			}

			Groups.clear();
		}
}

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ThreadManager.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

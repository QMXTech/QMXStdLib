////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ThreadManager.hpp
// Robert M. Baker | Created : 24FEB16 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.1
// This is a header file for 'QMXStdLib'; it defines the interface for a thread manager class.
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
  * @date    Last Modified : 27FEB16 by Robert M. Baker
  * @version 1.1.1
  *
  * @brief This is a header file for 'QMXStdLib'; it defines the interface for a thread manager class.
  *
  * @section Description
  *
  * This is a header file for 'QMXStdLib'; it defines the interface for a thread manager class.
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

#ifndef __QMX_QMXSTDLIB_THREADMANAGER_HPP_
#define __QMX_QMXSTDLIB_THREADMANAGER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "Object.hpp"
#include "Mixins/Singleton.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define THREAD_MANAGER                QMXStdLib::ThreadManager::GetSingleton()
#define THREAD_MANAGER_P              QMXStdLib::ThreadManager::GetSingletonPointer()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'ThreadManager' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class ThreadManager ThreadManager.hpp "include/ThreadManager.hpp"
  *
  * @brief This class defines thread management algorithms.
  *
  * These algorithms are useful when it is necessary to spawn and manage groups of threads.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Yes
  */

class ThreadManager : public Object< ThreadManager >, public Singleton< ThreadManager >
{
public:

	// Public Data Types

		/**
		  * @brief This structure stores a group's data.
		  */

		struct Group
		{
		public:

			// Public Fields

				/**
				  * @brief This is the group's map of thread pointers.
				  */

				ThreadPtrMap Threads;

				/**
				  * @brief This is the group's barrier used for execution synchronization.
				  */

				BarrierPtr GroupBarrier;
		};

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		virtual ~ThreadManager();

	// Public Methods

		/**
		  * @brief This method creates a new thread group, if it does not already exist.
		  *
		  * @param GroupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @exception QMXException
		  * 	If the specified thread group already exists.
		  */

		void CreateGroup( const std::string& GroupID );

		/**
		  * @brief This method destroys a thread group, with optional thread destruction/interruption, if it exists.
		  *
		  * @param GroupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @param DoDestroyThreads
		  * 	This is a boolean value which determines if a non-empty group should have its threads destroyed.
		  *
		  * @param DoInterrupt
		  * 	This is a boolean value which determines if destroyed threads are interrupted or detached.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does not exist.<br>
		  * 	If the specified thread group was not empty and 'DoDestroyThreads' was set to 'false'.
		  */

		void DestroyGroup( const std::string& GroupID, const bool DoDestroyThreads = false, const bool DoInterrupt = true );

		/**
		  * @brief This method sets the barrier size for the specified group, if it exists.
		  *
		  * This method should be called on a group to set its barrier size before any calls to 'Wait' are made; otherwise, the program could end up in a locked
		  * state.
		  *
		  * @param GroupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @param TargetSize
		  * 	This is the new barrier size to use.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does not exist.
		  */

		void SetBarrierSize( const std::string& GroupID, const size_t TargetSize );

		/**
		  * @brief This method destroys a thread in the specified group, with optional interruption, if both group and thread exist.
		  *
		  * @param GroupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @param ThreadID
		  * 	This is a string containing the thread's ID.
		  *
		  * @param DoInterrupt
		  * 	This is a boolean value which determines if the thread is interrupted or detached.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does not exist.<br>
		  * 	If the specified thread does not exist within the specified group.
		  */

		void DestroyThread( const std::string& GroupID, const std::string& ThreadID, const bool DoInterrupt = true );

		/**
		  * @brief This method calls 'wait' on the specified group's thread barrier, if it exists.
		  *
		  * This will cause the calling thread to be blocked until the number of threads equal to the value used in 'SetBarrierSize' have called this method.  If
		  * the barrier size is zero, this method will simply return immediately.  This is also a predefined interruption point.
		  *
		  * @param GroupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @exception ThreadInterrupted
		  * 	If the current thread has been issued an interrupt request, and interruption is enabled for the current thread.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does no exist.
		  */

		void Wait( const std::string& GroupID );

		/**
		  * @brief This method joins the specified thread in the specified group, if both group and thread exist.
		  *
		  * This will cause the thread calling this method to block until the specified thread exits, which is useful to ensure a spawned thread has completed its
		  * task before proceeding.  This is also a predefined interruption point.
		  * enabled.
		  *
		  * @param GroupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @param ThreadID
		  * 	This is a string containing the thread's ID.
		  *
		  * @exception ThreadInterrupted
		  * 	If the current thread has been issued an interrupt request, and interruption is enabled for the current thread.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does not exist.<br>
		  * 	If the specified thread does not exist within the specified group.
		  */

		void Join( const std::string& GroupID, const std::string& ThreadID );

		/**
		  * @brief This method joins all the threads in the specified group, if it exists.
		  *
		  * This will cause the thread calling this method to block until all threads in the specified group exit, which is useful to ensure all spawned threads
		  * in a group have completed their task before proceeding.  This is also a predefined interruption point.
		  *
		  * @param GroupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @exception ThreadInterrupted
		  * 	If the current thread has been issued an interrupt request, and interruption is enabled for the current thread.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does not exist.
		  */

		void JoinAll( const std::string& GroupID );

		/**
		  * @brief This method sends an interrupt request to the specified thread in the specified group, if both group and thread exist.
		  *
		  * This request will cause the current thread to be interrupted, if interruption is enabled, upon entering any of the predefined interruption points.
		  * The 'InterruptionRequested' method can be used to process the request manually, regardless of wether or not interruption is enabled.  In addition to
		  * the 'InterruptionPoint' method, the following are also predefined points of interruption: 'Wait', 'Join', 'JoinAll', 'TryJoin' and 'TryJoinAll'.
		  * Interruption can be disabled by instantiated the class 'DisableInterruption', which will disable interruption for the current thread upon construction
		  * and restore the previous state upon destruction.
		  *
		  * @param GroupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @param ThreadID
		  * 	This is a string containing the thread's ID.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does not exist.<br>
		  *	If the specified thread does not exist in the specified group.
		  */

		void Interrupt( const std::string& GroupID, const std::string& ThreadID );

		/**
		  * @brief This method sends an interrupt request to all threads in the specified group, if it exists.
		  *
		  * This request will cause all threads in the specified group to be interrupted, if interruption is enabled, upon entering any of the predefined
		  * interruption points.  The 'InterruptionRequested' method can be used to process the request manually, regardless of wether or not interruption is
		  * enabled.  In addition to the 'InterruptionPoint' method, the following are also predefined points of interruption: 'Wait', 'Join', 'JoinAll',
		  * 'TryJoin', and 'TryJoinAll'.  Interruption can be disabled by instantiated the class 'DisableInterruption', which will disable interruption for the
		  * current thread upon construction and restore the previous state upon destruction.
		  *
		  * @param GroupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does not exist.
		  */

		void InterruptAll( const std::string& GroupID );

		/**
		  * @brief This method determines if an interrupt request has been issued for the current thread.
		  *
		  * @return
		  * 	A boolean value of 'true' if an interrupt request has been issued for the current thread, and 'false' otherwise.
		  */

		bool InterruptionRequested();

		/**
		  * @brief This method is a predefined interruption point.
		  *
		  * Calling this method when an interrupt request has been issued for the current thread, and interruption is enabled for the current thread, will cause
		  * that thread to be interrupted.
		  *
		  * @exception ThreadInterrupted
		  * 	If the current thread has been issued an interrupt request, and interruption is enabled for the current thread.
		  */

		void InterruptionPoint();

		/**
		  * @brief This method retrieves the number of logical cores available on the current system.
		  *
		  * Logical cores are the number of physical cores times the number of threads which can execute per core via hyperthreading.
		  *
		  * @return
		  * 	The number of logical cores available on the current system, or '0' if that information is not available.
		  */

		uint32_t GetLogicalCoreCount();

		/**
		  * @brief This method retrieves the number of physical cores available on the current system.
		  *
		  * @return
		  * 	The number of physical cores available on the current system, or '0' if that information is not available.
		  */

		uint32_t GetPhysicalCoreCount();

		/**
		  * @brief This method creates a thread in the specified group, if both group and thread are valid.
		  *
		  * @param GroupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @param ThreadID
		  * 	This is a string containing the thread's ID.
		  *
		  * @param TargetFunction
		  * 	This is a pointer to the function which will be called by the new thread.
		  *
		  * @param TargetArguments
		  * 	This is a list of arguments to be sent to 'TargetFunction'.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does not exist.<br>
		  * 	If the specified thread already exists.
		  */

		template< typename Type, typename... ATypes > void CreateThread( const std::string& GroupID,
		                                                                 const std::string& ThreadID,
		                                                                 Type TargetFunction,
		                                                                 ATypes... TargetArguments  )
		{
			// Obtain locks.

				SCOPED_WRITE_LOCK;

			// Create scoped stack traces.

				SCOPED_STACK_TRACE( "ThreadManager::CreateThread", 0000 );

			// Create local variables.

				auto GroupMapIterator = Groups.find( GroupID );
				ThreadPtrMap::iterator ThreadPtrMapIterator;

			// Create specified thread in specified group, if both group and thread are valid.

				QMX_ASSERT( ( GroupMapIterator != Groups.end() ), "QMXStdLib", "ThreadManager::CreateThread", "00000033", GroupID << ", " << ThreadID );
				ThreadPtrMapIterator = GroupMapIterator->second.Threads.find( ThreadID );
				QMX_ASSERT( ( ThreadPtrMapIterator == GroupMapIterator->second.Threads.end() ),
				            "QMXStdLib",
				            "ThreadManager::CreateThread",
				            "00000034",
				            GroupID << ", " << ThreadID );
				GroupMapIterator->second.Threads.insert( ThreadPtrMap::value_type( ThreadID, std::make_shared< Thread >( TargetFunction, TargetArguments... ) ) );
		}

		/**
		  * @brief This method joins the specified thread in the specified group with a timeout duration, if both group and thread exist.
		  *
		  * This will cause the thread calling this method to block until either the specified thread exits or the timeout duration is reached, which is useful to
		  * wait for a spawned thread only a reasonable amount of time before proceeding.  This is also a predefined interruption point.
		  *
		  * @param GroupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @param ThreadID
		  * 	This is a string containing the thread's ID.
		  *
		  * @param Duration
		  * 	This is the timeout duration to use; it can be an instantiation of one of the following classes: 'Nanoseconds', 'Microseconds', 'Milliseconds',
		  * 	'Seconds', 'Minutes', or 'Hours'.
		  *
		  * @return
		  * 	A boolean value of 'true' if the thread was successfully joined, and 'false' otherwise.
		  *
		  * @exception ThreadInterrupted
		  * 	If the current thread has been issued an interrupt request, and interruption is enabled for the current thread.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does not exist.<br>
		  * 	If the specified thread does not exist within the specified group.
		  */

		template< typename RType, typename PType > bool TryJoin( const std::string& GroupID,
		                                                         const std::string& ThreadID,
		                                                         const boost::chrono::duration< RType, PType >& Duration )
		{
			// Obtain locks.

				SCOPED_READ_LOCK;

			// Create scoped stack traces.

				SCOPED_STACK_TRACE( "ThreadManager::TryJoin", 0000 );

			// Create local variables.

				bool Result = Null;
				auto GroupMapIterator = Groups.find( GroupID );
				ThreadPtrMap::iterator ThreadPtrMapIterator;

			// Join specified thread in specified group with specified timeout duration, if both group and thread exist.

				QMX_ASSERT( ( GroupMapIterator != Groups.end() ), "QMXStdLib", "ThreadManager::TryJoin", "0000002D", GroupID << ", " << ThreadID );
				ThreadPtrMapIterator = GroupMapIterator->second.Threads.find( ThreadID );
				QMX_ASSERT( ( ThreadPtrMapIterator != GroupMapIterator->second.Threads.end() ),
								"QMXStdLib",
								"ThreadManager::TryJoin",
								"0000002E",
								GroupID << ", " << ThreadID );

				if( ThreadPtrMapIterator->second->joinable() )
					Result = ThreadPtrMapIterator->second->try_join_for( Duration );

			// Return result to calling routine.

				return Result;
		}

		/**
		  * @brief This method joins all the threads in the specified group with a timeout duration, if it exists.
		  *
		  * This will cause the thread calling this method to block until either all threads in the specified group exit or the timeout duration is reached (which
		  * is applied per thread), which is useful to wait for all spawned threads in a group only a reasonable amount of time before proceeding.  This is also a
		  * predefined interruption point.
		  *
		  * @param GroupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @param Duration
		  * 	This is the timeout duration to use; it can be an instantiation of one of the following classes: 'Nanoseconds', 'Microseconds', 'Milliseconds',
		  * 	'Seconds', 'Minutes', or 'Hours'.
		  *
		  * @return
		  * 	A boolean value of 'true' if all threads were successfully joined, and 'false' otherwise.
		  *
		  * @exception ThreadInterrupted
		  * 	If the current thread has been issued an interrupt request, and interruption is enabled for the current thread.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does not exist.
		  */

		template< typename RType, typename PType > bool TryJoinAll( const std::string& GroupID, const boost::chrono::duration< RType, PType >& Duration )
		{
			// Obtain locks.

				SCOPED_READ_LOCK;

			// Create scoped stack traces.

				SCOPED_STACK_TRACE( "ThreadManager::TryJoinAll", 0000 );

			// Create local variables.

				bool Result = Null;
				auto GroupMapIterator = Groups.find( GroupID );

			// Join all spawned threads for specified group with specified timeout duration, if it exists.

				QMX_ASSERT( ( GroupMapIterator != Groups.end() ), "QMXStdLib", "ThreadManager::TryJoinAll", "0000002F", GroupID );

				for( auto& Index : GroupMapIterator->second.Threads )
				{
					if( Index.second->joinable() )
						Result = Index.second->try_join_for( Duration );
				}

			// Return result to calling routine.

				return Result;
		}

		/**
		  * @brief This method creates an instance of this class.
		  *
		  * @return
		  * 	A pointer to the newly created instance.
		  */

		static PointerType Create();

private:

	// Private Type Definitions

		typedef std::unordered_map< std::string, Group > GroupMap;

	// Private Fields

		/**
		  * @brief This is the map of thread groups.
		  */

		GroupMap Groups;

	// Private Constructors

		/**
		  * @brief This is the default constructor, which is made private to prevent direct instantiation.
		  */

		ThreadManager();

	// Private Methods

		/**
		  * @brief This is the overridden implementation for the 'Deallocate' method.
		  */

		void DeallocateImp();
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_THREADMANAGER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ThreadManager.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

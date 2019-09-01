////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ThreadManager.hpp
// Robert M. Baker | Created : 24FEB16 | Last Modified : 31AUG19 by Robert M. Baker
// Version : 2.1.0
// This is a header file for 'QMXStdLib'; it defines the interface for a thread manager class.
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
  * @date    Last Modified : 31AUG19 by Robert M. Baker
  * @version 2.1.0
  *
  * @brief This is a header file for 'QMXStdLib'; it defines the interface for a thread manager class.
  *
  * @section ThreadManagerH0000 Description
  *
  * This is a header file for 'QMXStdLib'; it defines the interface for a thread manager class.
  *
  * @section ThreadManagerH0001 License
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

#ifndef __QMX_QMXSTDLIB_THREADMANAGER_HPP_
#define __QMX_QMXSTDLIB_THREADMANAGER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "Object.hpp"
#include "Mixins/Singleton.hpp"
#include "RAII/ScopedLock.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define THREAD_MANAGER   QMXStdLib::ThreadManager::getSingleton()
#define THREAD_MANAGER_P QMXStdLib::ThreadManager::getSingletonPointer()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Type Definitions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef boost::thread                            Thread;
typedef boost::barrier                           Barrier;
typedef boost::this_thread::disable_interruption DisableInterruption;
typedef boost::thread_interrupted                ThreadInterrupted;

STANDARD_TYPEDEFS_X( Thread,                     Thread );
STANDARD_TYPEDEFS_X( Barrier,                    Barrier );

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
	// Friend Classes

		friend class Object< ThreadManager >;

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

				ThreadPtrMap threads;

				/**
				  * @brief This is the group's barrier used for execution synchronization.
				  */

				BarrierPtr groupBarrier;
		};

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		~ThreadManager();

	// Public Methods

		/**
		  * @brief This method creates a new thread group, if it does not already exist.
		  *
		  * @param groupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @exception QMXException
		  * 	If the specified thread group already exists.
		  */

		void createGroup( const std::string& groupID );

		/**
		  * @brief This method destroys a thread group, with optional thread destruction/interruption, if it exists.
		  *
		  * @param groupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @param doDestroyThreads
		  * 	This is a boolean value which determines if a non-empty group should have its threads destroyed.
		  *
		  * @param doInterrupt
		  * 	This is a boolean value which determines if destroyed threads are interrupted or detached.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does not exist.<br>
		  * 	If the specified thread group was not empty and 'DoDestroyThreads' was set to 'false'.
		  */

		void destroyGroup( const std::string& groupID, const bool doDestroyThreads = false, const bool doInterrupt = true );

		/**
		  * @brief This method retrieves all group IDs, if any exist.
		  *
		  * @param target
		  * 	This is a string vector which will be populated with the retrieved group IDs.
		  */

		void getGroupIDs( StringVector& target ) const;

		/**
		  * @brief This method sets the barrier size for the specified group, if it exists.
		  *
		  * This method should be called on a group to set its barrier size before any calls to 'wait' are made; otherwise, the program could end up in a locked
		  * state.
		  *
		  * @param groupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @param newSize
		  * 	This is the new barrier size to use.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does not exist.
		  */

		void setBarrierSize( const std::string& groupID, const size_t newSize );

		/**
		  * @brief This method destroys a thread in the specified group, with optional interruption, if both group and thread exist.
		  *
		  * @param groupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @param threadID
		  * 	This is a string containing the thread's ID.
		  *
		  * @param doInterrupt
		  * 	This is a boolean value which determines if the thread is interrupted or detached.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does not exist.<br>
		  * 	If the specified thread does not exist within the specified group.
		  */

		void destroyThread( const std::string& groupID, const std::string& threadID, const bool doInterrupt = true );

		/**
		  * @brief This method retrieves all thread IDs for the specified group, if it exists.
		  *
		  * @param groupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @param target
		  * 	This is a string vector which will be populated with the retrieved thread IDs.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does not exist.
		  */

		void getThreadIDs( const std::string& groupID, StringVector& target ) const;

		/**
		  * @brief This method calls 'wait' on the specified group's thread barrier, if it exists.
		  *
		  * This will cause the calling thread to be blocked until the number of threads equal to the value used in 'setBarrierSize' have called this method.  If
		  * the barrier size is zero, this method will simply return immediately.  This is also a predefined interruption point.
		  *
		  * @param groupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @exception ThreadInterrupted
		  * 	If the current thread has been issued an interrupt request, and interruption is enabled for the current thread.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does no exist.
		  */

		void wait( const std::string& groupID );

		/**
		  * @brief This method joins the specified thread in the specified group, if both group and thread exist.
		  *
		  * This will cause the thread calling this method to block until the specified thread exits, which is useful to ensure a spawned thread has completed its
		  * task before proceeding.  This is also a predefined interruption point.
		  * enabled.
		  *
		  * @param groupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @param threadID
		  * 	This is a string containing the thread's ID.
		  *
		  * @exception ThreadInterrupted
		  * 	If the current thread has been issued an interrupt request, and interruption is enabled for the current thread.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does not exist.<br>
		  * 	If the specified thread does not exist within the specified group.
		  */

		void join( const std::string& groupID, const std::string& threadID );

		/**
		  * @brief This method joins all the threads in the specified group, if it exists.
		  *
		  * This will cause the thread calling this method to block until all threads in the specified group exit, which is useful to ensure all spawned threads
		  * in a group have completed their task before proceeding.  This is also a predefined interruption point.
		  *
		  * @param groupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @exception threadInterrupted
		  * 	If the current thread has been issued an interrupt request, and interruption is enabled for the current thread.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does not exist.
		  */

		void joinAll( const std::string& groupID );

		/**
		  * @brief This method sends an interrupt request to the specified thread in the specified group, if both group and thread exist.
		  *
		  * This request will cause the current thread to be interrupted, if interruption is enabled, upon entering any of the predefined interruption points.
		  * The 'interruptionRequested' method can be used to process the request manually, regardless of wether or not interruption is enabled.  In addition to
		  * the 'interruptionPoint' method, the following are also predefined points of interruption: 'wait', 'join', 'joinAll', 'tryJoin' and 'tryJoinAll'.
		  * Interruption can be disabled via the class 'DisableInterruption', which will disable interruption for the current thread upon construction and restore
		  * the previous state upon destruction.
		  *
		  * @param groupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @param threadID
		  * 	This is a string containing the thread's ID.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does not exist.<br>
		  *	If the specified thread does not exist in the specified group.
		  */

		void interrupt( const std::string& groupID, const std::string& threadID );

		/**
		  * @brief This method sends an interrupt request to all threads in the specified group, if it exists.
		  *
		  * This request will cause all threads in the specified group to be interrupted, if interruption is enabled, upon entering any of the predefined
		  * interruption points.  The 'interruptionRequested' method can be used to process the request manually, regardless of wether or not interruption is
		  * enabled.  In addition to the 'interruptionPoint' method, the following are also predefined points of interruption: 'wait', 'join', 'joinAll',
		  * 'tryJoin', and 'tryJoinAll'.  Interruption can be disabled via the class 'DisableInterruption', which will disable interruption for the current thread
		  * upon construction and restore the previous state upon destruction.
		  *
		  * @param GroupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does not exist.
		  */

		void interruptAll( const std::string& GroupID );

		/**
		  * @brief This method determines if an interrupt request has been issued for the current thread.
		  *
		  * @return
		  * 	A boolean value of 'true' if an interrupt request has been issued for the current thread, and 'false' otherwise.
		  */

		bool interruptionRequested() const;

		/**
		  * @brief This method is a predefined interruption point.
		  *
		  * Calling this method when an interrupt request has been issued for the current thread, and interruption is enabled for the current thread, will cause
		  * that thread to be interrupted.
		  *
		  * @exception ThreadInterrupted
		  * 	If the current thread has been issued an interrupt request, and interruption is enabled for the current thread.
		  */

		void interruptionPoint() const;

		/**
		  * @brief This method retrieves the number of logical cores available on the current system.
		  *
		  * Logical cores are the number of physical cores times the number of threads which can execute per core via hyperthreading.
		  *
		  * @return
		  * 	The number of logical cores available on the current system, or '0' if that information is not available.
		  */

		uint32_t getLogicalCoreCount() const;

		/**
		  * @brief This method retrieves the number of physical cores available on the current system.
		  *
		  * @return
		  * 	The number of physical cores available on the current system, or '0' if that information is not available.
		  */

		uint32_t getPhysicalCoreCount() const;

		/**
		  * @brief This method creates a thread in the specified group, if both group and thread are valid.
		  *
		  * @param groupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @param threadID
		  * 	This is a string containing the thread's ID.
		  *
		  * @param targetFunction
		  * 	This is a pointer to the function which will be called by the new thread.
		  *
		  * @param targetArguments
		  * 	This is a list of arguments to be sent to 'TargetFunction'.
		  *
		  * @exception QMXException
		  * 	If the specified thread group does not exist.<br>
		  * 	If the specified thread already exists.
		  */

		template< typename Type, typename... ATypes > void createThread(
			const std::string& groupID,
			const std::string& threadID,
			Type targetFunction,
			ATypes... targetArguments
		)
		{
			// Obtain locks.

				SCOPED_WRITE_LOCK;

			// Create scoped stack traces.

				SCOPED_STACK_TRACE( "ThreadManager::createThread", 0000 );

			// Create local variables.

				auto groupMapIterator = groups.find( groupID );
				ThreadPtrMap::iterator threadPtrMapIterator;

			// Create specified thread in specified group, if both group and thread are valid.

				QMX_ASSERT( ( groupMapIterator != groups.end() ), "QMXStdLib", "ThreadManager::createThread", "00000025", groupID << ", " << threadID );
				threadPtrMapIterator = groupMapIterator->second.threads.find( threadID );

				QMX_ASSERT(
					( threadPtrMapIterator == groupMapIterator->second.threads.end() ),
					"QMXStdLib",
					"ThreadManager::createThread",
					"00000026",
					groupID << ", " << threadID
				);

				groupMapIterator->second.threads.insert( ThreadPtrMap::value_type( threadID, std::make_shared< Thread >( targetFunction, targetArguments... ) ) );
		}

		/**
		  * @brief This method joins the specified thread in the specified group with a timeout duration, if both group and thread exist.
		  *
		  * This will cause the thread calling this method to block until either the specified thread exits or the timeout duration is reached, which is useful to
		  * wait for a spawned thread only a reasonable amount of time before proceeding.  This is also a predefined interruption point.
		  *
		  * @param groupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @param threadID
		  * 	This is a string containing the thread's ID.
		  *
		  * @param duration
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

		template< typename RType, typename PType > bool tryJoin(
			const std::string& groupID,
			const std::string& threadID,
			const boost::chrono::duration< RType, PType >& duration
		)
		{
			// Obtain locks.

				SCOPED_READ_LOCK;

			// Create scoped stack traces.

				SCOPED_STACK_TRACE( "ThreadManager::tryJoin", 0000 );

			// Create local variables.

				bool result = UNSET;
				auto groupMapIterator = groups.find( groupID );
				ThreadPtrMap::iterator threadPtrMapIterator;

			// Join specified thread in specified group with specified timeout duration, if both group and thread exist.

				QMX_ASSERT( ( groupMapIterator != groups.end() ), "QMXStdLib", "ThreadManager::tryJoin", "0000001F", groupID << ", " << threadID );
				threadPtrMapIterator = groupMapIterator->second.threads.find( threadID );
				QMX_ASSERT( ( threadPtrMapIterator != groupMapIterator->second.threads.end() ),
					"QMXStdLib",
					"ThreadManager::tryJoin",
					"00000020",
					groupID << ", " << threadID
				);

				if( threadPtrMapIterator->second->joinable() )
					result = threadPtrMapIterator->second->try_join_for( duration );

			// Return result to calling routine.

				return result;
		}

		/**
		  * @brief This method joins all the threads in the specified group with a timeout duration, if it exists.
		  *
		  * This will cause the thread calling this method to block until either all threads in the specified group exit or the timeout duration is reached (which
		  * is applied per thread), which is useful to wait for all spawned threads in a group only a reasonable amount of time before proceeding.  This is also a
		  * predefined interruption point.
		  *
		  * @param groupID
		  * 	This is a string containing the thread group's ID.
		  *
		  * @param duration
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

		template< typename RType, typename PType > bool tryJoinAll( const std::string& groupID, const boost::chrono::duration< RType, PType >& duration )
		{
			// Obtain locks.

				SCOPED_READ_LOCK;

			// Create scoped stack traces.

				SCOPED_STACK_TRACE( "ThreadManager::tryJoinAll", 0000 );

			// Create local variables.

				bool result = UNSET;
				auto groupMapIterator = groups.find( groupID );

			// Join all spawned threads for specified group with specified timeout duration, if it exists.

				QMX_ASSERT( ( groupMapIterator != groups.end() ), "QMXStdLib", "ThreadManager::tryJoinAll", "00000021", groupID );

				for( auto& index : groupMapIterator->second.threads )
				{
					if( index.second->joinable() )
						result = index.second->try_join_for( duration );
				}

			// Return result to calling routine.

				return result;
		}

private:

	// Private Type Definitions

		typedef std::unordered_map< std::string, Group > GroupMap;

	// Private Fields

		/**
		  * @brief This is the map of thread groups.
		  */

		GroupMap groups;

	// Private Constructors

		/**
		  * @brief This is the default constructor, which is made private to prevent direct instantiation.
		  */

		ThreadManager();

	// Private Methods

		/**
		  * @brief This is the overridden implementation for the 'Deallocate' method.
		  */

		void deallocateImp();
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_THREADMANAGER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ThreadManager.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

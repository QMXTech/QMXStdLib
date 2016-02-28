////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StackTracer.hpp
// Robert M. Baker | Created : 29FEB12 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.1
// This is a header file for 'QMXStdLib'; it defines the interface for a stack tracer class.
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
  * @date    Created : 29FEB12
  * @date    Last Modified : 27FEB16 by Robert M. Baker
  * @version 1.1.1
  *
  * @brief This header file defines the interface for a stack tracer class.
  *
  * @section Description
  *
  * This header file defines the interface for a stack tracer class.
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

#ifndef __QMX_QMXSTDLIB_STACKTRACER_HPP_
#define __QMX_QMXSTDLIB_STACKTRACER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "QMXException.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define STACK_TRACE QMXStdLib::StackTracer::GetStackTrace()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'StackTracer' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class StackTracer StackTracer.hpp "include/StackTracer.hpp"
  *
  * @brief This class defines stack tracing algorithms.
  *
  * It is defined as a utility class; thus, it cannot be instantiated and contains only static members.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Yes
  */

class StackTracer
{
public:

	// Public Methods

		/**
		  * @brief This method gets the current value of 'IsEnabled'.
		  *
		  * @return
		  * 	A boolean value of 'true' if the stack tracer is enabled, and 'false' otherwise.
		  */

		static bool GetEnabled()
		{
			// Obtain locks.

				SharedLock ScopedReadLock( LocalMutex );

			// Report value of 'IsEnabled' to calling routine.

				return IsEnabled;
		}

		/**
		  * @brief This method sets the value of 'IsEnabled'.
		  *
		  * When 'IsEnabled' is 'false', none of the methods (other than 'GetEnabled' and 'SetEnabled') will have any effect.
		  *
		  * @param TargetValue
		  * 	This is the value with which to set 'IsEnabled'.
		  */

		static void SetEnabled( bool TargetValue )
		{
			// Obtain locks.

				UniqueLock ScopedWriteLock( LocalMutex );

			// Set value of 'IsEnabled' to specified value.

				IsEnabled = TargetValue;
		}

		/**
		  * @brief This method gets the current thread's ID.
		  *
		  * If a call was never made to 'SetThreadID' for the current thread, this will return an empty string.
		  *
		  * @return
		  * 	A string containing the current thread's ID.
		  */

		static std::string GetThreadID()
		{
			// Report current thread's ID to calling routine.

				return( ThreadID.get() ? *ThreadID : "" );
		}

		/**
		  * @brief This method sets the current thread's ID to the specified string.
		  *
		  * @param Target
		  * 	This is the string with which to set the current thread's ID.
		  */

		static void SetThreadID( const std::string& Target )
		{
			// Set the current thread's ID to the specified string.

				ThreadID.reset( ( new std::string( Target ) ) );
		}

		/**
		  * @brief This method adds the current thread to the stack trace map.
		  *
		  * The current thread's ID should first be set with a call to 'SetThreadID'.
		  *
		  * @param BaseStackTrace
		  * 	This is a string containing the base stack trace.
		  *
		  * @exception QMXException
		  * 	If the current thread's ID was not set.<br>
		  * 	If the current thread's ID was an empty string.<br>
		  * 	If the current thread was already added to the tracer.
		  */

		static void AddThread( const std::string& BaseStackTrace )
		{
			// Perform pre-lock abort check.

				if( !IsEnabled )
					return;

			// Obtain locks.

				UniqueLock ScopedWriteLock( LocalMutex );

			// Perform post-lock abort check.

				if( !IsEnabled )
					return;

			// Add current thread to stack trace map, if its name has been properly set and has not already been added.

				QMX_ASSERT_X( ThreadID.get(), "QMXStdLib", "StackTracer::AddThread", "00000022", BaseStackTrace );
				QMX_ASSERT_X( ThreadID->length(), "QMXStdLib", "StackTracer::AddThread", "00000023", BaseStackTrace );
				QMX_ASSERT_X( StackTraces.insert( StackTraceMap::value_type( *ThreadID, StringVector( 1, BaseStackTrace ) ) ).second,
				              "QMXStdLib",
				              "StackTracer::AddThread",
				              "00000024",
				              *ThreadID << ", " << BaseStackTrace );
		}

		/**
		  * @brief This method removes the current thread from the stack trace map.
		  *
		  * The current thread's ID should first be set with a call to 'SetThreadID'.
		  *
		  * @exception QMXException
		  * 	If the current thread's ID was not set.<br>
		  * 	If the current thread's ID was an empty string.<br>
		  * 	If the current thread was not added to the tracer.
		  */

		static void RemoveThread()
		{
			// Perform pre-lock abort check.

				if( !IsEnabled )
					return;

			// Obtain locks.

				UniqueLock ScopedWriteLock( LocalMutex );

			// Perform post-lock abort check.

				if( !IsEnabled )
					return;

			// Remove the current thread from stack trace map, if its name has been properly set and has been added.

				QMX_ASSERT_X( ThreadID.get(), "QMXStdLib", "StackTracer::RemoveThread", "00000022", "" );
				QMX_ASSERT_X( ThreadID->length(), "QMXStdLib", "StackTracer::RemoveThread", "00000023", "" );
				QMX_ASSERT_X( StackTraces.erase( *ThreadID ), "QMXStdLib", "StackTracer::RemoveThread", "00000025", *ThreadID );
		}

		/**
		  * @brief This method pushes an entry onto the current thread's stack trace.
		  *
		  * All pushed entries will be used to construct a stack trace when the 'GetStackTrace' method is called.
		  *
		  * @param Entry
		  * 	This is a string containing the entry to push.
		  *
		  * @exception QMXException
		  * 	If the current thread's ID was not set.<br>
		  * 	If the current thread's ID was an empty string.<br>
		  * 	If the current thread was not added to the tracer.
		  */

		static void Push( const std::string& Entry )
		{
			// Perform pre-lock abort check.

				if( !IsEnabled )
					return;

			// Obtain locks.

				UniqueLock ScopedWriteLock( LocalMutex );

			// Perform post-lock abort check.

				if( !IsEnabled )
					return;

			// Create local variables.

				StackTraceMap::iterator StackTraceMapIterator;

			// Push the specified entry onto the current thread's stack trace, if its name has been properly set and has been added.

				QMX_ASSERT_X( ThreadID.get(), "QMXStdLib", "StackTracer::Push", "00000022", Entry );
				QMX_ASSERT_X( ThreadID->length(), "QMXStdLib", "StackTracer::Push", "00000023", Entry );
				StackTraceMapIterator = StackTraces.find( *ThreadID );
				QMX_ASSERT_X( ( StackTraceMapIterator != StackTraces.end() ), "QMXStdLib", "StackTracer::Push", "00000025", *ThreadID << ", " << Entry );
				StackTraceMapIterator->second.push_back( Entry );
		}

		/**
		  * @brief This method pops an entry off the current thread's stack trace.
		  *
		  * This method will remove that last pushed entry, and should be used at the end of any scope which has made a call to push.  If no entries are present
		  * in the stack trace (other than the base stack trace), this method will have no effect.
		  *
		  * @exception QMXException
		  * 	If the current thread's ID was not set.<br>
		  * 	If the current thread's ID was an empty string.<br>
		  * 	If the current thread was not added to the tracer.
		  */

		static void Pop()
		{
			// Perform pre-lock abort check.

				if( !IsEnabled )
					return;

			// Obtain locks.

				UniqueLock ScopedWriteLock( LocalMutex );

			// Perform post-lock abort check.

				if( !IsEnabled )
					return;

			// Create local variables.

				StackTraceMap::iterator StackTraceMapIterator;

			// Pop the last pushed entry off the current thread's stack trace, if its name has been properly set and has been added.

				QMX_ASSERT_X( ThreadID.get(), "QMXStdLib", "StackTracer::Pop", "00000022", "" );
				QMX_ASSERT_X( ThreadID->length(), "QMXStdLib", "StackTracer::Pop", "00000023", "" );
				StackTraceMapIterator = StackTraces.find( *ThreadID );
				QMX_ASSERT_X( ( StackTraceMapIterator != StackTraces.end() ), "QMXStdLib", "StackTracer::Pop", "00000025", *ThreadID );

				if( StackTraceMapIterator->second.size() > 1 )
					StackTraceMapIterator->second.pop_back();
		}

		/**
		  * @brief This method constructs a stack trace for the current thread.
		  *
		  * @return
		  * 	The constructed stack trace string.
		  *
		  * @exception QMXException
		  * 	If the current thread's ID was not set.<br>
		  * 	If the current thread's ID was an empty string.<br>
		  * 	If the current thread was not added to the tracer.
		  */

		static std::string GetStackTrace()
		{
			// Perform pre-lock abort check.

				if( !IsEnabled )
					return "";

			// Obtain locks.

				SharedLock ScopedReadLock( LocalMutex );

			// Perform post-lock abort check.

				if( !IsEnabled )
					return "";

			// Create local variables.

				std::string Result;
				StackTraceMap::iterator StackTraceMapIterator;
				size_t Index = Null;

			// Construct the stack trace for the current thread, if its name has been properly set and has been added.

				QMX_ASSERT_X( ThreadID.get(), "QMXStdLib", "StackTracer::GetStackTrace", "00000022", "" );
				QMX_ASSERT_X( ThreadID->length(), "QMXStdLib", "StackTracer::GetStackTrace", "00000023", "" );
				StackTraceMapIterator = StackTraces.find( *ThreadID );
				QMX_ASSERT_X( ( StackTraceMapIterator != StackTraces.end() ), "QMXStdLib", "StackTracer::GetStackTrace", "00000025", *ThreadID );

				if( StackTraceMapIterator->second.size() == 1 )
					Result = StackTraceMapIterator->second[ 0 ];
				else
				{
					for( ; Index < ( StackTraceMapIterator->second.size() - 1 ); Index++ )
						Result += StackTraceMapIterator->second[ Index ] + STACKTRACER_ENTRY_SEPERATOR;

					Result += StackTraceMapIterator->second[ Index ];
				}

			// Return result to calling routine.

				return Result;
		}

		/**
		  * @brief This method resets the stack tracer to its default state.
		  */

		static void Reset()
		{
			// Obtain locks.

				UniqueLock ScopedWriteLock( LocalMutex );

			// Reset stack tracer to default state.

				IsEnabled = false;
				StackTraces.clear();
		}

private:

	// Private Type Definitions

		typedef std::unordered_map< std::string, StringVector > StackTraceMap;

	// Private Fields

		/**
		  * @brief This is the mutex for use when thread-safety is needed.
		  */

		static SharedMutex LocalMutex;

		/**
		  * @brief This is the flag which determines if the stack tracer is enabled.
		  */

		static bool IsEnabled;

		/**
		  * @brief This is a thread-specific pointer to a string containing the current thread's ID.
		  */

		static StringTLS ThreadID;

		/**
		  * @brief This is the stack trace map.
		  */

		static StackTraceMap StackTraces;

	// Private Constructors

		/**
		  * @brief This is the default constructor, which is made private to prevent instantiation.
		  */

		StackTracer()
		{
			// Do nothing.
		}
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_TRACER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'Tracer.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

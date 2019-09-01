////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StackTracer.hpp
// Robert M. Baker | Created : 29FEB12 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.1.0
// This is a header file for 'QMXStdLib'; it defines the interface for a stack tracer class.
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
  * @date    Created : 29FEB12
  * @date    Last Modified : 29AUG19 by Robert M. Baker
  * @version 2.1.0
  *
  * @brief This header file defines the interface for a stack tracer class.
  *
  * @section StackTracerH0000 Description
  *
  * This header file defines the interface for a stack tracer class.
  *
  * @section StackTracerH0001 License
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

#ifndef __QMX_QMXSTDLIB_STACKTRACER_HPP_
#define __QMX_QMXSTDLIB_STACKTRACER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "QMXException.hpp"
#include "RAII/ScopedLock.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define STACK_TRACE QMXStdLib::StackTracer::getStackTrace()

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
		  * @brief This method gets the current value of 'isEnabled'.
		  *
		  * @return
		  * 	A boolean value of 'true' if the stack tracer is enabled, and 'false' otherwise.
		  */

		static bool getEnabled()
		{
			// Obtain locks.

				ScopedLock readLock( ScopedLock::READ, localMutex );

			// Report value of 'IsEnabled' to calling routine.

				return isEnabled;
		}

		/**
		  * @brief This method sets the value of 'isEnabled'.
		  *
		  * When 'isEnabled' is 'false', none of the methods (other than 'getEnabled' and 'setEnabled') will have any effect.
		  *
		  * @param target
		  * 	This is the value with which to set 'isEnabled'.
		  */

		static void setEnabled( bool target )
		{
			// Obtain locks.

				ScopedLock writeLock( ScopedLock::WRITE, localMutex );

			// Set value of 'IsEnabled' to specified value.

				isEnabled = target;
		}

		/**
		  * @brief This method gets the current thread's ID.
		  *
		  * If a call was never made to 'setThreadID' for the current thread, this will return an empty string.
		  *
		  * @return
		  * 	A string containing the current thread's ID.
		  */

		static std::string getThreadID()
		{
			// Report current thread's ID to calling routine.

				return( threadID.get() ? *threadID : "" );
		}

		/**
		  * @brief This method sets the current thread's ID to the specified string.
		  *
		  * @param target
		  * 	This is the string with which to set the current thread's ID.
		  */

		static void setThreadID( const std::string& target )
		{
			// Set the current thread's ID to the specified string.

				threadID.reset( ( new std::string( target ) ) );
		}

		/**
		  * @brief This method adds the current thread to the stack trace map.
		  *
		  * The current thread's ID should first be set with a call to 'setThreadID'.
		  *
		  * @param baseStackTrace
		  * 	This is a string containing the base stack trace.
		  *
		  * @exception QMXException
		  * 	If the current thread's ID was not set.<br>
		  * 	If the current thread's ID was an empty string.<br>
		  * 	If the current thread was already added to the tracer.
		  */

		static void addThread( const std::string& base )
		{
			// Perform pre-lock abort check.

				if( !isEnabled )
					return;

			// Obtain locks.

				ScopedLock writeLock( ScopedLock::WRITE, localMutex );

			// Perform post-lock abort check.

				if( !isEnabled )
					return;

			// Add current thread to stack trace map, if its name has been properly set and has not already been added.

				QMX_ASSERT_X( threadID.get(), "QMXStdLib", "StackTracer::addThread", "00000013", base );
				QMX_ASSERT_X( threadID->length(), "QMXStdLib", "StackTracer::addThread", "00000014", base );

				QMX_ASSERT_X(
					stackTraces.insert( StackTraceMap::value_type( *threadID, StringVector( 1, base ) ) ).second,
					"QMXStdLib",
					"StackTracer::addThread",
					"00000015",
					*threadID << ", " << base
				);
		}

		/**
		  * @brief This method removes the current thread from the stack trace map.
		  *
		  * The current thread's ID should first be set with a call to 'setThreadID'.
		  *
		  * @exception QMXException
		  * 	If the current thread's ID was not set.<br>
		  * 	If the current thread's ID was an empty string.<br>
		  * 	If the current thread was not added to the tracer.
		  */

		static void removeThread()
		{
			// Perform pre-lock abort check.

				if( !isEnabled )
					return;

			// Obtain locks.

				ScopedLock writeLock( ScopedLock::WRITE, localMutex );

			// Perform post-lock abort check.

				if( !isEnabled )
					return;

			// Remove the current thread from stack trace map, if its name has been properly set and has been added.

				QMX_ASSERT_X( threadID.get(), "QMXStdLib", "StackTracer::removeThread", "00000013", "" );
				QMX_ASSERT_X( threadID->length(), "QMXStdLib", "StackTracer::removeThread", "00000014", "" );
				QMX_ASSERT_X( stackTraces.erase( *threadID ), "QMXStdLib", "StackTracer::removeThread", "00000016", *threadID );
		}

		/**
		  * @brief This method pushes an entry onto the current thread's stack trace.
		  *
		  * All pushed entries will be used to construct a stack trace when the 'GetStackTrace' method is called.
		  *
		  * @param target
		  * 	This is a string containing the entry to push.
		  *
		  * @exception QMXException
		  * 	If the current thread's ID was not set.<br>
		  * 	If the current thread's ID was an empty string.<br>
		  * 	If the current thread was not added to the tracer.
		  */

		static void push( const std::string& target )
		{
			// Perform pre-lock abort check.

				if( !isEnabled )
					return;

			// Obtain locks.

				ScopedLock writeLock( ScopedLock::WRITE, localMutex );

			// Perform post-lock abort check.

				if( !isEnabled )
					return;

			// Create local variables.

				StackTraceMap::iterator stackTraceMapIterator;

			// Push the specified entry onto the current thread's stack trace, if its name has been properly set and has been added.

				QMX_ASSERT_X( threadID.get(), "QMXStdLib", "StackTracer::push", "00000013", target );
				QMX_ASSERT_X( threadID->length(), "QMXStdLib", "StackTracer::push", "00000014", target );
				stackTraceMapIterator = stackTraces.find( *threadID );
				QMX_ASSERT_X( ( stackTraceMapIterator != stackTraces.end() ), "QMXStdLib", "StackTracer::push", "00000016", *threadID << ", " << target );
				stackTraceMapIterator->second.push_back( target );
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

		static void pop()
		{
			// Perform pre-lock abort check.

				if( !isEnabled )
					return;

			// Obtain locks.

				ScopedLock writeLock( ScopedLock::WRITE, localMutex );

			// Perform post-lock abort check.

				if( !isEnabled )
					return;

			// Create local variables.

				StackTraceMap::iterator stackTraceMapIterator;

			// Pop the last pushed entry off the current thread's stack trace, if its name has been properly set and has been added.

				QMX_ASSERT_X( threadID.get(), "QMXStdLib", "StackTracer::pop", "00000013", "" );
				QMX_ASSERT_X( threadID->length(), "QMXStdLib", "StackTracer::pop", "00000014", "" );
				stackTraceMapIterator = stackTraces.find( *threadID );
				QMX_ASSERT_X( ( stackTraceMapIterator != stackTraces.end() ), "QMXStdLib", "StackTracer::pop", "00000016", *threadID );

				if( stackTraceMapIterator->second.size() > 1 )
					stackTraceMapIterator->second.pop_back();
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

		static std::string getStackTrace()
		{
			// Perform pre-lock abort check.

				if( !isEnabled )
					return "";

			// Obtain locks.

				ScopedLock readLock( ScopedLock::READ, localMutex );

			// Perform post-lock abort check.

				if( !isEnabled )
					return "";

			// Create local variables.

				std::string result;
				StackTraceMap::iterator stackTraceMapIterator;
				size_t index = UNSET;

			// Construct the stack trace for the current thread, if its name has been properly set and has been added.

				QMX_ASSERT_X( threadID.get(), "QMXStdLib", "StackTracer::getStackTrace", "00000013", "" );
				QMX_ASSERT_X( threadID->length(), "QMXStdLib", "StackTracer::getStackTrace", "00000014", "" );
				stackTraceMapIterator = stackTraces.find( *threadID );
				QMX_ASSERT_X( ( stackTraceMapIterator != stackTraces.end() ), "QMXStdLib", "StackTracer::getStackTrace", "00000016", *threadID );

				if( stackTraceMapIterator->second.size() == 1 )
					result = stackTraceMapIterator->second[ 0 ];
				else
				{
					for( ; index < ( stackTraceMapIterator->second.size() - 1 ); index++ )
						result += stackTraceMapIterator->second[ index ] + STACKTRACER_ENTRY_SEPARATOR;

					result += stackTraceMapIterator->second[ index ];
				}

			// Return result to calling routine.

				return result;
		}

		/**
		  * @brief This method resets the stack tracer to its default state.
		  */

		static void reset()
		{
			// Obtain locks.

				ScopedLock writeLock( ScopedLock::WRITE, localMutex );

			// Reset stack tracer to default state.

				isEnabled = false;
				stackTraces.clear();
		}

private:

	// Private Type Definitions

		typedef std::unordered_map< std::string, StringVector > StackTraceMap;

	// Private Fields

		/**
		  * @brief This is the mutex for use when thread-safety is needed.
		  */

		static SharedMutexPair localMutex;

		/**
		  * @brief This is the flag which determines if the stack tracer is enabled.
		  */

		static bool isEnabled;

		/**
		  * @brief This is a thread-specific pointer to a string containing the current thread's ID.
		  */

		static StringTLS threadID;

		/**
		  * @brief This is the stack trace map.
		  */

		static StackTraceMap stackTraces;

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

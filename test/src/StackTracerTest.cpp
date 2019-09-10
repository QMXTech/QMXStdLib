////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StackTracerTest.cpp
// Robert M. Baker | Created : 04MAR12 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.3.0
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::StackTracer' class.
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../include/StackTracerTest.hpp"

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'StackTracerTest' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace StackTracerTest
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Definitions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void threadMain( const string& targetID, uint32_t targetIndex )
{
	// Create local variables.

		string separator = STACKTRACER_ENTRY_SEPARATOR;

	// Perform thread test based on specified arguments.

		switch( targetIndex )
		{
			case 0:
			{
				ASSERT_TRUE( StackTracer::getThreadID().empty() );
				StackTracer::setThreadID( targetID );
				ASSERT_EQ( targetID, StackTracer::getThreadID() );

				break;
			}

			case 1:
			{
				ASSERT_THROW( StackTracer::addThread( ( targetID + "Main" ) ), QMXException );
				StackTracer::setThreadID( "" );
				ASSERT_THROW( StackTracer::addThread( ( targetID + "Main" ) ), QMXException );
				StackTracer::setThreadID( targetID );
				StackTracer::addThread( ( targetID + "Main" ) );
				ASSERT_THROW( StackTracer::addThread( ( targetID + "Main" ) ), QMXException );

				break;
			}

			case 2:
			{
				ASSERT_THROW( StackTracer::removeThread(), QMXException );
				StackTracer::setThreadID( "" );
				ASSERT_THROW( StackTracer::removeThread(), QMXException );
				StackTracer::setThreadID( targetID );
				ASSERT_THROW( StackTracer::removeThread(), QMXException );
				StackTracer::addThread( ( targetID + "Main" ) );
				StackTracer::removeThread();

				break;
			}

			case 3:
			{
				ASSERT_THROW( StackTracer::push( "Class::method" ), QMXException );
				StackTracer::setThreadID( "" );
				ASSERT_THROW( StackTracer::push( "Class::method" ), QMXException );
				StackTracer::setThreadID( targetID );
				ASSERT_THROW( StackTracer::push( "Class::method" ), QMXException );
				StackTracer::addThread( ( targetID + "Main" ) );
				StackTracer::push( "Class::method" );

				break;
			}

			case 4:
			{
				ASSERT_THROW( StackTracer::pop(), QMXException );
				StackTracer::setThreadID( "" );
				ASSERT_THROW( StackTracer::pop(), QMXException );
				StackTracer::setThreadID( targetID );
				ASSERT_THROW( StackTracer::pop(), QMXException );
				StackTracer::addThread( ( targetID + "Main" ) );
				StackTracer::pop();

				break;
			}

			case 5:
			{
				ASSERT_THROW( StackTracer::getStackTrace(), QMXException );
				StackTracer::setThreadID( "" );
				ASSERT_THROW( StackTracer::getStackTrace(), QMXException );
				StackTracer::setThreadID( targetID );
				ASSERT_THROW( StackTracer::getStackTrace(), QMXException );
				StackTracer::addThread( ( targetID + "Main" ) );
				ASSERT_EQ( ( targetID + "Main" ), StackTracer::getStackTrace() );
				StackTracer::push( "Class::method" );
				ASSERT_EQ( ( targetID + "Main" + separator + "Class::method" ), StackTracer::getStackTrace() );
				StackTracer::pop();
				StackTracer::pop();
				ASSERT_EQ( ( targetID + "Main" ), StackTracer::getStackTrace() );

				break;
			}
		}
}

} // 'StackTracerTest' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'StackTracerTest' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::StackTracer' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( StackTracerTest, ThreadIDWorks )
{
	// Create local variables.

		boost::thread_group threads;

	// Perform unit test for 'threadID' methods.

		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadA", 0 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadB", 0 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadC", 0 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadD", 0 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadE", 0 ) ) );
		threads.join_all();
}

TEST( StackTracerTest, AddThreadWorks )
{
	// Create local variables.

		boost::thread_group threads;

	// Prepare stack tracer for testing.

		StackTracer::setEnabled( true );

	// Perform unit test for 'addThread' methods.

		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadA", 1 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadB", 1 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadC", 1 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadD", 1 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadE", 1 ) ) );
		threads.join_all();

	// Cleanup stack tracer.

		StackTracer::reset();
}

TEST( StackTracerTest, RemoveThreadWorks )
{
	// Create local variables.

		boost::thread_group threads;

	// Prepare stack tracer for testing.

		StackTracer::setEnabled( true );

	// Perform unit test for 'removeThread' methods.

		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadA", 2 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadB", 2 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadC", 2 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadD", 2 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadE", 2 ) ) );
		threads.join_all();

	// Cleanup stack tracer.

		StackTracer::reset();
}

TEST( StackTracerTest, PushWorks )
{
	// Create local variables.

		boost::thread_group threads;

	// Prepare stack tracer for testing.

		StackTracer::setEnabled( true );

	// Perform unit test for 'ThreadID' methods.

		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadA", 3 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadB", 3 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadC", 3 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadD", 3 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadE", 3 ) ) );
		threads.join_all();

	// Cleanup stack tracer.

		StackTracer::reset();
}

TEST( StackTracerTest, PopWorks )
{
	// Create local variables.

		boost::thread_group threads;

	// Prepare stack tracer for testing.

		StackTracer::setEnabled( true );

	// Perform unit test for 'ThreadID' methods.

		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadA", 4 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadB", 4 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadC", 4 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadD", 4 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadE", 4 ) ) );
		threads.join_all();

	// Cleanup stack tracer.

		StackTracer::reset();
}

TEST( StackTracerTest, GetStackTraceWorks )
{
	// Create local variables.

		boost::thread_group threads;

	// Prepare stack tracer for testing.

		StackTracer::setEnabled( true );

	// Perform unit test for 'ThreadID' methods.

		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadA", 5 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadB", 5 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadC", 5 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadD", 5 ) ) );
		threads.add_thread( ( new boost::thread( StackTracerTest::threadMain, "ThreadE", 5 ) ) );
		threads.join_all();

	// Cleanup stack tracer.

		StackTracer::reset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'StackTracerTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

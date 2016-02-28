////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StackTracerTest.cpp
// Robert M. Baker | Created : 04MAR12 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.2
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::StackTracer' class.
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

void ThreadMain( const string& TargetID, uint32_t TargetIndex )
{
	// Create local variables.

		string Seperator = STACKTRACER_ENTRY_SEPERATOR;

	// Perform thread test based on specified arguments.

		switch( TargetIndex )
		{
			case 0:
			{
				ASSERT_TRUE( StackTracer::GetThreadID().empty() );
				StackTracer::SetThreadID( TargetID );
				ASSERT_EQ( TargetID, StackTracer::GetThreadID() );

				break;
			}

			case 1:
			{
				ASSERT_THROW( StackTracer::AddThread( ( TargetID + "Main" ) ), QMXException );
				StackTracer::SetThreadID( "" );
				ASSERT_THROW( StackTracer::AddThread( ( TargetID + "Main" ) ), QMXException );
				StackTracer::SetThreadID( TargetID );
				StackTracer::AddThread( ( TargetID + "Main" ) );
				ASSERT_THROW( StackTracer::AddThread( ( TargetID + "Main" ) ), QMXException );

				break;
			}

			case 2:
			{
				ASSERT_THROW( StackTracer::RemoveThread(), QMXException );
				StackTracer::SetThreadID( "" );
				ASSERT_THROW( StackTracer::RemoveThread(), QMXException );
				StackTracer::SetThreadID( TargetID );
				ASSERT_THROW( StackTracer::RemoveThread(), QMXException );
				StackTracer::AddThread( ( TargetID + "Main" ) );
				StackTracer::RemoveThread();

				break;
			}

			case 3:
			{
				ASSERT_THROW( StackTracer::Push( "Class::Method" ), QMXException );
				StackTracer::SetThreadID( "" );
				ASSERT_THROW( StackTracer::Push( "Class::Method" ), QMXException );
				StackTracer::SetThreadID( TargetID );
				ASSERT_THROW( StackTracer::Push( "Class::Method" ), QMXException );
				StackTracer::AddThread( ( TargetID + "Main" ) );
				StackTracer::Push( "Class::Method" );

				break;
			}

			case 4:
			{
				ASSERT_THROW( StackTracer::Pop(), QMXException );
				StackTracer::SetThreadID( "" );
				ASSERT_THROW( StackTracer::Pop(), QMXException );
				StackTracer::SetThreadID( TargetID );
				ASSERT_THROW( StackTracer::Pop(), QMXException );
				StackTracer::AddThread( ( TargetID + "Main" ) );
				StackTracer::Pop();

				break;
			}

			case 5:
			{
				ASSERT_THROW( StackTracer::GetStackTrace(), QMXException );
				StackTracer::SetThreadID( "" );
				ASSERT_THROW( StackTracer::GetStackTrace(), QMXException );
				StackTracer::SetThreadID( TargetID );
				ASSERT_THROW( StackTracer::GetStackTrace(), QMXException );
				StackTracer::AddThread( ( TargetID + "Main" ) );
				ASSERT_EQ( ( TargetID + "Main" ), StackTracer::GetStackTrace() );
				StackTracer::Push( "Class::Method" );
				ASSERT_EQ( ( TargetID + "Main" + Seperator + "Class::Method" ), StackTracer::GetStackTrace() );
				StackTracer::Pop();
				StackTracer::Pop();
				ASSERT_EQ( ( TargetID + "Main" ), StackTracer::GetStackTrace() );

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

		boost::thread_group Threads;

	// Perform unit test for 'ThreadID' methods.

		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadA", 0 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadB", 0 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadC", 0 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadD", 0 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadE", 0 ) ) );
		Threads.join_all();
}

TEST( StackTracerTest, AddThreadWorks )
{
	// Create local variables.

		boost::thread_group Threads;

	// Prepare stack tracer for testing.

		StackTracer::SetEnabled( true );

	// Perform unit test for 'ThreadID' methods.

		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadA", 1 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadB", 1 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadC", 1 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadD", 1 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadE", 1 ) ) );
		Threads.join_all();

	// Cleanup stack tracer.

		StackTracer::Reset();
}

TEST( StackTracerTest, RemoveThreadWorks )
{
	// Create local variables.

		boost::thread_group Threads;

	// Prepare stack tracer for testing.

		StackTracer::SetEnabled( true );

	// Perform unit test for 'ThreadID' methods.

		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadA", 2 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadB", 2 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadC", 2 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadD", 2 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadE", 2 ) ) );
		Threads.join_all();

	// Cleanup stack tracer.

		StackTracer::Reset();
}

TEST( StackTracerTest, PushWorks )
{
	// Create local variables.

		boost::thread_group Threads;

	// Prepare stack tracer for testing.

		StackTracer::SetEnabled( true );

	// Perform unit test for 'ThreadID' methods.

		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadA", 3 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadB", 3 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadC", 3 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadD", 3 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadE", 3 ) ) );
		Threads.join_all();

	// Cleanup stack tracer.

		StackTracer::Reset();
}

TEST( StackTracerTest, PopWorks )
{
	// Create local variables.

		boost::thread_group Threads;

	// Prepare stack tracer for testing.

		StackTracer::SetEnabled( true );

	// Perform unit test for 'ThreadID' methods.

		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadA", 4 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadB", 4 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadC", 4 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadD", 4 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadE", 4 ) ) );
		Threads.join_all();

	// Cleanup stack tracer.

		StackTracer::Reset();
}

TEST( StackTracerTest, GetStackTraceWorks )
{
	// Create local variables.

		boost::thread_group Threads;

	// Prepare stack tracer for testing.

		StackTracer::SetEnabled( true );

	// Perform unit test for 'ThreadID' methods.

		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadA", 5 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadB", 5 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadC", 5 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadD", 5 ) ) );
		Threads.add_thread( ( new boost::thread( StackTracerTest::ThreadMain, "ThreadE", 5 ) ) );
		Threads.join_all();

	// Cleanup stack tracer.

		StackTracer::Reset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'StackTracerTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

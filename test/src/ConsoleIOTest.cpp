////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ConsoleIOTest.cpp
// Robert M. Baker | Created : 30JAN12 | Last Modified : 29JAN16 by Robert M. Baker
// Version : 1.1.0
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::ConsoleIO' class.
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

#include <ConsoleIOTest.hpp>

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'ConsoleIOTest' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ConsoleIOTest
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Definitions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ThreadMain( ConsoleIO::StreamType TargetType )
{
	// Output test data using the specified stream type.

		ConsoleIO::SynchronizedStream( TargetType ) << 'T' << 'e' << 's' << 't' << 'i' << 'n' << 'g' << ' ' << '1' << '2' << '3' << '4' << '5' << '\n';
}

} // 'ConsoleIOTest' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'ConsoleIOTest' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::ConsoleIO' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( ConsoleIOTest, SynchronizedStreamWorks )
{
	// Create local variables.

		ostream* Streams[] = { &cout, &cerr, &clog };
		streambuf* BufferBackups[] = { cout.rdbuf(), cerr.rdbuf(), clog.rdbuf() };
		ostringstream Buffers[ ConsoleIO::StreamType::StreamCount ];
		string ExpectedOutput;
		boost::thread_group Threads;
		size_t ThreadCount = 10;

	// Change stream buffers for output streams to output buffer streams.

		for( size_t Index = 0; Index < ARRAY_SIZE( Streams ); Index++ )
			Streams[ Index ]->rdbuf( Buffers[ Index ].rdbuf() );

	// Perform unit test for 'SynchronizedStream' class.

		for( size_t IndexA = 0; IndexA < ARRAY_SIZE( Streams ); IndexA++ )
		{
			for( size_t IndexB = 0; IndexB < ThreadCount; IndexB++ )
			{
				ExpectedOutput += "Testing 12345\n";
				Threads.add_thread( ( new boost::thread( ConsoleIOTest::ThreadMain, static_cast< ConsoleIO::StreamType >( IndexA ) ) ) );
			}

			Threads.join_all();
			ASSERT_EQ( ExpectedOutput, Buffers[ IndexA ].str() );
			ExpectedOutput = "";
		}

	// Restore stream buffers for output streams.

		for( size_t Index = 0; Index < ARRAY_SIZE( Streams ); Index++ )
			Streams[ Index ]->rdbuf( BufferBackups[ Index ] );
}

TEST( ConsoleIOTest, GetInputMinimumWorks )
{
	// Create local variables.

		real_t Result = Null;
		streambuf* BufferBackups[] = { cin.rdbuf(), cout.rdbuf() };
		istringstream InputBuffer;
		ostringstream OutputBuffer;
		ostringstream ResultBuffer;
		real_t TestInput[] = { 53.5477, -6.372, 43.17, -45.6, 73.0 };
		real_t TestArguments[] = { 10.8676, -39.494, 4.09, -88.9, 32.0 };
		real_t ExpectedOutput[] = { 53.5477, -6.372, 43.17, -45.6, 73.0 };

	// Change stream buffers for input/output streams to input/output buffer streams.

		cin.rdbuf( InputBuffer.rdbuf() );
		cout.rdbuf( OutputBuffer.rdbuf() );

	// Perform unit test for 'GetInput' method using 'Minimum' mode.

		for( size_t Index = 0; Index < ARRAY_SIZE( TestInput ); Index++ )
		{
			SET_TEST_DATA( TestInput[ Index ] );
			Result = ConsoleIO::GetInput< real_t >( TestArguments[ Index ], Null, ConsoleIO::Minimum );
			ASSERT_DOUBLE_EQ( ExpectedOutput[ Index ], Result );
		}

	// Restore stream buffers for input/output streams.

		cin.rdbuf( BufferBackups[ 0 ] );
		cout.rdbuf( BufferBackups[ 1 ] );
}

TEST( ConsoleIOTest, GetInputMaximumWorks )
{
	// Create local variables.

		real_t Result = Null;
		streambuf* BufferBackups[] = { cin.rdbuf(), cout.rdbuf() };
		istringstream InputBuffer;
		ostringstream OutputBuffer;
		ostringstream ResultBuffer;
		real_t TestInput[] = { 10.8676, -39.494, 4.09, -88.9, 32.0 };
		real_t TestArguments[] = { 53.5477, -6.372, 43.17, -45.6, 73.0 };
		real_t ExpectedOutput[] = { 10.8676, -39.494, 4.09, -88.9, 32.0 };

	// Change stream buffers for input/output streams to input/output buffer streams.

		cin.rdbuf( InputBuffer.rdbuf() );
		cout.rdbuf( OutputBuffer.rdbuf() );

	// Perform unit test for 'GetInput' method using 'Maximum' mode.

		for( size_t Index = 0; Index < ARRAY_SIZE( TestInput ); Index++ )
		{
			SET_TEST_DATA( TestInput[ Index ] );
			Result = ConsoleIO::GetInput< real_t >( Null, TestArguments[ Index ], ConsoleIO::Maximum );
			ASSERT_DOUBLE_EQ( ExpectedOutput[ Index ], Result );
		}

	// Restore stream buffers for input/output streams.

		cin.rdbuf( BufferBackups[ 0 ] );
		cout.rdbuf( BufferBackups[ 1 ] );
}

TEST( ConsoleIOTest, GetInputRangeWorks )
{
	// Create local variables.

		real_t Result = Null;
		streambuf* BufferBackups[] = { cin.rdbuf(), cout.rdbuf() };
		istringstream InputBuffer;
		ostringstream OutputBuffer;
		ostringstream ResultBuffer;
		real_t TestInput[] = { 53.5477, -6.372, 43.17, -45.6, 73.0 };
		real_t TestMinArguments[] = { 28.5477, -31.372, 18.17, -70.6, 48.0 };
		real_t TestMaxArguments[] = { 78.5477, 18.628, 68.17, -20.6, 98.0 };
		real_t ExpectedOutput[] = { 53.5477, -6.372, 43.17, -45.6, 73.0 };

	// Change stream buffers for input/output streams to input/output buffer streams.

		cin.rdbuf( InputBuffer.rdbuf() );
		cout.rdbuf( OutputBuffer.rdbuf() );

	// Perform unit test for 'GetInput' method using 'Range' mode.

		for( size_t Index = 0; Index < ARRAY_SIZE( TestInput ); Index++ )
		{
			SET_TEST_DATA( TestInput[ Index ] );
			Result = ConsoleIO::GetInput< real_t >( TestMinArguments[ Index ], TestMaxArguments[ Index ] );
			ASSERT_DOUBLE_EQ( ExpectedOutput[ Index ], Result );
		}

	// Restore stream buffers for input/output streams.

		cin.rdbuf( BufferBackups[ 0 ] );
		cout.rdbuf( BufferBackups[ 1 ] );
}

TEST( ConsoleIOTest, GetInputTwoChoiceWorks )
{
	// Create local variables.

		char Result = Null;
		streambuf* BufferBackups[] = { cin.rdbuf(), cout.rdbuf() };
		istringstream InputBuffer;
		ostringstream OutputBuffer;
		ostringstream ResultBuffer;
		char TestInput[] = { 'Y', 'F', 'A', 'D', 'X' };
		char TestChoice1Arguments[] = { 'Y', 'T', 'A', 'C', 'X'};
		char TestChoice2Arguments[] = { 'N', 'F', 'B', 'D', 'Y' };
		char ExpectedOutput[] = { 'Y', 'F', 'A', 'D', 'X' };

	// Change stream buffers for input/output streams to input/output buffer streams.

		cin.rdbuf( InputBuffer.rdbuf() );
		cout.rdbuf( OutputBuffer.rdbuf() );

	// Perform unit test for 'GetInput' method using 'TwoChoice' mode.

		for( size_t Index = 0; Index < ARRAY_SIZE( TestInput ); Index++ )
		{
			SET_TEST_DATA( TestInput[ Index ] );
			Result = ConsoleIO::GetInput< char >( TestChoice1Arguments[ Index ], TestChoice2Arguments[ Index ], ConsoleIO::TwoChoice );
			ASSERT_EQ( ExpectedOutput[ Index ], Result );
		}

	// Restore stream buffers for input/output streams.

		cin.rdbuf( BufferBackups[ 0 ] );
		cout.rdbuf( BufferBackups[ 1 ] );
}

TEST( ConsoleIOTest, GetInputMultipleChoiceWorks )
{
	// Create local variables.

		char Result = Null;
		streambuf* BufferBackups[] = { cin.rdbuf(), cout.rdbuf() };
		istringstream InputBuffer;
		ostringstream OutputBuffer;
		ostringstream ResultBuffer;
		char TestInput[] = { 'A', 'G', 'M', 'S', 'Y' };
		string TestArguments[] = { "A, B, C, D, or E",
		                           "F, G, H, I, or J",
		                           "K, L, M, N, or O",
		                           "P, Q, R, S, or T",
		                           "U, V, W, X, or Y" };
		char ExpectedOutput[] = { 'A', 'G', 'M', 'S', 'Y' };

	// Change stream buffers for input/output streams to input/output buffer streams.

		cin.rdbuf( InputBuffer.rdbuf() );
		cout.rdbuf( OutputBuffer.rdbuf() );

	// Perform unit test for 'GetInput' method using 'MultipleChoice' mode.

		for( size_t Index = 0; Index < ARRAY_SIZE( TestInput ); Index++ )
		{
			SET_TEST_DATA( TestInput[ Index ] );
			Result = ConsoleIO::GetInput< char >( Null, Null, ConsoleIO::MultipleChoice, TestArguments[ Index ] );
			ASSERT_EQ( ExpectedOutput[ Index ], Result );
		}

	// Restore stream buffers for input/output streams.

		cin.rdbuf( BufferBackups[ 0 ] );
		cout.rdbuf( BufferBackups[ 1 ] );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ConsoleIOTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

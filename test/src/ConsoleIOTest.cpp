////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ConsoleIOTest.cpp
// Robert M. Baker | Created : 30JAN12 | Last Modified : 31AUG19 by Robert M. Baker
// Version : 2.2.1
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::ConsoleIO' class.
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

#include "../include/ConsoleIOTest.hpp"

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

void threadMain( ConsoleIO::StreamType targetType )
{
	// Output test data using the specified stream type.

		ConsoleIO::SynchronizedStream( targetType ) << 'T' << 'e' << 's' << 't' << 'i' << 'n' << 'g' << ' ' << '1' << '2' << '3' << '4' << '5' << '\n';
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

		string expectedOutput;

		ostream* stream[] = {
			&cout,
			&cerr,
			&clog
		};

		streambuf* bufferBackups[] = {
			cout.rdbuf(),
			cerr.rdbuf(),
			clog.rdbuf()
		};

		ostringstream buffers[ ConsoleIO::StreamType::STREAM_COUNT ];
		boost::thread_group threads;
		size_t threadCount = 10;

	// Change stream buffers for output streams to output buffer streams.

		for( size_t index = 0; index < ARRAY_SIZE( stream ); index++ )
			stream[ index ]->rdbuf( buffers[ index ].rdbuf() );

	// Perform unit test for 'SynchronizedStream' class.

		for( size_t indexA = 0; indexA < ARRAY_SIZE( stream ); indexA++ )
		{
			for( size_t indexB = 0; indexB < threadCount; indexB++ )
			{
				expectedOutput += "Testing 12345\n";
				threads.add_thread( ( new boost::thread( ConsoleIOTest::threadMain, static_cast< ConsoleIO::StreamType >( indexA ) ) ) );
			}

			threads.join_all();
			ASSERT_EQ( expectedOutput, buffers[ indexA ].str() );
			expectedOutput = "";
		}

	// Restore stream buffers for output streams.

		for( size_t index = 0; index < ARRAY_SIZE( stream ); index++ )
			stream[ index ]->rdbuf( bufferBackups[ index ] );
}

TEST( ConsoleIOTest, GetInputMinimumWorks )
{
	// Create local variables.

		real_t testInput[] = {
			53.5477,
			-6.372,
			43.17,
			-45.6,
			73.0
		};

		real_t testArguments[] = {
			10.8676,
			-39.494,
			4.09,
			-88.9,
			32.0
		};

		real_t expectedOutput[] = {
			53.5477,
			-6.372,
			43.17,
			-45.6, 73.0
		};

		streambuf* bufferBackups[] = {
			cin.rdbuf(),
			cout.rdbuf()
		};

		real_t result = UNSET;
		istringstream inputBuffer;
		ostringstream outputBuffer;
		ostringstream resultBuffer;

	// Change stream buffers for input/output streams to input/output buffer streams.

		cin.rdbuf( inputBuffer.rdbuf() );
		cout.rdbuf( outputBuffer.rdbuf() );

	// Perform unit test for 'getInput' method using 'MINIMUM' mode.

		for( size_t index = 0; index < ARRAY_SIZE( testInput ); index++ )
		{
			SET_TEST_DATA( testInput[ index ] );
			result = ConsoleIO::getInput< real_t >( testArguments[ index ], UNSET, ConsoleIO::MINIMUM );
			ASSERT_DOUBLE_EQ( expectedOutput[ index ], result );
		}

	// Restore stream buffers for input/output streams.

		cin.rdbuf( bufferBackups[ 0 ] );
		cout.rdbuf( bufferBackups[ 1 ] );
}

TEST( ConsoleIOTest, GetInputMaximumWorks )
{
	// Create local variables.

		real_t testInput[] = {
			10.8676,
			-39.494,
			4.09,
			-88.9,
			32.0
		};

		real_t testArguments[] = {
			53.5477,
			-6.372,
			43.17,
			-45.6,
			73.0
		};

		real_t expectedOutput[] = {
			10.8676,
			-39.494,
			4.09,
			-88.9,
			32.0
		};

		streambuf* bufferBackups[] = {
			cin.rdbuf(),
			cout.rdbuf()
		};

		real_t result = UNSET;
		istringstream inputBuffer;
		ostringstream outputBuffer;
		ostringstream resultBuffer;

	// Change stream buffers for input/output streams to input/output buffer streams.

		cin.rdbuf( inputBuffer.rdbuf() );
		cout.rdbuf( outputBuffer.rdbuf() );

	// Perform unit test for 'getInput' method using 'MAXIMUM' mode.

		for( size_t index = 0; index < ARRAY_SIZE( testInput ); index++ )
		{
			SET_TEST_DATA( testInput[ index ] );
			result = ConsoleIO::getInput< real_t >( UNSET, testArguments[ index ], ConsoleIO::MAXIMUM );
			ASSERT_DOUBLE_EQ( expectedOutput[ index ], result );
		}

	// Restore stream buffers for input/output streams.

		cin.rdbuf( bufferBackups[ 0 ] );
		cout.rdbuf( bufferBackups[ 1 ] );
}

TEST( ConsoleIOTest, GetInputRangeWorks )
{
	// Create local variables.

		real_t testInput[] = {
			53.5477,
			-6.372,
			43.17,
			-45.6,
			73.0
		};

		real_t testMinArguments[] = {
			28.5477,
			-31.372,
			18.17,
			-70.6,
			48.0
		};

		real_t testMaxArguments[] = {
			78.5477,
			18.628,
			68.17,
			-20.6,
			98.0
		};

		real_t expectedOutput[] = {
			53.5477,
			-6.372,
			43.17,
			-45.6,
			73.0
		};

		streambuf* bufferBackups[] = {
			cin.rdbuf(),
			cout.rdbuf()
		};

		real_t result = UNSET;
		istringstream inputBuffer;
		ostringstream outputBuffer;
		ostringstream resultBuffer;

	// Change stream buffers for input/output streams to input/output buffer streams.

		cin.rdbuf( inputBuffer.rdbuf() );
		cout.rdbuf( outputBuffer.rdbuf() );

	// Perform unit test for 'getInput' method using 'RANGE' mode.

		for( size_t index = 0; index < ARRAY_SIZE( testInput ); index++ )
		{
			SET_TEST_DATA( testInput[ index ] );
			result = ConsoleIO::getInput< real_t >( testMinArguments[ index ], testMaxArguments[ index ] );
			ASSERT_DOUBLE_EQ( expectedOutput[ index ], result );
		}

	// Restore stream buffers for input/output streams.

		cin.rdbuf( bufferBackups[ 0 ] );
		cout.rdbuf( bufferBackups[ 1 ] );
}

TEST( ConsoleIOTest, GetInputTwoChoiceWorks )
{
	// Create local variables.

		char testInput[] = {
			'Y',
			'F',
			'A',
			'D',
			'X'
		};

		char testChoice1Arguments[] = {
			'Y',
			'T',
			'A',
			'C',
			'X'
		};

		char testChoice2Arguments[] = {
			'N',
			'F',
			'B',
			'D',
			'Y'
		};

		char expectedOutput[] = {
			'Y',
			'F',
			'A',
			'D',
			'X'
		};

		streambuf* bufferBackups[] = {
			cin.rdbuf(),
			cout.rdbuf()
		};

		char result = UNSET;
		istringstream inputBuffer;
		ostringstream outputBuffer;
		ostringstream resultBuffer;

	// Change stream buffers for input/output streams to input/output buffer streams.

		cin.rdbuf( inputBuffer.rdbuf() );
		cout.rdbuf( outputBuffer.rdbuf() );

	// Perform unit test for 'getInput' method using 'TWO_CHOICE' mode.

		for( size_t index = 0; index < ARRAY_SIZE( testInput ); index++ )
		{
			SET_TEST_DATA( testInput[ index ] );
			result = ConsoleIO::getInput< char >( testChoice1Arguments[ index ], testChoice2Arguments[ index ], ConsoleIO::TWO_CHOICE );
			ASSERT_EQ( expectedOutput[ index ], result );
		}

	// Restore stream buffers for input/output streams.

		cin.rdbuf( bufferBackups[ 0 ] );
		cout.rdbuf( bufferBackups[ 1 ] );
}

TEST( ConsoleIOTest, GetInputMultipleChoiceWorks )
{
	// Create local variables.

		char testInput[] = {
			'A',
			'G',
			'M',
			'S',
			'Y'
		};

		string testArguments[] = {
			"A, B, C, D, or E",
			"F, G, H, I, or J",
			"K, L, M, N, or O",
			"P, Q, R, S, or T",
			"U, V, W, X, or Y"
		};

		char expectedOutput[] = {
			'A',
			'G',
			'M',
			'S',
			'Y'
		};

		streambuf* bufferBackups[] = {
			cin.rdbuf(),
			cout.rdbuf()
		};

		char result = UNSET;
		istringstream inputBuffer;
		ostringstream outputBuffer;
		ostringstream resultBuffer;

	// Change stream buffers for input/output streams to input/output buffer streams.

		cin.rdbuf( inputBuffer.rdbuf() );
		cout.rdbuf( outputBuffer.rdbuf() );

	// Perform unit test for 'getInput' method using 'MULTIPLE_CHOICE' mode.

		for( size_t index = 0; index < ARRAY_SIZE( testInput ); index++ )
		{
			SET_TEST_DATA( testInput[ index ] );
			result = ConsoleIO::getInput< char >( UNSET, UNSET, ConsoleIO::MULTIPLE_CHOICE, testArguments[ index ] );
			ASSERT_EQ( expectedOutput[ index ], result );
		}

	// Restore stream buffers for input/output streams.

		cin.rdbuf( bufferBackups[ 0 ] );
		cout.rdbuf( bufferBackups[ 1 ] );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ConsoleIOTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

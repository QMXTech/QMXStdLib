////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NumericTest.cpp
// Robert M. Baker | Created : 10FEB12 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.1.0
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::Numeric' functions.
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

#include "../include/NumericTest.hpp"

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::Numeric' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( NumericTest, InRangeWorks )
{
	// Create local variables.

		int64_t testValuesI[] = {
			27,
			30,
			2,
			41,
			19
		};

		real_t testValuesF[] = {
			27.1416,
			30.142,
			2.14,
			41.1,
			19.0
		};

		int64_t testMinArgumentsI[] = {
			17,
			40,
			-8,
			51,
			9
		};

		real_t testMinArgumentsF[] = {
			17.1416,
			40.142,
			-7.86,
			51.1,
			9.0
		};

		int64_t testMaxArgumentsI[] = {
			37,
			50,
			12,
			61,
			29
		};

		real_t testMaxArgumentsF[] = {
			37.1416,
			50.142,
			12.14,
			61.1,
			29.0
		};

		bool expectedResultsI[] = {
			true,
			false,
			true,
			false,
			true
		};

		bool expectedResultsF[] = {
			true,
			false,
			true,
			false,
			true
		};

	// Perform unit test for 'inRange' function.

		for( size_t index = 0; index < ARRAY_SIZE( testValuesI ); index++ )
		{
			ASSERT_EQ( expectedResultsI[ index ], Numeric::inRange< int64_t >( testValuesI[ index ], testMinArgumentsI[ index ], testMaxArgumentsI[ index ] ) );
			ASSERT_EQ( expectedResultsF[ index ], Numeric::inRange< real_t >( testValuesF[ index ], testMinArgumentsF[ index ], testMaxArgumentsF[ index ] ) );
		}
}

TEST( NumericTest, ClampWorks )
{
	// Create local variables.

		int64_t testValuesI[] = {
			27,
			30,
			2,
			71,
			19
		};

		real_t testValuesF[] = {
			27.1416,
			30.142,
			2.14,
			71.1,
			19.0
		};

		int64_t testMinArgumentsI[] = {
			17,
			40,
			-8,
			51,
			9
		};

		real_t testMinArgumentsF[] = {
			17.1416,
			40.142,
			-7.86,
			51.1,
			9.0
		};

		int64_t testMaxArgumentsI[] = {
			37,
			50,
			12,
			61,
			29
		};

		real_t testMaxArgumentsF[] = {
			37.1416,
			50.142,
			12.14,
			61.1,
			29.0
		};

		int64_t expectedResultsI[] = {
			27,
			40,
			2,
			61,
			19
		};

		real_t expectedResultsF[] = {
			27.1416,
			40.142,
			2.14,
			61.1,
			19.0
		};

	// Perform unit test for 'clamp' function.

		for( size_t index = 0; index < ARRAY_SIZE( testValuesI ); index++ )
		{
			Numeric::clamp< int64_t >( testValuesI[ index ], testMinArgumentsI[ index ], testMaxArgumentsI[ index ] );
			ASSERT_EQ( expectedResultsI[ index ], testValuesI[ index ] );
			Numeric::clamp< real_t >( testValuesF[ index ], testMinArgumentsF[ index ], testMaxArgumentsF[ index ] );
			ASSERT_EQ( expectedResultsF[ index ], testValuesF[ index ] );
		}
}

TEST( NumericTest, WrapWorks )
{
	// Create local variables.

		int64_t testValuesI[] = {
			27,
			30,
			2,
			71,
			19
		};

		real_t testValuesF[] = {
			27.1416,
			30.142,
			2.14,
			71.1,
			19.0
		};

		int64_t testMinArgumentsI[] = {
			17,
			40,
			-8,
			51,
			9
		};

		real_t testMinArgumentsF[] = {
			17.1416,
			40.142,
			-7.86,
			51.1,
			9.0
		};

		int64_t testMaxArgumentsI[] = {
			37,
			50,
			12,
			61,
			29
		};

		real_t testMaxArgumentsF[] = {
			37.1416,
			50.142,
			12.14,
			61.1, 29.0
		};

		int64_t expectedResultsI[] = {
			27,
			50,
			2,
			51,
			19
		};

		real_t expectedResultsF[] = {
			27.1416,
			50.142,
			2.14,
			51.1,
			19.0
		};

	// Perform unit test for 'wrap' function.

		for( size_t index = 0; index < ARRAY_SIZE( testValuesI ); index++ )
		{
			Numeric::wrap< int64_t >( testValuesI[ index ], testMinArgumentsI[ index ], testMaxArgumentsI[ index ] );
			ASSERT_EQ( expectedResultsI[ index ], testValuesI[ index ] );
			Numeric::wrap< real_t >( testValuesF[ index ], testMinArgumentsF[ index ], testMaxArgumentsF[ index ] );
			ASSERT_EQ( expectedResultsF[ index ], testValuesF[ index ] );
		}
}

TEST( NumericTest, IsWholeNumberWorks )
{
	// Create local variables.

		real_t testValues[] = {
			27.0,
			30.142,
			2.0,
			41.1,
			19.0
		};

		bool expectedResults[] = {
			true,
			false,
			true,
			false,
			true
		};

	// Perform unit test for 'isWholeNumber' function.

		for( size_t index = 0; index < ARRAY_SIZE( testValues ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], Numeric::isWholeNumber< real_t >( testValues[ index ] ) );
		}
}

TEST( NumericTest, GetNextPowerOfTwoWorks )
{
	// Perform unit test for 'getNextPowerOfTwo' function.

		ASSERT_EQ( 1u, Numeric::getNextPowerOfTwo< uint64_t >( 1 ) );
		ASSERT_EQ( 4u, Numeric::getNextPowerOfTwo< uint64_t >( 3 ) );
		ASSERT_EQ( 32u, Numeric::getNextPowerOfTwo< uint64_t >( 27 ) );
		ASSERT_EQ( 64u, Numeric::getNextPowerOfTwo< uint64_t >( 33 ) );
		ASSERT_EQ( 256u, Numeric::getNextPowerOfTwo< uint64_t >( 212 ) );
		ASSERT_EQ( 512u, Numeric::getNextPowerOfTwo< uint64_t >( 301 ) );
		ASSERT_EQ( 1024u, Numeric::getNextPowerOfTwo< uint64_t >( 768 ) );
		ASSERT_EQ( 65536u, Numeric::getNextPowerOfTwo< uint64_t >( 65535 ) );
		ASSERT_EQ( 131072u, Numeric::getNextPowerOfTwo< uint64_t >( 104215 ) );
		ASSERT_EQ( 524288u, Numeric::getNextPowerOfTwo< uint64_t >( 265784 ) );
}

TEST( NumericTest, ToStringWorks )
{
	// Create local variables.

		Stringizable::StringFormat format;

	// Perform unit test for 'toString' function.

		ASSERT_THROW( Numeric::toString< int >( 1337, Stringizable::NONE ), QMXException );
		ASSERT_EQ( string( "0b11010100" ), Numeric::toString< uint8_t >( 212, Stringizable::BINARY ) );
		ASSERT_EQ( string( "0324" ), Numeric::toString< uint64_t >( 212, Stringizable::OCTAL ) );
		ASSERT_EQ( string( "3.14159" ), Numeric::toString< real_t >( 3.14159 ) );
		ASSERT_EQ( string( "0x00000000DEADBEEF" ), Numeric::toString< uint64_t >( 3735928559u, Stringizable::HEXIDECIMAL ) );
		Stringizable::setStringFormat( format, Stringizable::BINARY );
		ASSERT_EQ( string( "0b11010100" ), Numeric::toString< uint8_t >( 212, Stringizable::NONE, &format ) );
		Stringizable::setStringFormat( format, Stringizable::OCTAL );
		ASSERT_EQ( string( "0324" ), Numeric::toString< uint64_t >( 212, Stringizable::NONE, &format ) );
		Stringizable::setStringFormat( format, Stringizable::DECIMAL );
		ASSERT_EQ( string( "3.14159" ), Numeric::toString< real_t >( 3.14159, Stringizable::NONE, &format ) );
		Stringizable::setStringFormat( format, Stringizable::HEXIDECIMAL );
		ASSERT_EQ( string( "0x00000000DEADBEEF" ), Numeric::toString< uint64_t >( 3735928559u, Stringizable::NONE, &format ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'NumericTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

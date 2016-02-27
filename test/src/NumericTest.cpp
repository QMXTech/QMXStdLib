////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NumericTest.cpp
// Robert M. Baker | Created : 10FEB12 | Last Modified : 14FEB16 by Robert M. Baker
// Version : 1.1.0
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::Numeric' functions.
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

#include <NumericTest.hpp>

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::Numeric' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( NumericTest, InRangeWorks )
{
	// Create local variables.

		int64_t TestValuesI[] = { 27, 30, 2, 41, 19 };
		real_t TestValuesF[] = { 27.1416, 30.142, 2.14, 41.1, 19.0 };
		int64_t TestMinArgumentsI[] = { 17, 40, -8, 51, 9 };
		real_t TestMinArgumentsF[] = { 17.1416, 40.142, -7.86, 51.1, 9.0 };
		int64_t TestMaxArgumentsI[] = { 37, 50, 12, 61, 29 };
		real_t TestMaxArgumentsF[] = { 37.1416, 50.142, 12.14, 61.1, 29.0 };
		bool ExpectedResultsI[] = { true, false, true, false, true };
		bool ExpectedResultsF[] = { true, false, true, false, true };

	// Perform unit test for 'InRange' function.

		for( size_t Index = 0; Index < ARRAY_SIZE( TestValuesI ); Index++ )
		{
			ASSERT_EQ( ExpectedResultsI[ Index ], Numeric::InRange< int64_t >( TestValuesI[ Index ], TestMinArgumentsI[ Index ], TestMaxArgumentsI[ Index ] ) );
			ASSERT_EQ( ExpectedResultsF[ Index ], Numeric::InRange< real_t >( TestValuesF[ Index ], TestMinArgumentsF[ Index ], TestMaxArgumentsF[ Index ] ) );
		}
}

TEST( NumericTest, ClampWorks )
{
	// Create local variables.

		int64_t TestValuesI[] = { 27, 30, 2, 71, 19 };
		real_t TestValuesF[] = { 27.1416, 30.142, 2.14, 71.1, 19.0 };
		int64_t TestMinArgumentsI[] = { 17, 40, -8, 51, 9 };
		real_t TestMinArgumentsF[] = { 17.1416, 40.142, -7.86, 51.1, 9.0 };
		int64_t TestMaxArgumentsI[] = { 37, 50, 12, 61, 29 };
		real_t TestMaxArgumentsF[] = { 37.1416, 50.142, 12.14, 61.1, 29.0 };
		int64_t ExpectedResultsI[] = { 27, 40, 2, 61, 19 };
		real_t ExpectedResultsF[] = { 27.1416, 40.142, 2.14, 61.1, 19.0 };

	// Perform unit test for 'Clamp' function.

		for( size_t Index = 0; Index < ARRAY_SIZE( TestValuesI ); Index++ )
		{
			Numeric::Clamp< int64_t >( TestValuesI[ Index ], TestMinArgumentsI[ Index ], TestMaxArgumentsI[ Index ] );
			ASSERT_EQ( ExpectedResultsI[ Index ], TestValuesI[ Index ] );
			Numeric::Clamp< real_t >( TestValuesF[ Index ], TestMinArgumentsF[ Index ], TestMaxArgumentsF[ Index ] );
			ASSERT_EQ( ExpectedResultsF[ Index ], TestValuesF[ Index ] );
		}
}

TEST( NumericTest, IsWholeNumberWorks )
{
	// Create local variables.

		real_t TestValues[] = { 27.0, 30.142, 2.0, 41.1, 19.0 };
		bool ExpectedResults[] = { true, false, true, false, true };

	// Perform unit test for 'IsWholeNumber' function.

		for( size_t Index = 0; Index < ARRAY_SIZE( TestValues ); Index++ )
		{
			ASSERT_EQ( ExpectedResults[ Index ], Numeric::IsWholeNumber< real_t >( TestValues[ Index ] ) );
		}
}

TEST( NumericTest, GetNextPowerOfTwoWorks )
{
	// Perform unit test for 'GetNextPowerOfTwo' function.

		ASSERT_EQ( 1u, Numeric::GetNextPowerOfTwo< uint64_t >( 1 ) );
		ASSERT_EQ( 4u, Numeric::GetNextPowerOfTwo< uint64_t >( 3 ) );
		ASSERT_EQ( 32u, Numeric::GetNextPowerOfTwo< uint64_t >( 27 ) );
		ASSERT_EQ( 64u, Numeric::GetNextPowerOfTwo< uint64_t >( 33 ) );
		ASSERT_EQ( 256u, Numeric::GetNextPowerOfTwo< uint64_t >( 212 ) );
		ASSERT_EQ( 512u, Numeric::GetNextPowerOfTwo< uint64_t >( 301 ) );
		ASSERT_EQ( 1024u, Numeric::GetNextPowerOfTwo< uint64_t >( 768 ) );
		ASSERT_EQ( 65536u, Numeric::GetNextPowerOfTwo< uint64_t >( 65535 ) );
		ASSERT_EQ( 131072u, Numeric::GetNextPowerOfTwo< uint64_t >( 104215 ) );
		ASSERT_EQ( 524288u, Numeric::GetNextPowerOfTwo< uint64_t >( 265784 ) );
}

TEST( NumericTest, ToStringWorks )
{
	// Create local variables.

		Stringizable::StringFormat Format;

	// Perform unit test for 'ToString' function.

		ASSERT_THROW( Numeric::ToString< int >( 1337, Stringizable::None ), QMXException );
		ASSERT_EQ( string( "0324" ), Numeric::ToString< uint64_t >( 212, Stringizable::Octal ) );
		ASSERT_EQ( string( "3.14159" ), Numeric::ToString< real_t >( 3.14159 ) );
		ASSERT_EQ( string( "0x00000000DEADBEEF" ), Numeric::ToString< uint64_t >( 3735928559u, Stringizable::Hexidecimal ) );
		Stringizable::SetStringFormat( Format, Stringizable::Octal );
		ASSERT_EQ( string( "0324" ), Numeric::ToString< uint64_t >( 212, Stringizable::None, &Format ) );
		Stringizable::SetStringFormat( Format, Stringizable::Decimal );
		ASSERT_EQ( string( "3.14159" ), Numeric::ToString< real_t >( 3.14159, Stringizable::None, &Format ) );
		Stringizable::SetStringFormat( Format, Stringizable::Hexidecimal );
		ASSERT_EQ( string( "0x00000000DEADBEEF" ), Numeric::ToString< uint64_t >( 3735928559u, Stringizable::None, &Format ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'NumericTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

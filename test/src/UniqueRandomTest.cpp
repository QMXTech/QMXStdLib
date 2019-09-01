////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UniqueRandomTest.cpp
// Robert M. Baker | Created : 10FEB12 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.1.0
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::UniqueRandom' functions.
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

#include "../include/UniqueRandomTest.hpp"

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'UniqueRandom' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( UniqueRandomTest, GenerateIntegralWorks )
{
	// Create local variables.

		Int64Vector result;
		set< int64_t > numbers;

	// Initialize random number generator using the current time for the seed.

		Utility::setRandomSeed();

	// Perform unit test for 'generate' function using integral values.

		UniqueRandom::generateInt< int64_t >( result, 10, 0, 100 );

		for( const auto& index : result )
			numbers.insert( index );

		ASSERT_EQ( 10u, numbers.size() );
}

TEST( UniqueRandomTest, GenerateFloatingPointWorks )
{
	// Create local variables.

		RealVector result;
		set< real_t > numbers;

	// Initialize random number generator using the current time for the seed.

		Utility::setRandomSeed();

	// Perform unit test for 'generate' function using floating point values.

		UniqueRandom::generateFloat< real_t >( result, 10, 0.0, 100.0 );

		for( const auto& index : result )
			numbers.insert( index );

		ASSERT_EQ( 10u, numbers.size() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'UniqueRandomTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

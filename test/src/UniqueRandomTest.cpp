////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UniqueRandomTest.cpp
// Robert M. Baker | Created : 10FEB12 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.1
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::UniqueRandom' class.
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

#include "../include/UniqueRandomTest.hpp"

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'UniqueRandom' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( UniqueRandomTest, GenerateIntegralWorks )
{
	// Create local variables.

		set< int64_t > Numbers;
		UniqueRandomI< int64_t >::PointerType Instance = UniqueRandomI< int64_t >::Create();

	// Initialize random number generator using the current time for the seed.

		Utility::SetRandomSeed();

	// Perform unit test for 'Generator' method using integral values.

		Instance->Generate( 10, 0, 100 );

		for( const auto& Index : Instance->GetNumbers() )
			Numbers.insert( Index );

		ASSERT_EQ( 10u, Numbers.size() );
}

TEST( UniqueRandomTest, GenerateFloatingPointWorks )
{
	// Create local variables.

		set< real_t > Numbers;
		UniqueRandomF< real_t >::PointerType Instance = UniqueRandomF< real_t >::Create();

	// Initialize random number generator using the current time for the seed.

		Utility::SetRandomSeed();

	// Perform unit test for 'Generator' method using floating point values.

		Instance->Generate( 10, 0.0, 100.0 );

		for( const auto& Index : Instance->GetNumbers() )
			Numbers.insert( Index );

		ASSERT_EQ( 10u, Numbers.size() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'UniqueRandomTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

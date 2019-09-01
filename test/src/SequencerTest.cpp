////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SequencerTest.cpp
// Robert M. Baker | Created : 29FEB12 | Last Modified : 31AUG19 by Robert M. Baker
// Version : 2.1.1
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::Sequencer' class.
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

#include "../include/SequencerTest.hpp"

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::Sequencer' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( SequencerTest, OperatorPostIncrementIntegralNonLoopedLinearWorks )
{
	// Create local variables.

		int64_t expectedResults[] = {
			0,
			1,
			2,
			3,
			4,
			4,
			4,
			4,
			4,
			4
		};

		Sequencer< int64_t >::InstancePtr instance = Sequencer< int64_t >::create();

	// Perform unit test for 'operator++( int )' method using integral values in 'LINEAR' mode with no looping.

		instance->set( { false, Sequencer< int64_t >::LINEAR, 0, 4, 1, 0 } );

		for( size_t index = 0; index < ARRAY_SIZE( expectedResults ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], instance->getValue() );
			(*instance)++;
		}
}

TEST( SequencerTest, OperatorPostIncrementIntegralNonLoopedOscillateWorks )
{
	// Create local variables.

		int64_t expectedResults[] = {
			0,
			1,
			2,
			3,
			4,
			3,
			2,
			1,
			0,
			0
		};

		Sequencer< int64_t >::InstancePtr instance = Sequencer< int64_t >::create();

	// Perform unit test for 'operator++( int )' method using integral values in 'OSCILLATE' mode with no looping.

		instance->set( { false, Sequencer< int64_t >::OSCILLATE, 0, 4, 1, 0 } );

		for( size_t index = 0; index < ARRAY_SIZE( expectedResults ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], instance->getValue() );
			(*instance)++;
		}
}

TEST( SequencerTest, OperatorPostIncrementIntegralLoopedLinearWorks )
{
	// Create local variables.

		int64_t expectedResults[] = {
			0,
			1,
			2,
			3,
			4,
			0,
			1,
			2,
			3,
			4
		};

		Sequencer< int64_t >::InstancePtr instance = Sequencer< int64_t >::create();

	// Perform unit test for 'operator++( int )' method using integral values in 'LINEAR' mode with looping.

		instance->set( { true, Sequencer< int64_t >::LINEAR, 0, 4, 1, 0 } );

		for( size_t index = 0; index < ARRAY_SIZE( expectedResults ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], instance->getValue() );
			(*instance)++;
		}
}

TEST( SequencerTest, OperatorPostIncrementIntegralLoopedOscillateWorks )
{
	// Create local variables.
	
		int64_t expectedResults[] = {
			0,
			1,
			2,
			3,
			4,
			3,
			2,
			1,
			0,
			1
		};

		Sequencer< int64_t >::InstancePtr instance = Sequencer< int64_t >::create();

	// Perform unit test for 'operator++( int )' method using integral values in 'OSCILLATE' mode with looping.

		instance->set( { true, Sequencer< int64_t >::OSCILLATE, 0, 4, 1, 0 } );

		for( size_t index = 0; index < ARRAY_SIZE( expectedResults ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], instance->getValue() );
			(*instance)++;
		}
}

TEST( SequencerTest, OperatorPostIncrementFloatingPointNonLoopedLinearWorks )
{
	// Create local variables.

		real_t expectedResults[] = {
			0.0,
			0.5,
			1.0,
			1.5,
			2.0,
			2.0,
			2.0,
			2.0,
			2.0,
			2.0
		};

		Sequencer< real_t >::InstancePtr instance = Sequencer< real_t >::create();

	// Perform unit test for 'operator++( int )' method using floating point values in 'LINEAR' mode with no looping.

		instance->set( { false, Sequencer< real_t >::LINEAR, 0.0, 2.0, 0.5, 0.0 } );

		for( size_t index = 0; index < ARRAY_SIZE( expectedResults ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], instance->getValue() );
			(*instance)++;
		}
}

TEST( SequencerTest, OperatorPostIncrementFloatingPointNonLoopedOscillateWorks )
{
	// Create local variables.

		real_t expectedResults[] = {
			0.0,
			0.5,
			1.0,
			1.5,
			2.0,
			1.5,
			1.0,
			0.5,
			0.0,
			0.0
		};

		Sequencer< real_t >::InstancePtr instance = Sequencer< real_t >::create();

	// Perform unit test for 'operator++( int )' method using floating point values in 'OSCILLATE' mode with no looping.

		instance->set( { false, Sequencer< real_t >::OSCILLATE, 0.0, 2.0, 0.5, 0.0 } );

		for( size_t index = 0; index < ARRAY_SIZE( expectedResults ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], instance->getValue() );
			(*instance)++;
		}
}

TEST( SequencerTest, OperatorPostIncrementFloatingPointLoopedLinearWorks )
{
	// Create local variables.

		real_t expectedResults[] = {
			0.0,
			0.5,
			1.0,
			1.5,
			2.0,
			0.0,
			0.5,
			1.0,
			1.5,
			2.0
		};

		Sequencer< real_t >::InstancePtr instance = Sequencer< real_t >::create();

	// Perform unit test for 'operator++( int )' method using floating point values in 'LINEAR' mode with looping.

		instance->set( { true, Sequencer< real_t >::LINEAR, 0.0, 2.0, 0.5, 0.0 } );

		for( size_t index = 0; index < ARRAY_SIZE( expectedResults ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], instance->getValue() );
			(*instance)++;
		}
}

TEST( SequencerTest, OperatorPostIncrementFloatingPointLoopedOscillateWorks )
{
	// Create local variables.

		real_t expectedResults[] = {
			0.0,
			0.5,
			1.0,
			1.5,
			2.0,
			1.5,
			1.0,
			0.5,
			0.0,
			0.5
		};

		Sequencer< real_t >::InstancePtr instance = Sequencer< real_t >::create();

	// Perform unit test for 'operator++( int )' method using floating point values in 'OSCILLATE' mode with looping.

		instance->set( { true, Sequencer< real_t >::OSCILLATE, 0.0, 2.0, 0.5, 0.0 } );

		for( size_t index = 0; index < ARRAY_SIZE( expectedResults ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], instance->getValue() );
			(*instance)++;
		}
}

TEST( SequencerTest, OperatorPostDecrementIntegralNonLoopedLinearWorks )
{
	// Create local variables.

		int64_t expectedResults[] = {
			4,
			3,
			2,
			1,
			0,
			0,
			0,
			0,
			0,
			0
		};

		Sequencer< int64_t >::InstancePtr instance = Sequencer< int64_t >::create();

	// Perform unit test for 'operator++( int )' method using integral values in 'LINEAR' mode with no looping.

		instance->set( { false, Sequencer< int64_t >::LINEAR, 0, 4, 1, 4 } );

		for( size_t index = 0; index < ARRAY_SIZE( expectedResults ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], instance->getValue() );
			(*instance)--;
		}
}

TEST( SequencerTest, OperatorPostDecrementIntegralNonLoopedOscillateWorks )
{
	// Create local variables.

		int64_t expectedResults[] = {
			4,
			3,
			2,
			1,
			0,
			1,
			2,
			3,
			4,
			4
		};

		Sequencer< int64_t >::InstancePtr instance = Sequencer< int64_t >::create();

	// Perform unit test for 'operator++( int )' method using integral values in 'OSCILLATE' mode with no looping.

		instance->set( { false, Sequencer< int64_t >::OSCILLATE, 0, 4, 1, 4 } );

		for( size_t index = 0; index < ARRAY_SIZE( expectedResults ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], instance->getValue() );
			(*instance)--;
		}
}

TEST( SequencerTest, OperatorPostDecrementIntegralLoopedLinearWorks )
{
	// Create local variables.

		int64_t expectedResults[] = {
			4,
			3,
			2,
			1,
			0,
			4,
			3,
			2,
			1,
			0
		};

		Sequencer< int64_t >::InstancePtr instance = Sequencer< int64_t >::create();

	// Perform unit test for 'operator++( int )' method using integral values in 'LINEAR' mode with looping.

		instance->set( { true, Sequencer< int64_t >::LINEAR, 0, 4, 1, 4 } );

		for( size_t index = 0; index < ARRAY_SIZE( expectedResults ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], instance->getValue() );
			(*instance)--;
		}
}

TEST( SequencerTest, OperatorPostDecrementIntegralLoopedOscillateWorks )
{
	// Create local variables.

		int64_t expectedResults[] = {
			4,
			3,
			2,
			1,
			0,
			1,
			2,
			3,
			4,
			3
		};

		Sequencer< int64_t >::InstancePtr instance = Sequencer< int64_t >::create();

	// Perform unit test for 'operator++( int )' method using integral values in 'OSCILLATE' mode with looping.

		instance->set( { true, Sequencer< int64_t >::OSCILLATE, 0, 4, 1, 4 } );

		for( size_t index = 0; index < ARRAY_SIZE( expectedResults ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], instance->getValue() );
			(*instance)--;
		}
}

TEST( SequencerTest, OperatorPostDecrementFloatingPointNonLoopedLinearWorks )
{
	// Create local variables.

		real_t expectedResults[] = {
			2.0,
			1.5,
			1.0,
			0.5,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0
		};

		Sequencer< real_t >::InstancePtr instance = Sequencer< real_t >::create();

	// Perform unit test for 'operator++( int )' method using floating point values in 'LINEAR' mode with no looping.

		instance->set( { false, Sequencer< real_t >::LINEAR, 0.0, 2.0, 0.5, 2.0 } );

		for( size_t index = 0; index < ARRAY_SIZE( expectedResults ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], instance->getValue() );
			(*instance)--;
		}
}

TEST( SequencerTest, OperatorPostDecrementFloatingPointNonLoopedOscillateWorks )
{
	// Create local variables.

		real_t expectedResults[] = {
			2.0,
			1.5,
			1.0,
			0.5,
			0.0,
			0.5,
			1.0,
			1.5,
			2.0,
			2.0
		};

		Sequencer< real_t >::InstancePtr instance = Sequencer< real_t >::create();

	// Perform unit test for 'operator++( int )' method using floating point values in 'OSCILLATE' mode with no looping.

		instance->set( { false, Sequencer< real_t >::OSCILLATE, 0.0, 2.0, 0.5, 2.0 } );

		for( size_t index = 0; index < ARRAY_SIZE( expectedResults ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], instance->getValue() );
			(*instance)--;
		}
}

TEST( SequencerTest, OperatorPostDecrementFloatingPointLoopedLinearWorks )
{
	// Create local variables.

		real_t expectedResults[] = {
			2.0,
			1.5,
			1.0,
			0.5,
			0.0,
			2.0,
			1.5,
			1.0,
			0.5,
			0.0
		};

		Sequencer< real_t >::InstancePtr instance = Sequencer< real_t >::create();

	// Perform unit test for 'operator++( int )' method using floating point values in 'LINEAR' mode with looping.

		instance->set( { true, Sequencer< real_t >::LINEAR, 0.0, 2.0, 0.5, 2.0 } );

		for( size_t index = 0; index < ARRAY_SIZE( expectedResults ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], instance->getValue() );
			(*instance)--;
		}
}

TEST( SequencerTest, OperatorPostDecrementFloatingPointLoopedOscillateWorks )
{
	// Create local variables.

		real_t expectedResults[] = {
			2.0,
			1.5,
			1.0,
			0.5,
			0.0,
			0.5,
			1.0,
			1.5,
			2.0,
			1.5
		};

		Sequencer< real_t >::InstancePtr instance = Sequencer< real_t >::create();

	// Perform unit test for 'operator++( int )' method using floating point values in 'OSCILLATE' mode with looping.

		instance->set( { true, Sequencer< real_t >::OSCILLATE, 0.0, 2.0, 0.5, 2.0 } );

		for( size_t index = 0; index < ARRAY_SIZE( expectedResults ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], instance->getValue() );
			(*instance)--;
		}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'SequencerTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

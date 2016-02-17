////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SequencerTest.cpp
// Robert M. Baker | Created : 29FEB12 | Last Modified : 16FEB16 by Robert M. Baker
// Version : 1.0.0
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::Sequencer' class.
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

#include <SequencerTest.hpp>

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::Sequencer' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( SequencerTest, OperatorPostIncrementIntegralNonLoopedLinearWorks )
{
	// Create local variables.

		Sequencer< int64_t >::PointerType Instance = Sequencer< int64_t >::Create();
		int64_t ExpectedResults[] = { 0, 1, 2, 3, 4, 4, 4, 4, 4, 4 };

	// Perform unit test for 'operator++( int )' method using integral values in 'Linear' mode with no looping.

		Instance->Set( { false, Sequencer< int64_t >::Linear, 0, 4, 1, 0 } );

		for( size_t Index = 0; Index < ARRAY_SIZE( ExpectedResults ); Index++ )
		{
			ASSERT_EQ( ExpectedResults[ Index ], Instance->GetValue() );
			(*Instance)++;
		}
}

TEST( SequencerTest, OperatorPostIncrementIntegralNonLoopedOscillateWorks )
{
	// Create local variables.

		Sequencer< int64_t >::PointerType Instance = Sequencer< int64_t >::Create();
		int64_t ExpectedResults[] = { 0, 1, 2, 3, 4, 3, 2, 1, 0, 0 };

	// Perform unit test for 'operator++( int )' method using integral values in 'Oscillate' mode with no looping.

		Instance->Set( { false, Sequencer< int64_t >::Oscillate, 0, 4, 1, 0 } );

		for( size_t Index = 0; Index < ARRAY_SIZE( ExpectedResults ); Index++ )
		{
			ASSERT_EQ( ExpectedResults[ Index ], Instance->GetValue() );
			(*Instance)++;
		}
}

TEST( SequencerTest, OperatorPostIncrementIntegralLoopedLinearWorks )
{
	// Create local variables.

		Sequencer< int64_t >::PointerType Instance = Sequencer< int64_t >::Create();
		int64_t ExpectedResults[] = { 0, 1, 2, 3, 4, 0, 1, 2, 3, 4 };

	// Perform unit test for 'operator++( int )' method using integral values in 'Linear' mode with looping.

		Instance->Set( { true, Sequencer< int64_t >::Linear, 0, 4, 1, 0 } );

		for( size_t Index = 0; Index < ARRAY_SIZE( ExpectedResults ); Index++ )
		{
			ASSERT_EQ( ExpectedResults[ Index ], Instance->GetValue() );
			(*Instance)++;
		}
}

TEST( SequencerTest, OperatorPostIncrementIntegralLoopedOscillateWorks )
{
	// Create local variables.

		Sequencer< int64_t >::PointerType Instance = Sequencer< int64_t >::Create();
		int64_t ExpectedResults[] = { 0, 1, 2, 3, 4, 3, 2, 1, 0, 1 };

	// Perform unit test for 'operator++( int )' method using integral values in 'Oscillate' mode with looping.

		Instance->Set( { true, Sequencer< int64_t >::Oscillate, 0, 4, 1, 0 } );

		for( size_t Index = 0; Index < ARRAY_SIZE( ExpectedResults ); Index++ )
		{
			ASSERT_EQ( ExpectedResults[ Index ], Instance->GetValue() );
			(*Instance)++;
		}
}

TEST( SequencerTest, OperatorPostIncrementFloatingPointNonLoopedLinearWorks )
{
	// Create local variables.

		Sequencer< real_t >::PointerType Instance = Sequencer< real_t >::Create();
		real_t ExpectedResults[] = { 0.0, 0.5, 1.0, 1.5, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0 };

	// Perform unit test for 'operator++( int )' method using floating point values in 'Linear' mode with no looping.

		Instance->Set( { false, Sequencer< real_t >::Linear, 0.0, 2.0, 0.5, 0.0 } );

		for( size_t Index = 0; Index < ARRAY_SIZE( ExpectedResults ); Index++ )
		{
			ASSERT_EQ( ExpectedResults[ Index ], Instance->GetValue() );
			(*Instance)++;
		}
}

TEST( SequencerTest, OperatorPostIncrementFloatingPointNonLoopedOscillateWorks )
{
	// Create local variables.

		Sequencer< real_t >::PointerType Instance = Sequencer< real_t >::Create();
		real_t ExpectedResults[] = { 0.0, 0.5, 1.0, 1.5, 2.0, 1.5, 1.0, 0.5, 0.0, 0.0 };

	// Perform unit test for 'operator++( int )' method using floating point values in 'Oscillate' mode with no looping.

		Instance->Set( { false, Sequencer< real_t >::Oscillate, 0.0, 2.0, 0.5, 0.0 } );

		for( size_t Index = 0; Index < ARRAY_SIZE( ExpectedResults ); Index++ )
		{
			ASSERT_EQ( ExpectedResults[ Index ], Instance->GetValue() );
			(*Instance)++;
		}
}

TEST( SequencerTest, OperatorPostIncrementFloatingPointLoopedLinearWorks )
{
	// Create local variables.

		Sequencer< real_t >::PointerType Instance = Sequencer< real_t >::Create();
		real_t ExpectedResults[] = { 0.0, 0.5, 1.0, 1.5, 2.0, 0.0, 0.5, 1.0, 1.5, 2.0 };

	// Perform unit test for 'operator++( int )' method using floating point values in 'Linear' mode with looping.

		Instance->Set( { true, Sequencer< real_t >::Linear, 0.0, 2.0, 0.5, 0.0 } );

		for( size_t Index = 0; Index < ARRAY_SIZE( ExpectedResults ); Index++ )
		{
			ASSERT_EQ( ExpectedResults[ Index ], Instance->GetValue() );
			(*Instance)++;
		}
}

TEST( SequencerTest, OperatorPostIncrementFloatingPointLoopedOscillateWorks )
{
	// Create local variables.

		Sequencer< real_t >::PointerType Instance = Sequencer< real_t >::Create();
		real_t ExpectedResults[] = { 0.0, 0.5, 1.0, 1.5, 2.0, 1.5, 1.0, 0.5, 0.0, 0.5 };

	// Perform unit test for 'operator++( int )' method using floating point values in 'Oscillate' mode with looping.

		Instance->Set( { true, Sequencer< real_t >::Oscillate, 0.0, 2.0, 0.5, 0.0 } );

		for( size_t Index = 0; Index < ARRAY_SIZE( ExpectedResults ); Index++ )
		{
			ASSERT_EQ( ExpectedResults[ Index ], Instance->GetValue() );
			(*Instance)++;
		}
}

TEST( SequencerTest, OperatorPostDecrementIntegralNonLoopedLinearWorks )
{
	// Create local variables.

		Sequencer< int64_t >::PointerType Instance = Sequencer< int64_t >::Create();
		int64_t ExpectedResults[] = { 4, 3, 2, 1, 0, 0, 0, 0, 0, 0 };

	// Perform unit test for 'operator++( int )' method using integral values in 'Linear' mode with no looping.

		Instance->Set( { false, Sequencer< int64_t >::Linear, 0, 4, 1, 4 } );

		for( size_t Index = 0; Index < ARRAY_SIZE( ExpectedResults ); Index++ )
		{
			ASSERT_EQ( ExpectedResults[ Index ], Instance->GetValue() );
			(*Instance)--;
		}
}

TEST( SequencerTest, OperatorPostDecrementIntegralNonLoopedOscillateWorks )
{
	// Create local variables.

		Sequencer< int64_t >::PointerType Instance = Sequencer< int64_t >::Create();
		int64_t ExpectedResults[] = { 4, 3, 2, 1, 0, 1, 2, 3, 4, 4 };

	// Perform unit test for 'operator++( int )' method using integral values in 'Oscillate' mode with no looping.

		Instance->Set( { false, Sequencer< int64_t >::Oscillate, 0, 4, 1, 4 } );

		for( size_t Index = 0; Index < ARRAY_SIZE( ExpectedResults ); Index++ )
		{
			ASSERT_EQ( ExpectedResults[ Index ], Instance->GetValue() );
			(*Instance)--;
		}
}

TEST( SequencerTest, OperatorPostDecrementIntegralLoopedLinearWorks )
{
	// Create local variables.

		Sequencer< int64_t >::PointerType Instance = Sequencer< int64_t >::Create();
		int64_t ExpectedResults[] = { 4, 3, 2, 1, 0, 4, 3, 2, 1, 0 };

	// Perform unit test for 'operator++( int )' method using integral values in 'Linear' mode with looping.

		Instance->Set( { true, Sequencer< int64_t >::Linear, 0, 4, 1, 4 } );

		for( size_t Index = 0; Index < ARRAY_SIZE( ExpectedResults ); Index++ )
		{
			ASSERT_EQ( ExpectedResults[ Index ], Instance->GetValue() );
			(*Instance)--;
		}
}

TEST( SequencerTest, OperatorPostDecrementIntegralLoopedOscillateWorks )
{
	// Create local variables.

		Sequencer< int64_t >::PointerType Instance = Sequencer< int64_t >::Create();
		int64_t ExpectedResults[] = { 4, 3, 2, 1, 0, 1, 2, 3, 4, 3 };

	// Perform unit test for 'operator++( int )' method using integral values in 'Oscillate' mode with looping.

		Instance->Set( { true, Sequencer< int64_t >::Oscillate, 0, 4, 1, 4 } );

		for( size_t Index = 0; Index < ARRAY_SIZE( ExpectedResults ); Index++ )
		{
			ASSERT_EQ( ExpectedResults[ Index ], Instance->GetValue() );
			(*Instance)--;
		}
}

TEST( SequencerTest, OperatorPostDecrementFloatingPointNonLoopedLinearWorks )
{
	// Create local variables.

		Sequencer< real_t >::PointerType Instance = Sequencer< real_t >::Create();
		real_t ExpectedResults[] = { 2.0, 1.5, 1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

	// Perform unit test for 'operator++( int )' method using floating point values in 'Linear' mode with no looping.

		Instance->Set( { false, Sequencer< real_t >::Linear, 0.0, 2.0, 0.5, 2.0 } );

		for( size_t Index = 0; Index < ARRAY_SIZE( ExpectedResults ); Index++ )
		{
			ASSERT_EQ( ExpectedResults[ Index ], Instance->GetValue() );
			(*Instance)--;
		}
}

TEST( SequencerTest, OperatorPostDecrementFloatingPointNonLoopedOscillateWorks )
{
	// Create local variables.

		Sequencer< real_t >::PointerType Instance = Sequencer< real_t >::Create();
		real_t ExpectedResults[] = { 2.0, 1.5, 1.0, 0.5, 0.0, 0.5, 1.0, 1.5, 2.0, 2.0 };

	// Perform unit test for 'operator++( int )' method using floating point values in 'Oscillate' mode with no looping.

		Instance->Set( { false, Sequencer< real_t >::Oscillate, 0.0, 2.0, 0.5, 2.0 } );

		for( size_t Index = 0; Index < ARRAY_SIZE( ExpectedResults ); Index++ )
		{
			ASSERT_EQ( ExpectedResults[ Index ], Instance->GetValue() );
			(*Instance)--;
		}
}

TEST( SequencerTest, OperatorPostDecrementFloatingPointLoopedLinearWorks )
{
	// Create local variables.

		Sequencer< real_t >::PointerType Instance = Sequencer< real_t >::Create();
		real_t ExpectedResults[] = { 2.0, 1.5, 1.0, 0.5, 0.0, 2.0, 1.5, 1.0, 0.5, 0.0 };

	// Perform unit test for 'operator++( int )' method using floating point values in 'Linear' mode with looping.

		Instance->Set( { true, Sequencer< real_t >::Linear, 0.0, 2.0, 0.5, 2.0 } );

		for( size_t Index = 0; Index < ARRAY_SIZE( ExpectedResults ); Index++ )
		{
			ASSERT_EQ( ExpectedResults[ Index ], Instance->GetValue() );
			(*Instance)--;
		}
}

TEST( SequencerTest, OperatorPostDecrementFloatingPointLoopedOscillateWorks )
{
	// Create local variables.

		Sequencer< real_t >::PointerType Instance = Sequencer< real_t >::Create();
		real_t ExpectedResults[] = { 2.0, 1.5, 1.0, 0.5, 0.0, 0.5, 1.0, 1.5, 2.0, 1.5 };

	// Perform unit test for 'operator++( int )' method using floating point values in 'Oscillate' mode with looping.

		Instance->Set( { true, Sequencer< real_t >::Oscillate, 0.0, 2.0, 0.5, 2.0 } );

		for( size_t Index = 0; Index < ARRAY_SIZE( ExpectedResults ); Index++ )
		{
			ASSERT_EQ( ExpectedResults[ Index ], Instance->GetValue() );
			(*Instance)--;
		}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'SequencerTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

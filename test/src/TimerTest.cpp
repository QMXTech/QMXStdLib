////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TimerTest.cpp
// Robert M. Baker | Created : 19FEB12 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.2
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::Timer' class.
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

#include "../include/TimerTest.hpp"

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::Timer' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( TimerTest, IsRunningWorks )
{
	// Create local variables.

		Timer::PointerType Instance = Timer::Create();

	// Perform unit test for 'IsRunning' method.

		ASSERT_FALSE( Instance->IsRunning() );
}

TEST( TimerTest, ToggleWorks )
{
	// Create local variables.

		Timer::PointerType Instance = Timer::Create();

	// Perform unit test for 'Toggle' method.

 		ASSERT_FALSE( Instance->IsRunning() );
		Instance->Toggle();
		ASSERT_TRUE( Instance->IsRunning() );
		Instance->Toggle();
 		ASSERT_FALSE( Instance->IsRunning() );
}

TEST( TimerTest, GetTimeWorks )
{
	// Create local variables.

		Timer::PointerType Instance = Timer::Create();

	// Perform unit test for 'GetTime' method.

		Instance->Toggle();

		while( Instance->GetTime() < 0.25 );
			// Empty Loop

		Instance->Toggle();
		ASSERT_NEAR( 250.0, Instance->GetTime( Timer::Milliseconds ), 50.0 );
		ASSERT_NEAR( 0.25, Instance->GetTime( Timer::Seconds ), 0.05 );
		ASSERT_NEAR( 0.004167, Instance->GetTime( Timer::Minutes ), 0.0008333 );
		ASSERT_NEAR( 0.00006944, Instance->GetTime( Timer::Hours ), 0.00001389 );
}

TEST( TimerTest, ResetWorks )
{
	// Create local variables.

		Timer::PointerType Instance = Timer::Create();

	// Perform unit test for 'Reset' method.

		Instance->Toggle();

		while( Instance->GetTime() < 0.25 );
			// Empty Loop

		Instance->Toggle();
		ASSERT_NEAR( 0.25, Instance->GetTime(), 0.05 );
		Instance->Reset();
		ASSERT_NEAR( 0.0, Instance->GetTime(), 0.05 );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'TimerTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

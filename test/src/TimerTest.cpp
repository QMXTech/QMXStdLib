////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TimerTest.cpp
// Robert M. Baker | Created : 19FEB12 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.1.0
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::Timer' class.
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

#include "../include/TimerTest.hpp"

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::Timer' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( TimerTest, IsRunningWorks )
{
	// Create local variables.

		Timer::InstancePtr instance = Timer::create();

	// Perform unit test for 'isRunning' method.

		ASSERT_FALSE( instance->isRunning() );
}

TEST( TimerTest, ToggleWorks )
{
	// Create local variables.

		Timer::InstancePtr instance = Timer::create();

	// Perform unit test for 'toggle' method.

 		ASSERT_FALSE( instance->isRunning() );
		instance->toggle();
		ASSERT_TRUE( instance->isRunning() );
		instance->toggle();
 		ASSERT_FALSE( instance->isRunning() );
}

TEST( TimerTest, GetTimeWorks )
{
	// Create local variables.

		Timer::InstancePtr instance = Timer::create();

	// Perform unit test for 'getTime' method.

		instance->toggle();

		while( instance->getTime() < 0.25 );
			// Empty Loop

		instance->toggle();
		ASSERT_NEAR( 250.0, instance->getTime( Timer::MILLISECONDS ), 50.0 );
		ASSERT_NEAR( 0.25, instance->getTime( Timer::SECONDS ), 0.05 );
		ASSERT_NEAR( 0.004167, instance->getTime( Timer::MINUTES ), 0.0008333 );
		ASSERT_NEAR( 0.00006944, instance->getTime( Timer::HOURS ), 0.00001389 );
}

TEST( TimerTest, ResetWorks )
{
	// Create local variables.

		Timer::InstancePtr instance = Timer::create();

	// Perform unit test for 'reset' method.

		instance->toggle();

		while( instance->getTime() < 0.25 );
			// Empty Loop

		instance->toggle();
		ASSERT_NEAR( 0.25, instance->getTime(), 0.05 );
		instance->reset();
		ASSERT_NEAR( 0.0, instance->getTime(), 0.05 );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'TimerTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

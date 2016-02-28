////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Timer.cpp
// Robert M. Baker | Created : 11JAN12 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.0
// This is a source file for 'QMXStdLib'; it defines the implementation for a timer class.
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

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 11JAN12
  * @date    Last Modified : 27FEB16 by Robert M. Baker
  * @version 1.1.0
  *
  * @brief This source file defines the implementation for a timer class.
  *
  * @section Description
  *
  * This source file defines the implementation for a timer class.
  *
  * @section License
  *
  * Copyright (C) 2011-2016 QuantuMatriX Software, LLP.
  *
  * This file is part of 'QMXStdLib'.
  *
  * 'QMXStdLib' is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free
  * Software Foundation, either version 3 of the License, or (at your option) any later version.
  *
  * 'QMXStdLib' is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  * A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public License along with 'QMXStdLib'.  If not, see <http://www.gnu.org/licenses/>.
  */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../include/Timer.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Methods for the 'Timer' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Timer::~Timer()
{
	// Perform necessary cleanup.

		if( Initialized )
			Deallocate();
}

bool Timer::IsRunning() const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Report wether or not the timer is running to the calling routine.

		return !LocalTimer.is_stopped();
}

void Timer::Toggle()
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Toggle the timer.

		if( LocalTimer.is_stopped() )
			LocalTimer.resume();
		else
			LocalTimer.stop();
}

void Timer::Reset()
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Reset the timer.

		LocalTimer.start();
		LocalTimer.stop();
}

real_t Timer::GetTime( Timer::TimeUnits Units ) const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Return elapsed time, in specified units, to calling routine.

		return( LocalTimer.elapsed().wall / static_cast< real_t >( Units ) );
}

Timer::PointerType Timer::Create()
{
	// Create local variables.

		PointerType Result( new Timer() );

	// Initialize new instance.

		Result->Allocate();

	// Return result to calling routine.

		return Result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods for the 'Timer' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Timer::Timer()
{
	// Initialize fields.

		LocalTimer.start();
		LocalTimer.stop();
}

void Timer::OperatorAssignImp( const Object* Instance )
{
	// Create local variables.

		const Timer* DInstance = dynamic_cast< const Timer* >( Instance );

	// Assign specified object to 'this'.

		LocalTimer = DInstance->LocalTimer;
}

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'Timer.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

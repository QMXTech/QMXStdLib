////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Timer.cpp
// Robert M. Baker | Created : 11JAN12 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.3.0
// This is a source file for 'QMXStdLib'; it defines the implementation for a timer class.
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

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 11JAN12
  * @date    Last Modified : 29AUG19 by Robert M. Baker
  * @version 2.3.0
  *
  * @brief This source file defines the implementation for a timer class.
  *
  * @section TimerS0000 Description
  *
  * This source file defines the implementation for a timer class.
  *
  * @section TimerS0001 License
  *
  * Copyright (C) 2011-2019 QuantuMatriX Software, a QuantuMatriX Technologies Cooperative Partnership
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

using namespace std;

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
	try
	{
		// Perform necessary cleanup.

			if( initialized )
				deallocate();
	}
	catch( const exception& except )
	{
		// Do nothing.
	}
}

bool Timer::isRunning() const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Report wether or not the timer is running to the calling routine.

		return !localTimer.is_stopped();
}

void Timer::toggle()
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Toggle the timer.

		if( localTimer.is_stopped() )
			localTimer.resume();
		else
			localTimer.stop();
}

void Timer::reset()
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Reset the timer.

		localTimer.start();
		localTimer.stop();
}

real_t Timer::getTime( Timer::TimeUnits units ) const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Return elapsed time, in specified units, to calling routine.

		return( localTimer.elapsed().wall / static_cast< real_t >( units ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods for the 'Timer' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Timer::Timer()
{
	// Initialize fields.

		localTimer.start();
		localTimer.stop();
}

void Timer::cloneImp( Timer::InstancePtr& target ) const
{
	// Assign data of 'this' to specified object.

		target->localTimer = localTimer;
}

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'Timer.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

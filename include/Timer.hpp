////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Timer.hpp
// Robert M. Baker | Created : 11JAN12 | Last Modified : 28JAN16 by Robert M. Baker
// Version : 1.0.0
// This is a header file for 'QMXStdLib'; it defines the interface for a timer class.
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
  * @date    Last Modified : 28JAN16 by Robert M. Baker
  * @version 1.0.0
  *
  * @brief This header file defines the interface for a timer class.
  *
  * @section Description
  *
  * This header file defines the interface for a timer class.
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

#ifndef __QMX_QMXSTDLIB_TIMER_HPP_
#define __QMX_QMXSTDLIB_TIMER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "Object.hpp"
#include "RAII/ScopedStackTrace.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'Timer' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class Timer Timer.hpp "include/Timer.hpp"
  *
  * @brief This class defines timer algorithms.
  *
  * These algorithms are useful for such things as timing durations and synchronizing events.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Yes
  */

class Timer : public Object< Timer >
{
public:

	// Public Data Types

		/**
		  * @brief This enumeration defines all available time units.
		  */

		enum TimeUnits : unsigned long long int
		{
			Milliseconds = 1000000ull,
			Seconds = 1000000000ull,
			Minutes = 60000000000ull,
			Hours = 3600000000000ull
		};

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		virtual ~Timer();

	// Public Methods

		/**
		  * @brief This method reports whether or not the timer is running.
		  *
		  * @return
		  * 	A boolean value of 'true' if the timer is running, and 'false' otherwise.
		  */

		bool IsRunning() const;

		/**
		  * @brief This method toggles the timer.
		  */

		void Toggle();

		/**
		  * @brief this method resets the timer.
		  */

		void Reset();

		/**
		  * @brief This method gets the elapsed time in the specified units.
		  *
		  * @param Units
		  * 	This is the time units specifier; if it is set to an out-of-range value, it will be set to seconds.
		  *
		  * @return
		  * 	The elapsed time in the specified units.
		  */

		real_t GetTime( TimeUnits Units = Seconds ) const;

		/**
		  * @brief This method creates an instance of this class.
		  *
		  * @return
		  * 	A pointer to the newly created instance.
		  */

		static PointerType Create();

private:

	// Private Constructors

		/**
		  * @brief This is the default constructor, which is made private to prevent direct instantiation.
		  */

		Timer();

	// Private Methods

		/**
		  * @brief This is the overridden implementation for the 'operator=' method.
		  *
		  * @param Instance
		  * 	This is the 'Object' pointer with which to set 'this'.
		  */

		void OperatorAssignImp( const Object* Instance );

		/**
		  * @brief This is the overridden implementation for the 'Clone' method.
		  *
		  * @return
		  * 	A pointer to a copy of this object.
		  */

		CLONE_IMP( Timer )

	// Private Fields

		/**
		  * @brief This is the timer object.
		  */

		boost::timer::cpu_timer LocalTimer;
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_TIMER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'Timer.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

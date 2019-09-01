////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Lockable.hpp
// Robert M. Baker | Created : 04MAR12 | Last Modified : 27AUG19 by Robert M. Baker
// Version : 2.1.0
// This is a header file for 'QMXStdLib'; it defines the interface for a mixin class to enable object locking.
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
  * @date    Created : 04MAR12
  * @date    Last Modified : 27AUG19 by Robert M. Baker
  * @version 2.1.0
  *
  * @brief This header file defines the interface for a mixin class to enable object locking.
  *
  * @section LockableH0000 Description
  *
  * This header file defines the interface for a mixin class to enable object locking.
  *
  * @section LockableH0001 License
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

#ifndef __QMX_QMXSTDLIB_LOCKABLE_HPP_
#define __QMX_QMXSTDLIB_LOCKABLE_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../Base.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'Lockable' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class Lockable Lockable.hpp "include/Mixins/Lockable.hpp"
  *
  * @brief This class defines a mixin interface to enable object locking.
  *
  * This is useful when there is a need for thread-safetey within a class.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Yes
  */

class Lockable
{
public:

	// Public Constructors

		/**
		  * @brief This is the default constructor.
		  */

		Lockable()
		{
			// Do nothing.
		}

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		virtual ~Lockable()
		{
			// Do nothing.
		}

	// Public Methods

		/**
		  * @brief This method obtains the mutex pair object.
		  *
		  * @return
		  * 	A mutable reference to the mutex pair object.
		  */

		SharedMutexPair& getMutex() const
		{
			// Return a mutable reference to the mutex object to calling routine.

				return localMutex;
		}

protected:

	// Protected Fields

		/**
		  * @brief This is the mutex pair for use when thread-safety is needed.
		  */

		mutable SharedMutexPair localMutex;
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_LOCKABLE_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'Lockable.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

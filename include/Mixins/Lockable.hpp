////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Lockable.hpp
// Robert M. Baker | Created : 04MAR12 | Last Modified : 28JAN16 by Robert M. Baker
// Version : 1.0.0
// This is a header file for 'QMXStdLib'; it defines the interface for a mixin class.
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
  * @date    Created : 04MAR12
  * @date    Last Modified : 28JAN16 by Robert M. Baker
  * @version 1.0.0
  *
  * @brief This header file defines the interface for a mixin class.
  *
  * @section Description
  *
  * This header file defines the interface for a mixin class.
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

#ifndef __QMX_QMXSTDLIB_LOCKABLE_HPP_
#define __QMX_QMXSTDLIB_LOCKABLE_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../Base.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SCOPED_READ_LOCK         QMXStdLib::SharedLock ScopedReadLock( this->LocalMutex )
#define SCOPED_READ_LOCK_X(x,y)  QMXStdLib::SharedLock ScopedReadLock##y( x.GetMutex() )
#define SCOPED_WRITE_LOCK        QMXStdLib::UniqueLock ScopedWriteLock( this->LocalMutex )
#define SCOPED_WRITE_LOCK_X(x,y) QMXStdLib::UniqueLock ScopedWriteLock##y( x.GetMutex() )

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
		  * @brief This method obtains the mutex object.
		  *
		  * @return
		  * 	A mutable reference to the mutex object.
		  */

		SharedMutex& GetMutex() const
		{
			// Return a mutable reference to the mutex object to calling routine.

				return LocalMutex;
		}

protected:

	// Protected Fields

		/**
		  * @brief This is the mutex for use when thread-safety is needed.
		  */

		mutable SharedMutex LocalMutex;
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_LOCKABLE_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'Lockable.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

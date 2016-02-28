////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DEPRECATED
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NonCopyable.hpp
// Robert M. Baker | Created : 04MAR12 | Last Modified : 22FEB16 by Robert M. Baker
// Version : 1.1.2
// This is a header file for 'QMXStdLib'; it defines the interface for a mixin class to prevent copying.
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
  * @date    Last Modified : 22FEB16 by Robert M. Baker
  * @version 1.1.2
  *
  * @brief This header file defines the interface for a mixin class to prevent copying (DEPRECATED).
  *
  * @section Description
  *
  * This header file defines the interface for a mixin class to prevent copying.  Note: This class is now marked deprecated in favor of C++11 method deletion.
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

#ifndef __QMX_QMXSTDLIB_NONCOPYABLE_HPP_
#define __QMX_QMXSTDLIB_NONCOPYABLE_HPP_

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
// The 'NonCopyable' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class NonCopyable NonCopyable.hpp "include/NonCopyable.hpp"
  *
  * @brief This class defines a mixin interface to prevent copying (DEPRECATED).
  *
  * This is useful when it is necessary to prevent instance copying.  Note: This class is now marked deprecated in favor of C++11 method deletion.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Yes
  */

class NonCopyable
{
protected:

	// Protected Constructors

		/**
		  * @brief This is the default constructor, which is made protected to prevent instantiation.
		  */

		NonCopyable()
		{
			// Do nothing.
		}

	// Destructor

		/**
		  * @brief This is the destructor, which is made protected to prevent instantiation.
		  */

		virtual ~NonCopyable()
		{
			// Do nothing.
		}

private:

	// Private Constructors

		/**
		  * @brief This is the copy constructor, which is made private to prevent copying.
		  *
		  * @param Instance
		  * 	This is unused.
		  */

		explicit NonCopyable( const NonCopyable& Instance )
		{
			// Do nothing.
		}

	// Private Overloaded Operators

		/**
		  * @brief This is the default assignment-operator, which is made private to prevent copying.
		  *
		  * @param Instance
		  * 	This is unused.
		  *
		  * @return
		  * 	A reference to this object (only to suppress the 'no return statement in function returning non-void' warning).
		  */

		NonCopyable& operator=( const NonCopyable& Instance )
		{
			// Return a reference to this object to calling routine.

				return *this;
		}
} DEPRECATED;

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_NONCOPYABLE_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'NonCopyable.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ScopedStackTrace.hpp
// Robert M. Baker | Created : 04MAR12 | Last Modified : 28AUG19 by Robert M. Baker
// Version : 2.2.1
// This is a header file for 'QMXStdLib'; it defines the interface for an RAII class to create a scoped trace.
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
  * @date    Last Modified : 28AUG19 by Robert M. Baker
  * @version 2.2.1
  *
  * @brief This header file defines the interface for an RAII class to create a scoped trace.
  *
  * @section ScopedStackTraceH0000 Description
  *
  * This header file defines the interface for an RAII class to create a scoped trace.
  *
  * @section ScopedStackTraceH0001 License
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

#ifndef __QMX_QMXSTDLIB_SCOPEDSTACKTRACE_HPP_
#define __QMX_QMXSTDLIB_SCOPEDSTACKTRACE_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../Base.hpp"
#include "../StackTracer.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SCOPED_STACK_TRACE(x,y) QMXStdLib::ScopedStackTrace scopedStackTrace##y( x )

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'ScopedStackTrace' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class ScopedStackTrace ScopedStackTrace.hpp "include/RAII/ScopedStackTrace.hpp"
  *
  * @brief This class defines an RAII interface for a scoped trace.
  *
  * This is useful for ensuring all pushed stack tracer entries are appropriately popped.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Yes
  */

class ScopedStackTrace
{
public:

	// Public Constructors

		/**
		  * @brief This is the copy constructor, which is deleted to prevent copying.
		  *
		  * @param instance
		  * 	N/A
		  */

		ScopedStackTrace( const ScopedStackTrace& instance ) = delete;

		/**
		  * @brief This is the constructor which accepts the initialization data.
		  *
		  * @param entry
		  * 	This is the string to use when pushing the stack tracer entry.
		  */

		ScopedStackTrace( const std::string& entry )
		{
			// Push specified entry into stack tracer.

				StackTracer::push( entry );
		}

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		~ScopedStackTrace()
		{
			// Pop the entry from stack tracer.

				StackTracer::pop();
		}

	// Public Overloaded Operators

		/**
		  * @brief This is the default assignment-operator, which is deleted to prevent copying.
		  *
		  * @param instance
		  * 	N/A
		  *
		  * @return
		  * 	N/A
		  */

		ScopedStackTrace& operator=( const ScopedStackTrace& instance ) = delete;
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_SCOPEDSTACKTRACE_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ScopedStackTrace.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

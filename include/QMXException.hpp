////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QMXException.hpp
// Robert M. Baker | Created : 28FEB12 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.3.0
// This is a header file for 'QMXStdLib'; it defines the interface for an exception class.
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
  * @date    Created : 28FEB12
  * @date    Last Modified : 29AUG19 by Robert M. Baker
  * @version 2.3.0
  *
  * @brief This header file defines the interface for an exception class.
  *
  * @section QMXExceptionH0000 Description
  *
  * This header file defines the interface for an exception class.
  *
  * @section QMXExceptionH0001 License
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

#ifndef __QMX_QMXSTDLIB_QMXEXCEPTION_HPP_
#define __QMX_QMXSTDLIB_QMXEXCEPTION_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include <cstring>
#include <exception>

#include "Base.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define QMX_THROW(w,x,y,z)         SINGLE_STATEMENT(\
                                     std::ostringstream eventDataBuffer;\
                                     eventDataBuffer << z;\
                                     throw QMXStdLib::QMXException( w, x, y, eventDataBuffer.str().c_str(), STACK_TRACE.c_str() );\
                                   )

#define QMX_THROW_X(w,x,y,z)       SINGLE_STATEMENT(\
                                     std::ostringstream eventDataBuffer;\
                                     eventDataBuffer << z;\
                                     throw QMXStdLib::QMXException( w, x, y, eventDataBuffer.str().c_str() );\
                                   )

#define QMX_ASSERT(v,w,x,y,z)      SINGLE_STATEMENT( if( !v ) QMX_THROW( w, x, y, z ); )
#define QMX_ASSERT_X(v,w,x,y,z)    SINGLE_STATEMENT( if( !v ) QMX_THROW_X( w, x, y, z ); )
#define QMX_ASSERT_E(u,v,w,x,y,z)  SINGLE_STATEMENT( if( !u ) v;  QMX_THROW( w, x, y, z ); )
#define QMX_ASSERT_EX(u,v,w,x,y,z) SINGLE_STATEMENT( if( !u ) v;  QMX_THROW_X( w, x, y, z ); )

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'QMXException' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class QMXException QMXException.hpp "include/QMXException.hpp"
  *
  * @brief This class defines exception handling algorithms.
  *
  * These algorithms are useful when it is necessary to collect and report data concerning run-time exceptions.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Yes
  */

class QMXException : public std::exception
{
public:

	// Public Constructors

		/**
		  * @brief This is the default contructor.
		  */

		QMXException();

		/**
		  * @brief This is the constructor which accepts the initialization data.
		  *
		  * @param sourceRootID
		  * 	This is a string containing the root ID of the exception.
		  *
		  * @param sourceModuleID
		  *  	This is a string containing the module ID of the exception.
		  *
		  * @param sourceEventIndex
		  * 	This is a string containing the event index of the exception.
		  *
		  * @param sourceEventData
		  * 	This is a string containing the event data of the exception.
		  *
		  * @param sourceStackTrace
		  * 	This is a string containing the stack trace of the exception.
		  */

		QMXException(
			const char* sourceRootID,
			const char* sourceModuleID,
			const char* sourceEventIndex,
			const char* sourceEventData = "",
			const char* sourceStackTrace = ""
		);

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		virtual ~QMXException();

	// Public Methods

		/**
		  * @brief This method gets the exception's root ID.
		  *
		  * @return
		  * 	A string containing the exception's root ID.
		  */

		const char* getRootID() const;

		/**
		  * @brief This method gets the exception's module ID.
		  *
		  * @return
		  * 	A string containing the exception's module ID.
		  */

		const char* getModuleID() const;

		/**
		  * @brief This method gets the exception's event index.
		  *
		  * @return
		  * 	A string containing the exception's event index.
		  */

		const char* getEventIndex() const;

		/**
		  * @brief This method gets the exception's event data.
		  *
		  * @return
		  * 	A string containing the exception's event data.
		  */

		const char* getEventData() const;

		/**
		  * @brief This method gets the exception's stack trace.
		  *
		  * @return
		  * 	A string containing the exception's stack trace.
		  */

		const char* getStackTrace() const;

		/**
		  * @brief This method gets the exception's message, which will be in an unlocalized format.
		  *
		  * @return
		  * 	A string containing the exception's message.
		  */

		const char* getMessage() const;

		/**
		  * @brief This is the overridden implementation of the 'what' method.
		  *
		  * @return
		  * 	A string representing the nature of the exception.
		  */

		const char* what() const throw();

private:

	// Private Fields

		/**
		  * @brief This is the root ID of the exception.
		  */

		char rootID[ MAX_BUFFER_SIZE ];

		/**
		  * @brief This is the module ID in which the exception occurred.
		  */

		char moduleID[ MAX_BUFFER_SIZE ];

		/**
		  * @brief This is the event index of the exception.
		  */

		char eventIndex[ MAX_BUFFER_SIZE ];

		/**
		  * @brief This is the event data for the exception.
		  */

		char eventData[ MAX_BUFFER_SIZE ];

		/**
		  * @brief This is the stack trace of the exception.
		  */

		char stackTrace[ MAX_BUFFER_SIZE ];

		/**
		  * @brief This is the unlocalized message for the exception.
		  */

		char message[ ( MAX_BUFFER_SIZE * 3 ) ];

		/**
		  * @brief This is a buffer used to format the string representing the nature of the exception.
		  */

		char buffer[ ( MAX_BUFFER_SIZE * 9 ) ];
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_QMXEXCEPTION_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'QMXException.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

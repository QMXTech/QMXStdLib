////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QMXException.hpp
// Robert M. Baker | Created : 28FEB12 | Last Modified : 28JAN16 by Robert M. Baker
// Version : 1.1.0
// This is a header file for 'QMXStdLib'; it defines the interface for an exception class.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2011-2016 QuantuMatriX Software LLP.
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
  * @date    Last Modified : 28JAN16 by Robert M. Baker
  * @version 1.1.0
  *
  * @brief This header file defines the interface for an exception class.
  *
  * @section Description
  *
  * This header file defines the interface for an exception class.
  *
  * @section License
  *
  * Copyright (C) 2011-2016 QuantuMatriX Software LLP.
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

#include "Base.hpp"

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
		  * @param TargetRootID
		  * 	This is a string containing the root ID of the exception.
		  *
		  * @param TargetModuleID
		  *  	This is a string containing the module ID of the exception.
		  *
		  * @param TargetEventIndex
		  * 	This is a string containing the event index of the exception.
		  *
		  * @param TargetEventData
		  * 	This is a string containing the event data of the exception.
		  *
		  * @param TargetStackTrace
		  * 	This is a string containing the stack trace of the exception.
		  */

		QMXException( const char* TargetRootID,
		              const char* TargetModuleID,
		              const char* TargetEventIndex,
		              const char* TargetEventData = "",
		              const char* TargetStackTrace = "" );

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

		const char* GetRootID() const;

		/**
		  * @brief This method gets the exception's module ID.
		  *
		  * @return
		  * 	A string containing the exception's module ID.
		  */

		const char* GetModuleID() const;

		/**
		  * @brief This method gets the exception's event index.
		  *
		  * @return
		  * 	A string containing the exception's event index.
		  */

		const char* GetEventIndex() const;

		/**
		  * @brief This method gets the exception's event data.
		  *
		  * @return
		  * 	A string containing the exception's event data.
		  */

		const char* GetEventData() const;

		/**
		  * @brief This method gets the exception's stack trace.
		  *
		  * @return
		  * 	A string containing the exception's stack trace.
		  */

		const char* GetStackTrace() const;

		/**
		  * @brief This method gets the exception's message, which will be in an unlocalized format.
		  *
		  * @return
		  * 	A string containing the exception's message.
		  */

		const char* GetMessage() const;

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

		char RootID[ MAX_BUFFER_SIZE ];

		/**
		  * @brief This is the module ID in which the exception occurred.
		  */

		char ModuleID[ MAX_BUFFER_SIZE ];

		/**
		  * @brief This is the event index of the exception.
		  */

		char EventIndex[ MAX_BUFFER_SIZE ];

		/**
		  * @brief This is the event data for the exception.
		  */

		char EventData[ MAX_BUFFER_SIZE ];

		/**
		  * @brief This is the stack trace of the exception.
		  */

		char StackTrace[ MAX_BUFFER_SIZE ];

		/**
		  * @brief This is the unlocalized message for the exception.
		  */

		char Message[ MAX_BUFFER_SIZE ];

		/**
		  * @brief This is a buffer used to format the string representing the nature of the exception.
		  */

		char Buffer[ MAX_BUFFER_SIZE ];
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_QMXEXCEPTION_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'QMXException.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

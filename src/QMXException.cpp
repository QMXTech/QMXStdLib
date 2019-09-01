////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QMXException.cpp
// Robert M. Baker | Created : 28FEB12 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.1.1
// This is a source file for 'QMXStdLib'; it defines the implementation for an exception class.
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
  * @version 2.1.1
  *
  * @brief This source file defines the implementation for an exception class.
  *
  * @section QMXExceptionS0000 Description
  *
  * This source file defines the implementation for an exception class.
  *
  * @section QMXExceptionS0001 License
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

#include "../include/QMXException.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Methods for the 'QMXException' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QMXException::QMXException()
{
	// Initialize fields.

		ZERO_ARRAY( rootID );
		ZERO_ARRAY( moduleID );
		ZERO_ARRAY( eventIndex );
		ZERO_ARRAY( eventData );
		ZERO_ARRAY( stackTrace );
		ZERO_ARRAY( message );
		sprintf( buffer, "QMXStdLib::QMXException" );
}

QMXException::QMXException(
	const char* sourceRootID,
	const char* sourceModuleID,
	const char* sourceEventIndex,
	const char* sourceEventData,
	const char* sourceStackTrace
)
{
	// Initialize fields.

		strcpy( rootID, sourceRootID );
		strcpy( moduleID, sourceModuleID );
		strcpy( eventIndex, sourceEventIndex );
		strcpy( eventData, sourceEventData );
		strcpy( stackTrace, sourceStackTrace );
		sprintf( message, "%s.EventMessages.<LL>_<CC>.%s", rootID, eventIndex );
		sprintf( buffer, "Exception occurred in '%s::%s' -> %s", rootID, moduleID, message );

		if( strlen( eventData ) )
		{		
			strcat( buffer, " : " );
			strcpy( buffer, strcat( buffer, eventData ) );
		}

		if( strlen( stackTrace ) )
		{
			strcat( buffer, "\n\nStack Trace: " );
			strcpy( buffer, strcat( buffer, stackTrace ) );
		}
}

QMXException::~QMXException()
{
	// Do nothing.
}

const char* QMXException::getRootID() const
{
	// Return event root ID to calling routine.

		return rootID;
}

const char* QMXException::getModuleID() const
{
	// Return event module ID to calling routine.

		return moduleID;
}

const char* QMXException::getEventIndex() const
{
	// Return event index to calling routine.

		return eventIndex;
}

const char* QMXException::getEventData() const
{
	// Return event data to calling routine.

		return eventData;
}

const char* QMXException::getStackTrace() const
{
	// Return event stack trace to calling routine.

		return stackTrace;
}

const char* QMXException::getMessage() const
{
	// Return event message to calling routine.

		return message;
}

const char* QMXException::what() const throw()
{
	// Return nature of the exception to calling routine.

		return buffer;
}

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'QMXException.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QMXException.cpp
// Robert M. Baker | Created : 28FEB12 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.2
// This is a source file for 'QMXStdLib'; it defines the implementation for an exception class.
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
  * @date    Last Modified : 27FEB16 by Robert M. Baker
  * @version 1.1.2
  *
  * @brief This source file defines the implementation for an exception class.
  *
  * @section Description
  *
  * This source file defines the implementation for an exception class.
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

		ZERO_ARRAY( RootID );
		ZERO_ARRAY( ModuleID );
		ZERO_ARRAY( EventIndex );
		ZERO_ARRAY( EventData );
		ZERO_ARRAY( StackTrace );
		ZERO_ARRAY( Message );
		sprintf( Buffer, "QMXStdLib::QMXException" );
}

QMXException::QMXException( const char* TargetRootID,
                            const char* TargetModuleID,
                            const char* TargetEventIndex,
                            const char* TargetEventData,
                            const char* TargetStackTrace )
{
	// Initialize fields.

		strcpy( RootID, TargetRootID );
		strcpy( ModuleID, TargetModuleID );
		strcpy( EventIndex, TargetEventIndex );
		strcpy( EventData, TargetEventData );
		strcpy( StackTrace, TargetStackTrace );
		sprintf( Message, "%s.EventMessages.<LL>_<CC>.%s", RootID, EventIndex );
		sprintf( Buffer, "Exception ocurred in '%s::%s' -> %s", RootID, ModuleID, Message );

		if( strlen( EventData ) )
			sprintf( Buffer, "%s : %s", Buffer, EventData );

		if( strlen( StackTrace ) )
			sprintf( Buffer, "%s\n\nStack Trace: %s", Buffer, StackTrace );
}

QMXException::~QMXException()
{
	// Do nothing.
}

const char* QMXException::GetRootID() const
{
	// Return event root ID to calling routine.

		return RootID;
}

const char* QMXException::GetModuleID() const
{
	// Return event module ID to calling routine.

		return ModuleID;
}

const char* QMXException::GetEventIndex() const
{
	// Return event index to calling routine.

		return EventIndex;
}

const char* QMXException::GetEventData() const
{
	// Return event data to calling routine.

		return EventData;
}

const char* QMXException::GetStackTrace() const
{
	// Return event stack trace to calling routine.

		return StackTrace;
}

const char* QMXException::GetMessage() const
{
	// Return event message to calling routine.

		return Message;
}

const char* QMXException::what() const throw()
{
	// Return nature of the exception to calling routine.

		return Buffer;
}

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'QMXException.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

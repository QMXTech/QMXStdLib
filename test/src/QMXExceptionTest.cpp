////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QMXExceptionTest.cpp
// Robert M. Baker | Created : 29FEB12 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.1.0
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::QMXException' class.
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../include/QMXExceptionTest.hpp"

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::QMXException' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( QMXExceptionTest, DefaultConstructedWorks )
{
	// Perform unit test for 'QMXException' class using a default constructed object.

		try
		{
			throw QMXException();
		}
		catch( const QMXException& except )
		{
			ASSERT_TRUE( !strlen( except.getRootID() ) );
			ASSERT_TRUE( !strlen( except.getModuleID() ) );
			ASSERT_TRUE( !strlen( except.getEventIndex() ) );
			ASSERT_TRUE( !strlen( except.getEventData() ) );
			ASSERT_TRUE( !strlen( except.getStackTrace() ) );
			ASSERT_TRUE( !strlen( except.getMessage() ) );
			ASSERT_STREQ( "QMXStdLib::QMXException", except.what() );
		}
}

TEST( QMXExceptionTest, CustomConstructedWorks )
{
	// Create local variables.

		QMXException exceptions[] = {
			QMXException( "QMXStdLib", "Class::method", "DEADBEEF" ),
		   QMXException( "QMXStdLib", "Class::method", "DEADBEEF", "12345" ),
		   QMXException( "QMXStdLib", "Class::method", "DEADBEEF", "", "main->AppManager::start->Class::method" ),
		   QMXException( "QMXStdLib", "Class::method", "DEADBEEF", "12345", "main->AppManager::start->Class::method" )
		};

		const char* expectedEventData[] = {
			"",
		   "12345",
		   "",
		   "12345"
		};

		const char* expectedStackTrace[] = {
			"",
		   "",
		   "main->AppManager::start->Class::method",
		   "main->AppManager::start->Class::method"
		};

		const char* expectedBuffer[] = {
			"",
		   " : 12345",
		   "\n\nStack Trace: main->AppManager::start->Class::method",
		   " : 12345\n\nStack Trace: main->AppManager::start->Class::method"
		};

		char buffer[ MAX_BUFFER_SIZE ];

	// Perform unit test for 'QMXException' class using custom constructed objects.

		for( size_t index = 0; index < ARRAY_SIZE( exceptions ); index++ )
		{
			try
			{
				throw exceptions[ index ];
			}
			catch( const QMXException& except )
			{
				ASSERT_STREQ( "QMXStdLib", except.getRootID() );
				ASSERT_STREQ( "Class::method", except.getModuleID() );
				ASSERT_STREQ( "DEADBEEF", except.getEventIndex() );
				ASSERT_STREQ( expectedEventData[ index ], except.getEventData() );
				ASSERT_STREQ( expectedStackTrace[ index ], except.getStackTrace() );
				ASSERT_STREQ( "QMXStdLib.EventMessages.<LL>_<CC>.DEADBEEF", except.getMessage() );
				strcpy( buffer, "Exception occurred in 'QMXStdLib::Class::method' -> QMXStdLib.EventMessages.<LL>_<CC>.DEADBEEF" );
				strcat( buffer, expectedBuffer[ index ] );
				ASSERT_STREQ( buffer, except.what() );
			}
		}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'QMXExceptionTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

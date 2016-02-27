////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QMXExceptionTest.cpp
// Robert M. Baker | Created : 29FEB12 | Last Modified : 29JAN16 by Robert M. Baker
// Version : 1.1.0
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::QMXException' class.
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <QMXExceptionTest.hpp>

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
		catch( const QMXException& TargetException )
		{
			ASSERT_TRUE( !strlen( TargetException.GetRootID() ) );
			ASSERT_TRUE( !strlen( TargetException.GetModuleID() ) );
			ASSERT_TRUE( !strlen( TargetException.GetEventIndex() ) );
			ASSERT_TRUE( !strlen( TargetException.GetEventData() ) );
			ASSERT_TRUE( !strlen( TargetException.GetStackTrace() ) );
			ASSERT_TRUE( !strlen( TargetException.GetMessage() ) );
			ASSERT_STREQ( "QMXStdLib::QMXException", TargetException.what() );
		}
}

TEST( QMXExceptionTest, CustomConstructedWorks )
{
	// Create local variables.

		QMXException Exceptions[] = { QMXException( "QMXStdLib", "Class::Method", "DEADBEEF" ),
		                              QMXException( "QMXStdLib", "Class::Method", "DEADBEEF", "12345" ),
		                              QMXException( "QMXStdLib", "Class::Method", "DEADBEEF", "", "main->AppManager::Start->Class::Method" ),
		                              QMXException( "QMXStdLib", "Class::Method", "DEADBEEF", "12345", "main->AppManager::Start->Class::Method" ) };
		const char* ExpectedEventData[] = { "",
		                                    "12345",
		                                    "",
		                                    "12345" };
		const char* ExpectedStackTrace[] = { "",
		                                     "",
		                                     "main->AppManager::Start->Class::Method",
		                                     "main->AppManager::Start->Class::Method" };
		const char* ExpectedBuffer[] = { "",
		                                 " : 12345",
		                                 "\n\nStack Trace: main->AppManager::Start->Class::Method",
		                                 " : 12345\n\nStack Trace: main->AppManager::Start->Class::Method" };
		char Buffer[ MAX_BUFFER_SIZE ];

	// Perform unit test for 'QMXException' class using custom constructed objects.

		for( size_t Index = 0; Index < ARRAY_SIZE( Exceptions ); Index++ )
		{
			try
			{
				throw Exceptions[ Index ];
			}
			catch( const QMXException& TargetException )
			{
				ASSERT_STREQ( "QMXStdLib", TargetException.GetRootID() );
				ASSERT_STREQ( "Class::Method", TargetException.GetModuleID() );
				ASSERT_STREQ( "DEADBEEF", TargetException.GetEventIndex() );
				ASSERT_STREQ( ExpectedEventData[ Index ], TargetException.GetEventData() );
				ASSERT_STREQ( ExpectedStackTrace[ Index ], TargetException.GetStackTrace() );
				ASSERT_STREQ( "QMXStdLib.EventMessages.<LL>_<CC>.DEADBEEF", TargetException.GetMessage() );
				strcpy( Buffer, "Exception ocurred in 'QMXStdLib::Class::Method' -> QMXStdLib.EventMessages.<LL>_<CC>.DEADBEEF" );
				strcat( Buffer, ExpectedBuffer[ Index ] );
				ASSERT_STREQ( Buffer, TargetException.what() );
			}
		}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'QMXExceptionTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

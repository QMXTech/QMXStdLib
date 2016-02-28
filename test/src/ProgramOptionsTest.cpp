////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ProgramOptionsTest.cpp
// Robert M. Baker | Created : 24OCT13 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.2
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::ProgramOptions' class.
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

#include "../include/ProgramOptionsTest.hpp"

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::ProgramOptions' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( ProgramOptionsTest, SaveConfigFileWorks )
{
	// Create local variables.

		ProgramOptions::PointerType Instance = ProgramOptions::Create();
		string TestSaveFile = BASE_PATH + "TestSave.cfg";
		ifstream ConfigFile;
		char Buffer[ MAX_BUFFER_SIZE ];
		string Line;
		size_t FileIndex = Null;
		string Assignment( 1, PROGRAMOPTIONS_ASSIGNMENT_OPERATOR );
		string Comment( 1, PROGRAMOPTIONS_COMMENT_INITIATOR );
		string DelimiterLeft( 1, PROGRAMOPTIONS_GROUP_DELIMITER_LEFT );
		string DelimiterRight( 1, PROGRAMOPTIONS_GROUP_DELIMITER_RIGHT );
		string ExpectedResults[] = { ( Comment + " TestSave.cfg" ),
		                             "",
		                             ( DelimiterLeft + PROGRAMOPTIONS_GROUP_DEFAULT + DelimiterRight ),
		                             ( "alpha " + Assignment + " FooBar" ),
		                             ( "bit-mask " + Assignment + " 1337" ),
		                             "",
		                             ( DelimiterLeft + "TestGroup1" + DelimiterRight ),
		                             ( "bravo " + Assignment + " B2" ),
		                             ( "charlie " + Assignment + " C3" ),
		                             "",
		                             ( DelimiterLeft + "TestGroup2" + DelimiterRight ),
		                             ( "delta " + Assignment + " D4" ),
		                             ( "echo " + Assignment + " E5" ),
		                             "",
		                             "" };

	// Perform unit test for 'SaveConfigFile' method.

		ASSERT_THROW( PROGRAM_OPTIONS.ParseConfigFile( ( BASE_PATH + "NonExistent" ) ), QMXException );
		PROGRAM_OPTIONS.ParseConfigFile( ( BASE_PATH + "Test.cfg" ) );
		PROGRAM_OPTIONS.SaveConfigFile( TestSaveFile );
		ConfigFile.open( TestSaveFile );
		ASSERT_FALSE( ConfigFile.fail() );
		ConfigFile.getline( Buffer, MAX_BUFFER_SIZE );

		while( ConfigFile.good() )
		{
			Line = Buffer;
			ASSERT_EQ( ExpectedResults[ FileIndex++ ], Line );
			ConfigFile.getline( Buffer, MAX_BUFFER_SIZE );
		}

		ASSERT_EQ( ( ARRAY_SIZE( ExpectedResults ) - 1 ), FileIndex );
		ConfigFile.clear();
		ConfigFile.close();
		ASSERT_FALSE( ConfigFile.fail() );
		boost::filesystem::remove( TestSaveFile );
}

TEST( ProgramOptionsTest, IsToggleOptionPresentWorks )
{
	// Create local variables.

		ProgramOptions::PointerType Instance = ProgramOptions::Create();
		char Argument1[] = "--bit-mask=11";
		char Argument2[] = "--TestGroup1.bravo=2B";
		char Argument3[] = "--TestGroup2.delta=4D";
		char Argument4[] = "Foo.txt";
		char Argument5[] = "--help";
		char Argument6[] = "Bar.txt";
		char Argument7[] = "-zaybx";
		char* ArgumentValues[] = { Argument1,
		                           Argument2,
		                           Argument3,
		                           Argument4,
		                           Argument5,
		                           Argument6,
		                           Argument7 };

	// Perform unit test for 'IsToggleOptionPresent' method.

		PROGRAM_OPTIONS.ParseCommandLine( ARRAY_SIZE( ArgumentValues ), ArgumentValues );
		ASSERT_FALSE( PROGRAM_OPTIONS.IsToggleOptionPresent( "v" ) );
		ASSERT_FALSE( PROGRAM_OPTIONS.IsToggleOptionPresent( "w" ) );
		ASSERT_TRUE( PROGRAM_OPTIONS.IsToggleOptionPresent( "x" ) );
		ASSERT_TRUE( PROGRAM_OPTIONS.IsToggleOptionPresent( "y" ) );
		ASSERT_TRUE( PROGRAM_OPTIONS.IsToggleOptionPresent( "z" ) );
}

TEST( ProgramOptionsTest, IsCommandOptionPresentWorks )
{
	// Create local variables.

		ProgramOptions::PointerType Instance = ProgramOptions::Create();
		char Argument1[] = "--bit-mask=11";
		char Argument2[] = "--TestGroup1.bravo=2B";
		char Argument3[] = "--TestGroup2.delta=4D";
		char Argument4[] = "Foo.txt";
		char Argument5[] = "--help";
		char Argument6[] = "Bar.txt";
		char Argument7[] = "-zaybx";
		char* ArgumentValues[] = { Argument1,
		                           Argument2,
		                           Argument3,
		                           Argument4,
		                           Argument5,
		                           Argument6,
		                           Argument7 };

	// Perform unit test for 'IsCommandOptionPresent' method.

		PROGRAM_OPTIONS.ParseCommandLine( ARRAY_SIZE( ArgumentValues ), ArgumentValues );
		ASSERT_FALSE( PROGRAM_OPTIONS.IsCommandOptionPresent( "version" ) );
		ASSERT_TRUE( PROGRAM_OPTIONS.IsCommandOptionPresent( "help" ) );
}

TEST( ProgramOptionsTest, GetConfigOptionWorks )
{
	// Create local variables.

		ProgramOptions::PointerType Instance = ProgramOptions::Create();
		char Argument1[] = "--bit-mask=11";
		char Argument2[] = "--TestGroup1.bravo=Bubble";
		char Argument3[] = "--TestGroup2.delta=DingBat";
		char Argument4[] = "Foo.txt";
		char Argument5[] = "--help";
		char Argument6[] = "Bar.txt";
		char Argument7[] = "-zaybx";
		char* ArgumentValues[] = { Argument1,
		                           Argument2,
		                           Argument3,
		                           Argument4,
		                           Argument5,
		                           Argument6,
		                           Argument7 };

	// Perform unit test for 'GetConfigOption' method.

		PROGRAM_OPTIONS.ParseCommandLine( ARRAY_SIZE( ArgumentValues ), ArgumentValues );
		ASSERT_EQ( string( "" ), PROGRAM_OPTIONS.GetConfigOption( "config-path" ) );
		ASSERT_EQ( string( "11" ), PROGRAM_OPTIONS.GetConfigOption( "bit-mask" ) );
		ASSERT_EQ( string( "Bubble" ), PROGRAM_OPTIONS.GetConfigOption( "TestGroup1.bravo" ) );
		ASSERT_EQ( string( "DingBat" ), PROGRAM_OPTIONS.GetConfigOption( "TestGroup2.delta" ) );
		PROGRAM_OPTIONS.ParseConfigFile( ( BASE_PATH + "Test.cfg" ) );
		ASSERT_EQ( string( "FooBar" ), PROGRAM_OPTIONS.GetConfigOption( "alpha" ) );
		ASSERT_EQ( string( "1337" ), PROGRAM_OPTIONS.GetConfigOption( "bit-mask" ) );
		ASSERT_EQ( string( "B2" ), PROGRAM_OPTIONS.GetConfigOption( "TestGroup1.bravo" ) );
		ASSERT_EQ( string( "D4" ), PROGRAM_OPTIONS.GetConfigOption( "TestGroup2.delta" ) );
}

TEST( ProgramOptionsTest, SetConfigOptionWorks )
{
	// Create local variables.

		ProgramOptions::PointerType Instance = ProgramOptions::Create();
		StringPair TestOptions[] = { make_pair( "bit-mask", "42" ),
		                             make_pair( "TestGroup1.bravo", "Booger" ),
		                             make_pair( "TestGroup1.bit-mask", "84" ),
		                             make_pair( "TestGroup2.delta", "DungBeetle" ),
		                             make_pair( "TestGroup2.bit-mask", "168" ) };
		string ExpectedResults1[] = { "1337",
		                              "B2",
		                              "",
		                              "D4",
		                              "" };
		string ExpectedResults2[] = { "42",
		                              "Booger",
		                              "",
		                              "DungBeetle",
		                              "" };

	// Perform unit test for 'SetConfigOption' method.

		PROGRAM_OPTIONS.ParseConfigFile( ( BASE_PATH + "Test.cfg" ) );

		for( size_t Index = 0; Index < ARRAY_SIZE( TestOptions ); Index++ )
		{
			ASSERT_EQ( ExpectedResults1[ Index ], PROGRAM_OPTIONS.GetConfigOption( TestOptions[ Index ].first ) );
			PROGRAM_OPTIONS.SetConfigOption( TestOptions[ Index ].first, TestOptions[ Index ].second );
			ASSERT_EQ( ExpectedResults2[ Index ], PROGRAM_OPTIONS.GetConfigOption( TestOptions[ Index ].first ) );
		}

		PROGRAM_OPTIONS.ParseConfigFile( ( BASE_PATH + "Test.cfg" ) );

		for( size_t Index = 0; Index < ARRAY_SIZE( TestOptions ); Index++ )
		{
			ASSERT_EQ( ExpectedResults1[ Index ], PROGRAM_OPTIONS.GetConfigOption( TestOptions[ Index ].first ) );
			PROGRAM_OPTIONS.SetConfigOption( TestOptions[ Index ].first, TestOptions[ Index ].second, true );
			ASSERT_EQ( TestOptions[ Index ].second, PROGRAM_OPTIONS.GetConfigOption( TestOptions[ Index ].first ) );
		}
}

TEST( ProgramOptionsTest, RemoveConfigOptionWorks )
{
	// Create local variables.

		ProgramOptions::PointerType Instance = ProgramOptions::Create();
		StringPair TestOptions[] = { make_pair( "bit-mask", "42" ),
		                             make_pair( "TestGroup1.bravo", "Booger" ),
		                             make_pair( "TestGroup1.bit-mask", "84" ),
		                             make_pair( "TestGroup2.delta", "DungBeetle" ),
		                             make_pair( "TestGroup2.bit-mask", "168" ) };

	// Perform unit test for 'RemoveConfigOption' method.

		for( size_t Index = 0; Index < ARRAY_SIZE( TestOptions ); Index++ )
		{
			PROGRAM_OPTIONS.SetConfigOption( TestOptions[ Index ].first, TestOptions[ Index ].second, true );
			ASSERT_EQ( TestOptions[ Index ].second, PROGRAM_OPTIONS.GetConfigOption( TestOptions[ Index ].first ) );
			PROGRAM_OPTIONS.RemoveConfigOption( TestOptions[ Index ].first );
			ASSERT_EQ( string ( "" ), PROGRAM_OPTIONS.GetConfigOption( TestOptions[ Index ].first ) );
		}
}

TEST( ProgramOptionsTest, GetPositionalOptionWorks )
{
	// Create local variables.

		ProgramOptions::PointerType Instance = ProgramOptions::Create();
		char Argument1[] = "--bit-mask=11";
		char Argument2[] = "--TestGroup1.bravo=Bubble";
		char Argument3[] = "--TestGroup2.delta=DingBat";
		char Argument4[] = "Foo.txt";
		char Argument5[] = "--help";
		char Argument6[] = "Bar.txt";
		char Argument7[] = "-zaybx";
		char* ArgumentValues[] = { Argument1,
		                           Argument2,
		                           Argument3,
		                           Argument4,
		                           Argument5,
		                           Argument6,
		                           Argument7 };

	// Perform unit test for 'GetPositionalOption' method.

		PROGRAM_OPTIONS.ParseCommandLine( ARRAY_SIZE( ArgumentValues ), ArgumentValues );
		ASSERT_EQ( string( "Foo.txt" ), PROGRAM_OPTIONS.GetPositionalOption( 0 ) );
		ASSERT_EQ( string( "Bar.txt" ), PROGRAM_OPTIONS.GetPositionalOption( 1 ) );
		ASSERT_EQ( string( "" ), PROGRAM_OPTIONS.GetPositionalOption( 2 ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ProgramOptionsTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

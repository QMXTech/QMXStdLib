////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ProgramOptionsTest.cpp
// Robert M. Baker | Created : 24OCT13 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.0.0
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::ProgramOptions' class.
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

#include "../include/ProgramOptionsTest.hpp"

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::ProgramOptions' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( ProgramOptionsTest, SaveConfigFileWorks )
{
	// Create local variables.

		ProgramOptions::InstancePtr instance = ProgramOptions::create();
		string testSaveFile = BASE_PATH + "TestSave.cfg";
		ifstream configFile;
		char buffer[ MAX_BUFFER_SIZE ];
		string line;
		size_t fileIndex = UNSET;
		string assignment( 1, PROGRAMOPTIONS_ASSIGNMENT_OPERATOR );
		string comment( 1, PROGRAMOPTIONS_COMMENT_INITIATOR );
		string delimiterLeft( 1, PROGRAMOPTIONS_GROUP_DELIMITER_LEFT );
		string delimiterRight( 1, PROGRAMOPTIONS_GROUP_DELIMITER_RIGHT );

		string expectedResults[] = {
			( comment + " TestSave.cfg" ),
		   "",
		   ( delimiterLeft + PROGRAMOPTIONS_GROUP_DEFAULT + delimiterRight ),
		   ( "alpha " + assignment + " FooBar" ),
		   ( "bit-mask " + assignment + " 1337" ),
		   "",
		   ( delimiterLeft + "TestGroup1" + delimiterRight ),
		   ( "bravo " + assignment + " B2" ),
		   ( "charlie " + assignment + " C3" ),
		   "",
		   ( delimiterLeft + "TestGroup2" + delimiterRight ),
		   ( "delta " + assignment + " D4" ),
		   ( "echo " + assignment + " E5" ),
		   "",
		   ""
		};

	// Perform unit test for 'saveConfigFile' method.

		ASSERT_THROW( PROGRAM_OPTIONS.parseConfigFile( ( BASE_PATH + "NonExistent" ) ), QMXException );
		PROGRAM_OPTIONS.parseConfigFile( ( BASE_PATH + "Test.cfg" ) );
		PROGRAM_OPTIONS.saveConfigFile( testSaveFile );
		configFile.open( testSaveFile );
		ASSERT_FALSE( configFile.fail() );
		configFile.getline( buffer, MAX_BUFFER_SIZE );

		while( configFile.good() )
		{
			line = buffer;
			ASSERT_EQ( expectedResults[ fileIndex++ ], line );
			configFile.getline( buffer, MAX_BUFFER_SIZE );
		}

		ASSERT_EQ( ( ARRAY_SIZE( expectedResults ) - 1 ), fileIndex );
		configFile.clear();
		configFile.close();
		ASSERT_FALSE( configFile.fail() );
		boost::filesystem::remove( testSaveFile );
}

TEST( ProgramOptionsTest, IsToggleOptionPresentWorks )
{
	// Create local variables.

		ProgramOptions::InstancePtr instance = ProgramOptions::create();
		char argument1[] = "--bit-mask=11";
		char argument2[] = "--TestGroup1.bravo=2B";
		char argument3[] = "--TestGroup2.delta=4D";
		char argument4[] = "Foo.txt";
		char argument5[] = "--help";
		char argument6[] = "Bar.txt";
		char argument7[] = "-zaybx";

		char* argumentValues[] = {
			argument1,
		   argument2,
		   argument3,
		   argument4,
		   argument5,
		   argument6,
		   argument7
		};

	// Perform unit test for 'isToggleOptionPresent' method.

		PROGRAM_OPTIONS.parseCommandLine( ARRAY_SIZE( argumentValues ), argumentValues );
		ASSERT_FALSE( PROGRAM_OPTIONS.isToggleOptionPresent( "v" ) );
		ASSERT_FALSE( PROGRAM_OPTIONS.isToggleOptionPresent( "w" ) );
		ASSERT_TRUE( PROGRAM_OPTIONS.isToggleOptionPresent( "x" ) );
		ASSERT_TRUE( PROGRAM_OPTIONS.isToggleOptionPresent( "y" ) );
		ASSERT_TRUE( PROGRAM_OPTIONS.isToggleOptionPresent( "z" ) );
}

TEST( ProgramOptionsTest, IsCommandOptionPresentWorks )
{
	// Create local variables.

		ProgramOptions::InstancePtr instance = ProgramOptions::create();
		char argument1[] = "--bit-mask=11";
		char argument2[] = "--TestGroup1.bravo=2B";
		char argument3[] = "--TestGroup2.delta=4D";
		char argument4[] = "Foo.txt";
		char argument5[] = "--help";
		char argument6[] = "Bar.txt";
		char argument7[] = "-zaybx";

		char* argumentValues[] = {
			argument1,
		   argument2,
		   argument3,
		   argument4,
		   argument5,
		   argument6,
		   argument7
		};

	// Perform unit test for 'isCommandOptionPresent' method.

		PROGRAM_OPTIONS.parseCommandLine( ARRAY_SIZE( argumentValues ), argumentValues );
		ASSERT_FALSE( PROGRAM_OPTIONS.isCommandOptionPresent( "version" ) );
		ASSERT_TRUE( PROGRAM_OPTIONS.isCommandOptionPresent( "help" ) );
}

TEST( ProgramOptionsTest, GetConfigOptionWorks )
{
	// Create local variables.

		ProgramOptions::InstancePtr instance = ProgramOptions::create();
		char argument1[] = "--bit-mask=11";
		char argument2[] = "--TestGroup1.bravo=Bubble";
		char argument3[] = "--TestGroup2.delta=DingBat";
		char argument4[] = "Foo.txt";
		char argument5[] = "--help";
		char argument6[] = "Bar.txt";
		char argument7[] = "-zaybx";

		char* argumentValues[] = {
			argument1,
			argument2,
			argument3,
			argument4,
			argument5,
			argument6,
			argument7
		};

	// Perform unit test for 'getConfigOption' method.

		PROGRAM_OPTIONS.parseCommandLine( ARRAY_SIZE( argumentValues ), argumentValues );
		ASSERT_EQ( string( "" ), PROGRAM_OPTIONS.getConfigOption( "config-path" ) );
		ASSERT_EQ( string( "11" ), PROGRAM_OPTIONS.getConfigOption( "bit-mask" ) );
		ASSERT_EQ( string( "Bubble" ), PROGRAM_OPTIONS.getConfigOption( "TestGroup1.bravo" ) );
		ASSERT_EQ( string( "DingBat" ), PROGRAM_OPTIONS.getConfigOption( "TestGroup2.delta" ) );
		PROGRAM_OPTIONS.parseConfigFile( ( BASE_PATH + "Test.cfg" ) );
		ASSERT_EQ( string( "FooBar" ), PROGRAM_OPTIONS.getConfigOption( "alpha" ) );
		ASSERT_EQ( string( "1337" ), PROGRAM_OPTIONS.getConfigOption( "bit-mask" ) );
		ASSERT_EQ( string( "B2" ), PROGRAM_OPTIONS.getConfigOption( "TestGroup1.bravo" ) );
		ASSERT_EQ( string( "D4" ), PROGRAM_OPTIONS.getConfigOption( "TestGroup2.delta" ) );
}

TEST( ProgramOptionsTest, GetConfigOptionsWorks )
{
	// Create local variables.

		ProgramOptions::InstancePtr instance = ProgramOptions::create();
		char argument1[] = "--bit-mask=11";
		char argument2[] = "--TestGroup1.bravo=Bubble";
		char argument3[] = "--TestGroup2.delta=DingBat";
		char argument4[] = "Foo.txt";
		char argument5[] = "--help";
		char argument6[] = "Bar.txt";
		char argument7[] = "-zaybx";

		char* argumentValues[] = {
			argument1,
		   argument2,
		   argument3,
		   argument4,
		   argument5,
		   argument6,
		   argument7
		};

		ProgramOptions::ConfigMap configOptions;

		string expectedGroups[] = {
			"Global",
		   "TestGroup1",
		   "TestGroup2"
		};

		string expectedKeys[] = {
			"bit-mask",
		   "bravo",
		   "delta"
		};

		string expectedValues[] = {
			"11",
		   "Bubble",
		   "DingBat"
		};

	// Perform unit test for 'getConfigOptions' method.

		PROGRAM_OPTIONS.parseCommandLine( ARRAY_SIZE( argumentValues ), argumentValues );
		configOptions = PROGRAM_OPTIONS.getConfigOptions();

		for( size_t index = 0; index < ARRAY_SIZE( expectedGroups ); index++ )
		{
			ASSERT_EQ( expectedValues[ index ], configOptions[ expectedGroups[ index ] ][ expectedKeys[ index ] ] );
		}
}

TEST( ProgramOptionsTest, SetConfigOptionWorks )
{
	// Create local variables.

		ProgramOptions::InstancePtr instance = ProgramOptions::create();

		StringPair testOptions[] = {
			make_pair( "bit-mask", "42" ),
		   make_pair( "TestGroup1.bravo", "Booger" ),
		   make_pair( "TestGroup1.bit-mask", "84" ),
		   make_pair( "TestGroup2.delta", "DungBeetle" ),
		   make_pair( "TestGroup2.bit-mask", "168" )
		};
	
		string expectedResults1[] = {
			"1337",
		   "B2",
		   "",
		   "D4",
		   ""
		};

		string expectedResults2[] = {
			"42",
		   "Booger",
		   "",
		   "DungBeetle",
		   ""
		};

	// Perform unit test for 'setConfigOption' method.

		PROGRAM_OPTIONS.parseConfigFile( ( BASE_PATH + "Test.cfg" ) );

		for( size_t index = 0; index < ARRAY_SIZE( testOptions ); index++ )
		{
			ASSERT_EQ( expectedResults1[ index ], PROGRAM_OPTIONS.getConfigOption( testOptions[ index ].first ) );
			PROGRAM_OPTIONS.setConfigOption( testOptions[ index ].first, testOptions[ index ].second );
			ASSERT_EQ( expectedResults2[ index ], PROGRAM_OPTIONS.getConfigOption( testOptions[ index ].first ) );
		}

		PROGRAM_OPTIONS.parseConfigFile( ( BASE_PATH + "Test.cfg" ) );

		for( size_t index = 0; index < ARRAY_SIZE( testOptions ); index++ )
		{
			ASSERT_EQ( expectedResults1[ index ], PROGRAM_OPTIONS.getConfigOption( testOptions[ index ].first ) );
			PROGRAM_OPTIONS.setConfigOption( testOptions[ index ].first, testOptions[ index ].second, true );
			ASSERT_EQ( testOptions[ index ].second, PROGRAM_OPTIONS.getConfigOption( testOptions[ index ].first ) );
		}
}

TEST( ProgramOptionsTest, SetConfigOptionsWorks )
{
	// Create local variables.

		ProgramOptions::InstancePtr instance = ProgramOptions::create();
		ProgramOptions::ConfigMap configOptions;

		tuple< string, string, string > testOptions[] = {
			make_tuple( "Global", "bit-mask", "42" ),
		   make_tuple( "TestGroup1", "bravo", "Booger" ),
		   make_tuple( "TestGroup1", "bit-mask", "84" ),
		   make_tuple( "TestGroup2", "delta", "DungBeetle" ),
		   make_tuple( "TestGroup2", "bit-mask", "168" )
		};

		string targetOption;

	// Perform unit test for 'setConfigOptions' method.

		for( size_t index = 0; index < ARRAY_SIZE( testOptions ); index++ )
			configOptions[ get< 0 >( testOptions[ index ] ) ][ get< 1 >( testOptions[ index ] ) ] = get< 2 >( testOptions[ index ] );

		PROGRAM_OPTIONS.setConfigOptions( configOptions );

		for( size_t index = 0; index < ARRAY_SIZE( testOptions ); index++ )
		{
			targetOption = get< 0 >( testOptions[ index ] ) + "." + get< 1 >( testOptions[ index ] );
			ASSERT_EQ( get< 2 >( testOptions[ index ] ), PROGRAM_OPTIONS.getConfigOption( targetOption ) );
		}
}

TEST( ProgramOptionsTest, RemoveConfigOptionWorks )
{
	// Create local variables.

		ProgramOptions::InstancePtr instance = ProgramOptions::create();

		StringPair testOptions[] = {
			make_pair( "bit-mask", "42" ),
		   make_pair( "TestGroup1.bravo", "Booger" ),
		   make_pair( "TestGroup1.bit-mask", "84" ),
		   make_pair( "TestGroup2.delta", "DungBeetle" ),
		   make_pair( "TestGroup2.bit-mask", "168" )
		};

	// Perform unit test for 'removeConfigOption' method.

		for( size_t index = 0; index < ARRAY_SIZE( testOptions ); index++ )
		{
			PROGRAM_OPTIONS.setConfigOption( testOptions[ index ].first, testOptions[ index ].second, true );
			ASSERT_EQ( testOptions[ index ].second, PROGRAM_OPTIONS.getConfigOption( testOptions[ index ].first ) );
			PROGRAM_OPTIONS.removeConfigOption( testOptions[ index ].first );
			ASSERT_EQ( string ( "" ), PROGRAM_OPTIONS.getConfigOption( testOptions[ index ].first ) );
		}
}

TEST( ProgramOptionsTest, GetPositionalOptionWorks )
{
	// Create local variables.

		ProgramOptions::InstancePtr instance = ProgramOptions::create();
		char argument1[] = "--bit-mask=11";
		char argument2[] = "--TestGroup1.bravo=Bubble";
		char argument3[] = "--TestGroup2.delta=DingBat";
		char argument4[] = "Foo.txt";
		char argument5[] = "--help";
		char argument6[] = "Bar.txt";
		char argument7[] = "-zaybx";

		char* argumentValues[] = {
			argument1,
		   argument2,
		   argument3,
		   argument4,
		   argument5,
		   argument6,
		   argument7
		};

	// Perform unit test for 'getPositionalOption' method.

		PROGRAM_OPTIONS.parseCommandLine( ARRAY_SIZE( argumentValues ), argumentValues );
		ASSERT_EQ( string( "Foo.txt" ), PROGRAM_OPTIONS.getPositionalOption( 0 ) );
		ASSERT_EQ( string( "Bar.txt" ), PROGRAM_OPTIONS.getPositionalOption( 1 ) );
		ASSERT_EQ( string( "" ), PROGRAM_OPTIONS.getPositionalOption( 2 ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ProgramOptionsTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

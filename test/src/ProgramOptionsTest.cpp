////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ProgramOptionsTest.cpp
// Robert M. Baker | Created : 24OCT13 | Last Modified : 16FEB16 by Robert M. Baker
// Version : 1.0.0
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

#include <ProgramOptionsTest.hpp>

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::ProgramOptions' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( ProgramOptionsTest, IsToggleOptionPresentWorks )
{
	// Create local variables.

		ProgramOptions::PointerType Instance = ProgramOptions::Create();
		char Argument1[] = "--bit-mask=11";
		char Argument2[] = "Foo.txt";
		char Argument3[] = "--help";
		char Argument4[] = "Bar.txt";
		char Argument5[] = "-zaybx";
		char* ArgumentValues[] = { Argument1,
		                           Argument2,
		                           Argument3,
		                           Argument4,
		                           Argument5 };

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
		char Argument2[] = "Foo.txt";
		char Argument3[] = "--help";
		char Argument4[] = "Bar.txt";
		char Argument5[] = "-zaybx";
		char* ArgumentValues[] = { Argument1,
		                           Argument2,
		                           Argument3,
		                           Argument4,
		                           Argument5 };

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
		char Argument2[] = "Foo.txt";
		char Argument3[] = "--help";
		char Argument4[] = "Bar.txt";
		char Argument5[] = "-zaybx";
		char* ArgumentValues[] = { Argument1,
		                           Argument2,
		                           Argument3,
		                           Argument4,
		                           Argument5 };

	// Perform unit test for 'GetConfigOption' method.

		PROGRAM_OPTIONS.ParseCommandLine( ARRAY_SIZE( ArgumentValues ), ArgumentValues );
		ASSERT_EQ( string( "" ), PROGRAM_OPTIONS.GetConfigOption( "config-path" ) );
		ASSERT_EQ( string( "11" ), PROGRAM_OPTIONS.GetConfigOption( "bit-mask" ) );
		ASSERT_THROW( PROGRAM_OPTIONS.ParseConfigFile( ( BASE_PATH + "NonExistent" ) ), QMXException );
		PROGRAM_OPTIONS.ParseConfigFile( ( BASE_PATH + "Test.cfg" ) );
		ASSERT_EQ( string( "FooBar" ), PROGRAM_OPTIONS.GetConfigOption( "alpha" ) );
		ASSERT_EQ( string( "1337" ), PROGRAM_OPTIONS.GetConfigOption( "bit-mask" ) );
}

TEST( ProgramOptionsTest, GetPositionalOptionWorks )
{
	// Create local variables.

		ProgramOptions::PointerType Instance = ProgramOptions::Create();
		char Argument1[] = "--bit-mask=11";
		char Argument2[] = "Foo.txt";
		char Argument3[] = "--help";
		char Argument4[] = "Bar.txt";
		char Argument5[] = "-zaybx";
		char* ArgumentValues[] = { Argument1,
		                           Argument2,
		                           Argument3,
		                           Argument4,
		                           Argument5 };

	// Perform unit test for 'GetPositionalOption' method.

		PROGRAM_OPTIONS.ParseCommandLine( ARRAY_SIZE( ArgumentValues ), ArgumentValues );
		ASSERT_EQ( string( "Foo.txt" ), PROGRAM_OPTIONS.GetPositionalOption( 0 ) );
		ASSERT_EQ( string( "Bar.txt" ), PROGRAM_OPTIONS.GetPositionalOption( 1 ) );
		ASSERT_EQ( string( "" ), PROGRAM_OPTIONS.GetPositionalOption( 2 ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ProgramOptionsTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

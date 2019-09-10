////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DynamicLibraryTest.cpp
// Robert M. Baker | Created : 01JUL12 | Last Modified : 31OCT19 by Robert M. Baker
// Version : 2.3.0
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::DynamicLibrary' class.
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

#include "../include/DynamicLibraryTest.hpp"

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::DynamicLibrary' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( DynamicLibraryTest, LoadWorks )
{
	// Create local variables.

		string dynLibPathsBad[] = {
			"NonEmptyTestFile.txt",
			"NonExistent"
		};

		string dynLibPathGood = "TestLibrary";

		DynamicLibrary::InstancePtr instance = DynamicLibrary::create();

	// Perform unit test for 'load' method.

		for( size_t index = 0; index < ARRAY_SIZE( dynLibPathsBad ); index++ )
		{
			ASSERT_THROW( instance->load( ( BASE_PATH + dynLibPathsBad[ index ] ) ), QMXException );
		}

		instance->load( ( PLUGINS_PATH + dynLibPathGood + DYNLIB_EXTENSION ) );
}

TEST( DynamicLibraryTest, UnloadWorks )
{
	// Create local variables.

		DynamicLibrary::InstancePtr instance = DynamicLibrary::create();
		string dynLibPath = "TestLibrary";

	// Perform unit test for 'unload' method.

		ASSERT_THROW( instance->unload(), QMXException );
		instance->load( ( PLUGINS_PATH + dynLibPath + DYNLIB_EXTENSION ) );
		instance->unload();
}

TEST( DynamicLibraryTest, GetSymbolWorks )
{
	// Create local variables.

		DynamicLibrary::InstancePtr instance = DynamicLibrary::create();
		string dynLibPath = "TestLibrary";

	// Perform unit test for 'getSymbol' method.

		ASSERT_THROW( instance->getSymbol( "libraryFunction1" ), QMXException );
		instance->load( ( PLUGINS_PATH + dynLibPath + DYNLIB_EXTENSION ) );
		ASSERT_THROW( instance->getSymbol( "nonExistent" ), QMXException );
		ASSERT_TRUE( ( instance->getSymbol( "libraryFunction1" ) != nullptr ) );
		ASSERT_TRUE( ( instance->getSymbol( "libraryFunction2" ) != nullptr ) );
		ASSERT_TRUE( ( instance->getSymbol( "libraryFunction3" ) != nullptr ) );
		instance->unload();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'DynamicLibraryTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

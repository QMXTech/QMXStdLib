////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DynamicLibraryTest.cpp
// Robert M. Baker | Created : 01JUL12 | Last Modified : 15FEB16 by Robert M. Baker
// Version : 1.1.0
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::DynamicLibrary' class.
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

#include <DynamicLibraryTest.hpp>

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::DynamicLibrary' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( DynamicLibraryTest, LoadWorks )
{
	// Create local variables.

		DynamicLibrary::PointerType Instance = DynamicLibrary::Create();
		string DynLibPathsBad[] = { "NonEmptyTestFile.txt",
		                            "NonExistent" };
		string DynLibPathsGood[] = { "TestPlugin1",
		                             "TestPlugin2",
		                             "TestPlugin3" };

	// Perform unit test for 'Load' method.

		for( size_t Index = 0; Index < ARRAY_SIZE( DynLibPathsBad ); Index++ )
		{
			ASSERT_THROW( Instance->Load( ( BASE_PATH + DynLibPathsBad[ Index ] ) ), QMXException );
		}

		for( size_t Index = 0; Index < ARRAY_SIZE( DynLibPathsGood ); Index++ )
		{
			Instance->Load( ( PLUGINS_PATH + DynLibPathsGood[ Index ] + DYNLIB_EXTENSION ) );
		}
}

TEST( DynamicLibraryTest, UnloadWorks )
{
	// Create local variables.

		DynamicLibrary::PointerType Instance = DynamicLibrary::Create();
		string DynLibPaths[] = { "TestPlugin1",
		                         "TestPlugin2",
		                         "TestPlugin3" };

	// Perform unit test for 'Unload' method.

		for( size_t Index = 0; Index < ARRAY_SIZE( DynLibPaths ); Index++ )
		{
			ASSERT_THROW( Instance->Unload(), QMXException );
			Instance->Load( ( PLUGINS_PATH + DynLibPaths[ Index ] + DYNLIB_EXTENSION ) );
			Instance->Unload();
		}
}

TEST( DynamicLibraryTest, GetSymbolWorks )
{
	// Create local variables.

		DynamicLibrary::PointerType Instance = DynamicLibrary::Create();
		string DynLibPaths[] = { "TestPlugin1",
		                         "TestPlugin2",
		                         "TestPlugin3" };

	// Perform unit test for 'GetSymbol' method.

		for( size_t Index = 0; Index < ARRAY_SIZE( DynLibPaths ); Index++ )
		{
			ASSERT_THROW( Instance->GetSymbol( "PluginGetModule" ), QMXException );
			Instance->Load( ( PLUGINS_PATH + DynLibPaths[ Index ] + DYNLIB_EXTENSION ) );
			ASSERT_THROW( Instance->GetSymbol( "NonExistent" ), QMXException );
			ASSERT_TRUE( ( Instance->GetSymbol( "PluginGetModule" ) != nullptr ) );
			ASSERT_TRUE( ( Instance->GetSymbol( "PluginStart" ) != nullptr ) );
			ASSERT_TRUE( ( Instance->GetSymbol( "PluginStop" ) != nullptr ) );
			Instance->Unload();
		}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'DynamicLibraryTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

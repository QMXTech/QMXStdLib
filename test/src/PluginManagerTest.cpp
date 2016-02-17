////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PluginManagerTest.cpp
// Robert M. Baker | Created : 23APR12 | Last Modified : 16FEB16 by Robert M. Baker
// Version : 1.0.0
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::PluginManager' class.
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

#include <PluginManagerTest.hpp>

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::PluginManager' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( PluginManagerTest, RegisterModuleWorks )
{
	// Create local variables.

		PluginManager::PointerType Instance = PluginManager::Create();

	// Perform unit test for 'RegisterModule' method.

		PLUGIN_MANAGER.RegisterModule( "QMXStdLibTest" );
		ASSERT_THROW( PLUGIN_MANAGER.RegisterModule( "QMXStdLibTest" ), QMXException );
}

TEST( PluginManagerTest, UnregisterModuleWorks )
{
	// Create local variables.

		PluginManager::PointerType Instance = PluginManager::Create();

	// Perform unit test for 'UnregisterModule' method.

		ASSERT_THROW( PLUGIN_MANAGER.UnregisterModule( "QMXStdLibTest" ), QMXException );
		PLUGIN_MANAGER.RegisterModule( "QMXStdLibTest" );
		PLUGIN_MANAGER.UnregisterModule( "QMXStdLibTest" );
}

TEST( PluginManagerTest, AutoLoadWorks )
{
	// Create local variables.

		PluginManager::PointerType Instance = PluginManager::Create();
		string TestPathsBad[] = { "NonEmptyTestFile.txt",
		                          "TestDirectory" };

	// Perform unit test for 'AutoLoad' method.

		for( size_t Index = 0; Index < ARRAY_SIZE( TestPathsBad ); Index++ )
		{
			ASSERT_THROW( PLUGIN_MANAGER.AutoLoad( ( BASE_PATH + TestPathsBad[ Index ] ) ), QMXException );
		}

		ASSERT_THROW( PLUGIN_MANAGER.AutoLoad( PLUGINS_PATH ), QMXException );
		PLUGIN_MANAGER.RegisterModule( "QMXStdLibTest" );
		PLUGIN_MANAGER.AutoLoad( PLUGINS_PATH );
		ASSERT_THROW( PLUGIN_MANAGER.AutoLoad( PLUGINS_PATH ), QMXException );
}

TEST( PluginManagerTest, UnloadWorks )
{
	// Create local variables.

		PluginManager::PointerType Instance = PluginManager::Create();
		string PluginIDs[] = { "TestPlugin1",
		                       "TestPlugin2",
		                       "TestPlugin3" };

	// Perform unit test for 'Unload' method.

		PLUGIN_MANAGER.RegisterModule( "QMXStdLibTest" );
		PLUGIN_MANAGER.AutoLoad( PLUGINS_PATH );
		ASSERT_THROW( PLUGIN_MANAGER.Unload( "QMXStdLibTestX", "TestPlugin1" ), QMXException );
		ASSERT_THROW( PLUGIN_MANAGER.Unload( "QMXStdLibTest", "TestPluginX" ), QMXException );

		for( size_t Index = 0; Index < ARRAY_SIZE( PluginIDs ); Index++ )
			PLUGIN_MANAGER.Unload( "QMXStdLibTest", PluginIDs[ Index ] );
}

TEST( PluginManagerTest, GetPluginListWorks )
{
	// Create local variables.

		PluginManager::PointerType Instance = PluginManager::Create();
		PluginManager::PluginMap PluginList;
		PluginManager::PluginMap::iterator Iterator;
		string ExpectedIDs[] = { "TestPlugin1",
		                         "TestPlugin2",
		                         "TestPlugin3" };

	// Perform unit test for 'GetPluginList' method.

		PLUGIN_MANAGER.RegisterModule( "QMXStdLibTest" );
		PLUGIN_MANAGER.AutoLoad( PLUGINS_PATH );
		ASSERT_THROW( PLUGIN_MANAGER.GetPluginList( PluginList, "QMXStdLibTestX" ), QMXException );
		PLUGIN_MANAGER.GetPluginList( PluginList, "QMXStdLibTest" );
		ASSERT_EQ( 3u, PluginList.size() );

		for( size_t Index = 0; Index < ARRAY_SIZE( ExpectedIDs ); Index++ )
		{
			Iterator = PluginList.find( ExpectedIDs[ Index ] );
			ASSERT_NE( PluginList.end(), Iterator );
			ASSERT_EQ( 1u, Iterator->second.Major );
			ASSERT_EQ( 0u, Iterator->second.Minor );
			ASSERT_EQ( 0u, Iterator->second.Patch );
		}
}

TEST( PluginManagerTest, GetPluginMetaWorks )
{
	// Create local variables.

		PluginManager::PointerType Instance = PluginManager::Create();
		StringMap PluginMeta;
		StringMap::iterator Iterator;
		string PluginIDs[] = { "TestPlugin1",
		                       "TestPlugin2",
		                       "TestPlugin3" };
		string ExpectedKeys[] = { "Description",
		                          "Description",
		                          "Description" };
		string ExpectedValues[] = { "A simple plugin to test QMXStdLib's plugin framework (#1).",
		                            "A simple plugin to test QMXStdLib's plugin framework (#2).",
		                            "A simple plugin to test QMXStdLib's plugin framework (#3)." };

	// Perform unit test for 'GetPluginList' method.

		PLUGIN_MANAGER.RegisterModule( "QMXStdLibTest" );
		PLUGIN_MANAGER.AutoLoad( PLUGINS_PATH );
		ASSERT_THROW( PLUGIN_MANAGER.GetPluginMeta( PluginMeta, "QMXStdLibTestX", "TestPlugin1" ), QMXException );
		ASSERT_THROW( PLUGIN_MANAGER.GetPluginMeta( PluginMeta, "QMXStdLibTest", "TestPluginX" ), QMXException );

		for( size_t Index = 0; Index < ARRAY_SIZE( PluginIDs ); Index++ )
		{
			PLUGIN_MANAGER.GetPluginMeta( PluginMeta, "QMXStdLibTest", PluginIDs[ Index ] );
			ASSERT_EQ( 1u, PluginMeta.size() );
			Iterator = PluginMeta.begin();
			ASSERT_EQ( ExpectedKeys[ Index ], Iterator->first );
			ASSERT_EQ( ExpectedValues[ Index ], Iterator->second );
		}
}

TEST( PluginManagerTest, InitializeWorks )
{
	// Create local variables.

		PluginManager::PointerType Instance = PluginManager::Create();

	// Perform unit test for 'Initialize' method.

		PLUGIN_MANAGER.RegisterModule( "QMXStdLibTest" );
		PLUGIN_MANAGER.AutoLoad( PLUGINS_PATH );
		PLUGIN_MANAGER.Initialize();
		ASSERT_THROW( PLUGIN_MANAGER.Initialize(), QMXException );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'PluginManagerTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

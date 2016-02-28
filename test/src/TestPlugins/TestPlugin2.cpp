////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TestPlugin2.cpp
// Robert M. Baker | Created : 01JUL12 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.2
// This is a source file for 'QMXStdLibTest'; it defines the implementation for a test plugin.
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

#include "../../include/TestPlugins/TestPlugin2.hpp"

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Methods for the 'TestPlugin2' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TestPlugin2::TestPlugin2()
{
	// Initialize fields.

		MetaData[ "Description" ] = "A simple plugin to test QMXStdLib's plugin framework (#2).";
}

TestPlugin2::~TestPlugin2()
{
	// Do nothing.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods for the 'TestPlugin2' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string TestPlugin2::GetIDImp() const
{
	// Return unique plugin ID to calling routine.

		return "TestPlugin2";
}

Utility::VersionData TestPlugin2::GetVersionImp() const
{
	// Return plugin version to calling routine.

		return { 1, 0, 0 };
}

void TestPlugin2::GetMetaImp( StringMap& Target ) const
{
	// Set specified string map object to current meta data.

		Target = MetaData;
}

void TestPlugin2::InstallImp()
{
	// Do nothing.
}

void TestPlugin2::UninstallImp()
{
	// Do nothing.
}

void TestPlugin2::InitializeImp()
{
	// Do nothing.
}

void TestPlugin2::ShutdownImp()
{
	// Do nothing.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" string PluginGetModule()
{
	// Return dependent module ID to calling routine.

		return "QMXStdLibTest";
}

extern "C" void PluginStart( Plugin** Instance )
{
	// Start plugin.

		TestPlugin2Instance = new TestPlugin2();
		*Instance = TestPlugin2Instance;
		PLUGIN_MANAGER.Install( TestPlugin2Instance );
}

extern "C" void PluginStop()
{
	// Stop plugin.

		PLUGIN_MANAGER.Uninstall( TestPlugin2Instance );
		SAFE_DELETE( TestPlugin2Instance );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'TestPlugin2.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

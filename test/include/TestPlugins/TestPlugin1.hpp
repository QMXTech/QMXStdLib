////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TestPlugin1.hpp
// Robert M. Baker | Created : 01JUL12 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.2
// This is a header file for 'QMXStdLibTest'; it defines the interface for a test plugin.
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

#ifndef __QMX_QMXSTDLIBTEST_TESTPLUGIN1_HPP_
#define __QMX_QMXSTDLIBTEST_TESTPLUGIN1_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../../../include/PluginManager.hpp"
#include "../../../include/Mixins/Plugin.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'TestPlugin1' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TestPlugin1 : public QMXStdLib::Plugin
{
public:

	// Public Constructors

		TestPlugin1();

	// Destructor

		virtual ~TestPlugin1();

private:

	// Private Fields

		QMXStdLib::StringMap MetaData;

	// Private Methods

		std::string GetIDImp() const;
		QMXStdLib::Utility::VersionData GetVersionImp() const;
		void GetMetaImp( QMXStdLib::StringMap& Target ) const;
		void InstallImp();
		void UninstallImp();
		void InitializeImp();
		void ShutdownImp();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Global Variables
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TestPlugin1* TestPlugin1Instance = nullptr;

#endif // __QMX_QMXSTDLIBTEST_TESTPLUGIN1_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'TestPlugin1.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

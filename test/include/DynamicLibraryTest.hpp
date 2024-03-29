////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DynamicLibraryTest.hpp
// Robert M. Baker | Created : 01JUL12 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.3.0
// This is a header file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::DynamicLibrary' class.
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

#ifndef __QMX_QMXSTDLIBTEST_DYNAMICLIBRARYTEST_HPP_
#define __QMX_QMXSTDLIBTEST_DYNAMICLIBRARYTEST_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <gtest/gtest.h>

#include "../../include/QMXException.hpp"
#include "../../include/FileSystem.hpp"
#include "../../include/DynamicLibrary.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define BASE_PATH      "./TestDirectory/"

#ifdef _DEBUG
#	define PLUGINS_PATH ( BASE_PATH + std::string( "TestLibrary/debug/" ) )
#else
#	define PLUGINS_PATH ( BASE_PATH + std::string( "TestLibrary/release/" ) )
#endif // PLUGINS_PATH

#endif // __QMX_QMXSTDLIBTEST_DYNAMICLIBRARYTEST_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'DynamicLibraryTest.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

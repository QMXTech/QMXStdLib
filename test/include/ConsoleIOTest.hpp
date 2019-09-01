////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ConsoleIOTest.hpp
// Robert M. Baker | Created : 30JAN12 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.1.0
// This is a header file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::ConsoleIO' class.
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

#ifndef __QMX_QMXSTDLIBTEST_CONSOLEIOTEST_HPP_
#define __QMX_QMXSTDLIBTEST_CONSOLEIOTEST_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <string>
#include <gtest/gtest.h>

#include "../../include/ConsoleIO.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SET_TEST_DATA(x) resultBuffer.str( "" );  resultBuffer << x;  inputBuffer.str( ( resultBuffer.str() + '\n' ) );

#endif // __QMX_QMXSTDLIBTEST_CONSOLEIOTEST_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ConsoleIOTest.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

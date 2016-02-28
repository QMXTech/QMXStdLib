////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StackTracer.cpp
// Robert M. Baker | Created : 29FEB12 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.1
// This is a source file for 'QMXStdLib'; it defines the implementation for a stack tracer class.
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

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 29FEB12
  * @date    Last Modified : 27FEB16 by Robert M. Baker
  * @version 1.1.1
  *
  * @brief This source file defines the implementation for a stack tracer class.
  *
  * @section Description
  *
  * This source file defines the implementation for a stack tracer class.
  *
  * @section License
  *
  * Copyright (C) 2011-2016 QuantuMatriX Software, LLP.
  *
  * This file is part of 'QMXStdLib'.
  *
  * 'QMXStdLib' is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free
  * Software Foundation, either version 3 of the License, or (at your option) any later version.
  *
  * 'QMXStdLib' is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  * A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public License along with 'QMXStdLib'.  If not, see <http://www.gnu.org/licenses/>.
  */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../include/StackTracer.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Field Initializers for the 'StackTracer' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SharedMutex StackTracer::LocalMutex;
bool StackTracer::IsEnabled = false;
StringTLS StackTracer::ThreadID;
StackTracer::StackTraceMap StackTracer::StackTraces;

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'StackTracer.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

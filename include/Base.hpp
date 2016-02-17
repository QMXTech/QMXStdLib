////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Base.hpp
// Robert M. Baker | Created : 10DEC11 | Last Modified : 28JAN16 by Robert M. Baker
// Version : 1.0.0
// This is the base header file for 'QMXStdLib'; it defines data common to all modules.
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
  * @date    Created : 10DEC11
  * @date    Last Modified : 28JAN16 by Robert M. Baker
  * @version 1.0.0
  *
  * @brief This base header file defines data common to all modules.
  *
  * @section Description
  *
  * This base header file defines data common to all modules.
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

#ifndef __QMX_QMXSTDLIB_BASE_HPP_
#define __QMX_QMXSTDLIB_BASE_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Control Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define QMXSTDLIB_VER_MAJOR   1ull
#define QMXSTDLIB_VER_MINOR   0ull
#define QMXSTDLIB_VER_PATCH   0ull

#define QMX_PLATFORM_LINUX    1
#define QMX_PLATFORM_OSX      2
#define QMX_PLATFORM_WINDOWS  3

#define QMX_COMPILER_CLANG    1
#define QMX_COMPILER_GCC      2
#define QMX_COMPILER_MINGW    3

#ifndef __LP64__
#	define QMX_32BIT
#else
#	define QMX_64BIT
#endif // QMX_32BIT & QMX64BIT

#ifdef __linux__
#	define QMX_PLATFORM        QMX_PLATFORM_LINUX
#elif __MACH__
#	define QMX_PLATFORM        QMX_PLATFORM_OSX
#elif _WIN32
#	define QMX_PLATFORM        QMX_PLATFORM_WINDOWS
#else
#	error "Unsupported platform; aborting compile!"
#endif // QMX_PLATFORM

#if ( defined( __clang__ ) )
#  define QMX_COMPILER        QMX_COMPILER_CLANG
#elif( defined( __GNUC__ ) && !defined( __MINGW32__ ) )
#	define QMX_COMPILER        QMX_COMPILER_GCC
#elif( defined( __MINGW32__ ) )
#	define QMX_COMPILER        QMX_COMPILER_MINGW
#else
#	error "Unsupported compiler; aborting compile!"
#endif // QMX_COMPILER

#if ( ( QMX_PLATFORM == QMX_PLATFORM_WINDOWS ) && defined( QMX_64BIT ) )
#	define BOOST_USE_WINDOWS_H
#endif // BOOST_USE_WINDOWS_H

#if ( QMX_PLATFORM == QMX_PLATFORM_WINDOWS )
#	ifdef _WIN32_WINNT
#		undef _WIN32_WINNT
#	endif // _WIN32_WINNT
#	define _WIN32_WINNT        0x0600
#	define WIN32_LEAN_AND_MEAN
#endif // _WIN32_WINNT & WIN32_LEAN_AND_MEAN

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <deque>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <locale>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/locale.hpp>
#include <boost/timer/timer.hpp>

#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#	include <boost/thread.hpp>
#pragma GCC diagnostic pop

#if ( QMX_PLATFORM == QMX_PLATFORM_LINUX )
#	include <dlfcn.h>
#elif( QMX_PLATFORM == QMX_PLATFORM_OSX )
#	include <dlfcn.h>
#elif( QMX_PLATFORM == QMX_PLATFORM_WINDOWS )
#	include <windows.h>
#endif // Platform Headers

#include "Config.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SINGLE_STATEMENT(x)        do{ x }while( false )
#define STRINGIZE_IMP(x)           #x
#define STRINGIZE(x)               STRINGIZE_IMP( x )
#define PURE_VIRTUAL               0
#define WHITE_SPACE_CHARS          " \t\n\v\f\r"
#define BIT_FLAG(x)                1ull<<( x##ull - 1ull )
#define BIT_FLAG_ALL               0xFFFFFFFFFFFFFFFFull
#define ZERO_MEMORY(x,y)           memset( x, QMXStdLib::Null, y )
#define ZERO_ARRAY(x)              memset( x, QMXStdLib::Null, sizeof( x ) )
#define ARRAY_SIZE(x)              ( sizeof( x ) / sizeof( *x ) )
#define SAFE_DELETE(x)             SINGLE_STATEMENT( delete x;  x = nullptr; )
#define SAFE_DELETE_ARRAY(x)       SINGLE_STATEMENT( delete[] x;  x = nullptr; )
#define FLUSH_ISTREAM(x)           x.ignore( std::numeric_limits< std::streamsize >::max(), '\n' )
#define WAIT_FOR_ENTER             SINGLE_STATEMENT( COUT << "Press 'Enter' to continue...";  std::cin.peek();  FLUSH_ISTREAM( std::cin ); )
#define QMX_THROW(w,x,y,z)         SINGLE_STATEMENT(\
                                     std::ostringstream EventDataBuffer;\
                                     EventDataBuffer << z;\
                                     throw QMXStdLib::QMXException( w, x, y, EventDataBuffer.str().c_str(), STACK_TRACE.c_str() );\
                                   )
#define QMX_THROW_X(w,x,y,z)       SINGLE_STATEMENT(\
                                     std::ostringstream EventDataBuffer;\
                                     EventDataBuffer << z;\
                                     throw QMXStdLib::QMXException( w, x, y, EventDataBuffer.str().c_str() );\
                                   )
#define QMX_ASSERT(v,w,x,y,z)      SINGLE_STATEMENT( if( !v ) QMX_THROW( w, x, y, z ); )
#define QMX_ASSERT_X(v,w,x,y,z)    SINGLE_STATEMENT( if( !v ) QMX_THROW_X( w, x, y, z ); )
#define QMX_ASSERT_E(u,v,w,x,y,z)  SINGLE_STATEMENT( if( !u ) v;  QMX_THROW( w, x, y, z ); )
#define QMX_ASSERT_EX(u,v,w,x,y,z) SINGLE_STATEMENT( if( !u ) v;  QMX_THROW_X( w, x, y, z ); )
#define STANDARD_TYPEDEFS(x)       typedef std::shared_ptr< x > PointerType;\
                                   typedef std::pair< std::string, x > InstancePair;\
                                   typedef std::vector< x > InstanceVector;\
                                   typedef std::deque< x > InstanceDeque;\
                                   typedef std::unordered_set< x > InstanceSet;\
                                   typedef std::unordered_map< std::string, x > InstanceMap;\
                                   typedef std::pair< std::string, PointerType > PointerPair;\
                                   typedef std::vector< PointerType > PointerVector;\
                                   typedef std::deque< PointerType > PointerDeque;\
                                   typedef std::unordered_set< PointerType > PointerSet;\
                                   typedef std::unordered_map< std::string, PointerType > PointerMap;
#define STANDARD_TYPEDEFS_X(x,y)   typedef std::shared_ptr< x > y##Ptr;\
                                   typedef std::pair< std::string, x > y##Pair;\
                                   typedef std::vector< x > y##Vector;\
                                   typedef std::deque< x > y##Deque;\
                                   typedef std::unordered_set< x > y##Set;\
                                   typedef std::unordered_map< std::string, x > y##Map;\
                                   typedef std::pair< std::string, y##Ptr > y##PtrPair;\
                                   typedef std::vector< y##Ptr > y##PtrVector;\
                                   typedef std::deque< y##Ptr > y##PtrDeque;\
                                   typedef std::unordered_set< y##Ptr > y##PtrSet;\
                                   typedef std::unordered_map< std::string, y##Ptr > y##PtrMap;

#if ( QMX_PLATFORM == QMX_PLATFORM_LINUX )
#	define IS_LINUX                 true
#	define IS_OSX                   false
#	define IS_WINDOWS               false
#elif( QMX_PLATFORM == QMX_PLATFORM_OSX )
#	define IS_LINUX                 false
#	define IS_OSX                   true
#	define IS_WINDOWS               false
#elif( QMX_PLATFORM == QMX_PLATFORM_WINDOWS )
#	define IS_LINUX                 false
#	define IS_OSX                   false
#	define IS_WINDOWS               true
#else
#	error "Unsupported value for 'QMX_PLATFORM'; aborting compile!"
#endif // IS_LINUX, IS_OSX, & IS_LINUX

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This is the base QMXStdLib namespace.
  */

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Type Definitions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef long double                                           real_t;
typedef uint64_t                                              BitField;
typedef boost::shared_mutex                                   SharedMutex;
typedef boost::shared_lock< boost::shared_mutex >             SharedLock;
typedef boost::unique_lock< boost::shared_mutex >             UniqueLock;
typedef boost::filesystem::path                               Path;
typedef boost::filesystem::directory_iterator                 DirectoryIterator;

#ifdef QMX_32BIT
	typedef uint32_t                                           PointerSize;
#else
	typedef uint64_t                                           PointerSize;
#endif // PointerSize

STANDARD_TYPEDEFS_X( void*,       Void )
STANDARD_TYPEDEFS_X( bool,        Bool )
STANDARD_TYPEDEFS_X( int,         Int )
STANDARD_TYPEDEFS_X( int8_t,      Int8 )
STANDARD_TYPEDEFS_X( int16_t,     Int16 )
STANDARD_TYPEDEFS_X( int32_t,     Int32 )
STANDARD_TYPEDEFS_X( int64_t,     Int64 )
STANDARD_TYPEDEFS_X( uint8_t,     UInt8 )
STANDARD_TYPEDEFS_X( uint16_t,    UInt16 )
STANDARD_TYPEDEFS_X( uint32_t,    UInt32 )
STANDARD_TYPEDEFS_X( uint64_t,    UInt64 )
STANDARD_TYPEDEFS_X( float,       Float )
STANDARD_TYPEDEFS_X( double,      Double )
STANDARD_TYPEDEFS_X( real_t,      Real )
STANDARD_TYPEDEFS_X( std::string, String )

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Anonymous Enumerations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum
{
	Null = 0,
	Toggle = -1,
	True = 1,
	False = 0,
	On = 1,
	Off = 0,
	Yes = 1,
	No = 0,
	Active = 1,
	Inactive = 0
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_BASE_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'Base.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

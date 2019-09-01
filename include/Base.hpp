////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Base.hpp
// Robert M. Baker | Created : 10DEC11 | Last Modified : 31AUG19 by Robert M. Baker
// Version : 2.1.1
// This is the base header file for 'QMXStdLib'; it defines data common to all modules.
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

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 10DEC11
  * @date    Last Modified : 29AUG19 by Robert M. Baker
  * @version 2.1.1
  *
  * @brief This base header file defines data common to all modules.
  *
  * @section BaseH0000 Description
  *
  * This base header file defines data common to all modules.
  *
  * @section BaseH0001 License
  *
  * Copyright (C) 2011-2019 QuantuMatriX Software, a QuantuMatriX Technologies Cooperative Partnership
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

#define QMX_PLATFORM_LINUX   1
#define QMX_PLATFORM_MACOS   2
#define QMX_PLATFORM_WINDOWS 3

#define QMX_COMPILER_CLANG   1
#define QMX_COMPILER_GCC     2
#define QMX_COMPILER_MINGW   3

#if ( defined( __x86_64__ ) || defined( __ia64__ ) || defined( __ppc64__ ) || defined( __sparc_v9__ ) || defined( __mips64 ) || defined( __aarch64__ ) )
#	define QMX_64BIT
#else
#	define QMX_32BIT
#endif // QMX_64BIT & QMX32BIT

#ifdef __linux__
#	define QMX_PLATFORM       QMX_PLATFORM_LINUX
#elif __MACH__
#	define QMX_PLATFORM       QMX_PLATFORM_MACOS
#elif _WIN32
#	define QMX_PLATFORM       QMX_PLATFORM_WINDOWS
#else
#	error "Unsupported platform; aborting compile!"
#endif // QMX_PLATFORM

#if ( defined( __clang__ ) )
#  define QMX_COMPILER       QMX_COMPILER_CLANG
#elif( defined( __GNUC__ ) && !defined( __MINGW32__ ) )
#	define QMX_COMPILER       QMX_COMPILER_GCC
#elif( defined( __MINGW32__ ) )
#	define QMX_COMPILER       QMX_COMPILER_MINGW
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
#	define _WIN32_WINNT       0x0600
#	define WIN32_LEAN_AND_MEAN
#endif // _WIN32_WINNT & WIN32_LEAN_AND_MEAN

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstring>
#include <algorithm>
#include <deque>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <boost/algorithm/string.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#	include <boost/thread.hpp>
#pragma GCC diagnostic pop

#ifdef QMXSTDLIB_INTERNAL_BUILD
#	include "../build/Config.hpp"
#else
#	include "Config.hpp"
#endif // Configuration Header

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SINGLE_STATEMENT(x)        do{ x }while( false )
#define STRINGIZE_IMP(x)           #x
#define STRINGIZE(x)               STRINGIZE_IMP( x )
#define PURE_VIRTUAL               0
#define BIT_FLAG(x)                1ull<<( x##ull - 1ull )
#define BIT_FLAG_ALL               0xFFFFFFFFFFFFFFFFull
#define ZERO_MEMORY(x,y)           memset( x, UNSET, y )
#define ZERO_ARRAY(x)              memset( x, UNSET, sizeof( x ) )
#define ARRAY_SIZE(x)              ( sizeof( x ) / sizeof( *x ) )
#define SAFE_DELETE(x)             SINGLE_STATEMENT( delete x;  x = nullptr; )
#define SAFE_DELETE_ARRAY(x)       SINGLE_STATEMENT( delete[] x;  x = nullptr; )
#define FLUSH_ISTREAM(x)           x.ignore( std::numeric_limits< std::streamsize >::max(), '\n' )
#define STRIP_ALL_WHITESPACE(x)    x.erase( std::remove_if( x.begin(), x.end(), boost::algorithm::is_space() ), x.end() )
#define NOT_A_THREAD               boost::thread::id()
#define THIS_THREAD_HASH           boost::this_thread::get_id()

#define STANDARD_TYPEDEFS(x)       typedef std::shared_ptr< x > InstancePtr;\
                                   typedef std::pair< std::string, x > InstancePair;\
                                   typedef std::vector< x > InstanceVector;\
                                   typedef std::deque< x > InstanceDeque;\
                                   typedef std::unordered_set< x > InstanceSet;\
                                   typedef std::unordered_map< std::string, x > InstanceMap;\
                                   typedef boost::thread_specific_ptr< x > InstanceTLS;\
                                   typedef std::pair< std::string, InstancePtr > InstancePtrPair;\
                                   typedef std::vector< InstancePtr > InstancePtrVector;\
                                   typedef std::deque< InstancePtr > InstancePtrDeque;\
                                   typedef std::unordered_set< InstancePtr > InstancePtrSet;\
                                   typedef std::unordered_map< std::string, InstancePtr > InstancePtrMap;\
                                   typedef boost::thread_specific_ptr< InstancePtr > InstancePtrTLS;

#define STANDARD_TYPEDEFS_X(x,y)   typedef std::shared_ptr< x > y##Ptr;\
                                   typedef std::pair< std::string, x > y##Pair;\
                                   typedef std::vector< x > y##Vector;\
                                   typedef std::deque< x > y##Deque;\
                                   typedef std::unordered_set< x > y##Set;\
                                   typedef std::unordered_map< std::string, x > y##Map;\
                                   typedef boost::thread_specific_ptr< x > y##TLS;\
                                   typedef std::pair< std::string, y##Ptr > y##PtrPair;\
                                   typedef std::vector< y##Ptr > y##PtrVector;\
                                   typedef std::deque< y##Ptr > y##PtrDeque;\
                                   typedef std::unordered_set< y##Ptr > y##PtrSet;\
                                   typedef std::unordered_map< std::string, y##Ptr > y##PtrMap;\
                                   typedef boost::thread_specific_ptr< y##Ptr > y##PtrTLS;

#if ( QMX_PLATFORM == QMX_PLATFORM_LINUX )
#	define IS_LINUX                 true
#	define IS_MACOS                 false
#	define IS_WINDOWS               false
#elif( QMX_PLATFORM == QMX_PLATFORM_MACOS )
#	define IS_LINUX                 false
#	define IS_MACOS                 true
#	define IS_WINDOWS               false
#elif( QMX_PLATFORM == QMX_PLATFORM_WINDOWS )
#	define IS_LINUX                 false
#	define IS_MACOS                 false
#	define IS_WINDOWS               true
#else
#	error "Unsupported value for 'QMX_PLATFORM'; aborting compile!"
#endif // IS_LINUX, IS_MACOS, & IS_WINDOWS

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

typedef long double                              real_t;
typedef uint64_t                                 bit_field_t;
typedef boost::thread::id                        ThreadHash;
typedef boost::shared_mutex                      SharedMutex;
typedef std::pair< ThreadHash, SharedMutex >     SharedMutexPair;

#ifdef QMX_32BIT
	typedef uint32_t                              ptr_size_t;
#else
	typedef uint64_t                              ptr_size_t;
#endif // PointerSize

STANDARD_TYPEDEFS_X( void*,                      Void )
STANDARD_TYPEDEFS_X( bool,                       Bool )
STANDARD_TYPEDEFS_X( int,                        Int )
STANDARD_TYPEDEFS_X( int8_t,                     Int8 )
STANDARD_TYPEDEFS_X( int16_t,                    Int16 )
STANDARD_TYPEDEFS_X( int32_t,                    Int32 )
STANDARD_TYPEDEFS_X( int64_t,                    Int64 )
STANDARD_TYPEDEFS_X( uint8_t,                    UInt8 )
STANDARD_TYPEDEFS_X( uint16_t,                   UInt16 )
STANDARD_TYPEDEFS_X( uint32_t,                   UInt32 )
STANDARD_TYPEDEFS_X( uint64_t,                   UInt64 )
STANDARD_TYPEDEFS_X( float,                      Float )
STANDARD_TYPEDEFS_X( double,                     Double )
STANDARD_TYPEDEFS_X( real_t,                     Real )
STANDARD_TYPEDEFS_X( std::string,                String )

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Anonymous Enumerations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum
{
  UNSET = 0,
	TOGGLE = -1,
	TRUE = 1,
	FALSE = 0,
	ON = 1,
	OFF = 0,
	YES = 1,
	NO = 0,
	ACTIVE = 1,
	INACTIVE = 0
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_BASE_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'Base.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

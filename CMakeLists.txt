################################################################################################################################################################
# CMakeLists.txt
# Robert M. Baker | Created : 10DEC11 | Last Modified : 17FEB16 by Robert M. Baker
# Version : 1.0.0
# This is a CMake script for building 'QMXStdLib'.
################################################################################################################################################################
# Copyright (C) 2011-2016 QuantuMatriX Software, LLP.
#
# This file is part of 'QMXStdLib'.
#
# 'QMXStdLib' is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option) any later version.
#
# 'QMXStdLib' is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License along with 'QMXStdLib'.  If not, see <http://www.gnu.org/licenses/>.
################################################################################################################################################################

################################################################################################################################################################
# Setup
################################################################################################################################################################

cmake_minimum_required( VERSION 3.4 )
project( QMXStdLib C CXX )
find_package ( Threads REQUIRED )
set( DoUnitTests false
     CACHE BOOL
     "If 'true' build unit tests; otherwise, build library." )
set( MaxBufferSize "1024"
     CACHE STRING
     "Maximum default size for a c-string buffer." )
set( ConsoleIODefInputType "ConsoleIO::Range"
     CACHE STRING
     "Default input type for the 'ConsoleIO::GetInput' method." )
set( ConsoleIODefChoices "\"A, B, C, D, or E\""
     CACHE STRING
     "Default set of choices for the 'ConsoleIO::GetInput' method." )
configure_file( "${QMXStdLib_SOURCE_DIR}/Config.hpp.in"
                "${QMXStdLib_SOURCE_DIR}/include/Config.hpp" )

################################################################################################################################################################
# Targets
################################################################################################################################################################

if( NOT DoUnitTests )
	add_library( qmxstdlib SHARED
	             "src/ConsoleIO.cpp"
	             "src/DynamicLibrary.cpp"
	             "src/FileSystem.cpp"
	             "src/PluginManager.cpp"
	             "src/ProgramOptions.cpp"
	             "src/QMXException.cpp"
	             "src/StackTracer.cpp"
	             "src/String.cpp"
	             "src/Timer.cpp"
	             "src/Utility.cpp" )
	target_include_directories( qmxstdlib PRIVATE "${QMXStdLib_SOURCE_DIR}/include/" )
	target_link_libraries( qmxstdlib
	                       "${CMAKE_DL_LIBS}"
	                       "boost_filesystem"
	                       "boost_locale"
	                       "boost_system"
	                       "boost_thread"
	                       "boost_timer" )
	set_target_properties( qmxstdlib PROPERTIES
	                       VERSION "1.0.0"
	                       SOVERSION "1" )

	if( CMAKE_BUILD_TYPE MATCHES "Debug" )
		set_target_properties( qmxstdlib PROPERTIES
		                       OUTPUT_NAME "qmxstdlib_d"
		                       COMPILE_FLAGS "-std=c++11 -g -Wall -Wno-attributes -D_DEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
		                       LINK_FLAGS "-z defs" )
	elseif( CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo" )
		set_target_properties( qmxstdlib PROPERTIES
		                       OUTPUT_NAME "qmxstdlib_d"
		                       COMPILE_FLAGS "-std=c++11 -Og -g -Wall -Wno-attributes -D_DEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
		                       LINK_FLAGS "-z defs" )
	elseif( CMAKE_BUILD_TYPE MATCHES "Release" )
		set_target_properties( qmxstdlib PROPERTIES
		                       OUTPUT_NAME "qmxstdlib"
		                       COMPILE_FLAGS "-std=c++11 -O2 -Wall -Wno-attributes -DNDEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
		                       LINK_FLAGS "-z defs -s" )
	elseif( CMAKE_BUILD_TYPE MATCHES "MinSizeRel" )
		set_target_properties( qmxstdlib PROPERTIES
		                       OUTPUT_NAME "qmxstdlib"
		                       COMPILE_FLAGS "-std=c++11 -Os -Wall -Wno-attributes -DNDEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
		                       LINK_FLAGS "-z defs -s" )
	else()
		message( "Warning: Using unsupported value for 'CMAKE_BUILD_TYPE'!" )
	endif()
else()
	add_library( TestPlugin1 SHARED
	             "test/src/TestPlugins/TestPlugin1.cpp" )
	target_include_directories( TestPlugin1 PRIVATE "${QMXStdLib_SOURCE_DIR}/test/include/" )
	target_link_libraries( TestPlugin1
	                       "boost_system" )
	set_target_properties( TestPlugin1 PROPERTIES
	                       PREFIX "" )

	add_library( TestPlugin2 SHARED
	             "test/src/TestPlugins/TestPlugin2.cpp" )
	target_include_directories( TestPlugin2 PRIVATE "${QMXStdLib_SOURCE_DIR}/test/include/" )
	target_link_libraries( TestPlugin2
	                       "boost_system" )
	set_target_properties( TestPlugin2 PROPERTIES
	                       PREFIX "" )

	add_library( TestPlugin3 SHARED
	             "test/src/TestPlugins/TestPlugin3.cpp" )
	target_include_directories( TestPlugin3 PRIVATE "${QMXStdLib_SOURCE_DIR}/test/include/" )
	target_link_libraries( TestPlugin3
	                       "boost_system" )
	set_target_properties( TestPlugin3 PROPERTIES
	                       PREFIX "" )

	add_executable( qmxstdlib_test
	                "test/src/ConsoleIOTest.cpp"
	                "test/src/DynamicLibraryTest.cpp"
	                "test/src/FileSystemTest.cpp"
	                "test/src/Main.cpp"
	                "test/src/NumericTest.cpp"
	                "test/src/PluginManagerTest.cpp"
	                "test/src/ProgramOptionsTest.cpp"
	                "test/src/QMXExceptionTest.cpp"
	                "test/src/SequencerTest.cpp"
	                "test/src/StackTracerTest.cpp"
	                "test/src/StringTest.cpp"
	                "test/src/TimerTest.cpp"
	                "test/src/UniqueRandomTest.cpp"
	                "test/src/UtilityTest.cpp" )
	target_include_directories( qmxstdlib_test PRIVATE "${QMXStdLib_SOURCE_DIR}/test/include/" )
	target_link_libraries( qmxstdlib_test
	                       "${CMAKE_THREAD_LIBS_INIT}"
	                       "boost_filesystem"
	                       "boost_locale"
	                       "boost_system"
	                       "boost_thread"
	                       "gtest" )

	if( CMAKE_BUILD_TYPE MATCHES "Debug" )
		target_link_libraries( TestPlugin1
		                       "qmxstdlib_d" )
		set_target_properties( TestPlugin1 PROPERTIES
		                       LIBRARY_OUTPUT_DIRECTORY "${QMXStdLib_SOURCE_DIR}/test/TestDirectory/TestPlugins/debug/"
		                       COMPILE_FLAGS "-std=c++11 -g -Wall -Wno-maybe-uninitialized -Wno-attributes -D_DEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
		                       LINK_FLAGS "-z defs" )

		target_link_libraries( TestPlugin2
		                       "qmxstdlib_d" )
		set_target_properties( TestPlugin2 PROPERTIES
		                       LIBRARY_OUTPUT_DIRECTORY "${QMXStdLib_SOURCE_DIR}/test/TestDirectory/TestPlugins/debug/"
		                       COMPILE_FLAGS "-std=c++11 -g -Wall -Wno-maybe-uninitialized -Wno-attributes -D_DEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
		                       LINK_FLAGS "-z defs" )

		target_link_libraries( TestPlugin3
		                       "qmxstdlib_d" )
		set_target_properties( TestPlugin3 PROPERTIES
		                       LIBRARY_OUTPUT_DIRECTORY "${QMXStdLib_SOURCE_DIR}/test/TestDirectory/TestPlugins/debug/"
		                       COMPILE_FLAGS "-std=c++11 -g -Wall -Wno-maybe-uninitialized -Wno-attributes -D_DEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
		                       LINK_FLAGS "-z defs" )

		target_link_libraries( qmxstdlib_test
		                       "qmxstdlib_d" )
		set_target_properties( qmxstdlib_test PROPERTIES
		                       RUNTIME_OUTPUT_DIRECTORY "${QMXStdLib_SOURCE_DIR}/test/bin/debug/"
		                       COMPILE_FLAGS "-std=c++11 -g -Wall -Wno-maybe-uninitialized -Wno-attributes -D_DEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED" )
	elseif( CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo" )
		target_link_libraries( TestPlugin1
		                       "qmxstdlib_d" )
		set_target_properties( TestPlugin1 PROPERTIES
		                       LIBRARY_OUTPUT_DIRECTORY "${QMXStdLib_SOURCE_DIR}/test/TestDirectory/TestPlugins/debug/"
		                       COMPILE_FLAGS "-std=c++11 -Og -g -Wall -Wno-maybe-uninitialized -Wno-attributes -D_DEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
		                       LINK_FLAGS "-z defs" )

		target_link_libraries( TestPlugin2
		                       "qmxstdlib_d" )
		set_target_properties( TestPlugin2 PROPERTIES
		                       LIBRARY_OUTPUT_DIRECTORY "${QMXStdLib_SOURCE_DIR}/test/TestDirectory/TestPlugins/debug/"
		                       COMPILE_FLAGS "-std=c++11 -Og -g -Wall -Wno-maybe-uninitialized -Wno-attributes -D_DEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
		                       LINK_FLAGS "-z defs" )

		target_link_libraries( TestPlugin3
		                       "qmxstdlib_d" )
		set_target_properties( TestPlugin3 PROPERTIES
		                       LIBRARY_OUTPUT_DIRECTORY "${QMXStdLib_SOURCE_DIR}/test/TestDirectory/TestPlugins/debug/"
		                       COMPILE_FLAGS "-std=c++11 -Og -g -Wall -Wno-maybe-uninitialized -Wno-attributes -D_DEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
		                       LINK_FLAGS "-z defs" )

		target_link_libraries( qmxstdlib_test
		                       "qmxstdlib_d" )
		set_target_properties( qmxstdlib_test PROPERTIES
		                       RUNTIME_OUTPUT_DIRECTORY "${QMXStdLib_SOURCE_DIR}/test/bin/debug/"
		                       COMPILE_FLAGS "-std=c++11 -Og -g -Wall -Wno-maybe-uninitialized -Wno-attributes -D_DEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED" )
	elseif( CMAKE_BUILD_TYPE MATCHES "Release" )
		target_link_libraries( TestPlugin1
		                       "qmxstdlib" )
		set_target_properties( TestPlugin1 PROPERTIES
		                       LIBRARY_OUTPUT_DIRECTORY "${QMXStdLib_SOURCE_DIR}/test/TestDirectory/TestPlugins/release/"
		                       COMPILE_FLAGS "-std=c++11 -O2 -Wall -Wno-maybe-uninitialized -Wno-attributes -DNDEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
		                       LINK_FLAGS "-z defs -s" )

		target_link_libraries( TestPlugin2
		                       "qmxstdlib" )
		set_target_properties( TestPlugin2 PROPERTIES
		                       LIBRARY_OUTPUT_DIRECTORY "${QMXStdLib_SOURCE_DIR}/test/TestDirectory/TestPlugins/release/"
		                       COMPILE_FLAGS "-std=c++11 -O2 -Wall -Wno-maybe-uninitialized -Wno-attributes -DNDEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
		                       LINK_FLAGS "-z defs -s" )

		target_link_libraries( TestPlugin3
		                       "qmxstdlib" )
		set_target_properties( TestPlugin3 PROPERTIES
		                       LIBRARY_OUTPUT_DIRECTORY "${QMXStdLib_SOURCE_DIR}/test/TestDirectory/TestPlugins/release/"
		                       COMPILE_FLAGS "-std=c++11 -O2 -Wall -Wno-maybe-uninitialized -Wno-attributes -DNDEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
		                       LINK_FLAGS "-z defs -s" )

		target_link_libraries( qmxstdlib_test
		                       "qmxstdlib" )
		set_target_properties( qmxstdlib_test PROPERTIES
		                       RUNTIME_OUTPUT_DIRECTORY "${QMXStdLib_SOURCE_DIR}/test/bin/release/"
		                       COMPILE_FLAGS "-std=c++11 -O2 -Wall -Wno-maybe-uninitialized -Wno-attributes -DNDEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
		                       LINK_FLAGS "-s" )
	elseif( CMAKE_BUILD_TYPE MATCHES "MinSizeRel" )
		target_link_libraries( TestPlugin1
		                       "qmxstdlib" )
		set_target_properties( TestPlugin1 PROPERTIES
		                       LIBRARY_OUTPUT_DIRECTORY "${QMXStdLib_SOURCE_DIR}/test/TestDirectory/TestPlugins/release/"
		                       COMPILE_FLAGS "-std=c++11 -Os -Wall -Wno-maybe-uninitialized -Wno-attributes -DNDEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
		                       LINK_FLAGS "-z defs -s" )

		target_link_libraries( TestPlugin2
		                       "qmxstdlib" )
		set_target_properties( TestPlugin2 PROPERTIES
		                       LIBRARY_OUTPUT_DIRECTORY "${QMXStdLib_SOURCE_DIR}/test/TestDirectory/TestPlugins/release/"
		                       COMPILE_FLAGS "-std=c++11 -Os -Wall -Wno-maybe-uninitialized -Wno-attributes -DNDEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
		                       LINK_FLAGS "-z defs -s" )

		target_link_libraries( TestPlugin3
		                       "qmxstdlib" )
		set_target_properties( TestPlugin3 PROPERTIES
		                       LIBRARY_OUTPUT_DIRECTORY "${QMXStdLib_SOURCE_DIR}/test/TestDirectory/TestPlugins/release/"
		                       COMPILE_FLAGS "-std=c++11 -Os -Wall -Wno-maybe-uninitialized -Wno-attributes -DNDEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
		                       LINK_FLAGS "-z defs -s" )

		target_link_libraries( qmxstdlib_test
		                       "qmxstdlib" )
		set_target_properties( qmxstdlib_test PROPERTIES
		                       RUNTIME_OUTPUT_DIRECTORY "${QMXStdLib_SOURCE_DIR}/test/bin/release/"
		                       COMPILE_FLAGS "-std=c++11 -Os -Wall -Wno-maybe-uninitialized -Wno-attributes -DNDEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
		                       LINK_FLAGS "-s" )
	else()
		message( "Warning: Using unsupported value for 'CMAKE_BUILD_TYPE'!" )
	endif()
endif()

################################################################################################################################################################
# End of 'CMakeLists.txt'
################################################################################################################################################################

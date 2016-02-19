################################################################################################################################################################
# CMakeLists.txt
# Robert M. Baker | Created : 10DEC11 | Last Modified : 19FEB16 by Robert M. Baker
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

# TODO (Malachy - Priority 50): Complete and test for Apple Mac OS X platform.
# TODO (Malachy - Priority 50): Complete and test for Microsoft Windows platform.

################################################################################################################################################################
# Environment Check
################################################################################################################################################################

# General

cmake_minimum_required( VERSION 3.4 )

if( NOT "${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}/build" )
	message( FATAL_ERROR "You must build the project from '${CMAKE_SOURCE_DIR}/build'!  See 'README.md' for build instructions." )
endif()

project( PROJECT VERSION 1.0.0 LANGUAGES C CXX )

find_package( GTest 1.7.0 REQUIRED )
find_package( Doxygen )

# Project-Specific

find_package( Threads REQUIRED )
find_package( Boost 1.60.0 REQUIRED )

################################################################################################################################################################
# Setup
################################################################################################################################################################

# Project Info

set( PROJECT_TARGET "qmxstdlib" )
set( DOXYGEN_PROJECT_NAME "QMXStdLib" )
set( DOXYGEN_PROJECT_BRIEF "QuantuMatriX Standard Library" )

# General

set( CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true )
set( COMPILE_FLAGS_DEBUG "-std=c++11 -g -Wall -Wno-maybe-uninitialized -Wno-attributes -D_DEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
     CACHE STRING "These are the debug compile flags." )
set( COMPILE_FLAGS_RELWITHDEBINFO "-std=c++11 -O2 -g -Wall -Wno-maybe-uninitialized -Wno-attributes -DNDEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
     CACHE STRING "These are the release with debug info compile flags." )
set( COMPILE_FLAGS_RELEASE "-std=c++11 -O3 -Wall -Wno-maybe-uninitialized -Wno-attributes -DNDEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
     CACHE STRING "These are the release compile flags." )
set( COMPILE_FLAGS_MINSIZEREL "-std=c++11 -Os -Wall -Wno-maybe-uninitialized -Wno-attributes -DNDEBUG -DBOOST_FILESYSTEM_NO_DEPRECATED"
     CACHE STRING "These are the minimum size release compile flags." )
set( LINK_FLAGS_DEBUG "-z defs"
     CACHE STRING "These are the debug link flags." )
set( LINK_FLAGS_RELWITHDEBINFO "-z defs"
     CACHE STRING "These are the release with debug info link flags." )
set( LINK_FLAGS_RELEASE "-z defs -s"
     CACHE STRING "These are the release link flags." )
set( LINK_FLAGS_MINSIZEREL "-z defs -s"
     CACHE STRING "These are the minimum size release link flags." )

if( ${CMAKE_SYSTEM_NAME} STREQUAL "Linux" )
	set( PROJECT_INCLUDE_PATH "include/${PROJECT_TARGET}"
	     CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the headers will be installed." )
	set( PROJECT_LIB_PATH "lib"
	     CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the shared libraries will be installed." )
	set( PROJECT_DOC_PATH "share/doc/${PROJECT_TARGET}"
	     CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the documentation will be installed." )
elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin" )
	set( PROJECT_INCLUDE_PATH ""
	     CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the headers will be installed." )
	set( PROJECT_LIB_PATH ""
	     CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the shared libraries will be installed." )
	set( PROJECT_DOC_PATH ""
	     CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the documentation will be installed." )
elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Windows" )
	set( PROJECT_INCLUDE_PATH ""
	     CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the headers will be installed." )
	set( PROJECT_ARCHIVE_PATH ""
	     CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the import libraries will be installed." )
	set( PROJECT_LIB_PATH ""
	     CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the shared libraries will be installed." )
	set( PROJECT_DOC_PATH ""
	     CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the documentation will be installed." )
endif()

# Project-Specific

set( MAX_BUFFER_SIZE "1024"
     CACHE STRING "Maximum default size for a c-string buffer." )
set( CONSOLEIO_DEF_INPUT_TYPE "ConsoleIO::Range"
     CACHE STRING "Default input type for the 'ConsoleIO::GetInput' method." )
set( CONSOLEIO_DEF_CHOICES "\"A, B, C, D, or E\""
     CACHE STRING "Default set of choices for the 'ConsoleIO::GetInput' method." )

set( PROJECT_SOURCES
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
set( PROJECT_LIBRARIES_DEBUG
     "${CMAKE_DL_LIBS}"
     "boost_filesystem"
     "boost_locale"
     "boost_system"
     "boost_thread"
     "boost_timer" )
set( PROJECT_LIBRARIES_RELEASE ${PROJECT_LIBRARIES_DEBUG} )
set( PROJECT_TEST_SOURCES
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
set( PROJECT_TEST_LIBRARIES_DEBUG
     "${CMAKE_THREAD_LIBS_INIT}"
     "boost_filesystem"
     "boost_locale"
     "boost_system"
     "boost_thread"
     "gtest" )
set( PROJECT_TEST_LIBRARIES_RELEASE ${PROJECT_TEST_LIBRARIES_DEBUG} )

# Configure Files

configure_file( "Config.hpp.in" "../include/Config.hpp" )

if( DOXYGEN_FOUND )
	configure_file( "Doxyfile.in" "../Doxyfile" @ONLY )
endif()

################################################################################################################################################################
# Targets
################################################################################################################################################################

# Project

add_library( debug SHARED ${PROJECT_SOURCES} )
target_include_directories( debug PRIVATE "include/" )
target_link_libraries( debug ${PROJECT_LIBRARIES_DEBUG} )
set_target_properties( debug PROPERTIES
                       VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
                       SOVERSION "${PROJECT_VERSION_MAJOR}" )
set_target_properties( debug PROPERTIES
                       OUTPUT_NAME "${PROJECT_TARGET}_d"
                       COMPILE_FLAGS ${COMPILE_FLAGS_DEBUG}
                       LINK_FLAGS ${LINK_FLAGS_DEBUG} )

add_library( relwithdebinfo SHARED ${PROJECT_SOURCES} )
target_include_directories( relwithdebinfo PRIVATE "include/" )
target_link_libraries( relwithdebinfo ${PROJECT_LIBRARIES_RELEASE} )
set_target_properties( relwithdebinfo PROPERTIES
                       VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
                       SOVERSION "${PROJECT_VERSION_MAJOR}" )
set_target_properties( relwithdebinfo PROPERTIES
                       EXCLUDE_FROM_ALL true
                       EXCLUDE_FROM_DEFAULT_BUILD true
                       OUTPUT_NAME "${PROJECT_TARGET}"
                       COMPILE_FLAGS ${COMPILE_FLAGS_RELWITHDEBINFO}
                       LINK_FLAGS ${LINK_FLAGS_RELWITHDEBINFO} )

add_library( release SHARED ${PROJECT_SOURCES} )
target_include_directories( release PRIVATE "include/" )
target_link_libraries( release ${PROJECT_LIBRARIES_RELEASE} )
set_target_properties( release PROPERTIES
                       VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
                       SOVERSION "${PROJECT_VERSION_MAJOR}" )
set_target_properties( release PROPERTIES
                       OUTPUT_NAME "${PROJECT_TARGET}"
                       COMPILE_FLAGS ${COMPILE_FLAGS_RELEASE}
                       LINK_FLAGS ${LINK_FLAGS_RELEASE} )

add_library( minesizerel SHARED ${PROJECT_SOURCES} )
target_include_directories( minesizerel PRIVATE "include/" )
target_link_libraries( minesizerel ${PROJECT_LIBRARIES_RELEASE} )
set_target_properties( minesizerel PROPERTIES
                       VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
                       SOVERSION "${PROJECT_VERSION_MAJOR}" )
set_target_properties( minesizerel PROPERTIES
                       EXCLUDE_FROM_ALL true
                       EXCLUDE_FROM_DEFAULT_BUILD true
                       OUTPUT_NAME "${PROJECT_TARGET}"
                       COMPILE_FLAGS ${COMPILE_FLAGS_MINSIZEREL}
                       LINK_FLAGS ${LINK_FLAGS_MINSIZEREL} )

# TestPlugin1

add_library( testplugin1_debug SHARED "test/src/TestPlugins/TestPlugin1.cpp" )
target_include_directories( testplugin1_debug PRIVATE "test/include/" )
target_link_libraries( testplugin1_debug "boost_system" "${PROJECT_TARGET}_d" )
set_target_properties( testplugin1_debug PROPERTIES
                       EXCLUDE_FROM_ALL true
                       EXCLUDE_FROM_DEFAULT_BUILD true
                       PREFIX ""
                       LIBRARY_OUTPUT_DIRECTORY "../test/TestDirectory/TestPlugins/debug/"
                       OUTPUT_NAME "TestPlugin1"
                       COMPILE_FLAGS ${COMPILE_FLAGS_DEBUG}
                       LINK_FLAGS ${LINK_FLAGS_DEBUG} )
add_dependencies( testplugin1_debug debug )

add_library( testplugin1_relwithdebinfo SHARED "test/src/TestPlugins/TestPlugin1.cpp" )
target_include_directories( testplugin1_relwithdebinfo PRIVATE "test/include/" )
target_link_libraries( testplugin1_relwithdebinfo "boost_system" "${PROJECT_TARGET}" )
set_target_properties( testplugin1_relwithdebinfo PROPERTIES
                       EXCLUDE_FROM_ALL true
                       EXCLUDE_FROM_DEFAULT_BUILD true
                       PREFIX ""
                       LIBRARY_OUTPUT_DIRECTORY "../test/TestDirectory/TestPlugins/release/"
                       OUTPUT_NAME "TestPlugin1"
                       COMPILE_FLAGS ${COMPILE_FLAGS_RELWITHDEBINFO}
                       LINK_FLAGS ${LINK_FLAGS_RELWITHDEBINFO} )
add_dependencies( testplugin1_relwithdebinfo relwithdebinfo )

add_library( testplugin1_release SHARED "test/src/TestPlugins/TestPlugin1.cpp" )
target_include_directories( testplugin1_release PRIVATE "test/include/" )
target_link_libraries( testplugin1_release "boost_system" "${PROJECT_TARGET}" )
set_target_properties( testplugin1_release PROPERTIES
                       EXCLUDE_FROM_ALL true
                       EXCLUDE_FROM_DEFAULT_BUILD true
                       PREFIX ""
                       LIBRARY_OUTPUT_DIRECTORY "../test/TestDirectory/TestPlugins/release/"
                       OUTPUT_NAME "TestPlugin1"
                       COMPILE_FLAGS ${COMPILE_FLAGS_RELEASE}
                       LINK_FLAGS ${LINK_FLAGS_RELEASE} )
add_dependencies( testplugin1_release release )

add_library( testplugin1_minsizerel SHARED "test/src/TestPlugins/TestPlugin1.cpp" )
target_include_directories( testplugin1_minsizerel PRIVATE "test/include/" )
target_link_libraries( testplugin1_minsizerel "boost_system" "${PROJECT_TARGET}" )
set_target_properties( testplugin1_minsizerel PROPERTIES
                       EXCLUDE_FROM_ALL true
                       EXCLUDE_FROM_DEFAULT_BUILD true
                       PREFIX ""
                       LIBRARY_OUTPUT_DIRECTORY "../test/TestDirectory/TestPlugins/release/"
                       OUTPUT_NAME "TestPlugin1"
                       COMPILE_FLAGS ${COMPILE_FLAGS_MINSIZEREL}
                       LINK_FLAGS ${LINK_FLAGS_MINSIZEREL} )
add_dependencies( testplugin1_minsizerel minesizerel )

# TestPlugin2

add_library( testplugin2_debug SHARED "test/src/TestPlugins/TestPlugin2.cpp" )
target_include_directories( testplugin2_debug PRIVATE "test/include/" )
target_link_libraries( testplugin2_debug "boost_system" "${PROJECT_TARGET}_d" )
set_target_properties( testplugin2_debug PROPERTIES
                       EXCLUDE_FROM_ALL true
                       EXCLUDE_FROM_DEFAULT_BUILD true
                       PREFIX ""
                       LIBRARY_OUTPUT_DIRECTORY "../test/TestDirectory/TestPlugins/debug/"
                       OUTPUT_NAME "TestPlugin2"
                       COMPILE_FLAGS ${COMPILE_FLAGS_DEBUG}
                       LINK_FLAGS ${LINK_FLAGS_DEBUG} )
add_dependencies( testplugin2_debug debug )

add_library( testplugin2_relwithdebinfo SHARED "test/src/TestPlugins/TestPlugin2.cpp" )
target_include_directories( testplugin2_relwithdebinfo PRIVATE "test/include/" )
target_link_libraries( testplugin2_relwithdebinfo "boost_system" "${PROJECT_TARGET}" )
set_target_properties( testplugin2_relwithdebinfo PROPERTIES
                       EXCLUDE_FROM_ALL true
                       EXCLUDE_FROM_DEFAULT_BUILD true
                       PREFIX ""
                       LIBRARY_OUTPUT_DIRECTORY "../test/TestDirectory/TestPlugins/release/"
                       OUTPUT_NAME "TestPlugin2"
                       COMPILE_FLAGS ${COMPILE_FLAGS_RELWITHDEBINFO}
                       LINK_FLAGS ${LINK_FLAGS_RELWITHDEBINFO} )
add_dependencies( testplugin2_relwithdebinfo relwithdebinfo )

add_library( testplugin2_release SHARED "test/src/TestPlugins/TestPlugin2.cpp" )
target_include_directories( testplugin2_release PRIVATE "test/include/" )
target_link_libraries( testplugin2_release "boost_system" "${PROJECT_TARGET}" )
set_target_properties( testplugin2_release PROPERTIES
                       EXCLUDE_FROM_ALL true
                       EXCLUDE_FROM_DEFAULT_BUILD true
                       PREFIX ""
                       LIBRARY_OUTPUT_DIRECTORY "../test/TestDirectory/TestPlugins/release/"
                       OUTPUT_NAME "TestPlugin2"
                       COMPILE_FLAGS ${COMPILE_FLAGS_RELEASE}
                       LINK_FLAGS ${LINK_FLAGS_RELEASE} )
add_dependencies( testplugin2_release release )

add_library( testplugin2_minesizerel SHARED "test/src/TestPlugins/TestPlugin2.cpp" )
target_include_directories( testplugin2_minesizerel PRIVATE "test/include/" )
target_link_libraries( testplugin2_minesizerel "boost_system" "${PROJECT_TARGET}" )
set_target_properties( testplugin2_minesizerel PROPERTIES
                       EXCLUDE_FROM_ALL true
                       EXCLUDE_FROM_DEFAULT_BUILD true
                       PREFIX ""
                       LIBRARY_OUTPUT_DIRECTORY "../test/TestDirectory/TestPlugins/release/"
                       OUTPUT_NAME "TestPlugin2"
                       COMPILE_FLAGS ${COMPILE_FLAGS_MINSIZEREL}
                       LINK_FLAGS ${LINK_FLAGS_MINSIZEREL} )
add_dependencies( testplugin2_minesizerel minesizerel )

# TestPlugin3

add_library( testplugin3_debug SHARED "test/src/TestPlugins/TestPlugin3.cpp" )
target_include_directories( testplugin3_debug PRIVATE "test/include/" )
target_link_libraries( testplugin3_debug "boost_system" "${PROJECT_TARGET}_d" )
set_target_properties( testplugin3_debug PROPERTIES
                       EXCLUDE_FROM_ALL true
                       EXCLUDE_FROM_DEFAULT_BUILD true
                       PREFIX ""
                       LIBRARY_OUTPUT_DIRECTORY "../test/TestDirectory/TestPlugins/debug/"
                       OUTPUT_NAME "TestPlugin3"
                       COMPILE_FLAGS ${COMPILE_FLAGS_DEBUG}
                       LINK_FLAGS ${LINK_FLAGS_DEBUG} )
add_dependencies( testplugin3_debug debug )

add_library( testplugin3_relwithdebinfo SHARED "test/src/TestPlugins/TestPlugin3.cpp" )
target_include_directories( testplugin3_relwithdebinfo PRIVATE "test/include/" )
target_link_libraries( testplugin3_relwithdebinfo "boost_system" "${PROJECT_TARGET}" )
set_target_properties( testplugin3_relwithdebinfo PROPERTIES
                       EXCLUDE_FROM_ALL true
                       EXCLUDE_FROM_DEFAULT_BUILD true
                       PREFIX ""
                       LIBRARY_OUTPUT_DIRECTORY "../test/TestDirectory/TestPlugins/release/"
                       OUTPUT_NAME "TestPlugin3"
                       COMPILE_FLAGS ${COMPILE_FLAGS_RELWITHDEBINFO}
                       LINK_FLAGS ${LINK_FLAGS_RELWITHDEBINFO} )
add_dependencies( testplugin3_relwithdebinfo relwithdebinfo )

add_library( testplugin3_release SHARED "test/src/TestPlugins/TestPlugin3.cpp" )
target_include_directories( testplugin3_release PRIVATE "test/include/" )
target_link_libraries( testplugin3_release "boost_system" "${PROJECT_TARGET}" )
set_target_properties( testplugin3_release PROPERTIES
                       EXCLUDE_FROM_ALL true
                       EXCLUDE_FROM_DEFAULT_BUILD true
                       PREFIX ""
                       LIBRARY_OUTPUT_DIRECTORY "../test/TestDirectory/TestPlugins/release/"
                       OUTPUT_NAME "TestPlugin3"
                       COMPILE_FLAGS ${COMPILE_FLAGS_RELEASE}
                       LINK_FLAGS ${LINK_FLAGS_RELEASE} )
add_dependencies( testplugin3_release release )

add_library( testplugin3_minesizerel SHARED "test/src/TestPlugins/TestPlugin3.cpp" )
target_include_directories( testplugin3_minesizerel PRIVATE "test/include/" )
target_link_libraries( testplugin3_minesizerel "boost_system" "${PROJECT_TARGET}" )
set_target_properties( testplugin3_minesizerel PROPERTIES
                       EXCLUDE_FROM_ALL true
                       EXCLUDE_FROM_DEFAULT_BUILD true
                       PREFIX ""
                       LIBRARY_OUTPUT_DIRECTORY "../test/TestDirectory/TestPlugins/release/"
                       OUTPUT_NAME "TestPlugin3"
                       COMPILE_FLAGS ${COMPILE_FLAGS_MINSIZEREL}
                       LINK_FLAGS ${LINK_FLAGS_MINSIZEREL} )
add_dependencies( testplugin3_minesizerel minesizerel )

# Project Tests

add_executable( project_test_debug ${PROJECT_TEST_SOURCES} )
target_include_directories( project_test_debug PRIVATE "test/include/" )
target_link_libraries( project_test_debug ${PROJECT_TEST_LIBRARIES_DEBUG} "${PROJECT_TARGET}_d" )
set_target_properties( project_test_debug PROPERTIES
                       EXCLUDE_FROM_ALL true
                       EXCLUDE_FROM_DEFAULT_BUILD true
                       RUNTIME_OUTPUT_DIRECTORY "../test/bin/debug/"
                       OUTPUT_NAME "${PROJECT_TARGET}_test"
                       COMPILE_FLAGS ${COMPILE_FLAGS_DEBUG}
                       LINK_FLAGS ${LINK_FLAGS_DEBUG} )
add_dependencies( project_test_debug debug testplugin1_debug testplugin2_debug testplugin3_debug )

add_executable( project_test_relwithdebinfo ${PROJECT_TEST_SOURCES} )
target_include_directories( project_test_relwithdebinfo PRIVATE "test/include/" )
target_link_libraries( project_test_relwithdebinfo ${PROJECT_TEST_LIBRARIES_RELEASE} "${PROJECT_TARGET}" )
set_target_properties( project_test_relwithdebinfo PROPERTIES
                       EXCLUDE_FROM_ALL true
                       EXCLUDE_FROM_DEFAULT_BUILD true
                       RUNTIME_OUTPUT_DIRECTORY "../test/bin/release/"
                       OUTPUT_NAME "${PROJECT_TARGET}_test"
                       COMPILE_FLAGS ${COMPILE_FLAGS_RELWITHDEBINFO}
                       LINK_FLAGS ${LINK_FLAGS_RELWITHDEBINFO} )
add_dependencies( project_test_relwithdebinfo relwithdebinfo testplugin1_relwithdebinfo testplugin2_relwithdebinfo testplugin3_relwithdebinfo )

add_executable( project_test_release ${PROJECT_TEST_SOURCES} )
target_include_directories( project_test_release PRIVATE "test/include/" )
target_link_libraries( project_test_release ${PROJECT_TEST_LIBRARIES_RELEASE} "${PROJECT_TARGET}" )
set_target_properties( project_test_release PROPERTIES
                       EXCLUDE_FROM_ALL true
                       EXCLUDE_FROM_DEFAULT_BUILD true
                       RUNTIME_OUTPUT_DIRECTORY "../test/bin/release/"
                       OUTPUT_NAME "${PROJECT_TARGET}_test"
                       COMPILE_FLAGS ${COMPILE_FLAGS_RELEASE}
                       LINK_FLAGS ${LINK_FLAGS_RELEASE} )
add_dependencies( project_test_release release testplugin1_release testplugin2_release testplugin3_release )

add_executable( project_test_minesizerel ${PROJECT_TEST_SOURCES} )
target_include_directories( project_test_minesizerel PRIVATE "test/include/" )
target_link_libraries( project_test_minesizerel ${PROJECT_TEST_LIBRARIES_RELEASE} "${PROJECT_TARGET}" )
set_target_properties( project_test_minesizerel PROPERTIES
                       EXCLUDE_FROM_ALL true
                       EXCLUDE_FROM_DEFAULT_BUILD true
                       RUNTIME_OUTPUT_DIRECTORY "../test/bin/release/"
                       OUTPUT_NAME "${PROJECT_TARGET}_test"
                       COMPILE_FLAGS ${COMPILE_FLAGS_MINSIZEREL}
                       LINK_FLAGS ${LINK_FLAGS_MINSIZEREL} )
add_dependencies( project_test_minesizerel minesizerel testplugin1_minsizerel testplugin2_minesizerel testplugin3_minesizerel )

# Doxygen Documentation

if( DOXYGEN_FOUND )
	add_custom_target( doc ${DOXYGEN_EXECUTABLE} "${PROJECT_SOURCE_DIR}/Doxyfile"
	                   WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}" COMMENT "Generating Doxygen documentation ..." VERBATIM )
endif()

# Unit Tests

add_custom_target( tests_debug
                   DEPENDS debug testplugin1_debug testplugin2_debug testplugin3_debug project_test_debug )

add_custom_target( tests_relwithdebinfo
                   DEPENDS relwithdebinfo testplugin1_relwithdebinfo testplugin2_relwithdebinfo testplugin3_relwithdebinfo project_test_relwithdebinfo )

add_custom_target( tests_release
                   DEPENDS release testplugin1_release testplugin2_release testplugin3_release project_test_release )

add_custom_target( tests_minsizerel
                   DEPENDS minesizerel testplugin1_minsizerel testplugin2_minesizerel testplugin3_minesizerel project_test_minesizerel )

# Installation

install( DIRECTORY "include/" DESTINATION "${PROJECT_INCLUDE_PATH}" FILES_MATCHING PATTERN "*.hpp" )

if( ( ${CMAKE_SYSTEM_NAME} STREQUAL "Linux" ) OR ( ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin" ) )
	install( TARGETS debug LIBRARY DESTINATION "${PROJECT_LIB_PATH}" OPTIONAL )
	install( TARGETS release LIBRARY DESTINATION "${PROJECT_LIB_PATH}" OPTIONAL )
elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Windows" )
	install( TARGETS debug ARCHIVE DESTINATION "${PROJECT_ARCHIVE_PATH}" RUNTIME DESTINATION "${PROJECT_LIB_PATH}" OPTIONAL )
	install( TARGETS release ARCHIVE DESTINATION "${PROJECT_ARCHIVE_PATH}" RUNTIME DESTINATION "${PROJECT_LIB_PATH}" OPTIONAL )
endif()

install( FILES "CHANGELOG" "CONTRIBUTING.md" "LICENSE" "README.md" DESTINATION "${PROJECT_DOC_PATH}" )
install( DIRECTORY "doc/" DESTINATION "${PROJECT_DOC_PATH}" PATTERN "uml" EXCLUDE PATTERN "*.odg" EXCLUDE )
install( DIRECTORY "build/doc/html" DESTINATION "${PROJECT_DOC_PATH}" OPTIONAL FILES_MATCHING REGEX ".*[.][chjp][nst][gms]*[l]*" )

# Uninstallation

add_custom_target( uninstall
                   COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_INSTALL_PREFIX}/${PROJECT_INCLUDE_PATH}"
                   COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_INSTALL_PREFIX}/${PROJECT_LIB_PATH}/*${PROJECT_TARGET}*"
                   COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_INSTALL_PREFIX}/${PROJECT_DOC_PATH}"
                   COMMENT "Uninstalling the project ..." )

################################################################################################################################################################
# End of 'CMakeLists.txt'
################################################################################################################################################################

################################################################################################################################################################
# CMakeLists.txt
# Robert M. Baker | Created : 10DEC11 | Last Modified : 26AUG19 by Robert M. Baker
# Version : 2.1.1
# This is a CMake script for building 'QMXStdLib'.
################################################################################################################################################################
# Copyright (C) 2011-2019 QuantuMatriX Software, a QuantuMatriX Technologies Cooperative Partnership
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

# TODO (Malachy - Priority 50): Complete and test for Apple macOS platform.
# TODO (Malachy - Priority 50): Complete and test for Microsoft Windows platform.

################################################################################################################################################################
# Environment Check
################################################################################################################################################################

# General

cmake_minimum_required( VERSION 3.0 )

if( NOT "${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}/build" )
	message( FATAL_ERROR "You must build the project from '${CMAKE_SOURCE_DIR}/build'!  See 'README.md' for build instructions." )
endif()

project( PROJECT VERSION 2.1.1 LANGUAGES C CXX )

find_package( GTest 1.6 )
find_package( Doxygen )

# Project-Specific

find_package( Threads REQUIRED )
find_package( Boost 1.69 REQUIRED COMPONENTS chrono filesystem locale system thread timer )

################################################################################################################################################################
# Setup
################################################################################################################################################################

# Project Info

set( PROJECT_TARGET "qmxstdlib" )
set( DOXYGEN_PROJECT_NAME "QMXStdLib" )
set( DOXYGEN_PROJECT_BRIEF "QuantuMatriX Standard Library" )

# General

include( CMakePackageConfigHelpers )
set( CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true )

set(
	COMPILE_FLAGS_DEBUG "-g -Wall -Wno-unknown-warning-option -Wno-maybe-uninitialized -Wno-attributes -D_DEBUG"
	CACHE STRING "These are the debug compile flags."
)

set(
	COMPILE_FLAGS_RELWITHDEBINFO "-O2 -g -Wall -Wno-unknown-warning-option -Wno-maybe-uninitialized -Wno-attributes -DNDEBUG"
	CACHE STRING "These are the release with debug info compile flags."
)

set(
	COMPILE_FLAGS_RELEASE "-O3 -Wall -Wno-unknown-warning-option -Wno-maybe-uninitialized -Wno-attributes -DNDEBUG"
	CACHE STRING "These are the release compile flags."
)

set(
	COMPILE_FLAGS_MINSIZEREL "-Os -Wall -Wno-unknown-warning-option -Wno-maybe-uninitialized -Wno-attributes -DNDEBUG"
	CACHE STRING "These are the minimum size release compile flags."
)

set(
	LINK_FLAGS_DEBUG "-z defs"
	CACHE STRING "These are the debug link flags."
)

set(
	LINK_FLAGS_RELWITHDEBINFO "-z defs"
	CACHE STRING "These are the release with debug info link flags."
)

set(
	LINK_FLAGS_RELEASE "-z defs -s"
	CACHE STRING "These are the release link flags."
)

set(
	LINK_FLAGS_MINSIZEREL "-z defs -s"
	CACHE STRING "These are the minimum size release link flags."
)

if( ${CMAKE_SYSTEM_NAME} STREQUAL "Linux" )
	set(
		PROJECT_INCLUDE_PATH "include/${PROJECT_TARGET}"
		CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the headers will be installed."
	)

	set(
		PROJECT_LIB_PATH "lib"
		CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the shared libraries will be installed."
	)

	set(
		PROJECT_DOC_PATH "share/doc/${PROJECT_TARGET}"
		CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the documentation will be installed."
	)
elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin" )
	set(
		PROJECT_INCLUDE_PATH ""
		CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the headers will be installed."
	)

	set(
		PROJECT_LIB_PATH ""
		CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the shared libraries will be installed."
	)

	set(
		PROJECT_DOC_PATH ""
		CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the documentation will be installed."
	)
elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Windows" )
	set(
		PROJECT_INCLUDE_PATH "include/${PROJECT_TARGET}"
		CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the headers will be installed."
	)

	set(
		PROJECT_ARCHIVE_PATH "lib"
		CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the import libraries will be installed."
	)

	set(
		PROJECT_LIB_PATH "bin"
		CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the shared libraries will be installed."
	)

	set(
		PROJECT_DOC_PATH "share/doc/${PROJECT_TARGET}"
		CACHE STRING "This is the path (appended to 'CMAKE_INSTALL_PREFIX') where the documentation will be installed."
	)
endif()

# Project-Specific

set(
	MAX_BUFFER_SIZE "1024"
	CACHE STRING "Maximum default size for a c-string buffer."
)

set(
	CONSOLEIO_DEFAULT_INPUT_TYPE "ConsoleIO::RANGE"
	CACHE STRING "Default input type for the 'ConsoleIO::getInput' method."
)

set(
	CONSOLEIO_DEFAULT_CHOICES "A, B, C, D, or E"
	CACHE STRING "Default set of choices for the 'ConsoleIO::getInput' method."
)

set(
	FILESYSTEM_SYMBOL_DELIMITER_LEFT "<"
	CACHE STRING "Left delimiter for embedded symbols in paths.  This must be a single-character value."
)

set(
	FILESYSTEM_SYMBOL_DELIMITER_RIGHT ">"
	CACHE STRING "Right delimiter for embedded symbols in paths.  This must be a single-character value."
)

set(
	STACKTRACER_ENTRY_SEPARATOR "->"
	CACHE STRING "Separator between entries in a stack trace."
)

set(
	PROGRAMOPTIONS_TOGGLE_OPTION_PREFIX "-"
	CACHE STRING "The prefix for a toggle option.  This must be a single-character value."
)

set(
	PROGRAMOPTIONS_COMMAND_OPTION_PREFIX "--"
	CACHE STRING "The prefix for a command/config option.  This must be a two-character value."
)

set(
	PROGRAMOPTIONS_GROUP_KEY_SEPARATOR "."
	CACHE STRING "Separator used between the group and key of config options.  This must be a single-character value."
)

set(
	PROGRAMOPTIONS_ASSIGNMENT_OPERATOR "="
	CACHE STRING "The assignment operator used between a key and its value.  This must be a single-character value."
)

set(
	PROGRAMOPTIONS_COMMENT_INITIATOR "#"
	CACHE STRING "Character which initiates a comment.  This must be a single-character value."
)

set(
	PROGRAMOPTIONS_GROUP_DELIMITER_LEFT "["
	CACHE STRING "Left delimiter for a config file group.  This must be a single-character value."
)

set(
	PROGRAMOPTIONS_GROUP_DELIMITER_RIGHT "]"
	CACHE STRING "Right delimiter for a config file group.  This must be a single-character value."
)

set(
	PROGRAMOPTIONS_GROUP_DEFAULT "Global"
	CACHE STRING "The default group for any config option not specifying one."
)

set(
	PROJECT_INCLUDES
	"${Boost_INCLUDE_DIRS}"
)

set(
	PROJECT_SOURCES
	"src/ConsoleIO.cpp"
	"src/DynamicLibrary.cpp"
	"src/FileSystem.cpp"
	"src/ProgramOptions.cpp"
	"src/QMXException.cpp"
	"src/StackTracer.cpp"
	"src/String.cpp"
	"src/ThreadManager.cpp"
	"src/Timer.cpp"
	"src/Utility.cpp"
)

set(
	PROJECT_LIBRARIES_DEBUG
	"${CMAKE_DL_LIBS}"
	"${Boost_LIBRARIES}"
)

set( PROJECT_LIBRARIES_RELEASE ${PROJECT_LIBRARIES_DEBUG} )

set(
	PROJECT_TEST_INCLUDES
	"${Boost_INCLUDE_DIRS}"
	"${GTEST_INCLUDE_DIRS}"
)

set(
	PROJECT_TEST_SOURCES
	"test/src/ConsoleIOTest.cpp"
	"test/src/DynamicLibraryTest.cpp"
	"test/src/FileSystemTest.cpp"
	"test/src/Main.cpp"
	"test/src/NumericTest.cpp"
	"test/src/ProgramOptionsTest.cpp"
	"test/src/QMXExceptionTest.cpp"
	"test/src/SequencerTest.cpp"
	"test/src/StackTracerTest.cpp"
	"test/src/StringTest.cpp"
	"test/src/ThreadManagerTest.cpp"
	"test/src/TimerTest.cpp"
	"test/src/UniqueRandomTest.cpp"
	"test/src/UtilityTest.cpp"
)

set( PROJECT_TEST_LIBRARIES_DEBUG
	"${CMAKE_THREAD_LIBS_INIT}"
	"${Boost_LIBRARIES}"
	"${GTEST_LIBRARIES}"
)

set( PROJECT_TEST_LIBRARIES_RELEASE ${PROJECT_TEST_LIBRARIES_DEBUG} )

add_definitions( -DBOOST_ALL_DYN_LINK -DBOOST_FILESYSTEM_NO_DEPRECATED -DQMXSTDLIB_INTERNAL_BUILD )
link_directories( "${Boost_LIBRARY_DIRS}" "build/" )

if( NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Windows" )
	configure_file( "config/test_setup.sh.in" "test_setup.sh" @ONLY )
else()
	configure_file( "config/test_setup.bat.in" "test_setup.bat" @ONLY )
endif()

# Configure Files

configure_file( "config/Config.hpp.in" "Config.hpp" )

if( DOXYGEN_FOUND )
	configure_file( "config/Doxyfile.in" "Doxyfile" @ONLY )
endif()

configure_package_config_file(
	"config/ProjectConfig.cmake.in" "${DOXYGEN_PROJECT_NAME}Config.cmake"
	INSTALL_DESTINATION "${PROJECT_LIB_PATH}/cmake/${PROJECT_TARGET}"
	PATH_VARS PROJECT_INCLUDE_PATH PROJECT_LIB_PATH
	NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file( "${DOXYGEN_PROJECT_NAME}ConfigVersion.cmake" VERSION 2.1.1 COMPATIBILITY SameMajorVersion )

################################################################################################################################################################
# Targets
################################################################################################################################################################

# Project

add_library( debug SHARED ${PROJECT_SOURCES} )
target_include_directories( debug PRIVATE ${PROJECT_INCLUDES} )
target_link_libraries( debug ${PROJECT_LIBRARIES_DEBUG} )

set_target_properties(
	debug PROPERTIES
	COMPILE_FLAGS ${COMPILE_FLAGS_DEBUG}
	LINK_FLAGS ${LINK_FLAGS_DEBUG}
	OUTPUT_NAME "${PROJECT_TARGET}_d"
	VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
	SOVERSION "${PROJECT_VERSION_MAJOR}"
)

add_library( relwithdebinfo SHARED ${PROJECT_SOURCES} )
target_include_directories( relwithdebinfo PRIVATE ${PROJECT_INCLUDES} )
target_link_libraries( relwithdebinfo ${PROJECT_LIBRARIES_RELEASE} )

set_target_properties(
	relwithdebinfo PROPERTIES
	EXCLUDE_FROM_ALL true
	EXCLUDE_FROM_DEFAULT_BUILD true
	COMPILE_FLAGS ${COMPILE_FLAGS_RELWITHDEBINFO}
	LINK_FLAGS ${LINK_FLAGS_RELWITHDEBINFO}
	OUTPUT_NAME "${PROJECT_TARGET}"
	VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
	SOVERSION "${PROJECT_VERSION_MAJOR}"
)

add_library( release SHARED ${PROJECT_SOURCES} )
target_include_directories( release PRIVATE ${PROJECT_INCLUDES} )
target_link_libraries( release ${PROJECT_LIBRARIES_RELEASE} )

set_target_properties(
	release PROPERTIES
	COMPILE_FLAGS ${COMPILE_FLAGS_RELEASE}
	LINK_FLAGS ${LINK_FLAGS_RELEASE}
	OUTPUT_NAME "${PROJECT_TARGET}"
	VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
	SOVERSION "${PROJECT_VERSION_MAJOR}"
)

add_library( minsizerel SHARED ${PROJECT_SOURCES} )
target_include_directories( minsizerel PRIVATE ${PROJECT_INCLUDES} )
target_link_libraries( minsizerel ${PROJECT_LIBRARIES_RELEASE} )

set_target_properties(
	minsizerel PROPERTIES
	EXCLUDE_FROM_ALL true
	EXCLUDE_FROM_DEFAULT_BUILD true
	COMPILE_FLAGS ${COMPILE_FLAGS_MINSIZEREL}
	LINK_FLAGS ${LINK_FLAGS_MINSIZEREL}
	OUTPUT_NAME "${PROJECT_TARGET}"
	VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
	SOVERSION "${PROJECT_VERSION_MAJOR}"
)

# TestLibrary

add_library( testlibrary_debug SHARED "test/src/TestLibrary/TestLibrary.cpp" )

set_target_properties(
	testlibrary_debug PROPERTIES
	EXCLUDE_FROM_ALL true
	EXCLUDE_FROM_DEFAULT_BUILD true
	PREFIX ""
	LIBRARY_OUTPUT_DIRECTORY "TestDirectory/TestLibrary/debug/"
	OUTPUT_NAME "TestLibrary"
	COMPILE_FLAGS ${COMPILE_FLAGS_DEBUG}
	LINK_FLAGS ${LINK_FLAGS_DEBUG}
)

add_dependencies( testlibrary_debug debug )

add_library( testlibrary_relwithdebinfo SHARED "test/src/TestLibrary/TestLibrary.cpp" )

set_target_properties(
	testlibrary_relwithdebinfo PROPERTIES
	EXCLUDE_FROM_ALL true
	EXCLUDE_FROM_DEFAULT_BUILD true
	PREFIX ""
	LIBRARY_OUTPUT_DIRECTORY "TestDirectory/TestLibrary/release/"
	OUTPUT_NAME "TestLibrary"
	COMPILE_FLAGS ${COMPILE_FLAGS_RELWITHDEBINFO}
	LINK_FLAGS ${LINK_FLAGS_RELWITHDEBINFO}
)

add_dependencies( testlibrary_relwithdebinfo relwithdebinfo )

add_library( testlibrary_release SHARED "test/src/TestLibrary/TestLibrary.cpp" )

set_target_properties(
	testlibrary_release PROPERTIES
	EXCLUDE_FROM_ALL true
	EXCLUDE_FROM_DEFAULT_BUILD true
	PREFIX ""
	LIBRARY_OUTPUT_DIRECTORY "TestDirectory/TestLibrary/release/"
	OUTPUT_NAME "TestLibrary"
	COMPILE_FLAGS ${COMPILE_FLAGS_RELEASE}
	LINK_FLAGS ${LINK_FLAGS_RELEASE}
)

add_dependencies( testlibrary_release release )

add_library( testlibrary_minsizerel SHARED "test/src/TestLibrary/TestLibrary.cpp" )

set_target_properties(
	testlibrary_minsizerel PROPERTIES
	EXCLUDE_FROM_ALL true
	EXCLUDE_FROM_DEFAULT_BUILD true
	PREFIX ""
	LIBRARY_OUTPUT_DIRECTORY "TestDirectory/TestLibrary/release/"
	OUTPUT_NAME "TestLibrary"
	COMPILE_FLAGS ${COMPILE_FLAGS_MINSIZEREL}
	LINK_FLAGS ${LINK_FLAGS_MINSIZEREL}
)

add_dependencies( testlibrary_minsizerel minsizerel )

# Project Tests

add_executable( project_test_debug ${PROJECT_TEST_SOURCES} )
target_include_directories( project_test_debug PRIVATE ${PROJECT_TEST_INCLUDES} )
target_link_libraries( project_test_debug ${PROJECT_TEST_LIBRARIES_DEBUG} "${PROJECT_TARGET}_d" )

set_target_properties(
	project_test_debug PROPERTIES
	EXCLUDE_FROM_ALL true
	EXCLUDE_FROM_DEFAULT_BUILD true
	OUTPUT_NAME "${PROJECT_TARGET}_test_d"
	COMPILE_FLAGS ${COMPILE_FLAGS_DEBUG}
	LINK_FLAGS ${LINK_FLAGS_DEBUG}
)

add_dependencies( project_test_debug debug testlibrary_debug )

add_executable( project_test_relwithdebinfo ${PROJECT_TEST_SOURCES} )
target_include_directories( project_test_relwithdebinfo PRIVATE ${PROJECT_TEST_INCLUDES} )
target_link_libraries( project_test_relwithdebinfo ${PROJECT_TEST_LIBRARIES_RELEASE} "${PROJECT_TARGET}" )

set_target_properties(
	project_test_relwithdebinfo PROPERTIES
	EXCLUDE_FROM_ALL true
	EXCLUDE_FROM_DEFAULT_BUILD true
	OUTPUT_NAME "${PROJECT_TARGET}_test"
	COMPILE_FLAGS ${COMPILE_FLAGS_RELWITHDEBINFO}
	LINK_FLAGS ${LINK_FLAGS_RELWITHDEBINFO}
)

add_dependencies( project_test_relwithdebinfo relwithdebinfo testlibrary_relwithdebinfo )

add_executable( project_test_release ${PROJECT_TEST_SOURCES} )
target_include_directories( project_test_release PRIVATE ${PROJECT_TEST_INCLUDES} )
target_link_libraries( project_test_release ${PROJECT_TEST_LIBRARIES_RELEASE} "${PROJECT_TARGET}" )

set_target_properties(
	project_test_release PROPERTIES
	EXCLUDE_FROM_ALL true
	EXCLUDE_FROM_DEFAULT_BUILD true
	OUTPUT_NAME "${PROJECT_TARGET}_test"
	COMPILE_FLAGS ${COMPILE_FLAGS_RELEASE}
	LINK_FLAGS ${LINK_FLAGS_RELEASE}
)

add_dependencies( project_test_release release testlibrary_release )

add_executable( project_test_minsizerel ${PROJECT_TEST_SOURCES} )
target_include_directories( project_test_minsizerel PRIVATE ${PROJECT_TEST_INCLUDES} )
target_link_libraries( project_test_minsizerel ${PROJECT_TEST_LIBRARIES_RELEASE} "${PROJECT_TARGET}" )

set_target_properties(
	project_test_minsizerel PROPERTIES
	EXCLUDE_FROM_ALL true
	EXCLUDE_FROM_DEFAULT_BUILD true
	OUTPUT_NAME "${PROJECT_TARGET}_test"
	COMPILE_FLAGS ${COMPILE_FLAGS_MINSIZEREL}
	LINK_FLAGS ${LINK_FLAGS_MINSIZEREL}
)

add_dependencies( project_test_minsizerel minsizerel testlibrary_minsizerel )

# Doxygen Documentation

if( DOXYGEN_FOUND )
	add_custom_target( doc ${DOXYGEN_EXECUTABLE} "Doxyfile" COMMENT "Generating Doxygen documentation ..." VERBATIM )
endif()

# Unit Tests

add_custom_target( tests_debug DEPENDS project_test_debug )
add_custom_target( tests_relwithdebinfo DEPENDS project_test_relwithdebinfo )
add_custom_target( tests_release DEPENDS project_test_release )
add_custom_target( tests_minsizerel DEPENDS project_test_minsizerel )
add_custom_target( tests DEPENDS tests_debug tests_release )

# Installation

install( DIRECTORY "include/" DESTINATION "${PROJECT_INCLUDE_PATH}" FILES_MATCHING PATTERN "*.hpp" )
install( FILES "build/Config.hpp" DESTINATION "${PROJECT_INCLUDE_PATH}" )

if( ( ${CMAKE_SYSTEM_NAME} STREQUAL "Linux" ) OR ( ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin" ) )
	install( TARGETS debug LIBRARY DESTINATION "${PROJECT_LIB_PATH}" OPTIONAL )
	install( TARGETS release LIBRARY DESTINATION "${PROJECT_LIB_PATH}" OPTIONAL )
elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Windows" )
	install( TARGETS debug ARCHIVE DESTINATION "${PROJECT_ARCHIVE_PATH}" RUNTIME DESTINATION "${PROJECT_LIB_PATH}" OPTIONAL )
	install( TARGETS release ARCHIVE DESTINATION "${PROJECT_ARCHIVE_PATH}" RUNTIME DESTINATION "${PROJECT_LIB_PATH}" OPTIONAL )
endif()

install( DIRECTORY "doc/" DESTINATION "${PROJECT_DOC_PATH}" PATTERN "uml" EXCLUDE PATTERN "*.odg" EXCLUDE )
install( DIRECTORY "build/doc/html" DESTINATION "${PROJECT_DOC_PATH}" OPTIONAL FILES_MATCHING REGEX ".*[.][chjp][nst][gms]*[l]*" )
install( FILES "CHANGELOG" "CONTRIBUTING.md" "LICENSE" "README.md" DESTINATION "${PROJECT_DOC_PATH}" )

install(
	FILES "build/${DOXYGEN_PROJECT_NAME}Config.cmake" "build/${DOXYGEN_PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION "${PROJECT_LIB_PATH}/cmake/${PROJECT_TARGET}"
)

# Uninstallation

add_custom_target(
	uninstall
	COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_INSTALL_PREFIX}/${PROJECT_INCLUDE_PATH}"
	COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_INSTALL_PREFIX}/${PROJECT_LIB_PATH}/*${PROJECT_TARGET}*"
	COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_INSTALL_PREFIX}/${PROJECT_DOC_PATH}"
	COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_INSTALL_PREFIX}/${PROJECT_LIB_PATH}/cmake/${PROJECT_TARGET}"
	COMMENT "Uninstalling the project ..."
)

################################################################################################################################################################
# End of 'CMakeLists.txt'
################################################################################################################################################################

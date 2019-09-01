////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FileSystem.hpp
// Robert M. Baker | Created : 05MAR12 | Last Modified : 31AUG19 by Robert M. Baker
// Version : 2.1.1
// This is a header file for 'QMXStdLib'; it defines the interface for a set of file system functions.
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
  * @date    Created : 05MAR12
  * @date    Last Modified : 31AUG19 by Robert M. Baker
  * @version 2.1.1
  *
  * @brief This header file defines the interface for a set of file system functions.
  *
  * @section FileSystemH0000 Description
  *
  * This header file defines the interface for a set of file system functions.
  *
  * @section FileSystemH0001 License
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

#ifndef __QMX_QMXSTDLIB_FILESYSTEM_HPP_
#define __QMX_QMXSTDLIB_FILESYSTEM_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/filesystem.hpp>

#include "Base.hpp"
#include "String.hpp"
#include "RAII/ScopedStackTrace.hpp"

#if( QMX_PLATFORM == QMX_PLATFORM_WINDOWS )
#	include <windows.h>
#endif // Platform Headers

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DIRECTORY_END                   DirectoryIterator()

#if ( QMX_PLATFORM != QMX_PLATFORM_WINDOWS )
#	define FSMC_MAKE_CANONICAL           result = boost::filesystem::canonical( source, ( base.empty() ? boost::filesystem::current_path() : base ) );
#	define FSRS_READ_SYMLINK             result = boost::filesystem::read_symlink( source );
#	define FSCL_CREATE_BUFFERS
#	define FSCL_FILL_BUFFERS
#	define FSCL_CREATE_HARDLINK          boost::filesystem::create_hard_link( source, link )
#	define FSCL_CREATE_DIRECTORY_SYMLINK boost::filesystem::create_directory_symlink( source, link )
#	define FSCL_CREATE_SYMLINK           boost::filesystem::create_symlink( source, link )
#else
#	define FSMC_MAKE_CANONICAL           char buffer[ MAX_BUFFER_SIZE ];\
	                                     HANDLE handle = CreateFile(\
	                                       source.string().c_str(),\
	                                       FILE_READ_ATTRIBUTES,\
	                                       ( FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE ),\
	                                       nullptr,\
	                                       OPEN_EXISTING,\
	                                       FILE_FLAG_BACKUP_SEMANTICS,\
	                                       nullptr\
	                                     );\
	                                     QMX_ASSERT(\
	                                       ( handle != INVALID_HANDLE_VALUE ),\
	                                       "QMXStdLib",\
	                                       "FileSystem::makeCanonical",\
	                                       "0000000A",\
	                                       source << ", " << base\
	                                     );\
	                                     GetFinalPathNameByHandle( handle, buffer, MAX_BUFFER_SIZE, FILE_NAME_NORMALIZED );\
	                                     result = buffer;\
	                                     result = result.string().substr( 4 );

#	define FSRS_READ_SYMLINK             char buffer[ MAX_BUFFER_SIZE ];\
	                                     HANDLE handle = CreateFile(\
	                                       source.string().c_str(),\
	                                       FILE_READ_ATTRIBUTES,\
	                                       ( FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE ),\
	                                       nullptr,\
	                                       OPEN_EXISTING,\
	                                       FILE_FLAG_BACKUP_SEMANTICS,\
	                                       nullptr\
	                                     );\
	                                     QMX_ASSERT( ( handle != INVALID_HANDLE_VALUE ), "QMXStdLib", "FileSystem::readSymlink", "0000000B", source );\
	                                     GetFinalPathNameByHandle( handle, buffer, MAX_BUFFER_SIZE, FILE_NAME_NORMALIZED );\
	                                     result = buffer;\
	                                     result = result.string().substr( 4 );

#	define FSCL_CREATE_BUFFERS           char sourceBuffer[ MAX_BUFFER_SIZE ];\
	                                     char linkBuffer[ MAX_BUFFER_SIZE ];
#	define FSCL_FILL_BUFFERS             strcpy( sourceBuffer, source.string().c_str() );\
	                                     strcpy( linkBuffer, link.string().c_str() );
#	define FSCL_CREATE_HARDLINK          wasSuccessful = CreateHardLink( linkBuffer, sourceBuffer, nullptr )
#	define FSCL_CREATE_DIRECTORY_SYMLINK wasSuccessful = CreateSymbolicLink( linkBuffer, sourceBuffer, 0x1 )
#	define FSCL_CREATE_SYMLINK           wasSuccessful = CreateSymbolicLink( linkBuffer, sourceBuffer, 0x0 )
#endif // Platform dependent macros.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Type Definitions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef boost::filesystem::path               Path;
typedef boost::filesystem::directory_iterator DirectoryIterator;

STANDARD_TYPEDEFS_X( Path,                    Path );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'FileSystem' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This is the namespace for all file system functions.
  */

namespace FileSystem
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'CopyOption' Enumeration
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This enumeration contains all valid copy options.
  */

enum CopyOption
{
	SKIP_IF_EXISTS,
	FAIL_IF_EXISTS,
	OVERWRITE_IF_EXISTS
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Prototypes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This function parses the specified path to expand any embedded symbols.
  *
  * The default delimiters for embedded symbols are angled brackets (e.g. "<HOME>/projects/<PROJECT_NAME>"); though, they can be configured to something else.
  * All functions/methods in QMX libraries making use of paths will assume they have already been parsed.
  *
  * @param target
  * 	This is the path to be parsed.
  *
  * @exception QMXException
  * 	If a malformed symbol was found in the path.<br>
  * 	If a non-existent symbol was found in the path.
  */

void parse( Path& target );

/**
  * @brief This function converts the specified path into a canonical path (i.e. an absolute path with no symlinks, '.', or '..' elements ).
  *
  * @param source
  * 	This is the path to be converted.
  *
  * @param base
  * 	This is the base path to use when converting.  If empty, the current working directory will be used.
  *
  * @return
  * 	The converted path, or an empty path if conversion failed.
  *
  * @exception QMXException
  * 	If the specified path could not be converted into a canonical path.
  */

Path makeCanonical( const Path& source, const Path& base = "" );

/**
  * @brief This function retrieves the contents of a symlink at the specified path.
  *
  * @param source
  * 	This is the path from which to retrieve the symlink contents.
  *
  * @return
  * 	The retrieved symlink contents.
  *
  * @exception QMXException
  * 	If the specified path's symlink contents could not be retrieved.
  */

Path readSymlink( const Path& source );

/**
  * @brief This function creates a hardlink/symlink at the specified destination path from the specified source path.
  *
  * @param source
  * 	This is the path from which to create the link.
  *
  * @param link
  * 	This is the path where the link will be created.
  *
  * @param isHardlink
  * 	This is the boolean flag which determines if the link is a hardlink or symlink.
  *
  * @exception QMXException
  * 	If the specified hardlink could not be created due to an invalid source target.<br>
  * 	If the specified hardlink/symlink could not be created using the specified arguments.
  */

void createLink( const Path& source, const Path& link, bool isHardlink = false );

/**
  * @brief This function copies the specified source path to the specified destination path with optional recursion and overwriting.
  *
  * @param source
  * 	This is the path from which to copy.
  *
  * @param destination
  * 	This is the path to which to copy.
  *
  * @param isRecursive
  * 	This is the boolean flag which determines if the copying will be recursive.
  *
  * @param targetCopyOption
  * 	This value determines what actions to take if a target already exists during copying.
  *
  * @exception QMXException
  * 	If the copy operation could not be performed due to an invalid source target.<br>
  * 	If the copy operation could not be completed.
  */

void copy( const Path& source, const Path& destination, bool isRecursive = true, CopyOption targetCopyOption = SKIP_IF_EXISTS );

/**
  * @brief This function runs the specified console command.
  *
  * @param command
  * 	This is the console command to run; if null, this function will instead test for the presence of a console command processor.
  *
  * @param successValue
  * 	This is the return value of the console command processor which indicates success.
  *
  * @return
  * 	A boolean value of 'true' if the console command was succesful, and 'false' otherwise; if testing for the presence of a console command processor, a
  * 	boolean value of 'true' if one is present, and 'false' otherwise.
  */

bool runCommand( const char* command = nullptr, int successValue = UNSET );

} // 'FileSystem' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'FileSystem' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_FILESYSTEM_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'FileSystem.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

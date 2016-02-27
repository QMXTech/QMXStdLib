////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FileSystem.hpp
// Robert M. Baker | Created : 05MAR12 | Last Modified : 20FEB16 by Robert M. Baker
// Version : 1.1.0
// This is a header file for 'QMXStdLib'; it defines the interface for a set of file system functions.
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
  * @date    Created : 05MAR12
  * @date    Last Modified : 20FEB16 by Robert M. Baker
  * @version 1.1.0
  *
  * @brief This header file defines the interface for a set of file system functions.
  *
  * @section Description
  *
  * This header file defines the interface for a set of file system functions.
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

#ifndef __QMX_QMXSTDLIB_FILESYSTEM_HPP_
#define __QMX_QMXSTDLIB_FILESYSTEM_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "String.hpp"
#include "RAII/ScopedStackTrace.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DIRECTORY_END                   DirectoryIterator()

#if ( QMX_PLATFORM != QMX_PLATFORM_WINDOWS )
#	define FSMC_MAKE_CANONICAL           Result = boost::filesystem::canonical( Target, ( Base.empty() ? boost::filesystem::current_path() : Base ) );
#	define FSRS_READ_SYMLINK             Result = boost::filesystem::read_symlink( Target );
#	define FSCL_CREATE_BUFFERS
#	define FSCL_FILL_BUFFERS
#	define FSCL_CREATE_HARDLINK          boost::filesystem::create_hard_link( Source, Link )
#	define FSCL_CREATE_DIRECTORY_SYMLINK boost::filesystem::create_directory_symlink( Source, Link )
#	define FSCL_CREATE_SYMLINK           boost::filesystem::create_symlink( Source, Link )
#else
#	define FSMC_MAKE_CANONICAL           char Buffer[ MAX_BUFFER_SIZE ];\
                                        HANDLE Handle = CreateFile( Target.string().c_str(),\
                                                                    FILE_READ_ATTRIBUTES,\
                                                                    ( FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE ),\
                                                                    nullptr,\
                                                                    OPEN_EXISTING,\
                                                                    FILE_FLAG_BACKUP_SEMANTICS,\
                                                                    nullptr );\
                                        QMX_ASSERT( ( Handle != INVALID_HANDLE_VALUE ),\
                                                    "QMXStdLib",\
                                                    "FileSystem::MakeCanonical",\
                                                    "0000000A",\
                                                    Target << ", " << Base );\
                                        GetFinalPathNameByHandle( Handle, Buffer, MAX_BUFFER_SIZE, FILE_NAME_NORMALIZED );\
                                        Result = Buffer;\
                                        Result = Result.string().substr( 4 );
#	define FSRS_READ_SYMLINK             char Buffer[ MAX_BUFFER_SIZE ];\
                                        HANDLE Handle = CreateFile( Target.string().c_str(),\
                                                                    FILE_READ_ATTRIBUTES,\
                                                                    ( FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE ),\
                                                                    nullptr,\
                                                                    OPEN_EXISTING,\
                                                                    FILE_FLAG_BACKUP_SEMANTICS,\
                                                                    nullptr );\
                                        QMX_ASSERT( ( Handle != INVALID_HANDLE_VALUE ), "QMXStdLib", "FileSystem::ReadSymlink", "0000000B", Target );\
                                        GetFinalPathNameByHandle( Handle, Buffer, MAX_BUFFER_SIZE, FILE_NAME_NORMALIZED );\
                                        Result = Buffer;\
                                        Result = Result.string().substr( 4 );
#	define FSCL_CREATE_BUFFERS           char SourceBuffer[ MAX_BUFFER_SIZE ];\
                                        char LinkBuffer[ MAX_BUFFER_SIZE ];
#	define FSCL_FILL_BUFFERS             strcpy( SourceBuffer, Source.string().c_str() );\
                                        strcpy( LinkBuffer, Link.string().c_str() );
#	define FSCL_CREATE_HARDLINK          WasSuccessful = CreateHardLink( LinkBuffer, SourceBuffer, nullptr )
#	define FSCL_CREATE_DIRECTORY_SYMLINK WasSuccessful = CreateSymbolicLink( LinkBuffer, SourceBuffer, SYMBOLIC_LINK_FLAG_DIRECTORY )
#	define FSCL_CREATE_SYMLINK           WasSuccessful = CreateSymbolicLink( LinkBuffer, SourceBuffer, SYMBOLIC_LINK_FLAG_FILE )
#endif // Platform dependent macros.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'FileSystem' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	SkipIfExists,
	FailIfExists,
	OverwriteIfExists
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Prototypes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This function parses the specified path to expand any embedded symbols.
  *
  * The default delimiters for embedded symbols are angled brackets (e.g. "<HOME>/projects/<PROJECT_NAME>"); though, they can be configured to something else.
  * All functions/methods in QMXStdLib making use of paths will assume they have already been parsed.
  *
  * @param Target
  * 	This is the path to be parsed.
  *
  * @exception QMXException
  * 	If a malformed symbol was found in the path.<br>
  * 	If a non-existent symbol was found in the path.
  */

void Parse( Path& Target );

/**
  * @brief This function converts the specified path into a canonical path (i.e. an absolute path with no symlinks, '.', or '..' elements ).
  *
  * @param Target
  * 	This is the path to be converted.
  *
  * @param Base
  * 	This is the base path to use when converting.  If empty, the current working directory will be used.
  *
  * @return
  * 	The converted path, or an empty path if conversion failed.
  *
  * @exception QMXException
  * 	If the specified path could not be converted into a canonical path.
  */

Path MakeCanonical( const Path& Target, const Path& Base = "" );

/**
  * @brief This function retrieves the contents of a symlink at the specified path.
  *
  * @param Target
  * 	This is the path from which to retrieve the symlink contents.
  *
  * @return
  * 	The retrieved symlink contents.
  *
  * @exception QMXException
  * 	If the specified path's symlink contents could not be retrieved.
  */

Path ReadSymlink( const Path& Target );

/**
  * @brief This function creates a hardlink/symlink at the specified destination path from the specified source path.
  *
  * @param Source
  * 	This is the path from which to create the link.
  *
  * @param Link
  * 	This is the path where the link will be created.
  *
  * @param IsHardlink
  * 	This is the boolean flag which determines if the link is a hardlink or symlink.
  *
  * @exception QMXException
  * 	If the specified hardlink could not be created due to an invalid source target.<br>
  * 	If the specified hardlink/symlink could not be created using the specified arguments.
  */

void CreateLink( const Path& Source, const Path& Link, bool IsHardlink = false );

/**
  * @brief This function copies the specified source path to the specified destination path with optional recursion and overwriting.
  *
  * @param Source
  * 	This is the path from which to copy.
  *
  * @param Destination
  * 	This is the path to which to copy.
  *
  * @param IsRecursive
  * 	This is the boolean flag which determines if the copying will be recursive.
  *
  * @param TargetCopyOption
  * 	This value determines what actions to take if a target already exists during copying.
  *
  * @exception QMXException
  * 	If the copy operation could not be performed due to an invalid source target.<br>
  * 	If the copy operation could not be completed.
  */

void Copy( const Path& Source, const Path& Destination, bool IsRecursive = true, CopyOption TargetCopyOption = SkipIfExists );

/**
  * @brief This function runs the specified console command.
  *
  * @param Command
  * 	This is the console command to run; if null, this function will instead test for the presence of a console command processor.
  *
  * @param SuccessValue
  * 	This is the return value of the console command processor which indicates success.
  *
  * @return
  * 	A boolean value of 'true' if the console command was succesful, and 'false' otherwise; if testing for the presence of a console command processor, a
  * 	boolean value of 'true' if one is present, and 'false' otherwise.
  */

bool RunCommand( const char* Command = nullptr, int SuccessValue = Null );

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

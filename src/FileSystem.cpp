////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FileSystem.cpp
// Robert M. Baker | Created : 17DEC14 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.3.0
// This is a source file for 'QMXStdLib'; it defines the implementation for a set of file system functions.
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
  * @date    Created : 17DEC14
  * @date    Last Modified : 29AUG19 by Robert M. Baker
  * @version 2.3.0
  *
  * @brief This source file defines the implementation for a set of file system functions.
  *
  * @section FileSystemS0000 Description
  *
  * This source file defines the implementation for a set of file system functions.
  *
  * @section FileSystemS0001 License
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../include/FileSystem.hpp"

using namespace std;

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
// Function Definitions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void parse( Path& target )
{
	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "FileSystem::parse", 0000 );

	// Create local variables.

		bool isDone = false;
		size_t startIndex = UNSET;
		size_t endIndex = UNSET;
		char* expandedSymbol = nullptr;
		string parsedPath = target.string();

	// Parse the specified path and expand any embedded symbols.

		do
		{
			startIndex = parsedPath.find( FILESYSTEM_SYMBOL_DELIMITER_LEFT, 0 );

			if( startIndex != string::npos )
			{
				endIndex = parsedPath.find( FILESYSTEM_SYMBOL_DELIMITER_RIGHT, 0 );
				QMX_ASSERT( ( ( endIndex != string::npos ) && ( endIndex > startIndex ) ), "QMXStdLib", "FileSystem::parse", "00000008", target );
				expandedSymbol = getenv( parsedPath.substr( ( startIndex + 1 ), ( endIndex - startIndex - 1 ) ).c_str() );
				QMX_ASSERT( expandedSymbol, "QMXStdLib", "FileSystem::parse", "00000009", target );
				String::findReplace( parsedPath, parsedPath.substr( startIndex, ( endIndex - startIndex + 1 ) ), expandedSymbol, true );
			}
			else if( parsedPath.find( FILESYSTEM_SYMBOL_DELIMITER_RIGHT, 0 ) != string::npos )
				QMX_THROW( "QMXStdLib", "FileSystem::parse", "00000008", target );
			else
				isDone = true;
		} while( !isDone );

		target = parsedPath;
}

Path makeCanonical( const Path& source, const Path& base )
{
	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "FileSystem::makeCanonical", 0000 );

	// Create local variables.

		Path result;

	// Convert specified path into a canonical path.

		try
		{
			FSMC_MAKE_CANONICAL;
		}
		catch( const boost::filesystem::filesystem_error& except )
		{
			QMX_THROW( "QMXStdLib", "FileSystem::makeCanonical", "0000000A", source << ", " << base );
		}

	// Return result to calling routine.

		return result;
}

Path readSymlink( const Path& source )
{
	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "FileSystem::readSymlink", 0000 );

	// Create local variables.

		Path result;

	// Retrieve the contents of the symlink at the specified path.

		try
		{
			FSRS_READ_SYMLINK;
		}
		catch( const boost::filesystem::filesystem_error& except )
		{
			QMX_THROW( "QMXStdLib", "FileSystem::readSymlink", "0000000B", source );
		}

	// Return result to calling routine.

		return result;
}

void createLink( const Path& source, const Path& link, bool isHardlink )
{
	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "FileSystem::createLink", 0000 );

	// Create local variables.

		bool wasSuccessful = true;
		FSCL_CREATE_BUFFERS;

	// Create a hardlink/symlink at the specified destination path from the specified source path.

		try
		{
			FSCL_FILL_BUFFERS;

			if( isHardlink && boost::filesystem::is_regular_file( source ) )
				FSCL_CREATE_HARDLINK;
			else if( !isHardlink && boost::filesystem::is_directory( source ) )
				FSCL_CREATE_DIRECTORY_SYMLINK;
			else if( !isHardlink )
				FSCL_CREATE_SYMLINK;
			else
				QMX_THROW( "QMXStdLib", "FileSystem::createLink", "0000000C", source << ", " << link << ", " << boolalpha << isHardlink );

			QMX_ASSERT( wasSuccessful, "QMXStdLib", "FileSystem::createLink", "0000000D", source << ", " << link << ", " << boolalpha << isHardlink );
		}
		catch( const boost::filesystem::filesystem_error& except )
		{
			QMX_THROW( "QMXStdLib", "FileSystem::createLink", "0000000D", source << ", " << link << ", " << boolalpha << isHardlink );
		}
}

void copy( const Path& source, const Path& destination, bool isRecursive, CopyOption targetCopyOption )
{
	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "FileSystem::copy", 0000 );

	// Create local variables.

		boost::filesystem::file_status status;
		Path recursionSource;
		Path recursionDestination;

	// Copy the specified source path to the specified destination path with optional recursion and overwriting.

		try
		{
			status = boost::filesystem::symlink_status( source );

			if( boost::filesystem::is_directory( status ) )
			{
				if( !boost::filesystem::exists( destination ) )
					boost::filesystem::copy_directory( source, destination );
				else if( targetCopyOption == FAIL_IF_EXISTS )
					QMX_THROW(
						"QMXStdLib",
						"FileSystem::copy",
						"0000000F",
						source << ", " << destination << ", " << boolalpha << isRecursive << ", " << targetCopyOption
					);

				if( isRecursive )
				{
					for( DirectoryIterator index( source ); index != DIRECTORY_END; index++ )
					{
						recursionSource = index->path();
						recursionDestination = destination.string() + '/' + index->path().filename().string();
						copy( recursionSource, recursionDestination, true, targetCopyOption );
					}
				}
			}
			else
			{
				switch( targetCopyOption )
				{
					case SKIP_IF_EXISTS:
					{
						if( !boost::filesystem::exists( destination ) )
							boost::filesystem::copy( source, destination );

						break;
					}

					case FAIL_IF_EXISTS:
					{
						boost::filesystem::copy( source, destination );

						break;
					}

					case OVERWRITE_IF_EXISTS:
					{
						if( boost::filesystem::is_regular_file( status ) )
							boost::filesystem::copy_file( source, destination, boost::filesystem::copy_option::overwrite_if_exists );
						else if( boost::filesystem::is_symlink( status ) )
						{
							if( boost::filesystem::exists( destination ) )
								boost::filesystem::remove( destination );

							boost::filesystem::copy_symlink( source, destination );
						}
						else
							QMX_THROW(
								"QMXStdLib",
								"FileSystem::copy",
								"0000000E",
								source << ", " << destination << ", " << boolalpha << isRecursive << ", " << targetCopyOption
							);

						break;
					}
				}
			}
		}
		catch( const boost::filesystem::filesystem_error& except )
		{
			QMX_THROW(
				"QMXStdLib",
				"FileSystem::Copy",
				"0000000F",
				source << ", " << destination << ", " << boolalpha << isRecursive << ", " << targetCopyOption );
		}
}

bool runCommand( const char* command, int successValue )
{
	// Return result of running specified console command to calling routine.

		return( command ? ( system( command ) == successValue ) : static_cast< bool >( system( command ) ) );
}

} // 'FileSystem' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'FileSystem' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'FileSystem.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

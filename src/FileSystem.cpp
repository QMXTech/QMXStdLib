////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FileSystem.cpp
// Robert M. Baker | Created : 17DEC14 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.2
// This is a source file for 'QMXStdLib'; it defines the implementation for a set of file system functions.
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
  * @date    Created : 17DEC14
  * @date    Last Modified : 27FEB16 by Robert M. Baker
  * @version 1.1.2
  *
  * @brief This source file defines the implementation for a set of file system functions.
  *
  * @section Description
  *
  * This source file defines the implementation for a set of file system functions.
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

void Parse( Path& Target )
{
	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "FileSystem::Parse", 0000 );

	// Create local variables.

		bool IsDone = false;
		size_t StartIndex = Null;
		size_t EndIndex = Null;
		char* ExpandedSymbol = nullptr;
		string ParsedPath = Target.string();

	// Parse the specified path and expand any embedded symbols.

		do
		{
			StartIndex = ParsedPath.find( FILESYSTEM_SYMBOL_DELIMITER_LEFT, 0 );

			if( StartIndex != string::npos )
			{
				EndIndex = ParsedPath.find( FILESYSTEM_SYMBOL_DELIMITER_RIGHT, 0 );
				QMX_ASSERT( ( ( EndIndex != string::npos ) && ( EndIndex > StartIndex ) ), "QMXStdLib", "FileSystem::Parse", "00000008", Target );
				ExpandedSymbol = getenv( ParsedPath.substr( ( StartIndex + 1 ), ( EndIndex - StartIndex - 1 ) ).c_str() );
				QMX_ASSERT( ExpandedSymbol, "QMXStdLib", "FileSystem::Parse", "00000009", Target );
				String::FindReplace( ParsedPath, ParsedPath.substr( StartIndex, ( EndIndex - StartIndex + 1 ) ), ExpandedSymbol, true );
			}
			else if( ParsedPath.find( FILESYSTEM_SYMBOL_DELIMITER_RIGHT, 0 ) != string::npos )
				QMX_THROW( "QMXStdLib", "FileSystem::Parse", "00000008", Target );
			else
				IsDone = true;
		} while( !IsDone );

		Target = ParsedPath;
}

Path MakeCanonical( const Path& Target, const Path& Base )
{
	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "FileSystem::MakeCanonical", 0000 );

	// Create local variables.

		Path Result;

	// Convert specified path into a canonical path.

		try
		{
			FSMC_MAKE_CANONICAL;
		}
		catch( const boost::filesystem::filesystem_error& TargetException )
		{
			QMX_THROW( "QMXStdLib", "FileSystem::MakeCanonical", "0000000A", Target << ", " << Base );
		}

	// Return result to calling routine.

		return Result;
}

Path ReadSymlink( const Path& Target )
{
	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "FileSystem::ReadSymlink", 0000 );

	// Create local variables.

		Path Result;

	// Retrieve the contents of the symlink at the specified path.

		try
		{
			FSRS_READ_SYMLINK;
		}
		catch( const boost::filesystem::filesystem_error& TargetException )
		{
			QMX_THROW( "QMXStdLib", "FileSystem::ReadSymlink", "0000000B", Target );
		}

	// Return result to calling routine.

		return Result;
}

void CreateLink( const Path& Source, const Path& Link, bool IsHardlink )
{
	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "FileSystem::CreateLink", 0000 );

	// Create local variables.

		bool WasSuccessful = true;
		FSCL_CREATE_BUFFERS;

	// Create a hardlink/symlink at the specified destination path from the specified source path.

		try
		{
			FSCL_FILL_BUFFERS;

			if( IsHardlink && boost::filesystem::is_regular_file( Source ) )
				FSCL_CREATE_HARDLINK;
			else if( !IsHardlink && boost::filesystem::is_directory( Source ) )
				FSCL_CREATE_DIRECTORY_SYMLINK;
			else if( !IsHardlink )
				FSCL_CREATE_SYMLINK;
			else
				QMX_THROW( "QMXStdLib", "FileSystem::CreateLink", "0000000C", Source << ", " << Link << ", " << boolalpha << IsHardlink );

			QMX_ASSERT( WasSuccessful, "QMXStdLib", "FileSystem::CreateLink", "0000000D", Source << ", " << Link << ", " << boolalpha << IsHardlink );
		}
		catch( const boost::filesystem::filesystem_error& TargetException )
		{
			QMX_THROW( "QMXStdLib", "FileSystem::CreateLink", "0000000D", Source << ", " << Link << ", " << boolalpha << IsHardlink );
		}
}

void Copy( const Path& Source, const Path& Destination, bool IsRecursive, CopyOption TargetCopyOption )
{
	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "FileSystem::Copy", 0000 );

	// Create local variables.

		boost::filesystem::file_status Status;
		Path RecursionSource;
		Path RecursionDestination;

	// Copy the specified source path to the specified destination path with optional recursion and overwriting.

		try
		{
			Status = boost::filesystem::symlink_status( Source );

			if( boost::filesystem::is_directory( Status ) )
			{
				if( !boost::filesystem::exists( Destination ) )
					boost::filesystem::copy_directory( Source, Destination );
				else if( TargetCopyOption == FailIfExists )
					QMX_THROW( "QMXStdLib",
					           "FileSystem::Copy",
					           "0000000F",
					           Source << ", " << Destination << ", " << boolalpha << IsRecursive << ", " << TargetCopyOption );

				if( IsRecursive )
				{
					for( DirectoryIterator Index( Source ); Index != DIRECTORY_END; Index++ )
					{
						RecursionSource = Index->path();
						RecursionDestination = Destination.string() + '/' + Index->path().filename().string();
						Copy( RecursionSource, RecursionDestination, true, TargetCopyOption );
					}
				}
			}
			else
			{
				switch( TargetCopyOption )
				{
					case SkipIfExists:
					{
						if( !boost::filesystem::exists( Destination ) )
							boost::filesystem::copy( Source, Destination );

						break;
					}

					case FailIfExists:
					{
						boost::filesystem::copy( Source, Destination );

						break;
					}

					case OverwriteIfExists:
					{
						if( boost::filesystem::is_regular_file( Status ) )
							boost::filesystem::copy_file( Source, Destination, boost::filesystem::copy_option::overwrite_if_exists );
						else if( boost::filesystem::is_symlink( Status ) )
						{
							if( boost::filesystem::exists( Destination ) )
								boost::filesystem::remove( Destination );

							boost::filesystem::copy_symlink( Source, Destination );
						}
						else
							QMX_THROW( "QMXStdLib",
							           "FileSystem::Copy",
							           "0000000E",
							           Source << ", " << Destination << ", " << boolalpha << IsRecursive << ", " << TargetCopyOption );

						break;
					}
				}
			}
		}
		catch( const boost::filesystem::filesystem_error& TargetException )
		{
			QMX_THROW( "QMXStdLib",
			           "FileSystem::Copy",
			           "0000000F",
			           Source << ", " << Destination << ", " << boolalpha << IsRecursive << ", " << TargetCopyOption );
		}
}

bool RunCommand( const char* Command, int SuccessValue )
{
	// Return result of running specified console command to calling routine.

		return( Command ? ( system( Command ) == SuccessValue ) : static_cast< bool >( system( Command ) ) );
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

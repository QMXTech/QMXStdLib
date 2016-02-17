////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ProgramOptions.cpp
// Robert M. Baker | Created : 23OCT13 | Last Modified : 16FEB16 by Robert M. Baker
// Version : 1.0.0
// This is a source file for 'QMXStdLib'; it defines the implementation for a program options class.
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
  * @date    Created : 23OCT13
  * @date    Last Modified : 16FEB16 by Robert M. Baker
  * @version 1.0.0
  *
  * @brief This source file defines the implementation for a program options class.
  *
  * @section Description
  *
  * This source file defines the implementation for a program options class.
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

#include <ProgramOptions.hpp>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Field Initializers for the 'ProgramOptions' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<> ProgramOptions* Singleton< ProgramOptions >::SingletonInstance = nullptr;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Methods for the 'ProgramOptions' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ProgramOptions::~ProgramOptions()
{
	// Perform necessary cleanup.

		if( Initialized )
			Deallocate();
}

void ProgramOptions::ParseCommandLine( int ArgumentCount, char* ArgumentValues[] )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create local variables.

		string Target;
		string Key;
		string Value;

	// Parse specified command line arguments.

		for( int Index = 0; Index < ArgumentCount; Index++ )
		{
			Target = ArgumentValues[ Index ];

			if( Target.rfind( '-' ) == 0 )
			{
				for( size_t Position = 1; Position < Target.length(); Position++ )
					ToggleOptions.insert( Target.substr( Position, 1 ) );
			}
			else if( Target.substr( 0, 2 ) == "--" )
			{
				if( Target.find( '=' ) == string::npos )
					CommandOptions.insert( Target.substr( 2 ) );
				else
				{
					Key = Target.substr( 2, ( Target.find( '=' ) - 2 ) );
					Value = Target.substr( ( Target.find( '=' ) + 1 ) );
					ConfigOptions[ Key ] = Value;
				}
			}
			else
				PositionalOptions.push_back( Target );
		}
}

void ProgramOptions::ParseConfigFile( const Path& ConfigPath )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ProgramOptions::ParseConfigFile", 0000 );

	// Create local variables.

		ifstream ConfigFile( ConfigPath.string().c_str() );
		char Buffer[ MAX_BUFFER_SIZE ];
		string Line;
		string Key;
		string Value;
		size_t StartPosition = 0;
		size_t EndPosition = 0;

	// Parse specified config file, if it exists.

		QMX_ASSERT( ConfigFile, "QMXStdLib", "ProgramOptions::ParseConfigFile", "00000020", ConfigPath );
		ConfigFile.getline( Buffer, MAX_BUFFER_SIZE );

		while( ConfigFile.good() )
		{
			Line = Buffer;

			if( ( Line[ Line.find_first_not_of( WHITE_SPACE_CHARS ) ] != '#' ) && ( Line.find( '=' ) != string::npos ) )
			{
				Key = Line.substr( 0, Line.find( '=' ) );
				StartPosition = Key.find_first_not_of( WHITE_SPACE_CHARS );
				EndPosition = Key.find_last_not_of( WHITE_SPACE_CHARS );
				Key = Key.substr( StartPosition, ( EndPosition - StartPosition + 1 ) );
				Value = Line.substr( ( Line.find( '=' ) + 1 ) );
				StartPosition = Value.find_first_not_of( WHITE_SPACE_CHARS );
				EndPosition = Value.find_last_not_of( WHITE_SPACE_CHARS );
				Value = Value.substr( StartPosition, ( EndPosition - StartPosition + 1 ) );
				ConfigOptions[ Key ] = Value;
			}

			ConfigFile.getline( Buffer, MAX_BUFFER_SIZE );
		}
}

bool ProgramOptions::IsToggleOptionPresent( const string& TargetOption )
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Report whether or not specified toggle option is present to calling routine.

		return( ToggleOptions.count( TargetOption ) != 0 );
}

bool ProgramOptions::IsCommandOptionPresent( const string& TargetOption )
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Report whether or not specified command option is present to calling routine.

		return( CommandOptions.count( TargetOption ) != 0 );
}

string ProgramOptions::GetConfigOption( const string& TargetOption )
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Create local variables.

		auto StringMapIterator = ConfigOptions.find( TargetOption );

	// Report either specified config option value or an empty string to calling routine.

		return( ( StringMapIterator != ConfigOptions.end() ) ? StringMapIterator->second : "" );
}

string ProgramOptions::GetPositionalOption( size_t TargetIndex )
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Report either specified positional option value or an empty string to calling routine.

		return( ( TargetIndex < PositionalOptions.size() ) ? PositionalOptions[ TargetIndex ] : "" );
}

ProgramOptions::PointerType ProgramOptions::Create()
{
	// Create local variables.

		PointerType Result( new ProgramOptions() );

	// Initialize new instance.

		Result->Allocate();

	// Return result to calling routine.

		return Result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods for the 'ProgramOptions' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ProgramOptions::ProgramOptions()
{
	// Do nothing.
}

void ProgramOptions::DeallocateImp()
{
	// Perform necessary cleanup.

		if( !ToggleOptions.empty() )
			ToggleOptions.clear();

		if( !CommandOptions.empty() )
			CommandOptions.clear();

		if( !ConfigOptions.empty() )
			ConfigOptions.clear();

		if( !PositionalOptions.empty() )
			PositionalOptions.clear();
}

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ProgramOptions.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

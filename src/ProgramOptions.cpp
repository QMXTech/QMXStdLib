////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ProgramOptions.cpp
// Robert M. Baker | Created : 23OCT13 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.0
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
  * @date    Last Modified : 27FEB16 by Robert M. Baker
  * @version 1.1.0
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

#include "../include/ProgramOptions.hpp"

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
		string Value;
		string Key;
		string Group;
		size_t Position = Null;

	// Parse specified command line arguments.

		for( int Index = 0; Index < ArgumentCount; Index++ )
		{
			Target = ArgumentValues[ Index ];

			if( Target.rfind( PROGRAMOPTIONS_TOGGLE_OPTION_PREFIX ) == 0 )
			{
				Target = Target.substr( 1 );
				STRIP_ALL_WHITESPACE( Target );

				if( Target.length() )
				{
					for( size_t Position = 0; Position < Target.length(); Position++ )
						ToggleOptions.insert( Target.substr( Position, 1 ) );
				}
			}
			else if( Target.substr( 0, 2 ) == PROGRAMOPTIONS_COMMAND_OPTION_PREFIX )
			{
				Target = Target.substr( 2 );
				Position = Target.find( PROGRAMOPTIONS_ASSIGNMENT_OPERATOR );

				if( Position == string::npos )
				{
					STRIP_ALL_WHITESPACE( Target );

					if( Target.length() )
						CommandOptions.insert( Target );
				}
				else if( ( Position > 0 ) && ( Position < ( Target.length() - 1 ) ) )
				{
					Value = Target.substr( ( Position + 1 ) );
					Key = Target.substr( 0, Position );
					Group = ExtractGroup( Key );

					if( Key.length() )
						ConfigOptions[ Group ][ Key ] = Value;
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
		string Value;
		string Key;
		string Group = PROGRAMOPTIONS_GROUP_DEFAULT;
		size_t Position = Null;

	// Parse specified config file, if it exists.

		QMX_ASSERT( ConfigFile, "QMXStdLib", "ProgramOptions::ParseConfigFile", "00000020", ConfigPath );
		ConfigFile.getline( Buffer, MAX_BUFFER_SIZE );

		while( ConfigFile.good() )
		{
			Line = Buffer;
			STRIP_ALL_WHITESPACE( Line );

			if( ( Line[ 0 ] != PROGRAMOPTIONS_COMMENT_INITIATOR ) && ( Line.length() >= 3 ) )
			{
				Position = Line.find( PROGRAMOPTIONS_ASSIGNMENT_OPERATOR );
				
				if( ( Line[ 0 ] == PROGRAMOPTIONS_GROUP_DELIMITER_LEFT ) && ( Line[ Line.length() - 1 ] == PROGRAMOPTIONS_GROUP_DELIMITER_RIGHT ) )
					Group = Line.substr( 1, ( Line.length() - 2 ) );
				else if( ( Position != string::npos ) && ( Position > 0 ) && ( Position < ( Line.length() - 1 ) ) )
				{
					Key = Line.substr( 0, Position );
					Value = Line.substr( ( Position + 1 ) );
					ConfigOptions[ Group ][ Key ] = Value;
				}
			}

			ConfigFile.getline( Buffer, MAX_BUFFER_SIZE );
		}
}

void ProgramOptions::SaveConfigFile( const Path& ConfigPath ) const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ProgramOptions::SaveConfigFile", 0000 );

	// Create local variables.

		ofstream ConfigFile( ConfigPath.string().c_str() );
		map< string, map< string, string > > SortedOptions;

	// Save current config options to specified file.

		QMX_ASSERT( ConfigFile, "QMXStdLib", "ProgramOptions::SaveConfigFile", "00000021", ConfigPath );
		ConfigFile << PROGRAMOPTIONS_COMMENT_INITIATOR << ' ' << ConfigPath.filename().string() << "\n\n";

		for( const auto& IndexA : ConfigOptions )
		{
			for( const auto& IndexB : IndexA.second )
				SortedOptions[ IndexA.first ][ IndexB.first ] = IndexB.second;
		}

		for( const auto& IndexA : SortedOptions )
		{
			ConfigFile << PROGRAMOPTIONS_GROUP_DELIMITER_LEFT << IndexA.first << PROGRAMOPTIONS_GROUP_DELIMITER_RIGHT << '\n';

			for( const auto& IndexB : IndexA.second )
				ConfigFile << IndexB.first << ' ' << PROGRAMOPTIONS_ASSIGNMENT_OPERATOR << ' ' << IndexB.second << '\n';

			ConfigFile << '\n';
		}
}

bool ProgramOptions::IsToggleOptionPresent( const string& TargetOption ) const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Report whether or not specified toggle option is present to calling routine.

		return( ToggleOptions.count( TargetOption ) != 0 );
}

bool ProgramOptions::IsCommandOptionPresent( const string& TargetOption ) const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Report whether or not specified command option is present to calling routine.

		return( CommandOptions.count( TargetOption ) != 0 );
}

string ProgramOptions::GetConfigOption( const string& TargetOption ) const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Create local variables.

		string Result;
		string Key = TargetOption;
		string Group = ExtractGroup( Key );
		ConfigMap::const_iterator ConfigMapIterator;
		StringMap::const_iterator StringMapIterator;

	// Get specified config option value, with optional group, if it exists.

		if( Key.length() )
		{
			ConfigMapIterator = ConfigOptions.find( Group );

			if( ConfigMapIterator != ConfigOptions.end() )
			{
				StringMapIterator = ConfigMapIterator->second.find( Key );

				if( StringMapIterator != ConfigMapIterator->second.end() )
					Result = StringMapIterator->second;
			}
		}

	// Return result to calling routine.

		return Result;
}

void ProgramOptions::SetConfigOption( const string& TargetOption, const string& TargetValue, const bool DoCreate )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create local variables.

		string Key = TargetOption;
		string Group = ExtractGroup( Key );
		ConfigMap::iterator ConfigMapIterator;
		StringMap::iterator StringMapIterator;

	// Set specified config option value, with optional group, if it exists.

		if( Key.length() )
		{
			if( DoCreate )
				ConfigOptions[ Group ][ Key ] = TargetValue;
			else
			{
				ConfigMapIterator = ConfigOptions.find( Group );

				if( ConfigMapIterator != ConfigOptions.end() )
				{
					StringMapIterator = ConfigMapIterator->second.find( Key );

					if( StringMapIterator != ConfigMapIterator->second.end() )
						StringMapIterator->second = TargetValue;
				}
			}
		}
}

void ProgramOptions::RemoveConfigOption( const string& TargetOption )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create local variables.

		string Key = TargetOption;
		string Group = ExtractGroup( Key );
		ConfigMap::iterator ConfigMapIterator;
		StringMap::iterator StringMapIterator;

	// Remove specified config option, with optional group, if it exists.

		if( Key.length() )
		{
			ConfigMapIterator = ConfigOptions.find( Group );

			if( ConfigMapIterator != ConfigOptions.end() )
			{
				StringMapIterator = ConfigMapIterator->second.find( Key );

				if( StringMapIterator != ConfigMapIterator->second.end() )
				{
					ConfigMapIterator->second.erase( StringMapIterator );

					if( ConfigMapIterator->second.empty() )
						ConfigOptions.erase( ConfigMapIterator );
				}
			}
		}
}

string ProgramOptions::GetPositionalOption( size_t TargetIndex ) const
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

string ProgramOptions::ExtractGroup( string& Target ) const
{
	// Create local variables.

		string Result = PROGRAMOPTIONS_GROUP_DEFAULT;
		size_t Position = Null;

	// Extract embedded group ID from specified string, if there is one.

		STRIP_ALL_WHITESPACE( Target );

		if( Target.length() )
		{
			Position = Target.find( PROGRAMOPTIONS_GROUP_KEY_SEPERATOR );

			if( ( Position != string::npos ) && ( Position > 0 ) && ( Position < ( Target.length() - 1 ) ) )
			{
				Result = Target.substr( 0, Position );
				Target = Target.substr( ( Position + 1 ) );
			}
		}

	// Return result to calling routine.

		return Result;
}

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ProgramOptions.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

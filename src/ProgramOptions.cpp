////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ProgramOptions.cpp
// Robert M. Baker | Created : 23OCT13 | Last Modified : 03SEP19 by Robert M. Baker
// Version : 2.1.1
// This is a source file for 'QMXStdLib'; it defines the implementation for a program options class.
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
  * @date    Created : 23OCT13
  * @date    Last Modified : 03SEP19 by Robert M. Baker
  * @version 2.1.1
  *
  * @brief This source file defines the implementation for a program options class.
  *
  * @section ProgramOptionsS0000 Description
  *
  * This source file defines the implementation for a program options class.
  *
  * @section ProgramOptionsS0001 License
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

#include "../include/ProgramOptions.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Methods for the 'ProgramOptions' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ProgramOptions::~ProgramOptions()
{
	try
	{
		// Perform necessary cleanup.

			if( initialized )
				deallocate();
	}
	catch( const exception& except )
	{
		// Do nothing.
	}
}

void ProgramOptions::parseCommandLine( int argumentCount, char* argumentValues[] )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create local variables.

		string target;
		string value;
		string key;
		string group;
		size_t position = UNSET;

	// Parse specified command line arguments.

		for( int index = 0; index < argumentCount; index++ )
		{
			target = argumentValues[ index ];

			if( target.rfind( PROGRAMOPTIONS_TOGGLE_OPTION_PREFIX ) == 0 )
			{
				target = target.substr( 1 );
				STRIP_ALL_WHITESPACE( target );

				if( target.length() )
				{
					for( size_t position = 0; position < target.length(); position++ )
						toggleOptions.insert( target.substr( position, 1 ) );
				}
			}
			else if( target.substr( 0, 2 ) == PROGRAMOPTIONS_COMMAND_OPTION_PREFIX )
			{
				target = target.substr( 2 );
				position = target.find( PROGRAMOPTIONS_ASSIGNMENT_OPERATOR );

				if( position == string::npos )
				{
					STRIP_ALL_WHITESPACE( target );

					if( target.length() )
						commandOptions.insert( target );
				}
				else if( ( position > 0 ) && ( position < ( target.length() - 1 ) ) )
				{
					value = target.substr( ( position + 1 ) );
					key = target.substr( 0, position );
					group = extractGroup( key );

					if( key.length() )
						configOptions[ group ][ key ] = value;
				}
			}
			else
				positionalOptions.push_back( target );
		}
}

void ProgramOptions::parseConfigFile( const Path& configPath )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ProgramOptions::parseConfigFile", 0000 );

	// Create local variables.

		ifstream configFile( configPath.string().c_str() );
		char buffer[ MAX_BUFFER_SIZE ];
		string line;
		string value;
		string key;
		string group = PROGRAMOPTIONS_GROUP_DEFAULT;
		size_t position = UNSET;

	// Parse specified config file, if it exists.

		QMX_ASSERT( configFile, "QMXStdLib", "ProgramOptions::parseConfigFile", "00000011", configPath );
		configFile.getline( buffer, MAX_BUFFER_SIZE );

		while( configFile.good() )
		{
			line = buffer;
			STRIP_ALL_WHITESPACE( line );

			if( ( line[ 0 ] != PROGRAMOPTIONS_COMMENT_INITIATOR ) && ( line.length() >= 3 ) )
			{
				position = line.find( PROGRAMOPTIONS_ASSIGNMENT_OPERATOR );

				if( ( line[ 0 ] == PROGRAMOPTIONS_GROUP_DELIMITER_LEFT ) && ( line[ line.length() - 1 ] == PROGRAMOPTIONS_GROUP_DELIMITER_RIGHT ) )
					group = line.substr( 1, ( line.length() - 2 ) );
				else if( ( position != string::npos ) && ( position > 0 ) && ( position < ( line.length() - 1 ) ) )
				{
					key = line.substr( 0, position );
					value = line.substr( ( position + 1 ) );
					configOptions[ group ][ key ] = value;
				}
			}

			configFile.getline( buffer, MAX_BUFFER_SIZE );
		}
}

void ProgramOptions::saveConfigFile( const Path& configPath ) const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "ProgramOptions::saveConfigFile", 0000 );

	// Create local variables.

		ofstream configFile( configPath.string().c_str() );
		map< string, map< string, string > > sortedOptions;

	// Save current config options to specified file.

		QMX_ASSERT( configFile, "QMXStdLib", "ProgramOptions::saveConfigFile", "00000012", configPath );
		configFile << PROGRAMOPTIONS_COMMENT_INITIATOR << ' ' << configPath.filename().string() << "\n\n";

		for( const auto& indexA : configOptions )
		{
			for( const auto& indexB : indexA.second )
				sortedOptions[ indexA.first ][ indexB.first ] = indexB.second;
		}

		for( const auto& indexA : sortedOptions )
		{
			configFile << PROGRAMOPTIONS_GROUP_DELIMITER_LEFT << indexA.first << PROGRAMOPTIONS_GROUP_DELIMITER_RIGHT << '\n';

			for( const auto& indexB : indexA.second )
				configFile << indexB.first << ' ' << PROGRAMOPTIONS_ASSIGNMENT_OPERATOR << ' ' << indexB.second << '\n';

			configFile << '\n';
		}
}

bool ProgramOptions::isToggleOptionPresent( const string& targetOption ) const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Report whether or not specified toggle option is present to calling routine.

		return( toggleOptions.count( targetOption ) != 0 );
}

bool ProgramOptions::isCommandOptionPresent( const string& targetOption ) const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Report whether or not specified command option is present to calling routine.

		return( commandOptions.count( targetOption ) != 0 );
}

string ProgramOptions::getConfigOption( const string& targetOption ) const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Create local variables.

		string result;
		string key = targetOption;
		string group = extractGroup( key );
		ConfigMap::const_iterator configMapIterator;
		StringMap::const_iterator stringMapIterator;

	// Get specified config option value, with optional group, if it exists.

		if( key.length() )
		{
			configMapIterator = configOptions.find( group );

			if( configMapIterator != configOptions.end() )
			{
				stringMapIterator = configMapIterator->second.find( key );

				if( stringMapIterator != configMapIterator->second.end() )
					result = stringMapIterator->second;
			}
		}

	// Return result to calling routine.

		return result;
}

const ProgramOptions::ConfigMap& ProgramOptions::getConfigOptions() const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Return non-mutable reference to underlying config map to calling routine.

		return configOptions;
}

void ProgramOptions::setConfigOption( const string& targetOption, const string& newValue, const bool doCreate )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create local variables.

		string key = targetOption;
		string group = extractGroup( key );
		ConfigMap::iterator configMapIterator;
		StringMap::iterator stringMapIterator;

	// Set specified config option value, with optional group, if it exists.

		if( key.length() )
		{
			if( doCreate )
				configOptions[ group ][ key ] = newValue;
			else
			{
				configMapIterator = configOptions.find( group );

				if( configMapIterator != configOptions.end() )
				{
					stringMapIterator = configMapIterator->second.find( key );

					if( stringMapIterator != configMapIterator->second.end() )
						stringMapIterator->second = newValue;
				}
			}
		}
}

void ProgramOptions::setConfigOptions( const ConfigMap& targetOptions )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Set underlying config map to specified config map.

		configOptions = targetOptions;
}

void ProgramOptions::removeConfigOption( const string& targetOption )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create local variables.

		string key = targetOption;
		string group = extractGroup( key );
		ConfigMap::iterator configMapIterator;
		StringMap::iterator stringMapIterator;

	// Remove specified config option, with optional group, if it exists.

		if( key.length() )
		{
			configMapIterator = configOptions.find( group );

			if( configMapIterator != configOptions.end() )
			{
				stringMapIterator = configMapIterator->second.find( key );

				if( stringMapIterator != configMapIterator->second.end() )
				{
					configMapIterator->second.erase( stringMapIterator );

					if( configMapIterator->second.empty() )
						configOptions.erase( configMapIterator );
				}
			}
		}
}

string ProgramOptions::getPositionalOption( size_t targetIndex ) const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Report either specified positional option value or an empty string to calling routine.

		return( ( targetIndex < positionalOptions.size() ) ? positionalOptions[ targetIndex ] : "" );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods for the 'ProgramOptions' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ProgramOptions::ProgramOptions()
{
	// Do nothing.
}

void ProgramOptions::deallocateImp()
{
	// Perform necessary cleanup.

		if( !toggleOptions.empty() )
			toggleOptions.clear();

		if( !commandOptions.empty() )
			commandOptions.clear();

		if( !configOptions.empty() )
			configOptions.clear();

		if( !positionalOptions.empty() )
			positionalOptions.clear();
}

string ProgramOptions::extractGroup( string& target ) const
{
	// Create local variables.

		string result = PROGRAMOPTIONS_GROUP_DEFAULT;
		size_t position = UNSET;

	// Extract embedded group ID from specified string, if there is one.

		STRIP_ALL_WHITESPACE( target );

		if( target.length() )
		{
			position = target.find( PROGRAMOPTIONS_GROUP_KEY_SEPARATOR );

			if( ( position != string::npos ) && ( position > 0 ) && ( position < ( target.length() - 1 ) ) )
			{
				result = target.substr( 0, position );
				target = target.substr( ( position + 1 ) );
			}
		}

	// Return result to calling routine.

		return result;
}

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ProgramOptions.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

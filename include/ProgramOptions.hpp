////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ProgramOptions.hpp
// Robert M. Baker | Created : 23OCT13 | Last Modified : 28FEB16 by Robert M. Baker
// Version : 1.1.2
// This is a header file for 'QMXStdLib'; it defines the interface for a program options class.
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

// TODO (Robert M. Baker - Priority 50): Modify all '*ConfigOption' methods to use a separate parameter for group ID.

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 23OCT13
  * @date    Last Modified : 28FEB16 by Robert M. Baker
  * @version 1.1.2
  *
  * @brief This header file defines the interface for a program options class.
  *
  * @section Description
  *
  * This header file defines the interface for a program options class.
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

#ifndef __QMX_QMXSTDLIB_PROGRAMOPTIONS_HPP_
#define __QMX_QMXSTDLIB_PROGRAMOPTIONS_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "Object.hpp"
#include "FileSystem.hpp"
#include "Mixins/Singleton.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define PROGRAM_OPTIONS   QMXStdLib::ProgramOptions::GetSingleton()
#define PROGRAM_OPTIONS_P QMXStdLib::ProgramOptions::GetSingletonPointer()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'ProgramOptions' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class ProgramOptions ProgramOptions.hpp "include/ProgramOptions.hpp"
  *
  * @brief This class defines global program option algorithms.
  *
  * These algorithms are useful when it is necessary to acquire program options from various sources such as the command line or a config file and present them
  * in a globally accessible interface.
  *
  * Platform Independent	  : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe				  : Yes
  */

class ProgramOptions : public Object< ProgramOptions >, public Singleton< ProgramOptions >
{
	// Friend Classes

		friend class Object;

public:

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		virtual ~ProgramOptions();

	// Public Methods

		/**
		  * @brief This method parses the specified command line arguments.
		  *
		  * Any config options parsed may be overridden by a config file, depending on the order in which the methods are called (i.e. If a call is made to
		  * 'ParseCommandLine' and then to 'ParseConfigFile', any identical entries in the config file will override those on the command line.).
		  *
		  * Refer to the various option retrieval methods for more information on the different option types.
		  *
		  * @param ArgumentCount
		  * 	This is the number of arguments which have been passed to the application via the 'main' function.
		  *
		  * @param ArgumentValues
		  * 	This is an array containing all argument values which have been passed to the application via the 'main' function.
		  */

		void ParseCommandLine( int ArgumentCount, char* ArgumentValues[] );

		/**
		  * @brief This method parses the specified config file.
		  *
		  * The config file should be in plain text and contain key/value pairs on seperate lines (optionally divided into groups).  Before any line is processed,
		  * all whitespace characters are stripped.  Any line beginning with the configurable comment initiator, which by default is the number sign ('#'), will
		  * be ignored.  Any line containing a string enclosed in the configurable group delimiters, which by default are square brackets ('[' and ']'), will set
		  * the group for any key/value pairs that follow.  Any line containing two strings separated by the configurable assignment operator, which by default is
		  * the equal sign ('='), will become a key/value pair.  Any malformed lines will be ignored.  After the config file is parsed, any empty groups will be
		  * discarded.  Any config options parsed may be overridden by the command line, depending on the order in which the methods are called (i.e. If a call is
		  * made to 'ParseConfigFile' and then to 'ParseCommandLine', any identical entries on the command line will override those in the config file.).
		  *
		  * Refer to the 'GetConfigOption' method for more information on the config option type.
		  *
		  * @param ConfigPath
		  * 	This is the config file path to be parsed.
		  *
		  * @exception QMXException
		  * 	If the specified config file could not be opened for reading.
		  */

		void ParseConfigFile( const Path& ConfigPath );

		/**
		  * @brief This method saves the current config options to the specified file.
		  *
		  * @param ConfigPath
		  * 	This is the config file path to use when saving.
		  *
		  * @exception QMXException
		  * 	If the specified config file could not be opened for writing.
		  */

		void SaveConfigFile( const Path& ConfigPath ) const;

		/**
		  * @brief This method determines if the specified toggle option is present.
		  *
		  * A toggle option is one formed with the configurable prefix, which by default is the dash ('-'), followed by any number of characters (usually
		  * alphanumeric), and is usually meant to toggle a certain behavior.
		  *
		  * @param TargetOption
		  * 	This is the name of the toggle option whose presence is to be determined.
		  *
		  * @return
		  * 	A boolean value of 'true' if the specified toggle option is present, and 'false' otherwise.
		  */

		bool IsToggleOptionPresent( const std::string& TargetOption ) const;

		/**
		  * @brief This method determines if the specified command option is present.
		  *
		  * A command option is one formed with the configurable prefix, which by default is two dashes ('--'), followed by a string of characters (usually
		  * descriptive of its function), and is usually meant to invoke a function.
		  *
		  * @param TargetOption
		  * 	This is the name of the command option whose presence is to be determined.
		  *
		  * @return
		  * 	A boolean value of 'true' if the specified command option is present, and 'false' otherwise.
		  */

		bool IsCommandOptionPresent( const std::string& TargetOption ) const;

		/**
		  * @brief This method retrieves the value of the specified config option, with optional group, if it exists.
		  *
		  * A config option is one formed with the configurable prefix, which by default is two dashes ('--'), followed by a string of characters (usually a
		  * word), followed by the configurable assignment operator, which by default is the equal sign ('='), and then followed by another string of characters
		  * (usually a logical value for the preceding word), and is usually meant to define key/value pairs.  An optional group can be specified by placing it
		  * immediately after the prefix and then separating it from the key with the configurable group/key seperator, which by default is the period ('.').  If
		  * no group is specified, the configurable default is used, which by default is 'Global'.  Assuming all default configurable values, a full example would
		  * be '--Group.Key=Value'.
		  *
		  * @param TargetOption
		  * 	This is the name of the config option, with optional group, whose value is to be retrieved.
		  *
		  * @return
		  * 	A string containing the value of the specified config option, or an empty string if it does not exist.
		  */

		std::string GetConfigOption( const std::string& TargetOption ) const;

		/**
		  * @brief This method sets the specified config option, with optional group, to the specified value.
		  *
		  * If the specified group or key do not exist, this method will have no effect unless 'DoCreate' is set to 'true'; in which case, the group and/or the
		  * key will be created and the value assigned.
		  *
		  * @param TargetOption
		  * 	This is the name of the config option, with optional group, whose value is to be set.
		  *
		  * @param TargetValue
		  * 	This is the value to use when settings the config option.
		  *
		  * @param DoCreate
		  * 	If set to 'true' and the group and/or the key do not exist, they will first be created and then the value assigned.
		  */

		void SetConfigOption( const std::string& TargetOption, const std::string& TargetValue, const bool DoCreate = false );

		/**
		  * @brief This method removes the specified config option, with optional group, if it exists.
		  *
		  * If a removed config option is the last one in its group, the group will also be removed.
		  *
		  * @param TargetOption
		  * 	This is the name of the config option, with optional group, to be removed.
		  * 	
		  */

		void RemoveConfigOption( const std::string& TargetOption );

		/**
		  * @brief This method retrieves the positional option at the specified index, if it exists.
		  *
		  * A positional option is one which does not fit the form of any other option and whose purpose depends on its position in the argument list.
		  *
		  * @param TargetIndex
		  * 	This is the positional option index used in retrieval.
		  *
		  * @return
		  * 	A string containing the positional option at the specified index, or an empty string if it does not exist.
		  */

		std::string GetPositionalOption( size_t TargetIndex ) const;

private:

	// Private Type Definitions

		typedef std::unordered_map< std::string, StringMap > ConfigMap;

	// Private Fields

		/**
		  * @brief This is the set of strings containing all parsed toggle options.
		  */

		StringSet ToggleOptions;

		/**
		  * @brief This is the set of strings containing all parsed command options.
		  */

		StringSet CommandOptions;

		/**
		  * @brief This is the map containing all parsed config options.
		  */

		ConfigMap ConfigOptions;

		/**
		  * @brief This is the vector of strings containing all parsed positional options.
		  */

		StringVector PositionalOptions;

	// Private Constructors

		/**
		  * @brief This is the default constructor, which is made private to prevent direct instantiation.
		  */

		ProgramOptions();

	// Private Methods

		/**
		  * @brief This is the overridden implementation for the 'Deallocate' method.
		  */

		void DeallocateImp();

		/**
		  * @brief This method extracts the embedded group ID from the specified string, if there is one.
		  *
		  * @param Target
		  * 	This is string used for group ID extraction.
		  *
		  * @return
		  * 	A string containing the extracted group ID, or the default group ID if there was none.
		  */

		std::string ExtractGroup( std::string& Target ) const;
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_PROGRAMOPTIONS_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ProgramOptions.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

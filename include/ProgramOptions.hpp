////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ProgramOptions.hpp
// Robert M. Baker | Created : 23OCT13 | Last Modified : 28AUG19 by Robert M. Baker
// Version : 2.0.0
// This is a header file for 'QMXStdLib'; it defines the interface for a program options class.
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
  * @date    Last Modified : 28AUG19 by Robert M. Baker
  * @version 2.0.0
  *
  * @brief This header file defines the interface for a program options class.
  *
  * @section ProgramOptionsH0000 Description
  *
  * This header file defines the interface for a program options class.
  *
  * @section ProgramOptionsH0001 License
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

#ifndef __QMX_QMXSTDLIB_PROGRAMOPTIONS_HPP_
#define __QMX_QMXSTDLIB_PROGRAMOPTIONS_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "Object.hpp"
#include "FileSystem.hpp"
#include "Mixins/Singleton.hpp"
#include "RAII/ScopedLock.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define PROGRAM_OPTIONS   QMXStdLib::ProgramOptions::getSingleton()
#define PROGRAM_OPTIONS_P QMXStdLib::ProgramOptions::getSingletonPointer()

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

		friend class Object< ProgramOptions >;

public:

	// Public Type Definitions

		typedef std::unordered_map< std::string, StringMap > ConfigMap;

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		~ProgramOptions();

	// Public Methods

		/**
		  * @brief This method parses the specified command line arguments.
		  *
		  * Any config options parsed may be overridden by a config file, depending on the order in which the methods are called (i.e. If a call is made to
		  * 'parseCommandLine' and then to 'parseConfigFile', any identical entries in the config file will override those on the command line.).
		  *
		  * Refer to the various option retrieval methods for more information on the different option types.
		  *
		  * @param argumentCount
		  * 	This is the number of arguments which have been passed to the application via the 'main' function.
		  *
		  * @param argumentValues
		  * 	This is an array containing all argument values which have been passed to the application via the 'main' function.
		  */

		void parseCommandLine( int argumentCount, char* argumentValues[] );

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
		  * Refer to the 'getConfigOption' method for more information on the config option type.
		  *
		  * @param configPath
		  * 	This is the config file path to be parsed.
		  *
		  * @exception QMXException
		  * 	If the specified config file could not be opened for reading.
		  */

		void parseConfigFile( const Path& configPath );

		/**
		  * @brief This method saves the current config options to the specified file.
		  *
		  * @param configPath
		  * 	This is the config file path to use when saving.
		  *
		  * @exception QMXException
		  * 	If the specified config file could not be opened for writing.
		  */

		void saveConfigFile( const Path& configPath ) const;

		/**
		  * @brief This method determines if the specified toggle option is present.
		  *
		  * A toggle option is one formed with the configurable prefix, which by default is the dash ('-'), followed by any number of characters (usually
		  * alphanumeric), and is usually meant to toggle a certain behavior.
		  *
		  * @param targetOption
		  * 	This is the name of the toggle option whose presence is to be determined.
		  *
		  * @return
		  * 	A boolean value of 'true' if the specified toggle option is present, and 'false' otherwise.
		  */

		bool isToggleOptionPresent( const std::string& targetOption ) const;

		/**
		  * @brief This method determines if the specified command option is present.
		  *
		  * A command option is one formed with the configurable prefix, which by default is two dashes ('--'), followed by a string of characters (usually
		  * descriptive of its function), and is usually meant to invoke a function.
		  *
		  * @param targetOption
		  * 	This is the name of the command option whose presence is to be determined.
		  *
		  * @return
		  * 	A boolean value of 'true' if the specified command option is present, and 'false' otherwise.
		  */

		bool isCommandOptionPresent( const std::string& targetOption ) const;

		/**
		  * @brief This method retrieves the value of the specified config option, with optional group, if it exists.
		  *
		  * A config option is one formed with the configurable prefix, which by default is two dashes ('--'), followed by a string of characters (usually a
		  * word), followed by the configurable assignment operator, which by default is the equal sign ('='), and then followed by another string of characters
		  * (usually a logical value for the preceding word), and is usually meant to define key/value pairs.  An optional group can be specified by placing it
		  * immediately after the prefix and then separating it from the key with the configurable group/key separator, which by default is the period ('.').  If
		  * no group is specified, the configurable default is used, which by default is 'Global'.  Assuming all default configurable values, a full example would
		  * be '--Group.Key=Value'.
		  *
		  * @param targetOption
		  * 	This is the name of the config option, with optional group, whose value is to be retrieved.
		  *
		  * @return
		  * 	A string containing the value of the specified config option, or an empty string if it does not exist.
		  */

		std::string getConfigOption( const std::string& targetOption ) const;

		/**
		  * @brief This method retrieves the underlying config map.
		  *
		  * 	Refer to the 'getConfigOption' method for more information on the config option type.
		  *
		  * @return
		  * 	A non-mutable reference to the underlying config map.
		  */

		const ConfigMap& getConfigOptions() const;

		/**
		  * @brief This method sets the specified config option, with optional group, to the specified value.
		  *
		  * If the specified group or key do not exist, this method will have no effect unless 'doCreate' is set to 'true'; in which case, the group and/or the
		  * key will be created and the value assigned.
		  *
		  * @param targetOption
		  * 	This is the name of the config option, with optional group, whose value is to be set.
		  *
		  * @param newValue
		  * 	This is the value to use when settings the config option.
		  *
		  * @param doCreate
		  * 	If set to 'true' and the group and/or the key do not exist, they will first be created and then the value assigned.
		  */

		void setConfigOption( const std::string& targetOption, const std::string& newValue, const bool doCreate = false );

		/**
		  * @brief This method sets the underlying config map to the specified config map.
		  *
		  * 	Refer to the 'GetConfigOption' method for more information on the config option type.
		  *
		  * @param targetOptions
		  * 	This is the config map with which to set the underlying config map.
		  */

		void setConfigOptions( const ConfigMap& targetOptions );

		/**
		  * @brief This method removes the specified config option, with optional group, if it exists.
		  *
		  * If a removed config option is the last one in its group, the group will also be removed.
		  *
		  * @param targetOption
		  * 	This is the name of the config option, with optional group, to be removed.
		  *
		  */

		void removeConfigOption( const std::string& targetOption );

		/**
		  * @brief This method retrieves the positional option at the specified index, if it exists.
		  *
		  * A positional option is one which does not fit the form of any other option and whose purpose depends on its position in the argument list.
		  *
		  * @param targetIndex
		  * 	This is the positional option index used in retrieval.
		  *
		  * @return
		  * 	A string containing the positional option at the specified index, or an empty string if it does not exist.
		  */

		std::string getPositionalOption( size_t targetIndex ) const;

private:

	// Private Fields

		/**
		  * @brief This is the set of strings containing all parsed toggle options.
		  */

		StringSet toggleOptions;

		/**
		  * @brief This is the set of strings containing all parsed command options.
		  */

		StringSet commandOptions;

		/**
		  * @brief This is the map containing all parsed config options.
		  */

		ConfigMap configOptions;

		/**
		  * @brief This is the vector of strings containing all parsed positional options.
		  */

		StringVector positionalOptions;

	// Private Constructors

		/**
		  * @brief This is the default constructor, which is made private to prevent direct instantiation.
		  */

		ProgramOptions();

	// Private Methods

		/**
		  * @brief This is the overridden implementation for the 'deallocate' method.
		  */

		void deallocateImp();

		/**
		  * @brief This method extracts the embedded group ID from the specified string, if there is one.
		  *
		  * @param target
		  * 	This is the string used for group ID extraction.
		  *
		  * @return
		  * 	A string containing the extracted group ID, or the default group ID if there was none.
		  */

		std::string extractGroup( std::string& Target ) const;
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_PROGRAMOPTIONS_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ProgramOptions.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

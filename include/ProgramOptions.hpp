////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ProgramOptions.hpp
// Robert M. Baker | Created : 23OCT13 | Last Modified : 16FEB16 by Robert M. Baker
// Version : 1.0.0
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

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 23OCT13
  * @date    Last Modified : 16FEB16 by Robert M. Baker
  * @version 1.0.0
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
		  * This config file should be in plain text and contain lines in the format 'name = value'.  Any line whose first non-whitespace character is a number
		  * sign ('#') will be considered a comment.  Any line not containing an equal sign ('=') will be ignored regardless of wether or not it's a comment.
		  * Any config options parsed may be overridden by the command line, depending on the order in which the methods are called (i.e. If a call is made to
		  * 'ParseConfigFile' and then to 'ParseCommandLine', any identical entries on the command line will override those in the config file.).
		  *
		  * Refer to the 'GetConfigOption' method for more information on the config option type.
		  *
		  * @param ConfigPath
		  * 	This is the config file path to be parsed.
		  *
		  * @exception QMXException
		  * 	If the specified config file could not be opened.
		  */

		void ParseConfigFile( const Path& ConfigPath );

		/**
		  * @brief This method determines if the specified toggle option is present.
		  *
		  * A toggle option is one formed with a dash ('-') followed any number of characters (usually alphanumeric), and is usually meant to toggle a certain
		  * behavior.
		  *
		  * @param TargetOption
		  * 	This is the name of the toggle option whose presence is to be determined.
		  *
		  * @return
		  * 	A boolean value of 'true' if the specified toggle option is present, and 'false' otherwise.
		  */

		bool IsToggleOptionPresent( const std::string& TargetOption );

		/**
		  * @brief This method determines if the specified command option is present.
		  *
		  * A command option is one formed with two dashes ('--') followed by a string of characters (usually descriptive of its function), and is usually meant
		  * to invoke a function.
		  *
		  * @param TargetOption
		  * 	This is the name of the command option whose presence is to be determined.
		  *
		  * @return
		  * 	A boolean value of 'true' if the specified command option is present, and 'false' otherwise.
		  */

		bool IsCommandOptionPresent( const std::string& TargetOption );

		/**
		  * @brief This method retrieves the value of the specified config option, if it exists.
		  *
		  * A config option is one formed with a string of characters (usually a descriptive word) followed by an equal sign ('=') and then another string of
		  * characters (usually a logical value for the preceding word), and is usually meant to define key/value pairs.
		  *
		  * @param TargetOption
		  * 	This is the name of the config option whose value is to be retrieved.
		  *
		  * @return
		  * 	A string containing the value of the specified config option, or an empty string if it does not exist.
		  */

		std::string GetConfigOption( const std::string& TargetOption );

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

		std::string GetPositionalOption( size_t TargetIndex );

		/**
		  * @brief This method creates an instance of this class.
		  *
		  * @return
		  * 	A pointer to the newly created instance.
		  */

		static PointerType Create();

private:

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
		  * @brief This is the map of strings containing all parsed config options.
		  */

		StringMap ConfigOptions;

		/**
		  * @brief This is the vector of strings containing all parsed positional options.
		  */

		StringVector PositionalOptions;
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_PROGRAMOPTIONS_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ProgramOptions.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

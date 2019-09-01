////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ConsoleIO.hpp
// Robert M. Baker | Created : 12DEC11 | Last Modified : 27AUG19 by Robert M. Baker
// Version : 2.1.0
// This is a header file for 'QMXStdLib'; it defines the interface for a console I/O class.
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
  * @date    Created : 12DEC11
  * @date    Last Modified : 27AUG19 by Robert M. Baker
  * @version 2.1.0
  *
  * @brief This header file defines the interface for a console I/O class.
  *
  * @section ConsoleIOH0000 Description
  *
  * This header file defines the interface for a console I/O class.
  *
  * @section ConsoleIOH0001 License
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

#ifndef __QMX_QMXSTDLIB_CONSOLEIO_HPP_
#define __QMX_QMXSTDLIB_CONSOLEIO_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cctype>

#include "Base.hpp"
#include "Numeric.hpp"
#include "RAII/ScopedLock.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define COUT           QMXStdLib::ConsoleIO::SynchronizedStream( QMXStdLib::ConsoleIO::OUTPUT_STREAM )
#define CERR           QMXStdLib::ConsoleIO::SynchronizedStream( QMXStdLib::ConsoleIO::ERROR_STREAM )
#define CLOG           QMXStdLib::ConsoleIO::SynchronizedStream( QMXStdLib::ConsoleIO::LOG_STREAM )
#define WAIT_FOR_ENTER SINGLE_STATEMENT( COUT << "Press 'Enter' to continue...";  std::cin.peek();  FLUSH_ISTREAM( std::cin ); )

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'ConsoleIO' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class ConsoleIO ConsoleIO.hpp "include/ConsoleIO.hpp"
  *
  * @brief This class defines generic console input/output algorithms.
  *
  * It is defined as a utility class; thus, it cannot be instantiated and contains only static members.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Partially (The 'getInput' method is not thread-safe.)
  */

class ConsoleIO
{
	// Friend Classes

		friend class SynchronizedStream;

public:

	// Public Data Types

		/**
		  * @brief This enumeration contains all valid stream types.
		  */

		enum StreamType
		{
			OUTPUT_STREAM,
			ERROR_STREAM,
			LOG_STREAM,
			STREAM_COUNT
		};

		/**
		  * @brief This enumeration contains all valid input types.
		  */

		enum InputType
		{
			MINIMUM,
			MAXIMUM,
			RANGE,
			TWO_CHOICE,
			MULTIPLE_CHOICE
		};

		/**
		  * @brief This class is a thread-safe wrapper for a console stream.
		  */

		class SynchronizedStream
		{
		public:

			// Public Constructors

				/**
				  * @brief This is the copy constructor, which is deleted to prevent copying.
				  *
				  * @param instance
				  * 	N/A
				  */

				SynchronizedStream( const SynchronizedStream& instance ) = delete;

				/**
				  * @brief This is the constructor which accepts a stream type.
				  *
				  * @param sourceType
				  * 	This is the stream type to use for all operations.
				  */

				SynchronizedStream( StreamType sourceType )
				{
					// Initialize fields.

						type = sourceType;

					// Acquire lock.

						ConsoleIO::streamMutexes[ type ].lock();
				}

			// Destructor

				/**
				  * @brief This is the destructor.
				  */

				~SynchronizedStream()
				{
					// Release lock.

						ConsoleIO::streamMutexes[ type ].unlock();
				}

			// Public Overloaded Operators

				/**
				  * @brief This is the default assignment-operator, which is deleted to prevent copying.
				  *
				  * @param instance
				  * 	N/A
				  *
				  * @return
				  * 	N/A
				  */

				SynchronizedStream& operator=( const SynchronizedStream& instance ) = delete;

				/**
				  * @brief This is the overloaded bitwise left shift operator, which redirects inputs to the specified console stream.
				  *
				  * If the specified stream is disabled, the operation will be ignored.
				  *
				  * @param rhs
				  * 	This is the right-hand-side operand.
				  *
				  * @return
				  * 	A mutable reference to this object.
				  */

				template< typename DType > SynchronizedStream& operator<<( DType rhs )
				{
					// Perform abort check.

						if( ConsoleIO::isStreamDisabled[ type ] )
							return *this;

					// Redirect input to specified console stream.

						switch( type )
						{
							case ConsoleIO::OUTPUT_STREAM: { std::cout << rhs;  break; }
							case ConsoleIO::ERROR_STREAM: { std::cerr << rhs;  break; }
							case ConsoleIO::LOG_STREAM: { std::clog << rhs;  break; }

							default:
							{
								// Do nothing.
							}
						}

					// Return a mutable reference to this object to calling routine.

						return *this;
				}

		private:

				// Private Fields

					/**
					  * @brief This is the stream type to use.
					  */

					StreamType type;
		};

	// Public Methods

		/**
		  * @brief This method gets the current stream disabled flag for the specified type.
		  *
		  * @param type
		  * 	This is the stream type to use when getting the current stream disabled flag.
		  *
		  * @return
		  * 	A boolean value of 'true' if the specified stream type is disabled, and 'false' otherwise.
		  */

		static bool getStreamDisabled( StreamType type )
		{
			// Obtain locks.

				ScopedLock readLock( ScopedLock::READ, localMutex );

			// Return stream disabled flag for specified type to calling routine.

				return isStreamDisabled[ type ];
		}

		/**
		  * @brief This method sets the stream disabled flag for the specified type to the specified value.
		  *
		  * @param type
		  * 	This is the stream type to use when setting the stream disabled flag.
		  *
		  * @param value
		  * 	This is the target value for the specified stream disabled flag.
		  */

		static void setStreamDisabled( StreamType type, bool value )
		{
			// Obtain locks.

				ScopedLock writeLock( ScopedLock::WRITE, localMutex );

			// Set stream disabled flag of specified type to specified value.

				isStreamDisabled[ type ] = value;
		}

		/**
		  * @brief This method gets input based on the specified parameters.
		  *
		  * Only numeric primitive types (including 'char') are supported for the input types; using any other type, such as 'std::string', will have undefined
		  * results.
		  *
		  * @param min
		  * 	This is either the minimum value or one of two choices depending on the input type; if it is greater-than or equal-to 'max' and the input type is
		  * 	'RANGE', it will be set to 'max - 1'.
		  *
		  * @param max
		  * 	This is either the maximum value or one of two choices depending on the input type; if it is less-than or equal-to 'min' and the input type is
		  * 	'RANGE', 'min' will be set to 'max - 1'.
		  *
		  * @param type
		  * 	This value determines how the user input will be processed.
		  *
		  * @param choices
		  * 	This is a string containing all valid choices if the input type is set to 'MULTIPLE_CHOICE'; if it is empty, it will be set to the default choices;
		  * 	the proper format for this string is single characters separated by a comma-space combo and optionally having the word 'or' before the last choice
		  * 	(e.g. "A, B, C, D, or E").
		  *
		  * @param prompt
		  * 	This is a string containing the input prompt to display to the user; if 'min' is greater-than or equal-to 'max' and the input type is 'RANGE', or it
		  *   is empty, it will be set to a default prompt.
		  *
		  * @param error
		  * 	This is a string containing the error message to display on invalid input from the user; if 'min' is greater-than or equal-to 'max' and the input
		  * 	type is 'RANGE', or it is empty, it will be set to a default message.
		  *
		  * @return
		  * 	The value input by the user.
		  */

		template< typename DType > static DType getInput(
			DType min,
			DType max,
			InputType type = CONSOLEIO_DEFAULT_INPUT_TYPE,
			const std::string& choices = "",
			const std::string& prompt = "",
			const std::string& error = ""
		)
		{
			// Create local variables.

				DType result;
				bool isDone = false;
				std::ostringstream choicesBuffer( choices );
				std::ostringstream promptBuffer( prompt );
				std::ostringstream errorBuffer( error );

			// Check arguments.

				if( ( type == RANGE ) && ( min >= max ) )
				{
					min = max - 1;
					promptBuffer.str( "" );
					errorBuffer.str( "" );
				}

			// Set choices string if not specified.

				if( choicesBuffer.str().empty() )
					choicesBuffer.str( CONSOLEIO_DEFAULT_CHOICES );

			// Set prompt string if not specified.

				if( promptBuffer.str().empty() )
				{
					switch( type )
					{
						case MINIMUM:
						{
							promptBuffer << "\nPlease enter a value that is " << min << " or greater: ";

							break;
						}

						case MAXIMUM:
						{
							promptBuffer << "\nPlease enter a value that is " << max << " or less: ";

							break;
						}

						case RANGE:
						{
							promptBuffer << "\nPlease enter a value between " << min << " and " << max << ": ";

							break;
						}

						case TWO_CHOICE:
						{
							promptBuffer << "\nPlease enter either " << min << " or " << max << ": ";

							break;
						}

						case MULTIPLE_CHOICE:
						{
							promptBuffer << "\nPlease enter either " << choicesBuffer.str() << ": ";

							break;
						}
					}
				}

			// Set error string if not specified.

				if( errorBuffer.str().empty() )
				{
					switch( type )
					{
						case MINIMUM:
						{
							errorBuffer << "\nYou must enter a value that is " << min << " or greater.\n\n";

							break;
						}

						case MAXIMUM:
						{
							errorBuffer << "\nYou must enter a value that is " << max << " or less.\n\n";

							break;
						}

						case RANGE:
						{
							errorBuffer << "\nYou must enter a value between " << min << " and " << max << ".\n\n";

							break;
						}

						case TWO_CHOICE:
						{
							errorBuffer << "\nYou must enter either " << min << " or " << max << ".\n\n";

							break;
						}

						case MULTIPLE_CHOICE:
						{
							errorBuffer << "\nYou must enter either " << choicesBuffer.str() << ".\n\n";

							break;
						}
					}
				}

			// Loop until valid input is received based on given arguments.

				do
				{
					COUT << promptBuffer.str();
					std::cin >> result;

					switch( type )
					{
						case MINIMUM:
						{
							if( !std::cin.fail() && ( result >= min ) )
								isDone = true;

							break;
						}

						case MAXIMUM:
						{
							if( !std::cin.fail() && ( result <= max ) )
								isDone = true;

							break;
						}

						case RANGE:
						{
							if( !std::cin.fail() && Numeric::inRange< DType >( result, min, max ) )
								isDone = true;

							break;
						}

						case TWO_CHOICE:
						{
							result = toupper( result );

							if( !std::cin.fail() && ( ( result == min ) || ( result == max ) ) )
								isDone = true;

							break;
						}

						case MULTIPLE_CHOICE:
						{
							result = toupper( result );

							if( !std::cin.fail() && ( choicesBuffer.str().find( result ) != std::string::npos ) )
								isDone = true;

							break;
						}
					}

					if( !isDone )
					{
						COUT << errorBuffer.str();

						if( !std::cin )
						{
							std::cin.clear();
							FLUSH_ISTREAM( std::cin );
						}
					}
				} while( !isDone );

			// Flush input buffer to ensure no extraneous data causes issues.

				FLUSH_ISTREAM( std::cin );

			// Return result to calling routine.

				return result;
		}

private:

	// Private Fields

		/**
		  * @brief This is the flag array used to determine if a certain stream type is disabled.
		  */

		static bool isStreamDisabled[ STREAM_COUNT ];

		/**
		  * @brief This is the mutex used for synchronization of field manipulation.
		  */

		static SharedMutexPair localMutex;

		/**
		  * @brief This is the mutex array used for synchronization of a certain stream type.
		  */

		static SharedMutex streamMutexes[ STREAM_COUNT ];

	// Private Constructors

		/**
		  * @brief This is the default constructor, which is made private to prevent instantiation.
		  */

		ConsoleIO()
		{
			// Do nothing.
		}
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_CONSOLEIO_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ConsoleIO.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

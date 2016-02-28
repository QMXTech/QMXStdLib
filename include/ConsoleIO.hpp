////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ConsoleIO.hpp
// Robert M. Baker | Created : 12DEC11 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.1
// This is a header file for 'QMXStdLib'; it defines the interface for a console I/O class.
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
  * @date    Created : 12DEC11
  * @date    Last Modified : 27FEB16 by Robert M. Baker
  * @version 1.1.1
  *
  * @brief This header file defines the interface for a console I/O class.
  *
  * @section Description
  *
  * This header file defines the interface for a console I/O class.
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

#ifndef __QMX_QMXSTDLIB_CONSOLEIO_HPP_
#define __QMX_QMXSTDLIB_CONSOLEIO_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "Numeric.hpp"
#include "Mixins/NonCopyable.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define COUT QMXStdLib::ConsoleIO::SynchronizedStream( QMXStdLib::ConsoleIO::OutputStream )
#define CERR QMXStdLib::ConsoleIO::SynchronizedStream( QMXStdLib::ConsoleIO::ErrorStream )
#define CLOG QMXStdLib::ConsoleIO::SynchronizedStream( QMXStdLib::ConsoleIO::LogStream )

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
  * Thread-Safe              : Partially (The 'GetInput' method is not thread-safe.)
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
			OutputStream,
			ErrorStream,
			LogStream,
			StreamCount
		};

		/**
		  * @brief This enumeration contains all valid input types.
		  */

		enum InputType
		{
			Minimum,
			Maximum,
			Range,
			TwoChoice,
			MultipleChoice
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
				  * @param Instance
				  * 	N/A
				  */

				SynchronizedStream( const SynchronizedStream& Instance ) = delete;

				/**
				  * @brief This is the constructor which accepts a stream type.
				  *
				  * @param TargetType
				  * 	This is the stream type to use for all operations.
				  */

				SynchronizedStream( StreamType TargetType )
				{
					// Create local variables.

						UniqueLock WriteLockTarget( ConsoleIO::StreamMutexes[ TargetType ], boost::defer_lock );

					// Initialize fields.

						WriteLock.swap( WriteLockTarget );
						Type = TargetType;

					// Acquire lock.

						WriteLock.lock();
				}

			// Destructor

				/**
				  * @brief This is the destructor.
				  */

				virtual ~SynchronizedStream()
				{
					// Release lock.

						WriteLock.unlock();
				}

			// Public Overloaded Operators

				/**
				  * @brief This is the default assignment-operator, which is deleted to prevent copying.
				  *
				  * @param Instance
				  * 	N/A
				  *
				  * @return
				  * 	N/A
				  */

				SynchronizedStream& operator=( const SynchronizedStream& Instance ) = delete;

				/**
				  * @brief This is the overloaded bitwise left shift operator, which redirects inputs to the specified console stream.
				  *
				  * If the specified stream is disabled, the operation will be ignored.
				  *
				  * @param RHS
				  * 	This is the right-hand-side operand.
				  *
				  * @return
				  * 	A mutable reference to this object.
				  */

				template< typename DType > SynchronizedStream& operator<<( DType RHS )
				{
					// Perform precondition checks.

						if( ConsoleIO::IsStreamDisabled[ Type ] )
							return *this;

					// Redirect input to specified console stream.

						switch( Type )
						{
							case ConsoleIO::OutputStream:
							{
								std::cout << RHS;

								break;
							}

							case ConsoleIO::ErrorStream:
							{
								std::cerr << RHS;

								break;
							}

							case ConsoleIO::LogStream:
							{
								std::clog << RHS;

								break;
							}

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

					StreamType Type;

					/**
					  * @brief This is the lock object to use when acquiring/releasing a lock.
					  */

					UniqueLock WriteLock;
		};

	// Public Methods

		/**
		  * @brief This method gets the current stream disabled flag for the specified type.
		  *
		  * @param Type
		  * 	This is the stream type to use when getting the current stream disabled flag.
		  *
		  * @return
		  * 	A boolean value of 'true' if the specified stream type is disabled, and 'false' otherwise.
		  */

		static bool GetStreamDisabled( StreamType Type )
		{
			// Obtain locks.

				SharedLock ScopedReadLock( LocalMutex );

			// Return stream disabled flag for specified type to calling routine.

				return IsStreamDisabled[ Type ];
		}

		/**
		  * @brief This method sets the stream disabled flag for the specified type to the specified value.
		  *
		  * @param Type
		  * 	This is the stream type to use when setting the stream disabled flag.
		  *
		  * @param Value
		  * 	This is the target value for the specified stream disabled flag.
		  */

		static void SetStreamDisabled( StreamType Type, bool Value )
		{
			// Obtain locks.

				UniqueLock ScopedWriteLock( LocalMutex );

			// Set stream disabled flag of specified type to specified value.

				IsStreamDisabled[ Type ] = Value;
		}

		/**
		  * @brief This method gets input based on the specified parameters.
		  *
		  * Only numeric primitive types (including 'char') are supported for the input types; using any other type, such as 'std::string', will have undefined
		  * results.
		  *
		  * @param Min
		  * 	This is either the minimum value or one of two choices depending on the input type; if it is greater-than or equal-to 'max' and the input type is
		  * 	'Range', it will be set to 'max - 1'.
		  *
		  * @param Max
		  * 	This is either the maximum value or one of two choices depending on the input type; if it is less-than or equal-to 'min' and the input type is
		  * 	'Range', 'min' will be set to 'max - 1'.
		  *
		  * @param Type
		  * 	This value determines how the user input will be processed.
		  *
		  * @param Choices
		  * 	This is a string containing all valid choices if the input type is set to 'MultipleChoice'; if it is empty, it will be set to the default choices;
		  * 	the proper format for this string is single characters separated by a comma-space combo and optionally having the word 'or' before the last choice
		  * 	(e.g. "A, B, C, D, or E").
		  *
		  * @param Prompt
		  * 	This is a string containing the input prompt to display to the user; if 'min' is greater-than or equal-to 'max' and the input type is 'Range', or it
		  *   is empty, it will be set to a default prompt.
		  *
		  * @param Error
		  * 	This is a string containing the error message to display on invalid input from the user; if 'min' is greater-than or equal-to 'max' and the input
		  * 	type is 'Range', or it is empty, it will be set to a default message.
		  *
		  * @return
		  * 	The value input by the user.
		  */

		template< typename DType > static DType GetInput( DType Min,
		                                                  DType Max,
		                                                  InputType Type = CONSOLEIO_DEFAULT_INPUT_TYPE,
		                                                  const std::string& Choices = "",
		                                                  const std::string& Prompt = "",
		                                                  const std::string& Error = "" )
		{
			// Create local variables.

				DType Result;
				bool Done = false;
				std::ostringstream ChoicesBuffer( Choices );
				std::ostringstream PromptBuffer( Prompt );
				std::ostringstream ErrorBuffer( Error );

			// Check arguments.

				if( ( Type == Range ) && ( Min >= Max ) )
				{
					Min = Max - 1;
					PromptBuffer.str( "" );
					ErrorBuffer.str( "" );
				}

			// Set choices string if not specified.

				if( ChoicesBuffer.str().empty() )
					ChoicesBuffer.str( CONSOLEIO_DEFAULT_CHOICES );

			// Set prompt string if not specified.

				if( PromptBuffer.str().empty() )
				{
					switch( Type )
					{
						case Minimum:
						{
							PromptBuffer << "\nPlease enter a value that is " << Min << " or greater: ";

							break;
						}

						case Maximum:
						{
							PromptBuffer << "\nPlease enter a value that is " << Max << " or less: ";

							break;
						}

						case Range:
						{
							PromptBuffer << "\nPlease enter a value between " << Min << " and " << Max << ": ";

							break;
						}

						case TwoChoice:
						{
							PromptBuffer << "\nPlease enter either " << Min << " or " << Max << ": ";

							break;
						}

						case MultipleChoice:
						{
							PromptBuffer << "\nPlease enter either " << ChoicesBuffer.str() << ": ";

							break;
						}
					}
				}

			// Set error string if not specified.

				if( ErrorBuffer.str().empty() )
				{
					switch( Type )
					{
						case Minimum:
						{
							ErrorBuffer << "\nYou must enter a value that is " << Min << " or greater.\n\n";

							break;
						}

						case Maximum:
						{
							ErrorBuffer << "\nYou must enter a value that is " << Max << " or less.\n\n";

							break;
						}

						case Range:
						{
							ErrorBuffer << "\nYou must enter a value between " << Min << " and " << Max << ".\n\n";

							break;
						}

						case TwoChoice:
						{
							ErrorBuffer << "\nYou must enter either " << Min << " or " << Max << ".\n\n";

							break;
						}

						case MultipleChoice:
						{
							ErrorBuffer << "\nYou must enter either " << ChoicesBuffer.str() << ".\n\n";

							break;
						}
					}
				}

			// Loop until valid input is received based on given arguments.

				do
				{
					COUT << PromptBuffer.str();
					std::cin >> Result;

					switch( Type )
					{
						case Minimum:
						{
							if( !std::cin.fail() && ( Result >= Min ) )
								Done = true;

							break;
						}

						case Maximum:
						{
							if( !std::cin.fail() && ( Result <= Max ) )
								Done = true;

							break;
						}

						case Range:
						{
							if( !std::cin.fail() && Numeric::InRange< DType >( Result, Min, Max ) )
								Done = true;

							break;
						}

						case TwoChoice:
						{
							Result = toupper( Result );

							if( !std::cin.fail() && ( ( Result == Min ) || ( Result == Max ) ) )
								Done = true;

							break;
						}

						case MultipleChoice:
						{
							Result = toupper( Result );

							if( !std::cin.fail() && ( ChoicesBuffer.str().find( Result ) != std::string::npos ) )
								Done = true;

							break;
						}
					}

					if( !Done )
					{
						COUT << ErrorBuffer.str();

						if( !std::cin )
						{
							std::cin.clear();
							FLUSH_ISTREAM( std::cin );
						}
					}
				} while( !Done );

			// Flush input buffer to ensure no extraneous data causes issues.

				FLUSH_ISTREAM( std::cin );

			// Return result to calling routine.

				return Result;
		}

private:

	// Private Fields

		/**
		  * @brief This is the flag array used to determine if a certain stream type is disabled.
		  */

		static bool IsStreamDisabled[ StreamCount ];

		/**
		  * @brief This is the mutex used for synchronization of field manipulation.
		  */

		static SharedMutex LocalMutex;

		/**
		  * @brief This is the mutex array used for synchronization of a certain stream type.
		  */

		static SharedMutex StreamMutexes[ StreamCount ];

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utility.hpp
// Robert M. Baker | Created : 11JAN12 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.0
// This is a header file for 'QMXStdLib'; it defines the interface for a general utility class.
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
  * @date    Created : 11JAN12
  * @date    Last Modified : 27FEB16 by Robert M. Baker
  * @version 1.1.0
  *
  * @brief This header file defines the interface for a general utility class.
  *
  * @section Description
  *
  * This header file defines the interface for a general utility class.
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

#ifndef __QMX_QMXSTDLIB_UTILITY_HPP_
#define __QMX_QMXSTDLIB_UTILITY_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "Timer.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define UTILITY_LANGUAGES        187
#define UTILITY_COUNTRIES        249

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'Utility' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class Utility Utility.hpp "include/Utility.hpp"
  *
  * @brief This class defines general utility algorithms.
  *
  * It is defined as a utility class; thus, it cannot be instantiated and contains only static members.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Yes
  */

class Utility
{
public:

	// Public Data Types

		/**
		  * @brief This structure holds version number data.
		  */

		struct VersionData
		{
		public:

			// Public Fields

				/**
				  * @brief This is the major version.
				  */

				uint64_t Major;

				/**
				  * @brief This is the minor version.
				  */

				uint64_t Minor;

				/**
				  * @brief This is the patch version.
				  */

				uint64_t Patch;
		};

		/**
		  * @brief This structure stores data about a locale.
		  */

		struct LocaleData
		{
		public:

			// Public Fields

				/**
				  * @brief This is the full name of the locale (e.g. "en_US.UTF-8@currency=USD").
				  */

				std::string Name;

				/**
				  * @brief This is the ISO 639-1 language code of the locale (e.g. "en").
				  */

				std::string Language;

				/**
				  * @brief This is the ISO 3166-1 alpha-2 country code of the locale (e.g. "US").
				  */

				std::string Country;

				/**
				  * @brief This is the character encoding of the locale (e.g. "UTF-8").
				  */

				std::string Encoding;

				/**
				  * @brief This is the variant of the locale (e.g. "currency=USD").
				  */

				std::string Variant;
		};

		/**
		  * @brief This union allows access of a dwords lower and upper words.
		  */

		template< typename DWType, typename WType > union DWord
		{
		public:

			// Public Fields

				/**
				  * @brief This is the dword data.
				  */

				DWType DWordData;

				/**
				  * @brief This is the array to access the upper and lower words.
				  */

				WType WordData[ 2 ];
		};

	// Public Fields

		/**
		  * @brief This is the array of languages paired with their ISO 639-1 code.
		  */

		static const StringPair Languages[ UTILITY_LANGUAGES ];

		/**
		  * @brief This is the array of countries paired with their ISO 3166-1 alpha-2 code.
		  */

		static const StringPair Countries[ UTILITY_COUNTRIES ];

	// Public Methods

		/**
		  * @brief This method gets the current version data for this library.
		  *
		  * @return
		  * 	A 'VersionData' instance containing the version data for this library.
		  */

		static VersionData GetVersionNumber()
		{
			// Return version data for this library to calling routine.

				return { QMXSTDLIB_VER_MAJOR, QMXSTDLIB_VER_MINOR, QMXSTDLIB_VER_PATCH };
		}

		/**
		  * @brief This method gets the current version data for this library.
		  *
		  * @return
		  * 	A string representing the current version data for this library.
		  */

		static std::string GetVersionString()
		{
			// Create local variables.

				std::ostringstream Result;

			// Construct a string representation of the current version data for this library.

				Result << QMXSTDLIB_VER_MAJOR << '.' << QMXSTDLIB_VER_MINOR << '.' << QMXSTDLIB_VER_PATCH;

			// Return result to calling routine.

				return Result.str();
		}

		/**
		  * @brief This method gets the ISO 639-1 code for the specified language.
		  *
		  * @param Language
		  * 	This is the language from which to get the ISO 639-1 code.
		  *
		  * @return
		  * 	The ISO 639-1 code for the specified language, if it exists, or an empty string otherwise.
		  */

		static std::string GetLanguageCode( const std::string& Language )
		{
			// Create local variables.

				std::string Result;
				bool IsDone = false;
				const StringPair* LanguagesIterator = &Languages[ 0 ];
				const StringPair* LanguagesEnd = &Languages[ ( UTILITY_LANGUAGES - 1 ) ] + 1;

			// Get ISO 639-1 Code for specified language, if it exists.

				while( !IsDone && ( LanguagesIterator != LanguagesEnd ) )
				{
					if( LanguagesIterator->first == Language )
					{
						Result = LanguagesIterator->second;
						IsDone = true;
					}

					LanguagesIterator++;
				}

			// Return result to calling routine.

				return Result;
		}

		/**
		  * @brief This method gets the ISO 3166-1 alpha-2 code for the specified country.
		  *
		  * @param Country
		  * 	This is the country from which to get the ISO 3166-1 alpha-2 code.
		  *
		  * @return
		  * 	The ISO 3166-1 alpha-2 code for the specified country, if it exists, or an empty string otherwise.
		  */

		static std::string GetCountryCode( const std::string& Country )
		{
			// Create local variables.

				std::string Result;
				bool IsDone = false;
				const StringPair* CountriesIterator = &Countries[ 0 ];
				const StringPair* CountriesEnd = &Countries[ ( UTILITY_COUNTRIES - 1 ) ] + 1;

			// Get ISO 3166-1 alpha-2 Code for specified country, if it exists.

				while( !IsDone && ( CountriesIterator != CountriesEnd ) )
				{
					if( CountriesIterator->first == Country )
					{
						Result = CountriesIterator->second;
						IsDone = true;
					}

					CountriesIterator++;
				}

			// Return result to calling routine.

				return Result;
		}

		/**
		  * @brief This method generates a locale based on the specified ID.
		  *
		  * @param ID
		  * 	This is the ID to use when generating the locale.
		  *
		  * @return
		  * 	A locale object generated using the specified ID.
		  */

		static std::locale GenerateLocale( const std::string& ID )
		{
			// Create local variables.

				boost::locale::generator LocaleGenerator;

			// Return generated locale to calling routine.

				return LocaleGenerator( ID );
		}

		/**
		  * @brief This method gets data about the specified locale, if it is valid.
		  *
		  * @param Data
		  * 	This is a 'LocaleData' structure reference which will receive the data for the specified locale; if the specified locale is invalid, this will not
		  * 	be modified.
		  *
		  * @param TargetLocale
		  * 	This is the locale from which to retrieve data.
		  */

		static void GetLocaleData( LocaleData& Data, const std::locale& TargetLocale )
		{
			// Get locale data for specified locale, if it is valid.

				if( std::has_facet< boost::locale::info >( TargetLocale ) )
					Data = { std::use_facet< boost::locale::info >( TargetLocale ).name(),
					         std::use_facet< boost::locale::info >( TargetLocale ).language(),
					         std::use_facet< boost::locale::info >( TargetLocale ).country(),
					         std::use_facet< boost::locale::info >( TargetLocale ).encoding(),
					         std::use_facet< boost::locale::info >( TargetLocale ).variant() };
		}

		/**
		  * @brief This method generates a time stamp, in 24-hour format, using the current time (e.g. "13:37:00h" ).
		  *
		  * @return
		  * 	A string representing the time stamp.
		  */

		static std::string TimeStamp()
		{
			// Create local variables.

				std::ostringstream Result;
				time_t CurrentTime = time( nullptr );
				tm* SystemTime = localtime( &CurrentTime );

			// Construct a string representation of the time stamp using the current time.

				Result << std::setfill( '0' ) << std::setw( 2 ) << SystemTime->tm_hour << ':' <<
				          std::setw( 2 ) << SystemTime->tm_min << ':' <<
				          std::setw( 2 ) << SystemTime->tm_sec << 'h';

			// Return result to calling routine.

				return Result.str();
		}

		/**
		  * @brief This method halts execution of the application for the specified amount of time.
		  *
		  * This method will block any further execution during the period it is in effect.  This should only be used when constant logic processing is unneeded.
		  *
		  * @param Interval
		  * 	This is the time interval that the application will be halted.
		  *
		  * @param Units
		  * 	These are the units to use with the specified time interval.
		  */

		static void Pause( real_t Interval, Timer::TimeUnits Units = Timer::Milliseconds )
		{
			// Create local variables.

				Timer::PointerType DelayTimer = Timer::Create();

			// Pause for the specified time interval.

				DelayTimer->Toggle();

				while( DelayTimer->GetTime( Units ) < Interval );
					// Empty Loop
		}

		/**
		  * @brief This method sets the seed for the random number generator.
		  *
		  * @param Seed
		  * 	This is the seed to use; if it is set to 'Null', the current time will be used instead.
		  */

		static void SetRandomSeed( uint32_t Seed = Null )
		{
			// Seed random number generator with specified value, or use current time if specified value is 'Null'.

				Generator.seed( ( !Seed ? time( nullptr ) : Seed ) );
		}

		/**
		  * @brief This method defines the structure for a random integral number generator.
		  *
		  * @param Min
		  * 	This is the minimum value of the random number.
		  *
		  * @param Max
		  * 	This is the maximum value of the random number.
		  *
		  * @return
		  * 	The random number generated.
		  */

		template< typename IType > static IType RandomI( IType Min, IType Max )
		{
			// Create local variables.

				std::uniform_int_distribution< IType > Distro( Min, Max );

			// Return a random number within the specified range to calling routine.

				return Distro( Generator );
		}

		/**
		  * @brief This method defines the structure for a random floating point number generator.
		  *
		  * @param Min
		  * 	This is the minimum value of the random number.
		  *
		  * @param Max
		  * 	This is the maximum value of the random number.
		  *
		  * @return
		  * 	The random number generated.
		  */

		template< typename FType > static FType RandomF( FType Min, FType Max )
		{
			// Create local variables.

				std::uniform_real_distribution< FType > Distro( Min, Max );

			// Return a random number within the specified range to calling routine.

				return Distro( Generator );
		}

private:

	// Private Fields

		/**
		  * @brief This is the generator to use for the random number generation methods.
		  */

		static std::mt19937 Generator;

	// Private Constructors

		/**
		  * @brief This is the default constructor, which is made private to prevent instantiation.
		  */

		Utility()
		{
			// Do nothing.
		}
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_UTILITY_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'Utility.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

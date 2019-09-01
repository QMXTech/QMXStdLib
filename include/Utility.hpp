////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utility.hpp
// Robert M. Baker | Created : 11JAN12 | Last Modified : 31AUG19 by Robert M. Baker
// Version : 2.1.1
// This is a header file for 'QMXStdLib'; it defines the interface for a general utility class.
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
  * @date    Created : 11JAN12
  * @date    Last Modified : 31AUG19 by Robert M. Baker
  * @version 2.1.1
  *
  * @brief This header file defines the interface for a general utility class.
  *
  * @section UtilityH0000 Description
  *
  * This header file defines the interface for a general utility class.
  *
  * @section UtilityH0001 License
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

#ifndef __QMX_QMXSTDLIB_UTILITY_HPP_
#define __QMX_QMXSTDLIB_UTILITY_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <random>
#include <boost/locale.hpp>

#include "Base.hpp"
#include "Timer.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define UTILITY_LANGUAGES 187
#define UTILITY_COUNTRIES 249

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

				uint64_t major;

				/**
				  * @brief This is the minor version.
				  */

				uint64_t minor;

				/**
				  * @brief This is the patch version.
				  */

				uint64_t patch;
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

				std::string name;

				/**
				  * @brief This is the ISO 639-1 language code of the locale (e.g. "en").
				  */

				std::string language;

				/**
				  * @brief This is the ISO 3166-1 alpha-2 country code of the locale (e.g. "US").
				  */

				std::string country;

				/**
				  * @brief This is the character encoding of the locale (e.g. "UTF-8").
				  */

				std::string encoding;

				/**
				  * @brief This is the variant of the locale (e.g. "currency=USD").
				  */

				std::string variant;
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

				DWType dword;

				/**
				  * @brief This is the array to access the upper and lower words.
				  */

				WType word[ 2 ];
		};

	// Public Fields

		/**
		  * @brief This is the array of languages paired with their ISO 639-1 code.
		  */

		static const StringPair languages[ UTILITY_LANGUAGES ];

		/**
		  * @brief This is the array of countries paired with their ISO 3166-1 alpha-2 code.
		  */

		static const StringPair countries[ UTILITY_COUNTRIES ];

	// Public Methods

		/**
		  * @brief This method gets the current version data for this library.
		  *
		  * @return
		  * 	A 'VersionData' instance containing the version data for this library.
		  */

		static VersionData getVersionNumber()
		{
			// Return version data for this library to calling routine.

				return { QMXSTDLIB_VER_MAJOR, QMXSTDLIB_VER_MINOR, QMXSTDLIB_VER_PATCH };
		}

		/**
		  * @brief This method gets the current version string for this library.
		  *
		  * @return
		  * 	A string representing the current version data for this library.
		  */

		static std::string getVersionString()
		{
			// Create local variables.

				std::ostringstream result;

			// Construct a string representation of the current version data for this library.

				result << QMXSTDLIB_VER_MAJOR << '.' << QMXSTDLIB_VER_MINOR << '.' << QMXSTDLIB_VER_PATCH;

			// Return result to calling routine.

				return result.str();
		}

		/**
		  * @brief This method gets the ISO 639-1 code for the specified language.
		  *
		  * @param language
		  * 	This is the language from which to get the ISO 639-1 code.
		  *
		  * @return
		  * 	The ISO 639-1 code for the specified language, if it exists, or an empty string otherwise.
		  */

		static std::string getLanguageCode( const std::string& language )
		{
			// Create local variables.

				std::string result;
				bool isDone = false;
				const StringPair* languagesIterator = &languages[ 0 ];
				const StringPair* languagesEnd = &languages[ ( UTILITY_LANGUAGES - 1 ) ] + 1;

			// Get ISO 639-1 Code for specified language, if it exists.

				while( !isDone && ( languagesIterator != languagesEnd ) )
				{
					if( languagesIterator->first == language )
					{
						result = languagesIterator->second;
						isDone = true;
					}

					languagesIterator++;
				}

			// Return result to calling routine.

				return result;
		}

		/**
		  * @brief This method gets the ISO 3166-1 alpha-2 code for the specified country.
		  *
		  * @param country
		  * 	This is the country from which to get the ISO 3166-1 alpha-2 code.
		  *
		  * @return
		  * 	The ISO 3166-1 alpha-2 code for the specified country, if it exists, or an empty string otherwise.
		  */

		static std::string getCountryCode( const std::string& country )
		{
			// Create local variables.

				std::string result;
				bool isDone = false;
				const StringPair* countriesIterator = &countries[ 0 ];
				const StringPair* countriesEnd = &countries[ ( UTILITY_COUNTRIES - 1 ) ] + 1;

			// Get ISO 3166-1 alpha-2 Code for specified country, if it exists.

				while( !isDone && ( countriesIterator != countriesEnd ) )
				{
					if( countriesIterator->first == country )
					{
						result = countriesIterator->second;
						isDone = true;
					}

					countriesIterator++;
				}

			// Return result to calling routine.

				return result;
		}

		/**
		  * @brief This method generates a locale based on the specified ID.
		  *
		  * @param id
		  * 	This is the ID to use when generating the locale.
		  *
		  * @return
		  * 	A locale object generated using the specified ID.
		  */

		static std::locale generateLocale( const std::string& id )
		{
			// Create local variables.

				boost::locale::generator localeGenerator;

			// Return generated locale to calling routine.

				return localeGenerator( id );
		}

		/**
		  * @brief This method gets data about the specified locale, if it is valid.
		  *
		  * @param target
		  * 	This is a 'LocaleData' structure reference which will receive the data for the specified locale; if the specified locale is invalid, this will not
		  * 	be modified.
		  *
		  * @param source
		  * 	This is the locale from which to retrieve data.
		  */

		static void getLocaleData( LocaleData& target, const std::locale& source )
		{
			// Get locale data for specified locale, if it is valid.

				if( std::has_facet< boost::locale::info >( source ) )
					target = {
						std::use_facet< boost::locale::info >( source ).name(),
						std::use_facet< boost::locale::info >( source ).language(),
						std::use_facet< boost::locale::info >( source ).country(),
						std::use_facet< boost::locale::info >( source ).encoding(),
						std::use_facet< boost::locale::info >( source ).variant()
					};
		}

		/**
		  * @brief This method generates a time stamp, in 24-hour format, using the current time (e.g. "13:37:00h" ).
		  *
		  * @return
		  * 	A string representing the time stamp.
		  */

		static std::string timeStamp()
		{
			// Create local variables.

				std::ostringstream result;
				time_t currentTime = time( nullptr );
				tm* systemTime = localtime( &currentTime );

			// Construct a string representation of the time stamp using the current time.

				result << std::setfill( '0' ) << std::setw( 2 ) << systemTime->tm_hour << ':' <<
					std::setw( 2 ) << systemTime->tm_min << ':' <<
					std::setw( 2 ) << systemTime->tm_sec << 'h';

			// Return result to calling routine.

				return result.str();
		}

		/**
		  * @brief This method halts execution of the application for the specified amount of time.
		  *
		  * This method will block any further execution during the period it is in effect.  This should only be used when constant logic processing is unneeded.
		  *
		  * @param interval
		  * 	This is the time interval that the application will be halted.
		  *
		  * @param units
		  * 	These are the units to use with the specified time interval.
		  */

		static void pause( real_t interval, Timer::TimeUnits units = Timer::MILLISECONDS )
		{
			// Create local variables.

				Timer::InstancePtr delayTimer = Timer::create();

			// Pause for the specified time interval.

				delayTimer->toggle();

				while( delayTimer->getTime( units ) < interval );
					// Empty Loop
		}

		/**
		  * @brief This method sets the seed for the random number generator.
		  *
		  * @param seed
		  * 	This is the seed to use; if it is set to 'UNSET', the current time will be used instead.
		  */

		static void setRandomSeed( uint32_t seed = UNSET )
		{
			// Seed random number generator with specified value, or use current time if specified value is 'UNSET'.

				generator.seed( ( !seed ? time( nullptr ) : seed ) );
		}

		/**
		  * @brief This method defines the structure for a random integral number generator.
		  *
		  * @param min
		  * 	This is the minimum value of the random number.
		  *
		  * @param max
		  * 	This is the maximum value of the random number.
		  *
		  * @return
		  * 	The random number generated.
		  */

		template< typename IType > static IType randInt( IType min, IType max )
		{
			// Create local variables.

				std::uniform_int_distribution< IType > distro( min, max );

			// Return a random number within the specified range to calling routine.

				return distro( generator );
		}

		/**
		  * @brief This method defines the structure for a random floating point number generator.
		  *
		  * @param min
		  * 	This is the minimum value of the random number.
		  *
		  * @param max
		  * 	This is the maximum value of the random number.
		  *
		  * @return
		  * 	The random number generated.
		  */

		template< typename FType > static FType randFloat( FType min, FType max )
		{
			// Create local variables.

				std::uniform_real_distribution< FType > distro( min, max );

			// Return a random number within the specified range to calling routine.

				return distro( generator );
		}

private:

	// Private Fields

		/**
		  * @brief This is the generator to use for the random number generation methods.
		  */

		static std::mt19937 generator;

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

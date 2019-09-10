////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UtilityTest.cpp
// Robert M. Baker | Created : 22FEB12 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.3.0
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::Utility' class.
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../include/UtilityTest.hpp"

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::Utility' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( UtilityTest, GetVersionNumberWorks )
{
	// Create local variables.

		Utility::VersionData version = Utility::getVersionNumber();

	// Perform unit test for 'getVersionNumber' method.

		ASSERT_EQ( QMXSTDLIB_VER_MAJOR, version.major );
		ASSERT_EQ( QMXSTDLIB_VER_MINOR, version.minor );
		ASSERT_EQ( QMXSTDLIB_VER_PATCH, version.patch );
}

TEST( UtilityTest, GetVersionStringWorks )
{
	// Create local variables.

		ostringstream expectedResult;

	// Perform unit test for 'getVersionString' method.

		expectedResult << QMXSTDLIB_VER_MAJOR << '.' << QMXSTDLIB_VER_MINOR << '.' << QMXSTDLIB_VER_PATCH;
		ASSERT_EQ( expectedResult.str(), Utility::getVersionString() );
}

TEST( UtilityTest, GetLanguageCodeWorks )
{
	// Create local variables.

		string testValues[] = {
			"English",
			"Japanese",
			"Russian",
			"Spanish",
			"French"
		};

		string expectedResults[] = {
			"en",
			"ja",
			"ru",
			"es",
			"fr"
		};

	// Perform unit test for 'getLanguageCode' method.

		for( size_t index = 0; index < ARRAY_SIZE( testValues ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], Utility::getLanguageCode( testValues[ index ] ) );
		}
}

TEST( UtilityTest, GetCountryCodeWorks )
{
	// Create local variables.

		string testValues[] = {
			"United States",
			"Japan",
			"Russia",
			"Spain",
			"France"
		};

		string expectedResults[] = {
			"US",
			"JP",
			"RU",
			"ES",
			"FR"
		};

	// Perform unit test for 'getCountryCode' method.

		for( size_t index = 0; index < ARRAY_SIZE( testValues ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], Utility::getCountryCode( testValues[ index ] ) );
		}
}

TEST( UtilityTest, GenerateLocaleWorks )
{
	// Create local variables.

		vector< Utility::LocaleData > testValues;
		locale testLocale;

	// Perform unit test for 'generateLocale' method.

		testValues.push_back( { "en_US.UTF-8@currency=USD", "en", "US", "utf-8", "currency=usd" } );
		testValues.push_back( { "fr_CA.UTF-16@currency=CAD", "fr", "CA", "utf-16", "currency=cad" } );
		testValues.push_back( { "es_ES.UTF-32@currency=EUR", "es", "ES", "utf-32", "currency=eur" } );
		testValues.push_back( { "sw_MZ.UTF-8@currency=MZN", "sw", "MZ", "utf-8", "currency=mzn" } );
		testValues.push_back( { "ja_JP.UTF-16@currency=JPY", "ja", "JP", "utf-16", "currency=jpy" } );

		for( const auto& index : testValues )
		{
			testLocale = Utility::generateLocale( index.name );
			ASSERT_EQ( index.name, use_facet< boost::locale::info >( testLocale ).name() );
			ASSERT_EQ( index.language, use_facet< boost::locale::info >( testLocale ).language() );
			ASSERT_EQ( index.country, use_facet< boost::locale::info >( testLocale ).country() );
			ASSERT_EQ( index.encoding, use_facet< boost::locale::info >( testLocale ).encoding() );
			ASSERT_EQ( index.variant, use_facet< boost::locale::info >( testLocale ).variant() );
		}
}

TEST( UtilityTest, GetLocaleDataWorks )
{
	// Create local variables.

		string testValues[] = {
			"en_US.UTF-8@currency=USD",
		   "fr_CA.UTF-16@currency=CAD",
		   "es_ES.UTF-32@currency=EUR",
		   "sw_MZ.UTF-8@currency=MZN",
		   "ja_JP.UTF-16@currency=JPY"
		};

		locale testLocale;
		Utility::LocaleData testData;
		vector< Utility::LocaleData > expectedResults;

	// Perform unit test for 'getLocaleData' method.

		expectedResults.push_back( { "en_US.UTF-8@currency=USD", "en", "US", "utf-8", "currency=usd" } );
		expectedResults.push_back( { "fr_CA.UTF-16@currency=CAD", "fr", "CA", "utf-16", "currency=cad" } );
		expectedResults.push_back( { "es_ES.UTF-32@currency=EUR", "es", "ES", "utf-32", "currency=eur" } );
		expectedResults.push_back( { "sw_MZ.UTF-8@currency=MZN", "sw", "MZ", "utf-8", "currency=mzn" } );
		expectedResults.push_back( { "ja_JP.UTF-16@currency=JPY", "ja", "JP", "utf-16", "currency=jpy" } );

		for( size_t index = 0; index < ARRAY_SIZE( testValues ); index++ )
		{
			testLocale = Utility::generateLocale( testValues[ index ] );
			Utility::getLocaleData( testData, testLocale );
			ASSERT_EQ( expectedResults[ index ].name, testData.name );
			ASSERT_EQ( expectedResults[ index ].language, testData.language );
			ASSERT_EQ( expectedResults[ index ].country, testData.country );
			ASSERT_EQ( expectedResults[ index ].encoding, testData.encoding );
			ASSERT_EQ( expectedResults[ index ].variant, testData.variant );
		}
}

TEST( UtilityTest, TimeStampWorks )
{
	// Create local variables.

		string testTimeStamp = Utility::timeStamp();
		time_t currentTime = time( nullptr );
		tm* systemTime = localtime( &currentTime );

	// Perform unit test for 'timeStamp' method.

		ASSERT_EQ( systemTime->tm_hour, String::toValue< int >( testTimeStamp.substr( 0, 2 ) ) );
		ASSERT_EQ( systemTime->tm_min, String::toValue< int >( testTimeStamp.substr( 3, 2 ) ) );
		ASSERT_EQ( systemTime->tm_sec, String::toValue< int >( testTimeStamp.substr( 6, 2 ) ) );
}

TEST( UtilityTest, PauseWorks )
{
	// Create local variables.

		time_t baseTime = UNSET;
		time_t currentTime = UNSET;

	// Perform unit test for 'pause' method.

		baseTime = time( nullptr );
		Utility::pause( 1000.0, Timer::MILLISECONDS );
		currentTime = time( nullptr );
		ASSERT_NEAR( 1, ( currentTime - baseTime ), 1 );
		baseTime = time( nullptr );
		Utility::pause( 1.0, Timer::SECONDS );
		currentTime = time( nullptr );
		ASSERT_NEAR( 1, ( currentTime - baseTime ), 1 );
		baseTime = time( nullptr );
		Utility::pause( 0.01667, Timer::MINUTES );
		currentTime = time( nullptr );
		ASSERT_NEAR( 1, ( currentTime - baseTime ), 1 );
		baseTime = time( nullptr );
		Utility::pause( 0.0002778, Timer::HOURS );
		currentTime = time( nullptr );
		ASSERT_NEAR( 1, ( currentTime - baseTime ), 1 );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'UtilityTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

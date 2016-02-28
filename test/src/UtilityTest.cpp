////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UtilityTest.cpp
// Robert M. Baker | Created : 22FEB12 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.1
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::Utility' class.
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

		Utility::VersionData Version = Utility::GetVersionNumber();

	// Perform unit test for 'GerVersionNumber' method.

		ASSERT_EQ( QMXSTDLIB_VER_MAJOR, Version.Major );
		ASSERT_EQ( QMXSTDLIB_VER_MINOR, Version.Minor );
		ASSERT_EQ( QMXSTDLIB_VER_PATCH, Version.Patch );
}

TEST( UtilityTest, GetVersionStringWorks )
{
	// Create local variables.

		ostringstream ExpectedResult;

	// Perform unit test for 'GerVersionString' method.

		ExpectedResult << QMXSTDLIB_VER_MAJOR << '.' << QMXSTDLIB_VER_MINOR << '.' << QMXSTDLIB_VER_PATCH;
		ASSERT_EQ( ExpectedResult.str(), Utility::GetVersionString() );
}

TEST( UtilityTest, GetLanguageCodeWorks )
{
	// Create local variables.

		string TestValues[] = { "English", "Japanese", "Russian", "Spanish", "French" };
		string ExpectedResults[] = { "en", "ja", "ru", "es", "fr" };

	// Perform unit test for 'GetLanguageCode' method.

		for( size_t Index = 0; Index < ARRAY_SIZE( TestValues ); Index++ )
		{
			ASSERT_EQ( ExpectedResults[ Index ], Utility::GetLanguageCode( TestValues[ Index ] ) );
		}
}

TEST( UtilityTest, GetCountryCodeWorks )
{
	// Create local variables.

		string TestValues[] = { "United States", "Japan", "Russia", "Spain", "France" };
		string ExpectedResults[] = { "US", "JP", "RU", "ES", "FR" };

	// Perform unit test for 'GetCountryCode' method.

		for( size_t Index = 0; Index < ARRAY_SIZE( TestValues ); Index++ )
		{
			ASSERT_EQ( ExpectedResults[ Index ], Utility::GetCountryCode( TestValues[ Index ] ) );
		}
}

TEST( UtilityTest, GenerateLocaleWorks )
{
	// Create local variables.

		vector< Utility::LocaleData > TestValues;
		locale TestLocale;

	// Perform unit test for 'GenerateLocale' method.

		TestValues.push_back( { "en_US.UTF-8@currency=USD", "en", "US", "utf-8", "currency=usd" } );
		TestValues.push_back( { "fr_CA.UTF-16@currency=CAD", "fr", "CA", "utf-16", "currency=cad" } );
		TestValues.push_back( { "es_ES.UTF-32@currency=EUR", "es", "ES", "utf-32", "currency=eur" } );
		TestValues.push_back( { "sw_MZ.UTF-8@currency=MZN", "sw", "MZ", "utf-8", "currency=mzn" } );
		TestValues.push_back( { "ja_JP.UTF-16@currency=JPY", "ja", "JP", "utf-16", "currency=jpy" } );

		for( const auto& Index : TestValues )
		{
			TestLocale = Utility::GenerateLocale( Index.Name );
			ASSERT_EQ( Index.Name, use_facet< boost::locale::info >( TestLocale ).name() );
			ASSERT_EQ( Index.Language, use_facet< boost::locale::info >( TestLocale ).language() );
			ASSERT_EQ( Index.Country, use_facet< boost::locale::info >( TestLocale ).country() );
			ASSERT_EQ( Index.Encoding, use_facet< boost::locale::info >( TestLocale ).encoding() );
			ASSERT_EQ( Index.Variant, use_facet< boost::locale::info >( TestLocale ).variant() );
		}
}

TEST( UtilityTest, GetLocaleDataWorks )
{
	// Create local variables.

		string TestValues[] = { "en_US.UTF-8@currency=USD",
		                        "fr_CA.UTF-16@currency=CAD",
		                        "es_ES.UTF-32@currency=EUR",
		                        "sw_MZ.UTF-8@currency=MZN",
		                        "ja_JP.UTF-16@currency=JPY" };
		locale TestLocale;
		Utility::LocaleData TestData;
		vector< Utility::LocaleData > ExpectedResults;

	// Perform unit test for 'GetLocaleData' method.

		ExpectedResults.push_back( { "en_US.UTF-8@currency=USD", "en", "US", "utf-8", "currency=usd" } );
		ExpectedResults.push_back( { "fr_CA.UTF-16@currency=CAD", "fr", "CA", "utf-16", "currency=cad" } );
		ExpectedResults.push_back( { "es_ES.UTF-32@currency=EUR", "es", "ES", "utf-32", "currency=eur" } );
		ExpectedResults.push_back( { "sw_MZ.UTF-8@currency=MZN", "sw", "MZ", "utf-8", "currency=mzn" } );
		ExpectedResults.push_back( { "ja_JP.UTF-16@currency=JPY", "ja", "JP", "utf-16", "currency=jpy" } );

		for( size_t Index = 0; Index < ARRAY_SIZE( TestValues ); Index++ )
		{
			TestLocale = Utility::GenerateLocale( TestValues[ Index ] );
			Utility::GetLocaleData( TestData, TestLocale );
			ASSERT_EQ( ExpectedResults[ Index ].Name, TestData.Name );
			ASSERT_EQ( ExpectedResults[ Index ].Language, TestData.Language );
			ASSERT_EQ( ExpectedResults[ Index ].Country, TestData.Country );
			ASSERT_EQ( ExpectedResults[ Index ].Encoding, TestData.Encoding );
			ASSERT_EQ( ExpectedResults[ Index ].Variant, TestData.Variant );
		}
}

TEST( UtilityTest, TimeStampWorks )
{
	// Create local variables.

		string TestTimeStamp = Utility::TimeStamp();
		time_t CurrentTime = time( nullptr );
		tm* SystemTime = localtime( &CurrentTime );

	// Perform unit test for 'TimeStamp' method.

		ASSERT_EQ( SystemTime->tm_hour, String::ToValue< int >( TestTimeStamp.substr( 0, 2 ) ) );
		ASSERT_EQ( SystemTime->tm_min, String::ToValue< int >( TestTimeStamp.substr( 3, 2 ) ) );
		ASSERT_EQ( SystemTime->tm_sec, String::ToValue< int >( TestTimeStamp.substr( 6, 2 ) ) );
}

TEST( UtilityTest, PauseWorks )
{
	// Create local variables.

		time_t BaseTime = Null;
		time_t CurrentTime = Null;

	// Perform unit test for 'Pause' method.

		BaseTime = time( nullptr );
		Utility::Pause( 1000.0, Timer::Milliseconds );
		CurrentTime = time( nullptr );
		ASSERT_NEAR( 1, ( CurrentTime - BaseTime ), 1 );
		BaseTime = time( nullptr );
		Utility::Pause( 1.0, Timer::Seconds );
		CurrentTime = time( nullptr );
		ASSERT_NEAR( 1, ( CurrentTime - BaseTime ), 1 );
		BaseTime = time( nullptr );
		Utility::Pause( 0.01667, Timer::Minutes );
		CurrentTime = time( nullptr );
		ASSERT_NEAR( 1, ( CurrentTime - BaseTime ), 1 );
		BaseTime = time( nullptr );
		Utility::Pause( 0.0002778, Timer::Hours );
		CurrentTime = time( nullptr );
		ASSERT_NEAR( 1, ( CurrentTime - BaseTime ), 1 );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'UtilityTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

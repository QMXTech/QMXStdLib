////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StringTest.cpp
// Robert M. Baker | Created : 20FEB12 | Last Modified : 31AUG19 by Robert M. Baker
// Version : 2.1.0
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::String' functions.
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

#include "../include/StringTest.hpp"

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::String' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( StringTest, ToUTF8FromUTF16Works )
{
	// Create local variables.

		u16string testValues[] = {
			u"βετα/ΒΕΤΑ : beta/BETA",
		   u"This is a string of text (1).",
		   u"This is a string of text (2).",
		   u"This is a string of text (3).",
		   u"This is a string of text (4)."
		};

		string expectedResults[] = {
			u8"βετα/ΒΕΤΑ : beta/BETA",
		   u8"This is a string of text (1).",
		   u8"This is a string of text (2).",
		   u8"This is a string of text (3).",
		   u8"This is a string of text (4)."
		};

	// Perform unit test for 'toUTF8' function accepting a UTF-16 string.

		for( size_t index = 0; index < ARRAY_SIZE( testValues ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], String::toUTF8( testValues[ index ] ) );
		}
}

TEST( StringTest, ToUTF8FromUTF32Works )
{
	// Create local variables.

		u32string testValues[] = {
			U"βετα/ΒΕΤΑ : beta/BETA",
		   U"This is a string of text (1).",
		   U"This is a string of text (2).",
		   U"This is a string of text (3).",
		   U"This is a string of text (4)."
		};

		string expectedResults[] = {
			u8"βετα/ΒΕΤΑ : beta/BETA",
		   u8"This is a string of text (1).",
		   u8"This is a string of text (2).",
		   u8"This is a string of text (3).",
		   u8"This is a string of text (4)."
		};

	// Perform unit test for 'toUTF8' function accepting a UTF-32 string.

		for( size_t index = 0; index < ARRAY_SIZE( testValues ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], String::toUTF8( testValues[ index ] ) );
		}
}

TEST( StringTest, ToUTF16Works )
{
	// Create local variables.

		string testValues[] = {
			u8"βετα/ΒΕΤΑ : beta/BETA",
		   u8"This is a string of text (1).",
		   u8"This is a string of text (2).",
		   u8"This is a string of text (3).",
		   u8"This is a string of text (4)."
		};

		u16string expectedResults[] = {
			u"βετα/ΒΕΤΑ : beta/BETA",
		   u"This is a string of text (1).",
		   u"This is a string of text (2).",
		   u"This is a string of text (3).",
		   u"This is a string of text (4)."
		};

	// Perform unit test for 'toUTF16' function.

		for( size_t index = 0; index < ARRAY_SIZE( testValues ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], String::toUTF16( testValues[ index ] ) );
		}
}

TEST( StringTest, ToUTF32Works )
{
	// Create local variables.

		string testValues[] = {
			u8"βετα/ΒΕΤΑ : beta/BETA",
		   u8"This is a string of text (1).",
		   u8"This is a string of text (2).",
		   u8"This is a string of text (3).",
		   u8"This is a string of text (4)."
		};

		u32string expectedResults[] = {
			U"βετα/ΒΕΤΑ : beta/BETA",
		   U"This is a string of text (1).",
		   U"This is a string of text (2).",
		   U"This is a string of text (3).",
		   U"This is a string of text (4)."
		};

	// Perform unit test for 'toUTF32' function.

		for( size_t index = 0; index < ARRAY_SIZE( testValues ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], String::toUTF32( testValues[ index ] ) );
		}
}

TEST( StringTest, IsAllWhitespaceWorks )
{
	// Perform unit test for 'isAllWhitespace' function.

		ASSERT_TRUE( String::isAllWhitespace( " \t\n\v\f\r" ) );
		ASSERT_FALSE( String::isAllWhitespace( "     Text" ) );
}

TEST( StringTest, StripWorks )
{
	// Create local variables.

		string testValue = "How now brown cow!";

	// Perform unit test for 'strip' function.

		ASSERT_EQ( string( "How now brown cow!" ), String::strip( testValue, "xyzzy" ) );
		ASSERT_EQ( string( "How now brown cow!" ), testValue );
		ASSERT_EQ( string( "How now brown cow!" ), String::strip( testValue, "xyzzy", true ) );
		ASSERT_EQ( string( "How now brown cow!" ), testValue );
		ASSERT_EQ( string( "Hw nw brwn cw!" ), String::strip( testValue, "o" ) );
		ASSERT_EQ( string( "How now brown cow!" ), testValue );
		ASSERT_EQ( string( "Hw nw brwn cw!" ), String::strip( testValue, "o", true ) );
		ASSERT_EQ( string( "Hw nw brwn cw!" ), testValue );
}

TEST( StringTest, ToUpperWorks )
{
	// Create local variables.

		string testValue = u8"βετα/ΒΕΤΑ : beta/BETA";
		boost::locale::generator localeGenerator;

	// Set global locale.

		locale::global( localeGenerator( "en_US.UTF-8" ) );

	// Perform unit test for 'toUpper' function.

		ASSERT_EQ( string( u8"ΒΕΤΑ/ΒΕΤΑ : BETA/BETA" ), String::toUpper( testValue ) );
		ASSERT_EQ( string( u8"βετα/ΒΕΤΑ : beta/BETA" ), testValue );
		ASSERT_EQ( string( u8"ΒΕΤΑ/ΒΕΤΑ : BETA/BETA" ), String::toUpper( testValue, true ) );
		ASSERT_EQ( string( u8"ΒΕΤΑ/ΒΕΤΑ : BETA/BETA" ), testValue );
}

TEST( StringTest, ToLowerWorks )
{
	// Create local variables.

		string testValue = u8"βετα/ΒΕΤΑ : beta/BETA";
		boost::locale::generator localeGenerator;

	// Set global locale.

		locale::global( localeGenerator( "en_US.UTF-8" ) );

	// Perform unit test for 'toLower' function.

		ASSERT_EQ( string( u8"βετα/βετα : beta/beta" ), String::toLower( testValue ) );
		ASSERT_EQ( string( u8"βετα/ΒΕΤΑ : beta/BETA" ), testValue );
		ASSERT_EQ( string( u8"βετα/βετα : beta/beta" ), String::toLower( testValue, true ) );
		ASSERT_EQ( string( u8"βετα/βετα : beta/beta" ), testValue );
}

TEST( StringTest, FindReplaceWorks )
{
	// Create local variables.

		string testValue = "Things#without#all#remedy#should#be#without#regard.";

	// Perform unit test for 'findReplace' function.

		ASSERT_EQ( string( "Things#without#all#remedy#should#be#without#regard." ), String::findReplace( testValue, " ", "#" ) );
		ASSERT_EQ( string( "Things#without#all#remedy#should#be#without#regard." ), testValue );
		ASSERT_EQ( string( "Things#without#all#remedy#should#be#without#regard." ), String::findReplace( testValue, " ", "#", true ) );
		ASSERT_EQ( string( "Things#without#all#remedy#should#be#without#regard." ), testValue );
		ASSERT_EQ( string( "Things without all remedy should be without regard." ), String::findReplace( testValue, "#", " " ) );
		ASSERT_EQ( string( "Things#without#all#remedy#should#be#without#regard." ), testValue );
		ASSERT_EQ( string( "Things without all remedy should be without regard." ), String::findReplace( testValue, "#", " ", true ) );
		ASSERT_EQ( string( "Things without all remedy should be without regard." ), testValue );
}

TEST( StringTest, TokenizeWorks )
{
	// Create local variables.

		StringDeque tokens;

	// Perform unit test for 'tokenize' function.

		String::tokenize( tokens, "Bitches \t \v love \t \f smiley \n \r faces!" );
		ASSERT_EQ( string( "Bitches" ), tokens[ 0 ] );
		ASSERT_EQ( string( "love" ), tokens[ 1 ] );
		ASSERT_EQ( string( "smiley" ), tokens[ 2 ] );
		ASSERT_EQ( string( "faces!" ), tokens[ 3 ] );
}

TEST( StringTest, ToValueWorks )
{
	// Perform unit test for 'ToValue' function.

		ASSERT_TRUE( String::toValue< bool >( "true" ) );
		ASSERT_TRUE( String::toValue< bool >( "yes" ) );
		ASSERT_FALSE( String::toValue< bool >( "false" ) );
		ASSERT_FALSE( String::toValue< bool >( "no" ) );
		ASSERT_FALSE( String::toValue< bool >( "xyzzy" ) );
		ASSERT_EQ( -1337, String::toValue< int >( "-1337" ) );
		ASSERT_EQ( numeric_limits< int8_t >::min(), String::toValue< int16_t >( "-128" ) );
		ASSERT_EQ( numeric_limits< int8_t >::max(), String::toValue< int16_t >( "127" ) );
		ASSERT_EQ( numeric_limits< int8_t >::min(), String::toValue< int8_t >( "0b10000000", Stringizable::BINARY ) );
		ASSERT_EQ( numeric_limits< int8_t >::max(), String::toValue< int8_t >( "0b01111111", Stringizable::BINARY ) );
		ASSERT_EQ( numeric_limits< int8_t >::min(), String::toValue< int16_t >( "-0200", Stringizable::OCTAL ) );
		ASSERT_EQ( numeric_limits< int8_t >::max(), String::toValue< int16_t >( "0177", Stringizable::OCTAL ) );
		ASSERT_EQ( numeric_limits< int8_t >::min(), String::toValue< int16_t >( "-0x80", Stringizable::HEXIDECIMAL ) );
		ASSERT_EQ( numeric_limits< int8_t >::max(), String::toValue< int16_t >( "0x7F", Stringizable::HEXIDECIMAL ) );
		ASSERT_EQ( numeric_limits< int16_t >::min(), String::toValue< int16_t >( "-32768" ) );
		ASSERT_EQ( numeric_limits< int16_t >::max(), String::toValue< int16_t >( "32767" ) );
		ASSERT_EQ( numeric_limits< int16_t >::min(), String::toValue< int16_t >( "0b1000000000000000", Stringizable::BINARY ) );
		ASSERT_EQ( numeric_limits< int16_t >::max(), String::toValue< int16_t >( "0b0111111111111111", Stringizable::BINARY ) );
		ASSERT_EQ( numeric_limits< int16_t >::min(), String::toValue< int16_t >( "-0100000", Stringizable::OCTAL ) );
		ASSERT_EQ( numeric_limits< int16_t >::max(), String::toValue< int16_t >( "077777", Stringizable::OCTAL ) );
		ASSERT_EQ( numeric_limits< int16_t >::min(), String::toValue< int16_t >( "-0x8000", Stringizable::HEXIDECIMAL ) );
		ASSERT_EQ( numeric_limits< int16_t >::max(), String::toValue< int16_t >( "0x7FFF", Stringizable::HEXIDECIMAL ) );
		ASSERT_EQ( numeric_limits< int32_t >::min(), String::toValue< int32_t >( "-2147483648" ) );
		ASSERT_EQ( numeric_limits< int32_t >::max(), String::toValue< int32_t >( "2147483647" ) );
		ASSERT_EQ( numeric_limits< int32_t >::min(), String::toValue< int32_t >( "0b10000000000000000000000000000000", Stringizable::BINARY ) );
		ASSERT_EQ( numeric_limits< int32_t >::max(), String::toValue< int32_t >( "0b01111111111111111111111111111111", Stringizable::BINARY ) );
		ASSERT_EQ( numeric_limits< int32_t >::min(), String::toValue< int32_t >( "-020000000000", Stringizable::OCTAL ) );
		ASSERT_EQ( numeric_limits< int32_t >::max(), String::toValue< int32_t >( "017777777777", Stringizable::OCTAL ) );
		ASSERT_EQ( numeric_limits< int32_t >::min(), String::toValue< int32_t >( "-0x80000000", Stringizable::HEXIDECIMAL ) );
		ASSERT_EQ( numeric_limits< int32_t >::max(), String::toValue< int32_t >( "0x7FFFFFFF", Stringizable::HEXIDECIMAL ) );
		ASSERT_EQ( numeric_limits< int64_t >::min(), String::toValue< int64_t >( "-9223372036854775808" ) );
		ASSERT_EQ( numeric_limits< int64_t >::max(), String::toValue< int64_t >( "9223372036854775807" ) );
		ASSERT_EQ( numeric_limits< int64_t >::min(), String::toValue< int64_t >( "0b1000000000000000000000000000000000000000000000000000000000000000", Stringizable::BINARY ) );
		ASSERT_EQ( numeric_limits< int64_t >::max(), String::toValue< int64_t >( "0b0111111111111111111111111111111111111111111111111111111111111111", Stringizable::BINARY ) );
		ASSERT_EQ( numeric_limits< int64_t >::min(), String::toValue< int64_t >( "-01000000000000000000000", Stringizable::OCTAL ) );
		ASSERT_EQ( numeric_limits< int64_t >::max(), String::toValue< int64_t >( "0777777777777777777777", Stringizable::OCTAL ) );
		ASSERT_EQ( numeric_limits< int64_t >::min(), String::toValue< int64_t >( "-0x8000000000000000", Stringizable::HEXIDECIMAL ) );
		ASSERT_EQ( numeric_limits< int64_t >::max(), String::toValue< int64_t >( "0x7FFFFFFFFFFFFFFF", Stringizable::HEXIDECIMAL ) );
		ASSERT_EQ( numeric_limits< uint8_t >::min(), String::toValue< uint16_t >( "0" ) );
		ASSERT_EQ( numeric_limits< uint8_t >::max(), String::toValue< uint16_t >( "255" ) );
		ASSERT_EQ( numeric_limits< uint8_t >::min(), String::toValue< uint8_t >( "0b00000000", Stringizable::BINARY ) );
		ASSERT_EQ( numeric_limits< uint8_t >::max(), String::toValue< uint8_t >( "0b11111111", Stringizable::BINARY ) );
		ASSERT_EQ( numeric_limits< uint8_t >::min(), String::toValue< uint16_t >( "00", Stringizable::OCTAL ) );
		ASSERT_EQ( numeric_limits< uint8_t >::max(), String::toValue< uint16_t >( "0377", Stringizable::OCTAL ) );
		ASSERT_EQ( numeric_limits< uint8_t >::min(), String::toValue< uint16_t >( "0x0", Stringizable::HEXIDECIMAL ) );
		ASSERT_EQ( numeric_limits< uint8_t >::max(), String::toValue< uint16_t >( "0xFF", Stringizable::HEXIDECIMAL ) );
		ASSERT_EQ( numeric_limits< uint16_t >::min(), String::toValue< uint16_t >( "0" ) );
		ASSERT_EQ( numeric_limits< uint16_t >::max(), String::toValue< uint16_t >( "65535" ) );
		ASSERT_EQ( numeric_limits< uint16_t >::min(), String::toValue< uint16_t >( "0b0000000000000000", Stringizable::BINARY ) );
		ASSERT_EQ( numeric_limits< uint16_t >::max(), String::toValue< uint16_t >( "0b1111111111111111", Stringizable::BINARY ) );
		ASSERT_EQ( numeric_limits< uint16_t >::min(), String::toValue< uint16_t >( "00", Stringizable::OCTAL ) );
		ASSERT_EQ( numeric_limits< uint16_t >::max(), String::toValue< uint16_t >( "0177777", Stringizable::OCTAL ) );
		ASSERT_EQ( numeric_limits< uint16_t >::min(), String::toValue< uint16_t >( "0x0", Stringizable::HEXIDECIMAL ) );
		ASSERT_EQ( numeric_limits< uint16_t >::max(), String::toValue< uint16_t >( "0xFFFF", Stringizable::HEXIDECIMAL ) );
		ASSERT_EQ( numeric_limits< uint32_t >::min(), String::toValue< uint32_t >( "0" ) );
		ASSERT_EQ( numeric_limits< uint32_t >::max(), String::toValue< uint32_t >( "4294967295" ) );
		ASSERT_EQ( numeric_limits< uint32_t >::min(), String::toValue< uint32_t >( "0b00000000000000000000000000000000", Stringizable::BINARY ) );
		ASSERT_EQ( numeric_limits< uint32_t >::max(), String::toValue< uint32_t >( "0b11111111111111111111111111111111", Stringizable::BINARY ) );
		ASSERT_EQ( numeric_limits< uint32_t >::min(), String::toValue< uint32_t >( "00", Stringizable::OCTAL ) );
		ASSERT_EQ( numeric_limits< uint32_t >::max(), String::toValue< uint32_t >( "037777777777", Stringizable::OCTAL ) );
		ASSERT_EQ( numeric_limits< uint32_t >::min(), String::toValue< uint32_t >( "0x0", Stringizable::HEXIDECIMAL ) );
		ASSERT_EQ( numeric_limits< uint32_t >::max(), String::toValue< uint32_t >( "0xFFFFFFFF", Stringizable::HEXIDECIMAL ) );
		ASSERT_EQ( numeric_limits< uint64_t >::min(), String::toValue< uint64_t >( "0" ) );
		ASSERT_EQ( numeric_limits< uint64_t >::max(), String::toValue< uint64_t >( "18446744073709551615" ) );
		ASSERT_EQ( numeric_limits< uint64_t >::min(), String::toValue< uint64_t >( "0b0000000000000000000000000000000000000000000000000000000000000000", Stringizable::BINARY ) );
		ASSERT_EQ( numeric_limits< uint64_t >::max(), String::toValue< uint64_t >( "0b1111111111111111111111111111111111111111111111111111111111111111", Stringizable::BINARY ) );
		ASSERT_EQ( numeric_limits< uint64_t >::min(), String::toValue< uint64_t >( "00", Stringizable::OCTAL ) );
		ASSERT_EQ( numeric_limits< uint64_t >::max(), String::toValue< uint64_t >( "01777777777777777777777", Stringizable::OCTAL ) );
		ASSERT_EQ( numeric_limits< uint64_t >::min(), String::toValue< uint64_t >( "0x0", Stringizable::HEXIDECIMAL ) );
		ASSERT_EQ( numeric_limits< uint64_t >::max(), String::toValue< uint64_t >( "0xFFFFFFFFFFFFFFFF", Stringizable::HEXIDECIMAL ) );
		ASSERT_FLOAT_EQ( 2.71828f, String::toValue< float >( "2.71828" ) );
		ASSERT_DOUBLE_EQ( 3.14159, String::toValue< double >( "3.14159" ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'StringTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

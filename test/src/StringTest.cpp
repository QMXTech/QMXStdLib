////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StringTest.cpp
// Robert M. Baker | Created : 20FEB12 | Last Modified : 21FEB16 by Robert M. Baker
// Version : 1.1.0
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::String' functions.
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

#include <StringTest.hpp>

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::String' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( StringTest, ToUTF8FromUTF16Works )
{
	// TODO (Malachy - Priority 50): Complete once GCC becomes C++11 compliant.
	// Create local variables.

		/*
		u16string TestValues[] = { u"This is a string of text (1).",
		                           u"This is a string of text (2).",
		                           u"This is a string of text (3).",
		                           u"This is a string of text (4).",
		                           u"This is a string of text (5)." };
		string ExpectedResults[] = { u8"This is a string of text (1).",
		                             u8"This is a string of text (2).",
		                             u8"This is a string of text (3).",
		                             u8"This is a string of text (4).",
		                             u8"This is a string of text (5)." };
		*/

	// Perform unit test for 'ToUTF8' function accepting a UTF-16 string.

		/* Stub */
}

TEST( StringTest, ToUTF8FromUTF32Works )
{
	// TODO (Malachy - Priority 50): Complete once GCC becomes C++11 compliant.
	// Create local variables.

		/*
		u32string TestValues[] = { U"This is a string of text (1).",
		                           U"This is a string of text (2).",
		                           U"This is a string of text (3).",
		                           U"This is a string of text (4).",
		                           U"This is a string of text (5)." };
		string ExpectedResults[] = { u8"This is a string of text (1).",
		                             u8"This is a string of text (2).",
		                             u8"This is a string of text (3).",
		                             u8"This is a string of text (4).",
		                             u8"This is a string of text (5)." };
		*/

	// Perform unit test for 'ToUTF8' function accepting a UTF-32 string.

		/* Stub */
}

TEST( StringTest, ToUTF16Works )
{
	// TODO (Malachy - Priority 50): Complete once GCC becomes C++11 compliant.
	// Create local variables.

		/*
		string TestValues[] = { u8"This is a string of text (1).",
		                        u8"This is a string of text (2).",
		                        u8"This is a string of text (3).",
		                        u8"This is a string of text (4).",
		                        u8"This is a string of text (5)." };
		u16string ExpectedResults[] = { u"This is a string of text (1).",
		                                u"This is a string of text (2).",
		                                u"This is a string of text (3).",
		                                u"This is a string of text (4).",
		                                u"This is a string of text (5)." };
		*/

	// Perform unit test for 'ToUTF16' function.

		/* Stub */
}

TEST( StringTest, ToUTF32Works )
{
	// TODO (Malachy - Priority 50): Complete once GCC becomes C++11 compliant.
	// Create local variables.

		/*
		string TestValues[] = { u8"This is a string of text (1).",
		                        u8"This is a string of text (2).",
		                        u8"This is a string of text (3).",
		                        u8"This is a string of text (4).",
		                        u8"This is a string of text (5)." };
		u32string ExpectedResults[] = { U"This is a string of text (1).",
		                                U"This is a string of text (2).",
		                                U"This is a string of text (3).",
		                                U"This is a string of text (4).",
		                                U"This is a string of text (5)." };
		*/

	// Perform unit test for 'ToUTF32' function.

		/* Stub */
}

TEST( StringTest, IsAllWhitespaceWorks )
{
	// Perform unit test for 'IsAllWhitespace' function.

		ASSERT_TRUE( String::IsAllWhitespace( " \t\n\v\f\r" ) );
		ASSERT_FALSE( String::IsAllWhitespace( "     Text" ) );
}

TEST( StringTest, StripWorks )
{
	// Create local variables.

		string TestValue = "How now brown cow!";

	// Perform unit test for 'Strip' function.

		ASSERT_EQ( string( "How now brown cow!" ), String::Strip( TestValue, "xyzzy" ) );
		ASSERT_EQ( string( "How now brown cow!" ), TestValue );
		ASSERT_EQ( string( "How now brown cow!" ), String::Strip( TestValue, "xyzzy", true ) );
		ASSERT_EQ( string( "How now brown cow!" ), TestValue );
		ASSERT_EQ( string( "Hw nw brwn cw!" ), String::Strip( TestValue, "o" ) );
		ASSERT_EQ( string( "How now brown cow!" ), TestValue );
		ASSERT_EQ( string( "Hw nw brwn cw!" ), String::Strip( TestValue, "o", true ) );
		ASSERT_EQ( string( "Hw nw brwn cw!" ), TestValue );
}

TEST( StringTest, ToUpperWorks )
{
	// Create local variables.

		boost::locale::generator LocaleGenerator;
		string TestValue = u8"βετα/ΒΕΤΑ : beta/BETA";

	// Set global locale.

		locale::global( LocaleGenerator( "en_US.UTF-8" ) );

	// Perform unit test for 'ToUpper' function.

		ASSERT_EQ( string( u8"ΒΕΤΑ/ΒΕΤΑ : BETA/BETA" ), String::ToUpper( TestValue ) );
		ASSERT_EQ( string( u8"βετα/ΒΕΤΑ : beta/BETA" ), TestValue );
		ASSERT_EQ( string( u8"ΒΕΤΑ/ΒΕΤΑ : BETA/BETA" ), String::ToUpper( TestValue, true ) );
		ASSERT_EQ( string( u8"ΒΕΤΑ/ΒΕΤΑ : BETA/BETA" ), TestValue );
}

TEST( StringTest, ToLowerWorks )
{
	// Create local variables.

		boost::locale::generator LocaleGenerator;
		string TestValue = u8"βετα/ΒΕΤΑ : beta/BETA";

	// Set global locale.

		locale::global( LocaleGenerator( "en_US.UTF-8" ) );

	// Perform unit test for 'ToLower' function.

		ASSERT_EQ( string( u8"βετα/βετα : beta/beta" ), String::ToLower( TestValue ) );
		ASSERT_EQ( string( u8"βετα/ΒΕΤΑ : beta/BETA" ), TestValue );
		ASSERT_EQ( string( u8"βετα/βετα : beta/beta" ), String::ToLower( TestValue, true ) );
		ASSERT_EQ( string( u8"βετα/βετα : beta/beta" ), TestValue );
}

TEST( StringTest, FindReplaceWorks )
{
	// Create local variables.

		string TestValue = "Things#without#all#remedy#should#be#without#regard.";

	// Perform unit test for 'FindReplace' function.

		ASSERT_EQ( string( "Things#without#all#remedy#should#be#without#regard." ), String::FindReplace( TestValue, " ", "#" ) );
		ASSERT_EQ( string( "Things#without#all#remedy#should#be#without#regard." ), TestValue );
		ASSERT_EQ( string( "Things#without#all#remedy#should#be#without#regard." ), String::FindReplace( TestValue, " ", "#", true ) );
		ASSERT_EQ( string( "Things#without#all#remedy#should#be#without#regard." ), TestValue );
		ASSERT_EQ( string( "Things without all remedy should be without regard." ), String::FindReplace( TestValue, "#", " " ) );
		ASSERT_EQ( string( "Things#without#all#remedy#should#be#without#regard." ), TestValue );
		ASSERT_EQ( string( "Things without all remedy should be without regard." ), String::FindReplace( TestValue, "#", " ", true ) );
		ASSERT_EQ( string( "Things without all remedy should be without regard." ), TestValue );
}

TEST( StringTest, TokenizeWorks )
{
	// Create local variables.

		StringDeque Tokens;

	// Perform unit test for 'Tokenize' function.

		String::Tokenize( Tokens, "Bitches \t \v love \t \f smiley \n \r faces!" );
		ASSERT_EQ( string( "Bitches" ), Tokens[ 0 ] );
		ASSERT_EQ( string( "love" ), Tokens[ 1 ] );
		ASSERT_EQ( string( "smiley" ), Tokens[ 2 ] );
		ASSERT_EQ( string( "faces!" ), Tokens[ 3 ] );
}

TEST( StringTest, ToValueWorks )
{
	// Perform unit test for 'ToValue' function.

		ASSERT_TRUE( String::ToValue< bool >( "true" ) );
		ASSERT_TRUE( String::ToValue< bool >( "yes" ) );
		ASSERT_FALSE( String::ToValue< bool >( "false" ) );
		ASSERT_FALSE( String::ToValue< bool >( "no" ) );
		ASSERT_FALSE( String::ToValue< bool >( "xyzzy" ) );
		ASSERT_EQ( -1337, String::ToValue< int >( "-1337" ) );
		ASSERT_EQ( numeric_limits< int8_t >::min(), String::ToValue< int32_t >( "-128" ) );
		ASSERT_EQ( numeric_limits< int8_t >::max(), String::ToValue< int32_t >( "127" ) );
		ASSERT_EQ( numeric_limits< int8_t >::min(), String::ToValue< int32_t >( "-0200", Stringizable::Octal ) );
		ASSERT_EQ( numeric_limits< int8_t >::max(), String::ToValue< int32_t >( "0177", Stringizable::Octal ) );
		ASSERT_EQ( numeric_limits< int8_t >::min(), String::ToValue< int32_t >( "-0x80", Stringizable::Hexidecimal ) );
		ASSERT_EQ( numeric_limits< int8_t >::max(), String::ToValue< int32_t >( "0x7F", Stringizable::Hexidecimal ) );
		ASSERT_EQ( numeric_limits< int16_t >::min(), String::ToValue< int16_t >( "-32768" ) );
		ASSERT_EQ( numeric_limits< int16_t >::max(), String::ToValue< int16_t >( "32767" ) );
		ASSERT_EQ( numeric_limits< int16_t >::min(), String::ToValue< int16_t >( "-0100000", Stringizable::Octal ) );
		ASSERT_EQ( numeric_limits< int16_t >::max(), String::ToValue< int16_t >( "077777", Stringizable::Octal ) );
		ASSERT_EQ( numeric_limits< int16_t >::min(), String::ToValue< int16_t >( "-0x8000", Stringizable::Hexidecimal ) );
		ASSERT_EQ( numeric_limits< int16_t >::max(), String::ToValue< int16_t >( "0x7FFF", Stringizable::Hexidecimal ) );
		ASSERT_EQ( numeric_limits< int32_t >::min(), String::ToValue< int32_t >( "-2147483648" ) );
		ASSERT_EQ( numeric_limits< int32_t >::max(), String::ToValue< int32_t >( "2147483647" ) );
		ASSERT_EQ( numeric_limits< int32_t >::min(), String::ToValue< int32_t >( "-020000000000", Stringizable::Octal ) );
		ASSERT_EQ( numeric_limits< int32_t >::max(), String::ToValue< int32_t >( "017777777777", Stringizable::Octal ) );
		ASSERT_EQ( numeric_limits< int32_t >::min(), String::ToValue< int32_t >( "-0x80000000", Stringizable::Hexidecimal ) );
		ASSERT_EQ( numeric_limits< int32_t >::max(), String::ToValue< int32_t >( "0x7FFFFFFF", Stringizable::Hexidecimal ) );
		ASSERT_EQ( numeric_limits< int64_t >::min(), String::ToValue< int64_t >( "-9223372036854775808" ) );
		ASSERT_EQ( numeric_limits< int64_t >::max(), String::ToValue< int64_t >( "9223372036854775807" ) );
		ASSERT_EQ( numeric_limits< int64_t >::min(), String::ToValue< int64_t >( "-01000000000000000000000", Stringizable::Octal ) );
		ASSERT_EQ( numeric_limits< int64_t >::max(), String::ToValue< int64_t >( "0777777777777777777777", Stringizable::Octal ) );
		ASSERT_EQ( numeric_limits< int64_t >::min(), String::ToValue< int64_t >( "-0x8000000000000000", Stringizable::Hexidecimal ) );
		ASSERT_EQ( numeric_limits< int64_t >::max(), String::ToValue< int64_t >( "0x7FFFFFFFFFFFFFFF", Stringizable::Hexidecimal ) );
		ASSERT_EQ( numeric_limits< uint8_t >::min(), String::ToValue< int32_t >( "0" ) );
		ASSERT_EQ( numeric_limits< uint8_t >::max(), String::ToValue< int32_t >( "255" ) );
		ASSERT_EQ( numeric_limits< uint8_t >::min(), String::ToValue< int32_t >( "00", Stringizable::Octal ) );
		ASSERT_EQ( numeric_limits< uint8_t >::max(), String::ToValue< int32_t >( "0377", Stringizable::Octal ) );
		ASSERT_EQ( numeric_limits< uint8_t >::min(), String::ToValue< int32_t >( "0x0", Stringizable::Hexidecimal ) );
		ASSERT_EQ( numeric_limits< uint8_t >::max(), String::ToValue< int32_t >( "0xFF", Stringizable::Hexidecimal ) );
		ASSERT_EQ( numeric_limits< uint16_t >::min(), String::ToValue< uint16_t >( "0" ) );
		ASSERT_EQ( numeric_limits< uint16_t >::max(), String::ToValue< uint16_t >( "65535" ) );
		ASSERT_EQ( numeric_limits< uint16_t >::min(), String::ToValue< uint16_t >( "00", Stringizable::Octal ) );
		ASSERT_EQ( numeric_limits< uint16_t >::max(), String::ToValue< uint16_t >( "0177777", Stringizable::Octal ) );
		ASSERT_EQ( numeric_limits< uint16_t >::min(), String::ToValue< uint16_t >( "0x0", Stringizable::Hexidecimal ) );
		ASSERT_EQ( numeric_limits< uint16_t >::max(), String::ToValue< uint16_t >( "0xFFFF", Stringizable::Hexidecimal ) );
		ASSERT_EQ( numeric_limits< uint32_t >::min(), String::ToValue< uint32_t >( "0" ) );
		ASSERT_EQ( numeric_limits< uint32_t >::max(), String::ToValue< uint32_t >( "4294967295" ) );
		ASSERT_EQ( numeric_limits< uint32_t >::min(), String::ToValue< uint32_t >( "00", Stringizable::Octal ) );
		ASSERT_EQ( numeric_limits< uint32_t >::max(), String::ToValue< uint32_t >( "037777777777", Stringizable::Octal ) );
		ASSERT_EQ( numeric_limits< uint32_t >::min(), String::ToValue< uint32_t >( "0x0", Stringizable::Hexidecimal ) );
		ASSERT_EQ( numeric_limits< uint32_t >::max(), String::ToValue< uint32_t >( "0xFFFFFFFF", Stringizable::Hexidecimal ) );
		ASSERT_EQ( numeric_limits< uint64_t >::min(), String::ToValue< uint64_t >( "0" ) );
		ASSERT_EQ( numeric_limits< uint64_t >::max(), String::ToValue< uint64_t >( "18446744073709551615" ) );
		ASSERT_EQ( numeric_limits< uint64_t >::min(), String::ToValue< uint64_t >( "00", Stringizable::Octal ) );
		ASSERT_EQ( numeric_limits< uint64_t >::max(), String::ToValue< uint64_t >( "01777777777777777777777", Stringizable::Octal ) );
		ASSERT_EQ( numeric_limits< uint64_t >::min(), String::ToValue< uint64_t >( "0x0", Stringizable::Hexidecimal ) );
		ASSERT_EQ( numeric_limits< uint64_t >::max(), String::ToValue< uint64_t >( "0xFFFFFFFFFFFFFFFF", Stringizable::Hexidecimal ) );
		ASSERT_FLOAT_EQ( 2.71828f, String::ToValue< float >( "2.71828" ) );
		ASSERT_DOUBLE_EQ( 3.14159, String::ToValue< double >( "3.14159" ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'StringTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

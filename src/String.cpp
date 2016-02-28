////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// String.cpp
// Robert M. Baker | Created : 08JAN15 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.0
// This is a source file for 'QMXStdLib'; it defines the implementation for a set of string utility functions.
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
  * @date    Created : 08JAN15
  * @date    Last Modified : 27FEB16 by Robert M. Baker
  * @version 1.1.0
  *
  * @brief This source file defines the implementation for a set of string utility functions.
  *
  * @section Description
  *
  * This source file defines the implementation for a set of string utility functions.
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../include/String.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'String' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace String
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Definitions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string ToUTF8( const u16string& Target )
{
	// TODO (Malachy - Priority 50): Uncomment once GCC becomes C++11 compliant.
	// Create local variables.

		//wstring_convert< codecvt_utf8_utf16< char16_t >, char16_t > Convert;

	// Return result of converting specified UTF-16 string to a UTF-8 string to calling routine.

		//return Convert.to_bytes( Target );
		return string( u8"" );
}

string ToUTF8( const u32string& Target )
{
	// TODO (Malachy - Priority 50): Uncomment once GCC becomes C++11 compliant.
	// Create local variables.

		//wstring_convert< codecvt_utf8< char32_t >, char32_t > Convert;

	// Return result of converting specified UTF-32 string to a UTF-8 string to calling routine.

		//return Convert.to_bytes( Target );
		return string( u8"" );
}

u16string ToUTF16( const string& Target )
{
	// TODO (Malachy - Priority 50): Uncomment once GCC becomes C++11 compliant.
	// Create local variables.

		//wstring_convert< codecvt_utf8_utf16< char16_t >, char16_t > Convert;

	// Return result of converting specified UTF-8 string to a UTF-16 string to calling routine.

		//return Convert.from_bytes( Target );
		return u16string( u"" );
}

u32string ToUTF32( const string& Target )
{
	// TODO (Malachy - Priority 50): Uncomment once GCC becomes C++11 compliant.
	// Create local variables.

		//wstring_convert< codecvt_utf8< char32_t >, char32_t > Convert;

	// Return result of converting specified UTF-8 string to a UTF-32 string to calling routine.

		//return Convert.from_bytes( Target );
		return u32string( U"" );
}

bool IsAllWhitespace( const string& Target )
{
	// Report whether or not the specified string is all whitespace to calling routine.

		return boost::algorithm::all( Target, boost::algorithm::is_space() );
}

string Strip( string& Target, const string& Substring, bool ModifyTarget )
{
	// Create local variables.

		string Result = boost::algorithm::erase_all_copy( Target, Substring );

	// Modify target string if modify flag is set to 'true'.

		if( ModifyTarget )
			Target = Result;

	// Return result to calling routine.

		return Result;
}

string ToUpper( string& Target, bool ModifyTarget )
{
	// Create local variables.

		string Result = boost::locale::to_upper( Target );

	// Modify target string if modify flag is set to 'true'.

		if( ModifyTarget )
			Target = Result;

	// Return result to calling routine.

		return Result;
}

string ToLower( string& Target, bool ModifyTarget )
{
	// Create local variables.

		string Result = boost::locale::to_lower( Target );

	// Modify target string if modify flag is set to 'true'.

		if( ModifyTarget )
			Target = Result;

	// Return result to calling routine.

		return Result;
}

string FindReplace( string& Target, const string& Find, const string& Replace, bool ModifyTarget )
{
	// Create local variables.

		string Result = boost::algorithm::replace_all_copy( Target, Find, Replace );

	// Modify target string if modify flag is set to 'true'.

		if( ModifyTarget )
			Target = Result;

	// Return result to calling routine.

		return Result;
}

void Tokenize( StringDeque& Tokens, const string& Target )
{
	// Split specified string into tokens.

		boost::algorithm::split( Tokens, Target, boost::algorithm::is_space(), boost::algorithm::token_compress_on );
}

} // 'String' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'String' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'String.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

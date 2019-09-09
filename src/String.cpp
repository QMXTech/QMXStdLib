////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// String.cpp
// Robert M. Baker | Created : 08JAN15 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.2.1
// This is a source file for 'QMXStdLib'; it defines the implementation for a set of string utility functions.
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
  * @date    Created : 08JAN15
  * @date    Last Modified : 29AUG19 by Robert M. Baker
  * @version 2.2.1
  *
  * @brief This source file defines the implementation for a set of string utility functions.
  *
  * @section StringS0000 Description
  *
  * This source file defines the implementation for a set of string utility functions.
  *
  * @section StringS0001 License
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

string toUTF8( const u16string& source )
{
	// Create local variables.

		wstring_convert< codecvt_utf8_utf16< char16_t >, char16_t > convert;

	// Return result of converting specified UTF-16 string to a UTF-8 string to calling routine.

		return convert.to_bytes( source );
}

string toUTF8( const u32string& source )
{
	// Create local variables.

		wstring_convert< codecvt_utf8< char32_t >, char32_t > convert;

	// Return result of converting specified UTF-32 string to a UTF-8 string to calling routine.

		return convert.to_bytes( source );
}

u16string toUTF16( const string& source )
{
	// Create local variables.

		wstring_convert< codecvt_utf8_utf16< char16_t >, char16_t > convert;

	// Return result of converting specified UTF-8 string to a UTF-16 string to calling routine.

		return convert.from_bytes( source );
}

u32string toUTF32( const string& source )
{
	// Create local variables.

		wstring_convert< codecvt_utf8< char32_t >, char32_t > convert;

	// Return result of converting specified UTF-8 string to a UTF-32 string to calling routine.

		return convert.from_bytes( source );
}

bool isAllWhitespace( const string& source )
{
	// Report whether or not the specified string is all whitespace to calling routine.

		return boost::algorithm::all( source, boost::algorithm::is_space() );
}

string strip( string& target, const string& substring, bool modifyTarget )
{
	// Create local variables.

		string result = boost::algorithm::erase_all_copy( target, substring );

	// Modify target string if modify flag is set to 'true'.

		if( modifyTarget )
			target = result;

	// Return result to calling routine.

		return result;
}

string toUpper( string& target, bool modifyTarget )
{
	// Create local variables.

		string result = boost::locale::to_upper( target );

	// Modify target string if modify flag is set to 'true'.

		if( modifyTarget )
			target = result;

	// Return result to calling routine.

		return result;
}

string toLower( string& target, bool modifyTarget )
{
	// Create local variables.

		string result = boost::locale::to_lower( target );

	// Modify target string if modify flag is set to 'true'.

		if( modifyTarget )
			target = result;

	// Return result to calling routine.

		return result;
}

string findReplace( string& target, const string& find, const string& replace, bool modifyTarget )
{
	// Create local variables.

		string result = boost::algorithm::replace_all_copy( target, find, replace );

	// Modify target string if modify flag is set to 'true'.

		if( modifyTarget )
			target = result;

	// Return result to calling routine.

		return result;
}

void tokenize( StringDeque& target, const string& source )
{
	// Split specified string into tokens.

		boost::algorithm::split( target, source, boost::algorithm::is_space(), boost::algorithm::token_compress_on );
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

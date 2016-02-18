////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// String.hpp
// Robert M. Baker | Created : 11JAN12 | Last Modified : 17FEB16 by Robert M. Baker
// Version : 1.0.0
// This is a header file for 'QMXStdLib'; it defines the interface for a set of string utility functions.
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
  * @date    Last Modified : 17FEB16 by Robert M. Baker
  * @version 1.0.0
  *
  * @brief This header file defines the interface for a set of string utility functions.
  *
  * @section Description
  *
  * This header file defines the interface for a set of string utility functions.
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

#ifndef __QMX_QMXSTDLIB_STRING_HPP_
#define __QMX_QMXSTDLIB_STRING_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "Mixins/Stringizable.hpp"
#include "RAII/ScopedStackTrace.hpp"

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

/**
  * @brief This function converts the specified UTF-16 string to a UTF-8 string.
  *
  * @param Target
  * 	This is the UTF-16 string to convert.
  *
  * @return
  * 	A UTF-8 equivalent of the specified UTF-16 string.
  */

std::string ToUTF8( const std::u16string& Target );

/**
  * @brief This function converts the specified UTF-32 string to a UTF-8 string.
  *
  * @param Target
  * 	This is the UTF-32 string to convert.
  *
  * @return
  * 	A UTF-8 equivalent of the specified UTF-32 string.
  */

std::string ToUTF8( const std::u32string& Target );

/**
  * @brief This function converts the specified UTF-8 string to a UTF-16 string.
  *
  * @param Target
  * 	This is the UTF-8 string to convert.
  *
  * @return
  * 	A UTF-16 equivalent of the specified UTF-8 string.
  */

std::u16string ToUTF16( const std::string& Target );

/**
  * @brief This function converts the specified UTF-8 string to a UTF-32 string.
  *
  * @param Target
  * 	This is the UTF-8 string to convert.
  *
  * @return
  * 	A UTF-32 equivalent of the specified UTF-8 string.
  */

std::u32string ToUTF32( const std::string& Target );

/**
  * @brief This function determines if the specified string is all whitepace or not.
  *
  * @param Target
  * 	This is the string to check.
  *
  * @return
  * 	A boolean value of 'true' if the specified string is all whitespace, and 'false' otherwise.
  */

bool IsAllWhiteSpace( const std::string& Target );

/**
  * @brief This function strips all occurrences of the specified substring from the specified string.
  *
  * @param Target
  * 	This is the string from which to strip all occurrences of the specified substring.
  *
  * @param Substring
  * 	This is the substring to strip from the specified string.
  *
  * @param ModifyTarget
  * 	This is a flag that determines if the target string is modified.
  *
  * @return
  * 	The target string with all occurrences of the specified substring stripped.
  */

std::string Strip( std::string& Target, const std::string& Substring, bool ModifyTarget = false );

/**
  * @brief This function converts the specified string too all uppercase.
  *
  * Before using this function, the global locale must be set to a locale generated with 'QMXStdLib::Utility::GenerateLocale'.
  *
  * @param Target
  * 	This is the string to convert to uppercase.
  *
  * @param ModifyTarget
  * 	This is a flag that determines if the target string is modified.
  *
  * @return
  * 	The uppercased version of the target string.
  */

std::string ToUpper( std::string& Target, bool ModifyTarget = false );

/**
  * @brief This function converts the specified string too all lowercase.
  *
  * Before using this function, the global locale must be set to a locale generated with 'QMXStdLib::Utility::GenerateLocale'.
  *
  * @param Target
  * 	This is the string to convert to lowercase.
  *
  * @param ModifyTarget
  * 	This is a flag that determines if the target string is modified.
  *
  * @return
  * 	The lowercased version of the target string.
  */

std::string ToLower( std::string& Target, bool ModifyTarget = false );

/**
  * @brief This function replaces all occurrences of the 'Find' substring with the 'Replace' substring in the specified string.
  *
  * @param Target
  * 	This is the string to use for the find/replace operation.
  *
  * @param Find
  * 	This is the substring for which all occurrences will be replaced.
  *
  * @param Replace
  * 	This is the substring with which to replace all occurrences of the 'Find' substring.
  *
  * @param ModifyTarget
  * 	This is a flag that determines if the target string is modified.
  *
  * @return
  * 	The target string with all occurrences of the specified 'Find' substring replaced with the 'Replace' substring.
  */

std::string FindReplace( std::string& Target, const std::string& Find, const std::string& Replace, bool ModifyTarget = false );

/**
  * @brief This function splits the specified string into tokens.
  *
  * @param Tokens
  * 	This is the string deque into which the tokens are placed.
  *
  * @param Target
  * 	This is the string to split into tokens.
  */

void Tokenize( StringDeque& Tokens, const std::string& Target );

/**
  * @brief This template function defines the structure for a string to numeric value converter.
  *
  * If converting to a boolean value, the string must be exactly (case-sensitive) one of the following: "true", "yes", "false", "no"; otherwise, the value
  * will always be 'false'.  Using an 'NType' of 'int8' or 'uint8' can have undesired results, so it is recommended to substitute 'int32' in those cases.
  *
  * @param Target
  * 	This is the string to convert into a numeric value.
  *
  * @param Base
  * 	This is the numeric base to use during the conversion; if it is out-of-range, it will be set to decimal.
  *
  * @return
  * 	A numeric representation of the specified string.
  */

template< typename NType > NType ToValue( const std::string& Target, Stringizable::NumericBase Base = Stringizable::Decimal )
{
	// Create local variables.

		NType Result = Null;
		std::istringstream Value( Target );

	// Convert the specified string to a numerical value.

		if( typeid( NType ) == typeid( bool ) )
			Result = ( ( Target == "true" ) || ( Target == "yes" ) ) ? true : false;
		else
			Value >> ( ( Base == Stringizable::Octal ) ? std::oct : ( ( Base == Stringizable::Hexidecimal ) ? std::hex : std::dec ) ) >> Result;

	// Return result to calling routine.

		return Result;
}

} // 'String' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'String' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_STRING_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'String.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// String.hpp
// Robert M. Baker | Created : 11JAN12 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.0.0
// This is a header file for 'QMXStdLib'; it defines the interface for a set of string utility functions.
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
  * @date    Last Modified : 29AUG19 by Robert M. Baker
  * @version 2.0.0
  *
  * @brief This header file defines the interface for a set of string utility functions.
  *
  * @section StringH0000 Description
  *
  * This header file defines the interface for a set of string utility functions.
  *
  * @section StringH0001 License
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

#ifndef __QMX_QMXSTDLIB_STRING_HPP_
#define __QMX_QMXSTDLIB_STRING_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <codecvt>
#include <boost/locale.hpp>

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

/**
  * @brief This is the namespace for all string utility functions.
  */

namespace String
{

/**
  * @brief This function converts the specified UTF-16 string to a UTF-8 string.
  *
  * @param source
  * 	This is the UTF-16 string to convert.
  *
  * @return
  * 	A UTF-8 equivalent of the specified UTF-16 string.
  */

std::string toUTF8( const std::u16string& source );

/**
  * @brief This function converts the specified UTF-32 string to a UTF-8 string.
  *
  * @param source
  * 	This is the UTF-32 string to convert.
  *
  * @return
  * 	A UTF-8 equivalent of the specified UTF-32 string.
  */

std::string toUTF8( const std::u32string& source );

/**
  * @brief This function converts the specified UTF-8 string to a UTF-16 string.
  *
  * @param source
  * 	This is the UTF-8 string to convert.
  *
  * @return
  * 	A UTF-16 equivalent of the specified UTF-8 string.
  */

std::u16string toUTF16( const std::string& source );

/**
  * @brief This function converts the specified UTF-8 string to a UTF-32 string.
  *
  * @param source
  * 	This is the UTF-8 string to convert.
  *
  * @return
  * 	A UTF-32 equivalent of the specified UTF-8 string.
  */

std::u32string toUTF32( const std::string& source );

/**
  * @brief This function determines if the specified string is all whitepace or not.
  *
  * @param source
  * 	This is the string to check.
  *
  * @return
  * 	A boolean value of 'true' if the specified string is all whitespace, and 'false' otherwise.
  */

bool isAllWhitespace( const std::string& source );

/**
  * @brief This function strips all occurrences of the specified substring from the specified string.
  *
  * @param target
  * 	This is the string from which to strip all occurrences of the specified substring.
  *
  * @param substring
  * 	This is the substring to strip from the specified string.
  *
  * @param modifyTarget
  * 	This is a flag that determines if the target string is modified.
  *
  * @return
  * 	The target string with all occurrences of the specified substring stripped.
  */

std::string strip( std::string& target, const std::string& substring, bool modifyTarget = false );

/**
  * @brief This function converts the specified string too all uppercase.
  *
  * Before using this function, the global locale must be set to a locale generated with 'QMXStdLib::Utility::GenerateLocale'.
  *
  * @param target
  * 	This is the string to convert to uppercase.
  *
  * @param modifyTarget
  * 	This is a flag that determines if the target string is modified.
  *
  * @return
  * 	The uppercased version of the target string.
  */

std::string toUpper( std::string& target, bool modifyTarget = false );

/**
  * @brief This function converts the specified string too all lowercase.
  *
  * Before using this function, the global locale must be set to a locale generated with 'QMXStdLib::Utility::GenerateLocale'.
  *
  * @param target
  * 	This is the string to convert to lowercase.
  *
  * @param modifyTarget
  * 	This is a flag that determines if the target string is modified.
  *
  * @return
  * 	The lowercased version of the target string.
  */

std::string toLower( std::string& target, bool modifyTarget = false );

/**
  * @brief This function replaces all occurrences of the 'Find' substring with the 'Replace' substring in the specified string.
  *
  * @param target
  * 	This is the string to use for the find/replace operation.
  *
  * @param find
  * 	This is the substring for which all occurrences will be replaced.
  *
  * @param replace
  * 	This is the substring with which to replace all occurrences of the 'Find' substring.
  *
  * @param modifyTarget
  * 	This is a flag that determines if the target string is modified.
  *
  * @return
  * 	The target string with all occurrences of the specified 'Find' substring replaced with the 'Replace' substring.
  */

std::string findReplace( std::string& target, const std::string& find, const std::string& replace, bool modifyTarget = false );

/**
  * @brief This function splits the specified string into tokens.
  *
  * @param target
  * 	This is the string deque into which the tokens are placed.
  *
  * @param source
  * 	This is the string to split into tokens.
  */

void tokenize( StringDeque& target, const std::string& source );

/**
  * @brief This function defines the structure for a string to numeric value converter.
  *
  * If converting to a boolean value, the string must be exactly (case-sensitive) one of the following: "true", "yes", "false", "no"; otherwise, the value
  * will always be 'false'.  Using an 'NType' of 'int8' or 'uint8' can have undesired results, so it is recommended to substitute 'int32' in those cases.
  *
  * @param source
  * 	This is the string to convert into a numeric value.
  *
  * @param base
  * 	This is the numeric base to use during the conversion; if it is out-of-range, it will be set to decimal.
  *
  * @return
  * 	A numeric representation of the specified string.
  */

template< typename NType > NType toValue( const std::string& source, Stringizable::NumericBase base = Stringizable::DECIMAL )
{
	// Create local variables.

		NType result = UNSET;
		std::string targetSource = ( source.substr( 0, 2 ) == "0b" ) ? source.substr( 2 ) : source;
		std::istringstream value( source );

	// Convert the specified string to a numerical value.

		if( typeid( NType ) == typeid( bool ) )
			result = ( ( source == "true" ) || ( source == "yes" ) ) ? true : false;
		else if( base == Stringizable::BINARY )
			result = static_cast< NType >( std::bitset< ( sizeof( NType ) * 8 ) >( targetSource ).to_ullong() );
		else
			value >> ( ( base == Stringizable::OCTAL ) ? std::oct : ( ( base == Stringizable::HEXIDECIMAL ) ? std::hex : std::dec ) ) >> result;

	// Return result to calling routine.

		return result;
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

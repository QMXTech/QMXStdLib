////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Numeric.hpp
// Robert M. Baker | Created : 07JAN12 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.0.0
// This is a header file for 'QMXStdLib'; it defines the interface for a set of numeric manipulation functions.
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
  * @date    Created : 27AUG19
  * @date    Last Modified : 29AUG19 by Robert M. Baker
  * @version 2.0.0
  *
  * @brief This header file defines the interface for a set of numeric manipulation functions.
  *
  * @section NumericH0000 Description
  *
  * This header file defines the interface for a set of numeric manipulation functions.
  *
  * @section NumericH0001 License
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

#ifndef __QMX_QMXSTDLIB_NUMERIC_HPP_
#define __QMX_QMXSTDLIB_NUMERIC_HPP_

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
// Start of the 'Numeric' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This is the namespace for all numeric functions.
  */

namespace Numeric
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Definitions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This function determines if the specified value falls within the specified closed interval.
  *
  * If 'min' is greater-than 'max', this function will always return 'false'.
  *
  * @param value
  * 	This is the value to use when performing the range check.
  *
  * @param min
  * 	This is the minimum value to use when performing the range check.
  *
  * @param max
  * 	This is the maximum value to use when performing the range check.
  *
  * @return
  * 	A boolean value of 'true' if 'Value' falls within the closed interval from 'min' to 'max', and 'false' otherwise.
  */

template< typename NType > bool inRange( NType value, NType min, NType max )
{
	// Report whether or not the specified value falls within the specified closed range to calling routine.

		return( ( value >= min ) && ( value <= max ) );
}

/**
  * @brief This function clamps the specified value within the specified closed interval.
  *
  * If 'min' is greater-than 'max', 'Value' will be clamped to 'min' when 'value < min' and always 'max' otherwise.
  *
  * @param value
  * 	This is the value to be clamped.
  *
  * @param min
  * 	This is the minimum value to use when clamping.
  *
  * @param max
  * 	This is the maximum value to use when clamping.
  */

template< typename NType > void clamp( NType& value, NType min, NType max )
{
	// Clamp the specified value between the specified closed range, if necessary.

		if( value < min )
			value = min;
		else if( value > max )
			value = max;
}

/**
  * @brief This function wraps the specified value within the specified closed interval.
  *
  * If 'min' is greater-than 'max', 'value' will be wrapped to 'max' when 'value < min' and always 'min' otherwise.
  *
  * @param value
  * 	This is the value to be wrapped.
  *
  * @param min
  * 	This is the minimum value to use when wrapping.
  *
  * @param max
  * 	This is the maximum value to use when wrapping.
  */

template< typename NType > void wrap( NType& value, NType min, NType max )
{
	// Wrap the specified value between the specified closed range, if necessary.

		if( value < min )
			value = max;
		else if( value > max )
			value = min;
}

/**
  * @brief This function determines if the specified value is a whole number.
  *
  * If 'NType' is not a valid floating point type, then this function will always return 'true'.
  *
  * @param value
  * 	This is the numeric value to check.
  *
  * @return
  * 	A boolean value of 'true' if the specified value is a whole number, and 'false' otherwise.
  */

template< typename NType > bool isWholeNumber( NType value )
{
	// Report whether or not the specified value is a whole number to calling routine.

		return( ( value - static_cast< int64_t >( value ) ) == 0 );
}

/**
  * @brief This function gets the next power of 2 greater-than or equal-to to the specified value.
  *
  * @param value
  * 	This is the numeric value that will be used in determining the next power of 2.
  *
  * @return
  * 	A numeric value of the next power of 2 greater-than or equal-to the specified value.
  */

template< typename NType > NType getNextPowerOfTwo( NType value )
{
	// Create local variables.

		NType result = 1;

	// Get next power of 2 greater-than or equal-to specified value.

		while( result < value )
			result <<= 1;

	// Return result to calling routine.

		return result;
}

/**
  * @brief This function constructs a string representation of the specified value.
  *
  * @param value
  * 	This is the value to use when constructing the string.
  *
  * @param base
  * 	This is the numeric base to use when constructing a string format object; if set to none, it will be ignored in favor of 'Format'.
  *
  * @param targetFormat
  * 	This is a pointer to a string format object, which must be valid if 'base' is set to none.  If base is none, it will be set to decimal.
  *
  * @return
  * 	A string representing the specified value.
  *
  * @exception QMXException
  * 	If the base was set to none, but the string format pointer was null.
  */

template< typename NType > std::string toString(
	NType value,
	Stringizable::NumericBase base = Stringizable::DECIMAL,
	const Stringizable::StringFormat* targetFormat = nullptr
)
{
	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "Numeric::toString", 0000 );

	// Create local variables.

		std::ostringstream result;
		Stringizable::StringFormat format;

	// Construct a string representation of the specified value.

		if( base != Stringizable::NONE )
			Stringizable::setStringFormat( format, base );
		else
		{
			QMX_ASSERT( targetFormat, "QMXStdLib", "Numeric::toString", "00000010", value << ", " << base );
			format = *targetFormat;

			if( format.base == Stringizable::NONE )
				format.base = Stringizable::DECIMAL;
		}

		if( typeid( NType ) == typeid( bool ) )
		{
			if( format.useYesNo )
				result << ( value ? "yes" : "no" );
			else
				result << std::boolalpha << value;
		}
		else
		{
			if( format.usePrefix && ( format.base != Stringizable::DECIMAL ) )
				result << ( ( format.base == Stringizable::BINARY ) ? "0b" : ( ( format.base == Stringizable::OCTAL ) ? "0" : "0x" ) );

			result << ( format.useUpperCase ? std::uppercase : std::nouppercase );

			if( format.filler )
				result << std::setfill( format.filler ) << std::setw( format.width );
			else
				result << std::setw( 0 );

			if( format.base == Stringizable::DECIMAL )
				result << std::dec << std::setprecision( format.precision ) << std::fixed;
			else if( format.base != Stringizable::BINARY )
				result << ( ( format.base == Stringizable::OCTAL ) ? std::oct : std::hex );

			if( format.base == Stringizable::BINARY )
				result << std::bitset< ( sizeof( NType ) * 8 ) >( value ).to_string();
			else
			{
				if( format.charsAsInts && ( ( typeid( NType ) == typeid( int8_t ) ) || ( typeid( NType ) == typeid( uint8_t ) ) ) )
					result << static_cast< int32_t >( value );
				else
					result << value;
			}
		}

	// Return result to calling routine.

		return result.str();
}

} // 'Numeric' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'Numeric' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_NUMERIC_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'Numeric.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

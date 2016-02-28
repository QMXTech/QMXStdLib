////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Numeric.hpp
// Robert M. Baker | Created : 07JAN12 | Last Modified : 28JAN16 by Robert M. Baker
// Version : 1.1.2
// This is a header file for 'QMXStdLib'; it defines the interface for a set of numeric manipulation functions.
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
  * @date    Created : 07JAN12
  * @date    Last Modified : 28JAN16 by Robert M. Baker
  * @version 1.1.2
  *
  * @brief This header file defines the interface for a set of numeric manipulation functions.
  *
  * @section Description
  *
  * This header file defines the interface for a set of numeric manipulation functions.
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

namespace Numeric
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Definitions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This function determines if the specified value falls within the specified closed interval.
  *
  * If 'Min' is greater-than 'Max', this function will always return 'false'.
  *
  * @param Value
  * 	This is the value to use when performing the range check.
  *
  * @param Min
  * 	This is the minimum value to use when performing the range check.
  *
  * @param Max
  * 	This is the maximum value to use when performing the range check.
  *
  * @return
  * 	A boolean value of 'true' if 'Value' falls within the closed interval from 'Min' to 'Max', and 'false' otherwise.
  */

template< typename NType > bool InRange( NType Value, NType Min, NType Max )
{
	// Report whether or not the specified value falls within the specified closed range to calling routine.

		return( ( Value >= Min ) && ( Value <= Max ) );
}

/**
  * @brief This function clamps the specified value within the specified closed interval.
  *
  * If 'Min' is greater-than 'Max', 'Value' will be clamped to 'Min' when 'Value < Min' and always 'Max' otherwise.
  *
  * @param Value
  * 	This is the value to be clamped.
  *
  * @param Min
  * 	This is the minimum value to use when clamping.
  *
  * @param Max
  * 	This is the maximum value to use when clamping.
  */

template< typename NType > void Clamp( NType& Value, NType Min, NType Max )
{
	// Clamp the specified value between the specified closed range, if necessary;

		if( Value < Min )
			Value = Min;
		else if( Value > Max )
			Value = Max;
}

/**
  * @brief This function determines if the specified value is a whole number.
  *
  * If 'NType' is not a valid floating point type, then this function will always return 'true'.
  *
  * @param Value
  * 	This is the numeric value to check.
  *
  * @return
  * 	A boolean value of 'true' if the specified value is a whole number, and 'false' otherwise.
  */

template< typename NType > bool IsWholeNumber( NType Value )
{
	// Report whether or not the specified value is a whole number to calling routine.

		return( ( Value - static_cast< int64_t >( Value ) ) == 0 );
}

/**
  * @brief This function gets the next power of 2 greater-than or equal-to to the specified value.
  *
  * @param Value
  * 	This is the numeric value that will be used in determining the next power of 2.
  *
  * @return
  * 	A numeric value of the next power of 2 greater-than or equal-to the specified value.
  */

template< typename NType > NType GetNextPowerOfTwo( NType Value )
{
	// Create local variables.

		NType Result = 1;

	// Get next power of 2 greater-than or equal-to specified value.

		while( Result < Value )
			Result <<= 1;

	// Return result to calling routine.

		return Result;
}

/**
  * @brief This function constructs a string representation of the specified value.
  *
  * @param Value
  * 	This is the value to use when constructing the string.
  *
  * @param Base
  * 	This is the numeric base to use when constructing a string format object; if set to none, it will be ignored in favor of 'Format'.
  *
  * @param TargetFormat
  * 	This is a pointer to a string format object, which must be valid if 'Base' is set to none.  If base is none, it will be set to decimal.
  *
  * @return
  * 	A string representing the specified value.
  *
  * @exception QMXException
  * 	If the base was set to none, but the string format pointer was null.
  */

template< typename NType > std::string ToString( NType Value,
                                                 Stringizable::NumericBase Base = Stringizable::Decimal,
                                                 const Stringizable::StringFormat* TargetFormat = nullptr )
{
	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "Numeric::ToString", 0000 );

	// Create local variables.

		std::ostringstream Result;
		Stringizable::StringFormat Format;

	// Construct a string representation of the specified value.

		if( Base != Stringizable::None )
			Stringizable::SetStringFormat( Format, Base );
		else
		{
			QMX_ASSERT( TargetFormat, "QMXStdLib", "Numeric::ToString", "00000010", Value << ", " << Base );
			Format = *TargetFormat;

			if( Format.Base == Stringizable::None )
				Format.Base = Stringizable::Decimal;
		}

		if( typeid( NType ) == typeid( bool ) )
		{
			if( Format.UseYesNo )
				Result << ( Value ? "yes" : "no" );
			else
				Result << std::boolalpha << Value;
		}
		else
		{
			if( Format.UsePrefix && ( Format.Base != Stringizable::Decimal ) )
				Result << ( ( Format.Base == Stringizable::Octal ) ? "0" : "0x" );

			Result << ( Format.UseUpperCase ? std::uppercase : std::nouppercase );

			if( Format.Filler )
				Result << std::setfill( Format.Filler ) << std::setw( Format.Width );
			else
				Result << std::setw( 0 );

			if( Format.Base == Stringizable::Decimal )
				Result << std::dec << std::setprecision( Format.Precision ) << std::fixed;
			else
				Result << ( ( Format.Base == Stringizable::Octal ) ? std::oct : std::hex );

			if( Format.CharsAsInts && ( ( typeid( NType ) == typeid( int8_t ) ) || ( typeid( NType ) == typeid( uint8_t ) ) ) )
				Result << static_cast< int32_t >( Value );
			else
				Result << Value;
		}

	// Return result to calling routine.

		return Result.str();
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

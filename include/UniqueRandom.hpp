////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UniqueRandom.hpp
// Robert M. Baker | Created : 03FEB12 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.1.0
// This is a header file for 'QMXStdLib'; it defines the interface for a set of unique random number generation functions.
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
  * @date    Created : 03FEB12
  * @date    Last Modified : 29AUG19 by Robert M. Baker
  * @version 2.1.0
  *
  * @brief This header file defines the interface for a unique random number generation class.
  *
  * @section UniqueRandomH0000 Description
  *
  * This header file defines the interface for a unique random number generation class.
  *
  * @section UniqueRandomH0001 License
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

#ifndef __QMX_QMXSTDLIB_UNIQUERANDOM_HPP_
#define __QMX_QMXSTDLIB_UNIQUERANDOM_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <type_traits>

#include "Base.hpp"
#include "Object.hpp"
#include "Numeric.hpp"
#include "Utility.hpp"
#include "RAII/ScopedLock.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'UniqueRandom' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace UniqueRandom
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Prototypes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This function defines the structure for a generator which will produce a set of unique random integral numbers.
  *
  * If 'min' is less-than 'max', 'min' will be set to 'max - 1';  'quantity' will be clamped on the closed interval [0, ( max - min + 1 )].
  *
  * @param target
  * 	This is a reference to a numeric vector which will receive the generated values; it will be cleared if not empty.
  *
  * @param quantity
  * 	This is the quantity of unique random numbers to generate.
  *
  * @param min
  * 	This is the minimum value to use while generating random numbers.
  *
  * @param max
  * 	This is the maximum value to use while generating random numbers.
  */

template< typename NType > void generateInt( std::vector< NType >& target, size_t quantity, NType min, NType max )
{
	// Create local variables.

		NType value = UNSET;

	// Check arguments.

		if( min >= max )
			min = max - 1;

		Numeric::clamp< size_t >( quantity, 0, ( max - min + 1 ) );

	// Clear number vector if necessary.

		if( !target.empty() )
			target.clear();

	// Generate random numbers based on specified data.

		while( target.size() < quantity )
		{
			value = QMXStdLib::Utility::randInt< NType >( min, max );

			if( std::find( target.begin(), target.end(), value ) == target.end() )
				target.push_back( value );
		}
}

/**
  * @brief This function defines the structure for a generator which will produce a set of unique random floating point numbers.
  *
  * If 'min' is less-than 'max', 'min' will be set to 'max - 1'.
  *
  * @param target
  * 	This is a reference to a numeric vector which will receive the generated values; it will be cleared if not empty.
  *
  * @param quantity
  * 	This is the quantity of unique random numbers to generate.
  *
  * @param min
  * 	This is the minimum value to use while generating random numbers.
  *
  * @param max
  * 	This is the maximum value to use while generating random numbers.
  */

template< typename NType > void generateFloat( std::vector< NType >& target, size_t quantity, NType min, NType max )
{
	// Create local variables.

		NType value = UNSET;

	// Check arguments.

		if( min >= max )
			min = max - 1;

	// Clear number vector if necessary.

		if( !target.empty() )
			target.clear();

	// Generate random numbers based on specified data.

		while( target.size() < quantity )
		{
			value = QMXStdLib::Utility::randFloat< NType >( min, max );

			if( std::find( target.begin(), target.end(), value ) == target.end() )
				target.push_back( value );
		}
}

} // 'UniqueRandom' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'UniqueRandom' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_UNIQUERANDOM_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'UniqueRandom.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

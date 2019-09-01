////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BaseIterator.hpp
// Robert M. Baker | Created : 08OCT17 | Last Modified : 28AUG19 by Robert M. Baker
// Version : 2.1.1
// This is a header file for 'QMXStdLib'; it defines data common to all the various iterator classes.
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
  * @date    Created : 08OCT17
  * @date    Last Modified : 28AUG19 by Robert M. Baker
  * @version 2.1.1
  *
  * @brief This header file defines data common to all the various iterator classes.
  *
  * @section BaseIteratorH0000 Description
  *
  * This header file defines data common to all the various iterator classes.
  *
  * @section BaseIteratorH0001 License
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

#ifndef __QMX_QMXSTDLIB_BASEITERATOR_HPP_
#define __QMX_QMXSTDLIB_BASEITERATOR_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../Base.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'Iterator' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This is the namespace for common iterator functors.
  */

namespace Iterator
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'GetReferenceCopy' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This functor is for use in cases where an iterator needs to retrieve a copy to the underlying iterator value.
  */

template< typename Type > class GetReferenceCopy
{
public:

	// Public Overloaded Operators

		/**
		  * @brief This is the overloaded function-call operator, which accepts an element pointer.
		  *
		  * @param target
		  * 	This is a pointer to an iterator element.
		  *
		  * @return
		  * 	A copy of the underlying iterator value.
		  */

		Type operator()( Type* target ) const
		{
			// Return copy of underlying iterator value to calling routine.

				return *target;
		}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'GetReference' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This functor is for use in cases where an iterator needs to retrieve a reference to the underlying iterator value.
  */

template< typename Type > class GetReference
{
public:

	// Public Overloaded Operators

		/**
		  * @brief This is the overloaded function-call operator, which accepts an element pointer.
		  *
		  * @param target
		  * 	This is a pointer to an iterator element.
		  *
		  * @return
		  * 	A reference to the underlying iterator value.
		  */

		Type& operator()( Type* target ) const
		{
			// Return reference to underlying iterator value to calling routine.

				return *target;
		}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'GetPointer' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This functor is for use in cases where an iterator needs to retrieve a pointer to the underlying iterator value.
  */

template< typename Type > class GetPointer
{
public:

	// Public Overloaded Operators

		/**
		  * @brief This is the overloaded function-call operator, which accepts an element pointer.
		  *
		  * @param target
		  * 	This is a pointer to an iterator element.
		  *
		  * @return
		  * 	A pointer to the underlying iterator value.
		  */

		Type* operator()( Type* target ) const
		{
			// Return pointer to underlying iterator value to calling routine.

				return target;
		}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'OperatorAddition' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This functor is for use in cases where an iterator needs to perform an addition operation with a numerical offset.
  */

template< typename Type > class OperatorAddition
{
public:

	// Public Overloaded Operators

		/**
		  * @brief This is the overloaded function-call operator, which accepts an element pointer LHS and numerical offset RHS.
		  *
		  * @param lhs
		  * 	This is a pointer to an iterator element.
		  *
		  * @param rhs
		  * 	This is a numerical offset by which to modify the iterator element.
		  *
		  * @return
		  * 	A pointer to the modified iterator element.
		  */

		Type* operator()( Type* lhs, ptrdiff_t rhs ) const
		{
			// Return pointer to modified iterator element to calling routine.

				return ( lhs + rhs );
		}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'OperatorSubtraction1' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This functor is for use in cases where an iterator needs to perform a subtraction operation with a numerical offset.
  */

template< typename Type > class OperatorSubtraction1
{
public:

	// Public Overloaded Operators

		/**
		  * @brief This is the overloaded function-call operator, which accepts an element pointer LHS and numerical offset RHS.
		  *
		  * @param lhs
		  * 	This is a pointer to an iterator element.
		  *
		  * @param rhs
		  * 	This is a numerical offset by which to modify the iterator element.
		  *
		  * @return
		  * 	A pointer to the modified iterator element.
		  */

		Type* operator()( Type* lhs, ptrdiff_t rhs ) const
		{
			// Return pointer to modified iterator element to calling routine.

				return ( lhs - rhs );
		}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'OperatorSubtraction2' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This functor is for use in cases where an iterator needs to perform a subtraction operation with another iterator.
  */

template< typename Type > class OperatorSubtraction2
{
public:

	// Public Overloaded Operators

		/**
		  * @brief This is the overloaded function-call operator, which accepts an element pointer LHS and element pointer RHS.
		  *
		  * @param lhs
		  * 	This is a pointer to the first iterator element.
		  *
		  * @param rhs
		  * 	This is a pointer to the second iterator element.
		  *
		  * @return
		  * 	A numerical offset from the second iterator element to the first.
		  */

		ptrdiff_t operator()( Type* lhs, Type* rhs ) const
		{
			// Return numerical offset from second iterator element to first to calling routine.

				return ( reinterpret_cast< ptrdiff_t >( ( lhs - rhs ) ) );
		}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'OperatorGreaterThan' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This functor is for use in cases where an iterator needs to perform a greater-than comparison with another iterator.
  */

template< typename Type > class OperatorGreaterThan
{
public:

	// Public Overloaded Operators

		/**
		  * @brief This is the overloaded function-call operator, which accepts an element pointer LHS and element pointer RHS.
		  *
		  * @param lhs
		  * 	This is a pointer to the first iterator element.
		  *
		  * @param rhs
		  * 	This is a pointer to the second iterator element.
		  *
		  * @return
		  * 	A boolean value of 'true' if the first iterator element is greater-than the second, and 'false' otherwise.
		  */

		bool operator()( Type* lhs, Type* rhs ) const
		{
			// Report whether or not the first iterator element is greater-than the second to calling routine.

				return ( lhs > rhs );
		}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'OperatorSubscript' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This functor is for use in cases where an iterator needs to retrieve a reference to the underlying value at an offset from an element.
  */

template< typename Type > class OperatorSubscript
{
public:

	// Public Overloaded Operators

		/**
		  * @brief This is the overloaded function-call operator, which accepts an element pointer LHS and numerical offset RHS.
		  *
		  * @param lhs
		  * 	This is a pointer to an iterator element.
		  *
		  * @param rhs
		  * 	This is a numerical offset used to acquire a mutable reference to the underlying value.
		  *
		  * @return
		  * 	A reference to the underlying iterator value at the specified offset from the element.
		  */

		Type& operator()( Type* lhs, ptrdiff_t rhs ) const
		{
			// Return reference to underlying iterator value at specified offset from element to calling routine.

				return lhs[ rhs ];
		}
};

} // 'Iterator' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'Iterator' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_BASEITERATOR_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'BaseIterator.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RandomAccessIterator.hpp
// Robert M. Baker | Created : 08OCT17 | Last Modified : 28AUG19 by Robert M. Baker
// Version : 2.0.0
// This is a header file for 'QMXStdLib'; it defines the interface for a random access iterator class.
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
  * @version 2.0.0
  *
  * @brief This header file defines the interface for a random access iterator class.
  *
  * @section RandomAccessIteratorH0000 Description
  *
  * This header file defines the interface for a random access iterator class.
  *
  * @section RandomAccessIteratorH0001 License
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

#ifndef __QMX_QMXSTDLIB_RANDOMACCESSITERATOR_HPP_
#define __QMX_QMXSTDLIB_RANDOMACCESSITERATOR_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../Base.hpp"
#include "BaseIterator.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define RANDOM_ACCESS_ITERATOR RandomAccessIterator< UType, EType, IsReverse, FType1, FType2, FType3, FType4, FType5, FType6, FType7 >

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'RandomAccessIterator' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class RandomAccessIterator RandomAccessIterator.hpp "include/Iterators/RandomAccessIterator.hpp"
  *
  * @brief This class defines the interface for an random access iterator.
  *
  * These algorithms are useful when it is necessary to create STL-style iterators with random access capabilities.  The iterator element must support the
  * following operators:
  *
  * - Addition with a Numerical Offset RHS<br>
  * - Subtraction with a Numerical Offset RHS<br>
  * - Subtraction with an Iterator RHS<br>
  * - Pre-Increment<br>
  * - Post-Increment<br>
  * - Pre-Decrement<br>
  * - Post-Decrement<br>
  * - Greater-Than with an Iterator RHS<br>
  * - Subscript Operator with a Numerical Offset RHS<br>
  * - Dereferencing<br>
  * - Arrow
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : No
  */

template<
	typename UType,
	typename EType = UType,
	typename IsReverse = std::false_type,
	typename FType1 = Iterator::GetReference< UType >,
	typename FType2 = Iterator::GetPointer< UType >,
	typename FType3 = Iterator::OperatorAddition< UType >,
	typename FType4 = Iterator::OperatorSubtraction1< UType >,
	typename FType5 = Iterator::OperatorSubtraction2< UType >,
	typename FType6 = Iterator::OperatorGreaterThan< UType >,
	typename FType7 = Iterator::OperatorSubscript< UType >
> class RandomAccessIterator
{
public:

	// Public Type Definitions

		typedef std::random_access_iterator_tag iterator_category;
		typedef UType value_type;
		typedef value_type& reference;
		typedef value_type* pointer;
		typedef ptrdiff_t difference_type;

	// Public Constructors

		/**
		  * @brief This is the default constructor.
		  */

		RandomAccessIterator()
		{
			// Initialize fields.

				elementCurrent = nullptr;
		}

		/**
		  * @brief This is the constructor which accepts an element pointer.
		  *
		  * @param target
		  * 	This is the element pointer with which to initialize this iterator.
		  */

		RandomAccessIterator( EType* target )
		{
			// Initialize fields.

				elementCurrent = target;
		}

		/**
		  * @brief This is the copy constructor.
		  *
		  * @param instance
		  * 	This is the instance with which to initialize this iterator.
		  */

		RandomAccessIterator( const RandomAccessIterator& instance )
		{
			// Initialize fields.

				elementCurrent = instance.elementCurrent;
		}

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		~RandomAccessIterator()
		{
			// Do nothing.
		}

	// Public Methods

		/**
		  * @brief This method retrieves a pointer to the underlying iterator value.
		  *
		  * @return
		  * 	A pointer to the underlying iterator value.
		  */

		pointer base() const
		{
			// Return pointer to underlying iterator value to calling routine.

				return getPointerImp( elementCurrent );
		}

	// Public Overloaded Operators

		/**
		  * @brief This is the overloaded assignment operator which accepts an element pointer.
		  *
		  * @param target
		  * 	This is a pointer to an iterator element.
		  *
		  * @return
		  * 	A mutable reference to this iterator.
		  */

		RandomAccessIterator& operator=( EType* target )
		{
			// Assign specified element pointer to iterator.

				elementCurrent = target;

			// Return a mutable reference to this iterator to calling routine.

				return *this;
		}

		/**
		  * @brief This is the overloaded copy assignment operator.
		  *
		  * @param instance
		  * 	This is a non-mutable iterator instance.
		  *
		  * @return
		  * 	A mutable reference to this iterator.
		  */

		RandomAccessIterator& operator=( const RandomAccessIterator& instance )
		{
			// Assign specified instance to iterator.

				elementCurrent = instance.elementCurrent;

			// Return a mutable reference to this iterator to calling routine.

				return *this;
		}

		/**
		  * @brief This is the overloaded addition operator, which accepts a numerical offset.
		  *
		  * @param rhs
		  * 	This is a numerical offset by which to modify the iterator.
		  *
		  * @return
		  * 	An iterator instance containing the result of the addition operation.
		  */

		RandomAccessIterator operator+( difference_type rhs ) const
		{
			// Return an iterator instance containing the result of the addition operation to calling routine.

				return RandomAccessIterator( operatorAdditionImp( elementCurrent, rhs ) );
		}

		/**
		  * @brief This is the overloaded subtraction operator, which accepts a numerical offset.
		  *
		  * @param rhs
		  * 	This is a numerical offset by which to modify the iterator.
		  *
		  * @return
		  * 	An iterator instance containing the result of the subtraction operation.
		  */

		RandomAccessIterator operator-( difference_type rhs ) const
		{
			// Return an iterator instance containing the result of the subtraction operation to calling routine.

				return RandomAccessIterator( operatorSubtraction1Imp( elementCurrent, rhs ) );
		}

		/**
		  * @brief This is the overloaded subtraction operator, which accepts an iterator instance.
		  *
		  * @param rhs
		  * 	This is the instance with which to modify the iterator.
		  *
		  * @return
		  * 	A numerical offset between the iterators.
		  */

		difference_type operator-( const RandomAccessIterator& rhs ) const
		{
			// Return numerical offset between iterators to calling routine.

				return operatorSubtraction2Imp( elementCurrent, rhs.elementCurrent );
		}

		/**
		  * @brief This is the overloaded pre-increment operator.
		  *
		  * @return
		  * 	A mutable reference to this iterator.
		  */

		RandomAccessIterator& operator++()
		{
			// Increment or decrement this iterator based on 'IsReverse'.

				if( !IsReverse::value )
					++elementCurrent;
				else
					--elementCurrent;

			// Return a mutable reference to this iterator to calling routine.

				return *this;
		}

		/**
		  * @brief This is the overloaded post-increment operator.
		  *
		  * @return
		  * 	A reference copy to this iterator before modification.
		  */

		RandomAccessIterator operator++( int )
		{
			// Create local variables.

				RandomAccessIterator result( elementCurrent );

			// Increment or decrement this iterator based on 'IsReverse'.

				if( !IsReverse::value )
					elementCurrent++;
				else
					elementCurrent--;

			// Return result to calling routine.

				return result;
		}

		/**
		  * @brief This is the overloaded pre-decrement operator.
		  *
		  * @return
		  * 	A mutable reference to this iterator.
		  */

		RandomAccessIterator& operator--()
		{
			// Decrement or increment this iterator based on 'IsReverse'.

				if( !IsReverse::value )
					--elementCurrent;
				else
					++elementCurrent;

			// Return a mutable reference to this iterator to calling routine.

				return *this;
		}

		/**
		  * @brief This is the overloaded post-decrement operator.
		  *
		  * @return
		  * 	A reference copy to this iterator before modification.
		  */

		RandomAccessIterator operator--( int )
		{
			// Create local variables.

				RandomAccessIterator result( elementCurrent );

			// Decrement or increment this iterator based on 'IsReverse'.

				if( !IsReverse::value )
					elementCurrent--;
				else
					elementCurrent++;

			// Return result to calling routine.

				return result;
		}

		/**
		  * @brief This is the overloaded equality operator.
		  *
		  * @param rhs
		  * 	This is a non-mutable iterator instance.
		  *
		  * @return
		  * 	A boolean value of 'true' if the iterator instances are equal, and 'false' otherwise.
		  */

		bool operator==( const RandomAccessIterator& rhs ) const
		{
			// Report whether or not iterator instances are equal to calling routine.

				return ( elementCurrent == rhs.elementCurrent );
		}

		/**
		  * @brief This is the overloaded inequality operator.
		  *
		  * @param rhs
		  * 	This is a non-mutable iterator instance.
		  *
		  * @return
		  * 	A boolean value of 'true' if the iterator instances are NOT equal, and 'false' otherwise.
		  */

		bool operator!=( const RandomAccessIterator& rhs ) const
		{
			// Report whether or not iterator instances are NOT equal to calling routine.

				return ( elementCurrent != rhs.elementCurrent );
		}

		/**
		  * @brief This is the overloaded greater-than operator, which accepts an iterator instance.
		  *
		  * @param rhs
		  * 	This is the instance with which to compare the iterator.
		  *
		  * @return
		  * 	A boolean value of 'true' if the iterator is greater-than the specified instance, and 'false' otherwise.
		  */

		bool operator>( const RandomAccessIterator& rhs ) const
		{
			// Report whether or not the iterator is greater-than the specified instance to calling routine.

				return operatorGreaterThanImp( elementCurrent, rhs.elementCurrent );
		}

		/**
		  * @brief This is the overloaded less-than operator, which accepts an iterator instance.
		  *
		  * @param rhs
		  * 	This is the instance with which to compare the iterator.
		  *
		  * @return
		  * 	A boolean value of 'true' if the iterator is less-than the specified instance, and 'false' otherwise.
		  */

		bool operator<( const RandomAccessIterator& rhs ) const
		{
			// Report whether or not the iterator is less-than the specified instance to calling routine.

				return ( !( *this > rhs ) && ( *this != rhs ) );
		}

		/**
		  * @brief This is the overloaded greater-than-or-equal-to operator, which accepts an iterator instance.
		  *
		  * @param rhs
		  * 	This is the instance with which to compare the iterator.
		  *
		  * @return
		  * 	A boolean value of 'true' if the iterator is greater-than-or-equal-to the specified instance, and 'false' otherwise.
		  */

		bool operator>=( const RandomAccessIterator& rhs ) const
		{
			// Report whether or not the iterator is greater-than-or-equal-to the specified instance to calling routine.

				return ( ( *this > rhs ) || ( *this == rhs ) );
		}

		/**
		  * @brief This is the overloaded less-than-or-equal-to operator, which accepts an iterator instance.
		  *
		  * @param rhs
		  * 	This is the instance with which to compare the iterator.
		  *
		  * @return
		  * 	A boolean value of 'true' if the iterator is less-than-or-equal-to the specified instance, and 'false' otherwise.
		  */

		bool operator<=( const RandomAccessIterator& rhs ) const
		{
			// Report whether or not the iterator is less-than-or-equal-to the specified instance to calling routine.

				return !( *this > rhs );
		}

		/**
		  * @brief This is the overloaded addition-assignment operator, which accepts a numerical offset.
		  *
		  * @param rhs
		  * 	This is a numerical offset by which to modify the iterator.
		  *
		  * @return
		  * 	A mutable reference to this iterator.
		  */

		RandomAccessIterator& operator+=( difference_type rhs )
		{
			// Assign to the current iterator element itself plus the specified offset.

				*this = *this + rhs;

			// Return a mutable reference to this iterator to calling routine.

				return *this;
		}

		/**
		  * @brief This is the overloaded subtraction-assignment operator, which accepts a numerical offset.
		  *
		  * @param rhs
		  * 	This is a numerical offset by which to modify the iterator.
		  *
		  * @return
		  * 	A mutable reference to this iterator.
		  */

		RandomAccessIterator& operator-=( difference_type rhs )
		{
			// Assign to the current iterator element itself minus the specified offset.

				*this = *this - rhs;

			// Return a mutable reference to this iterator to calling routine.

				return *this;
		}

		/**
		  * @brief This is the overloaded subscript operator, which accepts a numerical offset.
		  *
		  * @param rhs
		  * 	This is a numerical offset used to acquire a mutable reference to the underlying value.
		  *
		  * @return
		  * 	A mutable reference to the underlying value at the specified offset from the current element.
		  */

		reference operator[]( difference_type rhs ) const
		{
			// Return mutable reference to underlying value at specified offset from current element to calling routine.

				return operatorSubscriptImp( elementCurrent, rhs );
		}

		/**
		  * @brief This is the overloaded dereferencing operator.
		  *
		  * @return
		  * 	A reference to the underlying iterator value.
		  */

		reference operator*() const
		{
			// Return reference to underlying iterator value to calling routine.

				return getReferenceImp( elementCurrent );
		}

		/**
		  * @brief This is the overloaded arrow operator.
		  *
		  * @return
		  * 	A pointer to the underlying iterator value.
		  */

		pointer operator->() const
		{
			// Return pointer to underlying iterator value to calling routine.

				return getPointerImp( elementCurrent );
		}

private:

	// Private Fields

		/**
		  * @brief This is a pointer to the current iterator element.
		  */

		EType* elementCurrent;

		/**
		  * @brief This is the functor for retrieving a reference to the underlying iterator value.
		  */

		FType1 getReferenceImp;

		/**
		  * @brief This is the functor for retrieving a pointer to the underlying iterator value.
		  */

		FType2 getPointerImp;

		/**
		  * @brief This is the functor for the overloaded addition operator implementation, which accepts an element pointer LHS and numerical offset RHS.
		  */

		FType3 operatorAdditionImp;

		/**
		  * @brief This is the functor for the overloaded subtraction operator implementation, which accepts an element pointer LHS numerical offset RHS.
		  */

		FType4 operatorSubtraction1Imp;

		/**
		  * @brief This is the functor for the overloaded subtraction operator implementation, which accepts an element pointer LHS and element pointer RHS.
		  */

		FType5 operatorSubtraction2Imp;

		/**
		  * @brief This is the functor for the overloaded greater-than operator implementation, which accepts an element pointer LHS and element pointer RHS.
		  */

		FType6 operatorGreaterThanImp;

		/**
		  * @brief This is the functor for the overloaded subscript operator implementation, which accepts an element pointer LHS and numerical offset RHS.
		  */

		FType7 operatorSubscriptImp;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Overloaded Operators for the 'RandomAccessIterator' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This is the overloaded addition operator, which accepts a numerical offset LHS and an iterator RHS.
  *
  * @param lhs
  * 	This is a numerical offset by which to modify the iterator.
  *
  * @param rhs
  * 	This is a non-mutable iterator instance.
  *
  * @return
  * 	An iterator instance containing the result of the addition operation.
  */

template<
	typename UType,
	typename EType,
	typename IsReverse,
	typename FType1,
	typename FType2,
	typename FType3,
	typename FType4,
	typename FType5,
	typename FType6,
	typename FType7
> RANDOM_ACCESS_ITERATOR operator+( typename RANDOM_ACCESS_ITERATOR::difference_type lhs, const RANDOM_ACCESS_ITERATOR& rhs )
{
	// Return an iterator instance containing the result of the addition operation to calling routine.

		return ( rhs + lhs );
}

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_RANDOMACCESSITERATOR_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'RandomAccessIterator.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

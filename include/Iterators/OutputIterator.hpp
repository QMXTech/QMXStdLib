////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OutputIterator.hpp
// Robert M. Baker | Created : 08OCT17 | Last Modified : 28AUG19 by Robert M. Baker
// Version : 2.3.0
// This is a header file for 'QMXStdLib'; it defines the interface for an output iterator class.
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
  * @version 2.3.0
  *
  * @brief This header file defines the interface for an output iterator class.
  *
  * @section OutputIteratorH0000 Description
  *
  * This header file defines the interface for an output iterator class.
  *
  * @section OutputIteratorH0001 License
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

#ifndef __QMX_QMXSTDLIB_OUTPUTITERATOR_HPP_
#define __QMX_QMXSTDLIB_OUTPUTITERATOR_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../Base.hpp"
#include "BaseIterator.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'OutputIterator' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class OutputIterator OutputIterator.hpp "include/Iterators/OutputIterator.hpp"
  *
  * @brief This class defines the interface for an output iterator.
  *
  * These algorithms are useful when it is necessary to create STL-style iterators with output-only capabilities.  The iterator element must support the
  * following operators:
  *
  * - Pre-Increment<br>
  * - Post-Increment<br>
  * - Pre-Decrement<br>
  * - Post-Decrement<br>
  * - Dereferencing
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
	typename FType2 = Iterator::GetPointer< UType >
> class OutputIterator
{
public:

	// Public Type Definitions

		typedef std::output_iterator_tag iterator_category;
		typedef UType value_type;
		typedef value_type& reference;
		typedef value_type* pointer;

	// Public Constructors

		/**
		  * @brief This is the constructor which accepts an element pointer.
		  *
		  * @param target
		  * 	This is the element pointer with which to initialize this iterator.
		  */

		OutputIterator( EType* target )
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

		OutputIterator( const OutputIterator& instance )
		{
			// Initialize fields.

				elementCurrent = instance.elementCurrent;
		}

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		~OutputIterator()
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

		OutputIterator& operator=( EType* target )
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

		OutputIterator& operator=( const OutputIterator& instance )
		{
			// Assign specified instance to iterator.

				elementCurrent = instance.elementCurrent;

			// Return a mutable reference to this iterator to calling routine.

				return *this;
		}

		/**
		  * @brief This is the overloaded pre-increment operator.
		  *
		  * @return
		  * 	A mutable reference to this iterator.
		  */

		OutputIterator& operator++()
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

		OutputIterator operator++( int )
		{
			// Create local variables.

				OutputIterator result( elementCurrent );

			// Increment or decrement this iterator based on 'IsReverse'.

				if( !IsReverse::value )
					elementCurrent++;
				else
					elementCurrent--;

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

		bool operator==( const OutputIterator& rhs ) const
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

		bool operator!=( const OutputIterator& rhs ) const
		{
			// Report whether or not iterator instances are NOT equal to calling routine.

				return ( elementCurrent != rhs.elementCurrent );
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
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_OUTPUTITERATOR_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'OutputIterator.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

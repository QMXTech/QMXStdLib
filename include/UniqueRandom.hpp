////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UniqueRandom.hpp
// Robert M. Baker | Created : 03FEB12 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.0
// This is a header file for 'QMXStdLib'; it defines the interface for a unique random number generation class.
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
  * @date    Created : 03FEB12
  * @date    Last Modified : 27FEB16 by Robert M. Baker
  * @version 1.1.0
  *
  * @brief This header file defines the interface for a unique random number generation class.
  *
  * @section Description
  *
  * This header file defines the interface for a unique random number generation class.
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

#ifndef __QMX_QMXSTDLIB_UNIQUERANDOM_HPP_
#define __QMX_QMXSTDLIB_UNIQUERANDOM_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "Object.hpp"
#include "Numeric.hpp"
#include "Utility.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'UniqueRandom' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class UniqueRandom UniqueRandom.hpp "include/UniqueRandom.hpp"
  *
  * @brief This class defines unique random number generation algorithms.
  *
  * These algorithms are useful when it is necessary to have a set of unique random numbers.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Conditionally ('GenerateImp' must be defined in a thread-safe manner.)
  */

template< typename NType > class UniqueRandom
{
public:

	// Public Type Definitions

		typedef std::vector< NType > NumberVector;

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		virtual ~UniqueRandom()
		{
			// Do nothing.
		}

	// Public Methods

		/**
		  * @brief This method generates the set of unique random numbers based on the specified values.
		  *
		  * If 'Min' is less-than 'Max', 'Min' will be set to 'Max - 1';  'Quantity' will be clamped on the closed interval [0, ( Max - Min + 1 )] if 'NType' is
		  * an integral type.
		  *
		  * @param Quantity
		  * 	This is the quantity of unique random numbers to generate.
		  *
		  * @param Min
		  * 	This is the minimum value to use while generating random numbers.
		  *
		  * @param Max
		  * 	This is the maximum value to use while generating random numbers.
		  */

		void Generate( size_t Quantity, NType Min, NType Max )
		{
			// Generate random numbers based on specified data.

				GenerateImp( Quantity, Min, Max );
		}

protected:

	// Protected Fields

		/**
		  * @brief This is the vector of unique random numbers.
		  */

		NumberVector Numbers;

	// Protected Constructors

		/**
		  * @brief This is the default constructor, which is made protected to prevent direct instantiation.
		  */

		UniqueRandom()
		{
			// Do nothing.
		}

private:

	// Private Methods

		/**
		  * @brief This is the overridable implementation for the 'Generate' method.
		  *
		  * @param Quantity
		  * 	This is the quantity of unique random numbers to generate.
		  *
		  * @param Min
		  * 	This is the minimum value to use while generating random numbers.
		  *
		  * @param Max
		  * 	This is the maximum value to use while generating random numbers.
		  */

		virtual void GenerateImp( size_t Quantity, NType Min, NType Max ) = PURE_VIRTUAL;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'UniqueRandomI' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class UniqueRandomI UniqueRandom.hpp "include/UniqueRandom.hpp"
  *
  * @brief This class specializes the 'UniqueRandom' class for integral numbers.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Yes
  */

template< typename NType > class UniqueRandomI : public Object< UniqueRandomI< NType > >, public UniqueRandom< NType >
{
public:

	// Destructor

		/**
		  * @brief This is the destructor
		  */

		virtual ~UniqueRandomI()
		{
			// Perform necessary cleanup.

				if( this->Initialized )
					this->Deallocate();
		}

	// Public Methods

		/**
		  * @brief This method gets a non-mutable reference to the number vector.
		  *
		  * @return
		  * 	A non-mutable reference to the number vector.
		  */

		const typename UniqueRandom< NType >::NumberVector& GetNumbers() const
		{
			// Obtain locks.

				SCOPED_READ_LOCK;

			// Return a non-mutable number vector reference to the calling routine.

				return this->Numbers;
		}

		/**
		  * @brief This method creates an instance of this class.
		  *
		  * @return
		  * 	A pointer to the newly created instance.
		  */

		static typename UniqueRandomI< NType >::PointerType Create()
		{
			// Create local variables.

				typename UniqueRandomI< NType >::PointerType Result( new UniqueRandomI() );

			// Initialize new instance.

				Result->Allocate();

			// Return result to calling routine.

				return Result;
		}

private:

	// Private Constructors

		/**
		  * @brief This is the default constructor, which is made private to prevent direct instantiation.
		  */

		UniqueRandomI()
		{
			// Do nothing.
		}

	// Private Methods

		/**
		  * @brief This is the overridden implementation for the 'operator=' method.
		  *
		  * @param Instance
		  * 	This is the 'Object' pointer with which to set 'this'.
		  */

		void OperatorAssignImp( const Object< UniqueRandomI< NType > >* Instance )
		{
			// Create local variables.

				const UniqueRandomI< NType >* DInstance = dynamic_cast< const UniqueRandomI< NType >* >( Instance );

			// Assign specified object to 'this'.

				this->Numbers = DInstance->Numbers;
		}

		/**
		  * @brief This is the overridden implementation for the 'Clone' method.
		  *
		  * @return
		  * 	A pointer to a copy of this object.
		  */

		CLONE_IMP_T( UniqueRandomI< NType > )

		/**
		  * @brief This is the overridden implementation for the 'Generate' method.
		  *
		  * @param Quantity
		  * 	This is the quantity of unique random numbers to generate.
		  *
		  * @param Min
		  * 	This is the minimum value to use while generating random numbers.
		  *
		  * @param Max
		  * 	This is the maximum value to use while generating random numbers.
		  */

		void GenerateImp( size_t Quantity, NType Min, NType Max )
		{
			// Obtain locks.

				SCOPED_WRITE_LOCK;

			// Create local variables.

				NType Value = Null;

			// Check arguments.

				if( Min >= Max )
					Min = Max - 1;

				Numeric::Clamp< size_t >( Quantity, 0, ( Max - Min + 1 ) );

			// Clear number vector if necessary.

				if( !this->Numbers.empty() )
					this->Numbers.clear();

			// Generate random numbers based on specified data.

				while( this->Numbers.size() < Quantity )
				{
					Value = QMXStdLib::Utility::RandomI< NType >( Min, Max );

					if( std::find( this->Numbers.begin(), this->Numbers.end(), Value ) == this->Numbers.end() )
						this->Numbers.push_back( Value );
				}
		}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'UniqueRandomF' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class UniqueRandomF UniqueRandom.hpp "include/UniqueRandom.hpp"
  *
  * @brief This class specializes the 'UniqueRandom' class for floating point numbers.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Yes
  */

template< typename NType > class UniqueRandomF : public Object< UniqueRandomF< NType > >, public UniqueRandom< NType >
{
public:

	// Destructor

		/**
		  * @brief This is the destructor
		  */

		virtual ~UniqueRandomF()
		{
			// Perform necessary cleanup.

				if( this->Initialized )
					this->Deallocate();
		}

	// Public Methods

		/**
		  * @brief This method gets a non-mutable reference to the number vector.
		  *
		  * @return
		  * 	A non-mutable reference to the number vector.
		  */

		const typename UniqueRandom< NType >::NumberVector& GetNumbers() const
		{
			// Obtain locks.

				SCOPED_READ_LOCK;

			// Return a non-mutable number vector reference to the calling routine.

				return this->Numbers;
		}

		/**
		  * @brief This method creates an instance of this class.
		  *
		  * @return
		  * 	A pointer to the newly created instance.
		  */

		static typename UniqueRandomF< NType >::PointerType Create()
		{
			// Create local variables.

				typename UniqueRandomF< NType >::PointerType Result( new UniqueRandomF() );

			// Initialize new instance.

				Result->Allocate();

			// Return result to calling routine.

				return Result;
		}

private:

	// Private Constructors

		/**
		  * @brief This is the default constructor, which is made private to prevent direct instantiation.
		  */

		UniqueRandomF()
		{
			// Do nothing.
		}

	// Private Methods

		/**
		  * @brief This is the overridden implementation for the 'operator=' method.
		  *
		  * @param Instance
		  * 	This is the 'Object' pointer with which to set 'this'.
		  */

		void OperatorAssignImp( const Object< UniqueRandomF< NType > >* Instance )
		{
			// Create local variables.

				const UniqueRandomF< NType >* DInstance = dynamic_cast< const UniqueRandomF< NType >* >( Instance );

			// Assign specified object to 'this'.

				this->Numbers = DInstance->Numbers;
		}

		/**
		  * @brief This is the overridden implementation for the 'Clone' method.
		  *
		  * @return
		  * 	A pointer to a copy of this object.
		  */

		CLONE_IMP_T( UniqueRandomF< NType > )

		/**
		  * @brief This is the overridden implementation for the 'Generate' method.
		  *
		  * @param Quantity
		  * 	This is the quantity of unique random numbers to generate.
		  *
		  * @param Min
		  * 	This is the minimum value to use while generating random numbers.
		  *
		  * @param Max
		  * 	This is the maximum value to use while generating random numbers.
		  */

		void GenerateImp( size_t Quantity, NType Min, NType Max )
		{
			// Obtain locks.

				SCOPED_WRITE_LOCK;

			// Create local variables.

				NType Value = Null;

			// Check arguments.

				if( Min >= Max )
					Min = Max - 1;

			// Clear number vector if necessary.

				if( !this->Numbers.empty() )
					this->Numbers.clear();

			// Generate random numbers based on specified data.

				while( this->Numbers.size() < Quantity )
				{
					Value = QMXStdLib::Utility::RandomF< NType >( Min, Max );

					if( std::find( this->Numbers.begin(), this->Numbers.end(), Value ) == this->Numbers.end() )
						this->Numbers.push_back( Value );
				}
		}
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_UNIQUERANDOM_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'UniqueRandom.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

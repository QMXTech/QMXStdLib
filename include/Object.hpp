////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Object.hpp
// Robert M. Baker | Created : 05JAN12 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.3.0
// This is a header file for 'QMXStdLib'; it defines the interface for a generic base class.
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
  * @date    Created : 05JAN12
  * @date    Last Modified : 29AUG19 by Robert M. Baker
  * @version 2.3.0
  *
  * @brief This header file defines the interface for a generic base class.
  *
  * @section ObjectH0000 Description
  *
  * This header file defines the interface for a generic base class.
  *
  * @section ObjectH0001 License
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

#ifndef __QMX_QMXSTDLIB_OBJECT_HPP_
#define __QMX_QMXSTDLIB_OBJECT_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "Mixins/Lockable.hpp"
#include "RAII/ScopedLock.hpp"
#include "RAII/ScopedStackTrace.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'NoPublicProperties' Structure
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This structure is for use in cases where a class derived from 'Object' has no public properties.
  */

struct NoPublicProperties
{
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'Object' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class Object Object.hpp "include/Object.hpp"
  *
  * @brief This class defines base algorithms for all classes.
  *
  * The purpose of this generic base-class is to encapsulate functionality useful to all sub-classes.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Yes
  */

template< typename DType, typename PPType = NoPublicProperties > class Object : public Lockable
{
public:

	// Public Type Definitions

		STANDARD_TYPEDEFS( DType )
		typedef PPType PublicPropertiesType;

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		virtual ~Object()
		{
			// Do nothing.
		}

	// Public Methods

		/**
		  * @brief This method determines if this object is initialized.
		  *
		  * @return
		  * 	A boolean value of 'true' if this object is initialized, and 'false' otherwise.
		  */

		bool isObjectInitialized() const
		{
			// Report wether or not this object is initialized to calling routine.

				return initialized;
		}

		/**
		  * @brief This method performs necessary initialization.
		  *
		  * @exception QMXException
		  * 	If the object instance was already initialized.
		  */

		void allocate()
		{
			// Obtain locks.

				SCOPED_WRITE_LOCK;

			// Create scoped stack traces.

				SCOPED_STACK_TRACE( "Object::allocate", 0000 );

			// Perform necessary initialization.

				QMX_ASSERT( !initialized, "QMXStdLib", "Object::Allocate", "00000000", "" );
				allocateImp();
				initialized = true;
		}

		/**
		  * @brief This method performs necessary cleanup.
		  *
		  * @exception QMXException
		  * 	If the object instance was not initialized.
		  */

		void deallocate()
		{
			// Obtain locks.

				SCOPED_WRITE_LOCK;

			// Create scoped stack traces.

				SCOPED_STACK_TRACE( "Object::deallocate", 0000 );

			// Perform necessary cleanup.

				QMX_ASSERT( initialized, "QMXStdLib", "Object::deallocate", "00000001", "" );
				deallocateImp();
				initialized = false;
		}

		/**
		  * @brief This is the public properties accessor for this class.
		  *
		  * @param target
		  * 	This is a 'PPType' structure which will be set using the public properties of 'this'.
		  */

		void get( PPType& target ) const
		{
			// Obtain locks.

				SCOPED_READ_LOCK;

			// Set specified 'PPType' structure using the public properties of 'this'.

				target = properties;
		}

		/**
		  * @brief This is the public properties mutator for this class.
		  *
		  * @param source
		  * 	This is a 'PPType' structure which will be used to set the public properties of 'this'.
		  */

		void set( const PPType& source )
		{
			// Obtain locks.

				SCOPED_WRITE_LOCK;

			// Set public properties of 'this' using the specified 'PPType' structure.

				properties = source;
		}

		/**
		  * @brief This method creates an instance of this class.
		  *
		  * @param doAllocate
		  * 	This is a boolean value which determines if 'allocate' is called on the created instance.
		  *
		  * @return
		  * 	A pointer to the newly created instance.
		  *
		  * @exception QMXException
		  * 	If the an error occurs during allocation.
		  */

		static InstancePtr create( const bool doAllocate = true )
		{
			// Create scoped stack traces.

				SCOPED_STACK_TRACE( "Object::create", 0000 );

			// Create local variables.

				InstancePtr result( ( new DType() ) );

			// Initialize new instance, if 'doAllocate' is 'true'.

				if( doAllocate )
					result->allocate();

			// Return result to calling routine.

				return result;
		}

		/**
		  * @brief This method assigns the data of 'this' to the specified object.
		  *
		  * If the specified object pointer is the same as 'this', this method will have no effect.
		  *
		  * @param target
		  * 	This is the object pointer to use when setting.
		  */

		void clone( InstancePtr& target ) const
		{
			// Perform abort check.

				if( target.get() == this )
					return;

			// Obtain locks.

				SCOPED_READ_LOCK;
				SCOPED_WRITE_LOCK_X( target, 0000 );

			// Assign data of 'this' to specified object.

				target->initialized = initialized;
				target->properties = properties;
				cloneImp( target );
		}

protected:

	// Protected Fields

		/**
		  * @brief This is the flag used to determine initialization state.
		  */

		bool initialized;

		/**
		  * @brief These are the public properties of this class.
		  */

		PPType properties;

	// Protected Methods

		/**
		  * @brief This is the default constructor, which is made protected to prevent direct instantiation.
		  */

		Object()
		{
			// Initialize fields.

				initialized = false;
		}

private:

	// Private Methods

		/**
		  * @brief This is the overridable implementation for the 'allocate' method.
		  */

		virtual void allocateImp()
		{
			// Do nothing.
		}

		/**
		  * @brief This is the overridable implementation for the 'deallocate' method.
		  */

		virtual void deallocateImp()
		{
			// Do nothing.
		}

		/**
		  * @brief This is the overridable implementation for the 'clone' method.
		  *
		  * @param target
		  * 	This is the object pointer to use when setting.
		  */

		virtual void cloneImp( InstancePtr& target ) const
		{
			// Do nothing.
		}
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_OBJECT_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'Object.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

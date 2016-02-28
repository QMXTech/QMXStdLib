////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Object.hpp
// Robert M. Baker | Created : 05JAN12 | Last Modified : 28FEB16 by Robert M. Baker
// Version : 1.1.2
// This is a header file for 'QMXStdLib'; it defines the interface for a generic base class.
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
  * @date    Created : 05JAN12
  * @date    Last Modified : 28FEB16 by Robert M. Baker
  * @version 1.1.2
  *
  * @brief This header file defines the interface for a generic base class.
  *
  * @section Description
  *
  * This header file defines the interface for a generic base class.
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

#ifndef __QMX_QMXSTDLIB_OBJECT_HPP_
#define __QMX_QMXSTDLIB_OBJECT_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "Mixins/Lockable.hpp"
#include "RAII/ScopedStackTrace.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define CLONE_IMP(x)   x::PointerType CloneImp() const { x::PointerType Result( new x() );  *Result = *this;  return Result; }
#define CLONE_IMP_T(x) typename x::PointerType CloneImp() const { typename x::PointerType Result( new x() );  *Result = *this;  return Result; }

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

		bool IsObjectInitialized() const
		{
			// Report wether or not this object is initialized to calling routine.
			
				return Initialized;
		}

		/**
		  * @brief This method performs necessary initialization.
		  *
		  * @exception QMXException
		  * 	If the object instance was already initialized.
		  */

		void Allocate()
		{
			// Obtain locks.

				SCOPED_WRITE_LOCK;

			// Create scoped stack traces.

				SCOPED_STACK_TRACE( "Object::Allocate", 0000 );

			// Perform necessary initialization.

				QMX_ASSERT( !Initialized, "QMXStdLib", "Object::Allocate", "00000000", "" );
				AllocateImp();
				Initialized = true;
		}

		/**
		  * @brief This method performs necessary cleanup.
		  *
		  * @exception QMXException
		  * 	If the object instance was not initialized.
		  */

		void Deallocate()
		{
			// Obtain locks.

				SCOPED_WRITE_LOCK;

			// Create scoped stack traces.

				SCOPED_STACK_TRACE( "Object::Deallocate", 0000 );

			// Perform necessary cleanup.

				QMX_ASSERT( Initialized, "QMXStdLib", "Object::Deallocate", "00000001", "" );
				DeallocateImp();
				Initialized = false;
		}

		/**
		  * @brief This is the public properties accessor for this class.
		  *
		  * @param Target
		  * 	This is a 'PPType' structure which will be set using the public properties of 'this'.
		  */

		void Get( PPType& Target ) const
		{
			// Obtain locks.

				SCOPED_READ_LOCK;

			// Set specified 'PPType' structure using the public properties of 'this'.

				Target = Properties;
		}

		/**
		  * @brief This is the public properties mutator for this class.
		  *
		  * @param Target
		  * 	This is a 'PPType' structure which will be used to set the public properties of 'this'.
		  */

		void Set( const PPType& Target )
		{
			// Obtain locks.

				SCOPED_WRITE_LOCK;

			// Set public properties of 'this' using the specified 'PPType' structure.

				Properties = Target;
		}

		/**
		  * @brief This method creates a copy of this object.
		  *
		  * @return
		  * 	A pointer to a copy of this object.
		  */

		PointerType Clone() const
		{
			// Obtain locks.

				SCOPED_READ_LOCK;

			// Return copy of this object to calling routine.

				return CloneImp();
		}

		/**
		  * @brief This method creates an instance of this class.
		  *
		  * @param DoAllocate
		  * 	This is a boolean value which determines if 'Allocate' is called on the created instance.
		  *
		  * @return
		  * 	A pointer to the newly created instance.
		  */

		static PointerType Create( const bool DoAllocate = true )
		{
			// Create local variables.

				PointerType Result( new DType() );

			// Initialize new instance, if 'DoAllocate' is 'true'.

				if( DoAllocate )
					Result->Allocate();

			// Return result to calling routine.

				return Result;
		}

protected:

	// Protected Fields

		/**
		  * @brief This is the flag used to determine initialization state.
		  */

		bool Initialized;

		/**
		  * @brief These are the public properties of this class.
		  */

		PPType Properties;

	// Protected Methods

		/**
		  * @brief This is the default constructor, which is made protected to prevent direct instantiation.
		  */

		Object()
		{
			// Initialize fields.

				Initialized = false;
		}

	// Protected Overloaded Operators

		/**
		  * @brief This is the default assignment-operator, which is made protected to prevent direct copying.
		  *
		  * @param Instance
		  * 	This is the 'Object' instance with which to set 'this'.
		  *
		  * @return
		  * 	A reference to this object.
		  */

		Object& operator=( const Object& Instance )
		{
			// Obtain locks.

				SCOPED_WRITE_LOCK;
				SCOPED_READ_LOCK_X( Instance, 0000 );

			// Assign specified object to 'this'.

				Initialized = Instance.Initialized;
				Properties = Instance.Properties;
				OperatorAssignImp( &Instance );

			// Return a reference to this object to calling routine.

				return *this;
		}

private:

	// Private Methods

		/**
		  * @brief This is the overridable implementation for the 'Allocate' method.
		  */

		virtual void AllocateImp()
		{
			// Do nothing.
		}

		/**
		  * @brief This is the overridable implementation for the 'Deallocate' method.
		  */

		virtual void DeallocateImp()
		{
			// Do nothing.
		}

		/**
		  * @brief This is the overridable implementation for the 'operator=' method.
		  *
		  * @param Instance
		  * 	This is the 'Object' pointer with which to set 'this'.
		  */

		virtual void OperatorAssignImp( const Object* Instance )
		{
			// Do nothing.
		}

		/**
		  * @brief This is the overridable implementation for the 'Clone' method.
		  *
		  * @return
		  * 	A pointer to a copy of this object.
		  */

		virtual PointerType CloneImp() const
		{
			// Return a null pointer to calling routine.

				return PointerType( nullptr );
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

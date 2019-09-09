////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Singleton.hpp
// Robert M. Baker | Created : 04MAR12 | Last Modified : 03SEP19 by Robert M. Baker
// Version : 2.2.1
// This is a header file for 'QMXStdLib'; it defines the interface for a mixin class to a singleton instance.
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
  * @date    Created : 04MAR12
  * @date    Last Modified : 03SEP19 by Robert M. Baker
  * @version 2.2.1
  *
  * @brief This header file defines the interface for a mixin class to a singleton instance.
  *
  * @section SingletonH0000 Description
  *
  * This header file defines the interface for a mixin class to a singleton instance.
  *
  * @section SingletonH0001 License
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

#ifndef __QMX_QMXSTDLIB_SINGLETON_HPP_
#define __QMX_QMXSTDLIB_SINGLETON_HPP_

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
// The 'Singleton' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class Singleton Singleton.hpp "include/Mixins/Singleton.hpp"
  *
  * @brief This class defines a mixin interface to provide singleton instances.
  *
  * These algorithms are useful when it is necessary to create classes which need a global scope and single instance.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Yes
  */

template< typename DType > class Singleton
{
public:

	// Public Constructors

		/**
		  * @brief This is the default constructor.
		  */

		Singleton()
		{
			// Initialize fields.

				singletonInstance = static_cast< DType* >( this );
		}

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		virtual ~Singleton()
		{
			// Perform necessary cleanup.

				singletonInstance = nullptr;
		}

	// Public Methods

		/**
		  * @brief This method obtains a reference to the singleton interface for this class.
		  *
		  * Once one has the reference of the singleton, it may be used as would any other class reference.  Make certain the singleton has been instantiated
		  * before calling this function; otherwise, the application will crash on an attempt to use the reference.
		  *
		  * @return
		  * 	A reference to the singleton instance.
		  */

		static DType& getSingleton()
		{
			// Return a singleton reference to calling routine.

				return *singletonInstance;
		}

		/**
		  * @brief This method obtains a pointer to the singleton interface for this class.
		  *
		  * Once one has a pointer to the singleton, it may be used as would any other class pointer.  Make certain the singleton has been instantiated before
		  * calling this function; otherwise, the application will crash on an attempt to use the pointer.
		  *
		  * @return
		  * 	A pointer to the singleton instance.
		  */

		static DType* getSingletonPointer()
		{
			// Return a singleton pointer to calling routine.

				return singletonInstance;
		}

protected:

	// Protected Fields

		/**
		  * @brief This is the singleton pointer.
		  */

		inline static DType* singletonInstance = nullptr;
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_SINGLETON_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'Singleton.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

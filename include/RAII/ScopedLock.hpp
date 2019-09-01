////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ScopedLock.hpp
// Robert M. Baker | Created : 30MAR16 | Last Modified : 28AUG19 by Robert M. Baker
// Version : 2.1.0
// This is a header file for 'QMXStdLib'; it defines the interface for an RAII class to obtain a scoped lock.
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
  * @date    Created : 30MAR16
  * @date    Last Modified : 28AUG19 by Robert M. Baker
  * @version 2.1.0
  *
  * @brief This is a header file for 'QMXStdLib'; it defines the interface for an RAII class to obtain a scoped lock.
  *
  * @section Description
  *
  * This is a header file for 'QMXStdLib'; it defines the interface for an RAII class to obtain a scoped lock.
  *
  * @section License
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

#ifndef __QMX_QMXSTDLIB_SCOPEDLOCK_HPP_
#define __QMX_QMXSTDLIB_SCOPEDLOCK_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../Base.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SCOPED_READ_LOCK         QMXStdLib::ScopedLock readLock( QMXStdLib::ScopedLock::READ, this->localMutex )
#define SCOPED_READ_LOCK_X(x,y)  QMXStdLib::ScopedLock readLock##y( QMXStdLib::ScopedLock::READ, x->getMutex() )
#define SCOPED_WRITE_LOCK        QMXStdLib::ScopedLock writeLock( QMXStdLib::ScopedLock::WRITE, this->localMutex )
#define SCOPED_WRITE_LOCK_X(x,y) QMXStdLib::ScopedLock writeLock##y( QMXStdLib::ScopedLock::WRITE, x->getMutex() )

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'ScopedLock' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class ScopedLock ScopedLock.hpp "include/RAII/ScopedLock.hpp"
  *
  * @brief This class defines an RAII interface for a scoped lock.
  *
  * This is useful for ensuring all obtained mutex locks are appropriately released.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Yes
  */

class ScopedLock
{
public:

	// Public Data Types

		/**
		  * @brief This enumeration contains all valid lock types.
		  */

		enum LockType
		{
			READ,
			WRITE
		};

	// Public Constructors

		/**
		  * @brief This is the copy constructor, which is deleted to prevent copying.
		  *
		  * @param instance
		  * 	N/A
		  */

		ScopedLock( const ScopedLock& instance ) = delete;

		/**
		  * @brief This is the constructor which accepts a mutex pair and a lock type.
		  *
		  * @param targetType
		  * 	This is the lock type used in acquiring/releasing necessary locks.
		  *
		  * @param targetMutex
		  * 	This is the mutex pair used in acquiring/releasing necessary locks.
		  */

		ScopedLock( const LockType targetType, SharedMutexPair& targetMutex )
		{
			// Initialize fields.

				isLocked = false;
				type = targetType;
				localMutex = &targetMutex;

			// Obtain lock on mutex, if necessary.

				if( ( localMutex->first == NOT_A_THREAD ) || ( localMutex->first != THIS_THREAD_HASH ) )
				{
					switch( type )
					{
						case READ: { localMutex->second.lock_shared();  break; }
						case WRITE: { localMutex->second.lock();  break; }
					}

					localMutex->first = THIS_THREAD_HASH;
					isLocked = true;
				}
		}

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		~ScopedLock()
		{
			// Release read lock on mutex, if necessary;

				if( isLocked )
				{
					switch( type )
					{
						case READ: { localMutex->second.unlock_shared();  break; }
						case WRITE: { localMutex->second.unlock();  break; }
					}

					localMutex->first = NOT_A_THREAD;
				}
		}

	// Public Overloaded Operators

		/**
		  * @brief This is the default assignment-operator, which is deleted to prevent copying.
		  *
		  * @param instance
		  * 	N/A
		  *
		  * @return
		  * 	N/A
		  */

		ScopedLock& operator=( const ScopedLock& instance ) = delete;

private:

	// Private Fields

		/**
		  * @brief This is the flag used to determine mutex locked state.
		  */

		bool isLocked;

		/**
		  * @brief This is the type used when acquiring/releasing locks.
		  */

		LockType type;

		/**
		  * @brief This is the mutex pair pointer used when acquiring/releasing locks.
		  */

		SharedMutexPair* localMutex;
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_SCOPEDLOCK_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ScopedLock.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

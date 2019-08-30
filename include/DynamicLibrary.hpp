////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DynamicLibrary.hpp
// Robert M. Baker | Created : 14APR12 | Last Modified : 27AUG19 by Robert M. Baker
// Version : 2.0.0
// This is a header file for 'QMXStdLib'; it defines the interface for a dynamically-loaded library class.
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
  * @date    Created : 14APR12
  * @date    Last Modified : 27AUG19 by Robert M. Baker
  * @version 2.0.0
  *
  * @brief This header file defines the interface for a dynamically-loaded library class.
  *
  * @section DynamicLibraryH0000 Description
  *
  * This header file defines the interface for a dynamically-loaded library class.
  *
  * @section DynamicLibraryH0001 License
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

#ifndef __QMX_QMXSTDLIB_DYNAMICLIBRARY_HPP_
#define __QMX_QMXSTDLIB_DYNAMICLIBRARY_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "Object.hpp"
#include "FileSystem.hpp"
#include "RAII/ScopedLock.hpp"
#include "RAII/ScopedStackTrace.hpp"

#if ( ( QMX_PLATFORM == QMX_PLATFORM_LINUX ) || ( QMX_PLATFORM == QMX_PLATFORM_MACOS ) )
#	include <dlfcn.h>
#elif( QMX_PLATFORM == QMX_PLATFORM_WINDOWS )
#	include <windows.h>
#endif // Platform Headers

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if ( QMX_PLATFORM == QMX_PLATFORM_LINUX )
#	define DYNLIB_EXTENSION      ".so"
#	define DYNLIB_HANDLE         void*
#	define DYNLIB_LOAD(x)        dlopen( x, ( RTLD_LAZY | RTLD_GLOBAL ) )
#	define DYNLIB_UNLOAD(x)      dlclose( x )
#	define DYNLIB_GETSYMBOL(x,y) dlsym( x, y )
#elif( QMX_PLATFORM == QMX_PLATFORM_MACOS )
#	define DYNLIB_EXTENSION      ".dylib"
#	define DYNLIB_HANDLE         void*
#	define DYNLIB_LOAD(x)        dlopen( x, ( RTLD_LAZY | RTLD_GLOBAL ) )
#	define DYNLIB_UNLOAD(x)      dlclose( x )
#	define DYNLIB_GETSYMBOL(x,y) dlsym( x, y )
#elif( QMX_PLATFORM == QMX_PLATFORM_WINDOWS )
#	define DYNLIB_EXTENSION      ".dll"
#	define DYNLIB_HANDLE         HMODULE
#	define DYNLIB_LOAD(x)        LoadLibraryEx( x, nullptr, LOAD_WITH_ALTERED_SEARCH_PATH )
#	define DYNLIB_UNLOAD(x)      !FreeLibrary( x )
#	define DYNLIB_GETSYMBOL(x,y) GetProcAddress( x, y )
#else
#	error "Unsupported value for 'QMX_PLATFORM'; aborting compile!"
#endif // DYNLIB_EXTENSION, DYNLIB_HANDLE, DYNLIB_LOAD, DYNLIB_UNLOAD, & DYNLIB_GETSYMBOL

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'DynamicLibrary' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class DynamicLibrary DynamicLibrary.hpp "include/DynamicLibrary.hpp"
  *
  * @brief This class defines dynamically-loaded library algorithms.
  *
  * These algorithms are useful when implementing such things as a plugin system.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Yes
  */

class DynamicLibrary : public Object< DynamicLibrary >
{
	// Friend Classes

		friend class Object< DynamicLibrary >;

public:

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		~DynamicLibrary();

	// Public Methods

		/**
		  * @brief This method loads a dynamic library using the specified path.
		  *
		  * If a dynamic library is already loaded, it will first be unloaded before proceeding.
		  *
		  * @param source
		  * 	This is the path to use when loading the dynamic library.
		  *
		  * @exception QMXException
		  * 	If the specified file was not a dynamic library.<br>
		  * 	If the specified dynamic library could not be loaded.
		  */

		void load( const Path& source );

		/**
		  * @brief This method unloads the dynamic library.
		  *
		  * @exception QMXException
		  * 	If the dynamic library could not be unloaded because it was not loaded.<br>
		  * 	If the dynamic library could not be unloaded.
		  */

		void unload();

		/**
		  * @brief This method gets the dynamic library path.
		  *
		  * @return
		  * 	A non-mutable reference to the dynamic library path.
		  */

		const Path& getPath() const;

		/**
		  * @brief This method retrieves the specified symbol from the dynamic library.
		  *
		  * @param symbol
		  * 	This is the symbol to retrieve from the dynamic library.
		  *
		  * @return
		  * 	A pointer to the retrieved symbol on success.
		  *
		  * @exception QMXException
		  * 	If the symbol could not be retrieved because the dynamic library was not loaded.<br>
		  * 	If the symbol could not be retrieved.
		  */

		void* getSymbol( const std::string& symbol ) const;

private:

	// Private Fields

		/**
		  * @brief This is the handle to the dynamic library.
		  */

		DYNLIB_HANDLE handle;

		/**
		  * @brief This is the path to the dyanmic library.
		  */

		Path dynLibPath;

	// Private Constructors

		/**
		  * @brief This is the default constructor, which is made private to prevent direct instantiation.
		  */

		DynamicLibrary();

	// Private Methods

		/**
		  * @brief This is the overridden implementation for the 'Deallocate' method.
		  *
		  * @exception QMXException
		  * 	If the dynamic library could not be unloaded.
		  */

		void deallocateImp();

		/**
		  * @brief This method unloads the dynamic library.
		  *
		  * @exception QMXException
		  * 	If the dynamic library could not be unloaded because it was not loaded.<br>
		  * 	If the dynamic library could not be unloaded.
		  */

		void unloadImp();
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_DYNAMICLIBRARY_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'DynamicLibrary.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

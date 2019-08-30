////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DynamicLibrary.cpp
// Robert M. Baker | Created : 15APR12 | Last Modified : 27AUG19 by Robert M. Baker
// Version : 2.0.0
// This is a source file for 'QMXStdLib'; it defines the implementation for a dynamically-loaded library class.
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
  * @date    Created : 15APR12
  * @date    Last Modified : 27AUG19 by Robert M. Baker
  * @version 2.0.0
  *
  * @brief This source file defines the implementation for a dynamically-loaded library class.
  *
  * @section DynamicLibraryS0000 Description
  *
  * This source file defines the implementation for a dynamically-loaded library class.
  *
  * @section DynamicLibraryS0001 License
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../include/DynamicLibrary.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Methods for the 'DynamicLibrary' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DynamicLibrary::~DynamicLibrary()
{
	try
	{
		// Perform necessary cleanup.

			if( initialized )
				deallocate();
	}
	catch( const exception& except )
	{
		// Do nothing.
	}
}

void DynamicLibrary::load( const Path& source )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "DynamicLibrary::load", 0000 );

	// Create local variables.

		Path localSource = source;

	// If a dynamic library is currently loaded, unload it.

		if( handle )
			unloadImp();

	// Load dynamic library using the specified path.

		if( !localSource.has_extension() )
			localSource.replace_extension( DYNLIB_EXTENSION );

		QMX_ASSERT( ( localSource.extension() == DYNLIB_EXTENSION ), "QMXStdLib", "DynamicLibrary::load", "00000002", localSource );
		handle = reinterpret_cast< DYNLIB_HANDLE >( DYNLIB_LOAD( localSource.string().c_str() ) );
		QMX_ASSERT( handle, "QMXStdLib", "DynamicLibrary::load", "00000003", localSource );
		dynLibPath = localSource;
}

void DynamicLibrary::unload()
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

   // Create scoped stack traces.

   	SCOPED_STACK_TRACE( "DynamicLibrary::unload", 0000 );

	// Unload dynamic library.

		unloadImp();
}

const Path& DynamicLibrary::getPath() const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Return dynamic library path to calling routine.

		return dynLibPath;
}

void* DynamicLibrary::getSymbol( const std::string& symbol ) const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "DynamicLibrary::getSymbol", 0000 );

	// Create local variables.

		void* result = nullptr;

	// Retrieve specified symbol from the dynamic library.

		QMX_ASSERT( handle, "QMXStdLib", "DynamicLibrary::getSymbol", "00000004", symbol );

		QMX_ASSERT(
			( result = reinterpret_cast< void* >( DYNLIB_GETSYMBOL( handle, symbol.c_str() ) ) ),
			"QMXStdLib",
			"DynamicLibrary::getSymbol",
			"00000005",
			dynLibPath << ", " << symbol
		);

	// Return result to calling routine.

		return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods for the 'DynamicLibrary' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DynamicLibrary::DynamicLibrary()
{
	// Intialize fields.

		handle = nullptr;
}

void DynamicLibrary::deallocateImp()
{
	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "DynamicLibrary::deallocateImp", 0000 );

	// Perform necessary cleanup.

		if( handle )
			unloadImp();
}

void DynamicLibrary::unloadImp()
{
	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "DynamicLibrary::unloadImp", 0000 );

	// Unload dynamic library.

		QMX_ASSERT( handle, "QMXStdLib", "DynamicLibrary::unloadImp", "00000006", "" );
		QMX_ASSERT( !DYNLIB_UNLOAD( handle ), "QMXStdLib", "DynamicLibrary::unloadImp", "00000007", dynLibPath );
		dynLibPath.clear();
		handle = nullptr;
}

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'DynamicLibrary.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

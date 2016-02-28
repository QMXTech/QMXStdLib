////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DynamicLibrary.cpp
// Robert M. Baker | Created : 15APR12 | Last Modified : 28FEB16 by Robert M. Baker
// Version : 1.1.2
// This is a source file for 'QMXStdLib'; it defines the implementation for a dynamically-loaded library class.
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
  * @date    Created : 15APR12
  * @date    Last Modified : 28FEB16 by Robert M. Baker
  * @version 1.1.2
  *
  * @brief This source file defines the implementation for a dynamically-loaded library class.
  *
  * @section Description
  *
  * This source file defines the implementation for a dynamically-loaded library class.
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
	// Perform necessary cleanup.

		if( Initialized )
			Deallocate();
}

void DynamicLibrary::Load( const Path& Target )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "DynamicLibrary::Load", 0000 );

	// Create local variables.

		Path LocalTarget = Target;

	// If a dynamic library is currently loaded, unload it.

		if( Handle )
			UnloadImp();

	// Load dynamic library using the specified path.

		if( !LocalTarget.has_extension() )
			LocalTarget.replace_extension( DYNLIB_EXTENSION );

		QMX_ASSERT( ( LocalTarget.extension() == DYNLIB_EXTENSION ), "QMXStdLib", "DynamicLibrary::Load", "00000002", LocalTarget );
		Handle = reinterpret_cast< DYNLIB_HANDLE >( DYNLIB_LOAD( LocalTarget.string().c_str() ) );
		QMX_ASSERT( Handle, "QMXStdLib", "DynamicLibrary::Load", "00000003", LocalTarget );
		DynLibTarget = LocalTarget;
}

void DynamicLibrary::Unload()
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

   // Create scoped stack traces.

   	SCOPED_STACK_TRACE( "DynamicLibrary::Unload", 0000 );

	// Unload dynamic library.

		UnloadImp();
}

const Path& DynamicLibrary::GetPath() const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Return dynamic library path to calling routine.

		return DynLibTarget;
}

void* DynamicLibrary::GetSymbol( const std::string& Target ) const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "DynamicLibrary::GetSymbol", 0000 );

	// Create local variables.

		void* Result = nullptr;

	// Retrieve specified symbol from the dynamic library.

		QMX_ASSERT( Handle, "QMXStdLib", "DynamicLibrary::GetSymbol", "00000004", Target );
		QMX_ASSERT( ( Result = reinterpret_cast< void* >( DYNLIB_GETSYMBOL( Handle, Target.c_str() ) ) ),
		            "QMXStdLib",
		            "DynamicLibrary::GetSymbol",
		            "00000005",
		            DynLibTarget << ", " << Target );

	// Return result to calling routine.

		return Result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods for the 'DynamicLibrary' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DynamicLibrary::DynamicLibrary()
{
	// Intialize fields.

		Handle = nullptr;
}

void DynamicLibrary::DeallocateImp()
{
	// Perform necessary cleanup.

		if( Handle )
			UnloadImp();
}

void DynamicLibrary::OperatorAssignImp( const Object* Instance )
{
	// Create local variables.

		const DynamicLibrary* DInstance = dynamic_cast< const DynamicLibrary* >( Instance );

	// Assign specified object to 'this'.

		Handle = DInstance->Handle;
		DynLibTarget = DInstance->DynLibTarget;
}

void DynamicLibrary::UnloadImp()
{
	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "DynamicLibrary::UnloadImp", 0000 );

	// Unload dynamic library.

		QMX_ASSERT( Handle, "QMXStdLib", "DynamicLibrary::UnloadImp", "00000006", "" );
		QMX_ASSERT( !DYNLIB_UNLOAD( Handle ), "QMXStdLib", "DynamicLibrary::UnloadImp", "00000007", DynLibTarget );
		DynLibTarget.clear();
		Handle = nullptr;
}

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'DynamicLibrary.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

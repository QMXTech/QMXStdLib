////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PluginManager.cpp
// Robert M. Baker | Created : 15APR12 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.1
// This is a source file for 'QMXStdLib'; it defines the implementation for a plugin manager class.
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
  * @date    Last Modified : 27FEB16 by Robert M. Baker
  * @version 1.1.1
  *
  * @brief This source file defines the implementation for a plugin manager class.
  *
  * @section Description
  *
  * This source file defines the implementation for a plugin manager class.
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

#include "../include/PluginManager.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Field Initializers for the 'PluginManager' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<> PluginManager* Singleton< PluginManager >::SingletonInstance = nullptr;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Methods for the 'PluginManager' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PluginManager::~PluginManager()
{
	// Perform necessary cleanup.

		if( Initialized )
			Deallocate();
}

void PluginManager::RegisterModule( const string& ModuleID )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "PluginManager::RegisterModule", 0000 );

	// Register specified module with plugin manager, if it has not already been registered.

		QMX_ASSERT( Modules.insert( ModuleMap::value_type( ModuleID, PluginVector() ) ).second,
		            "QMXStdLib",
		            "PluginManager::RegisterModule",
		            "00000011",
		            ModuleID );
}

void PluginManager::UnregisterModule( const string& ModuleID )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "PluginManager::UnregisterModule", 0000 );

	// Create local variables.

		auto ModuleMapIterator = Modules.find( ModuleID );

	// Unregister specified module from plugin manager, if it has been registered.

		QMX_ASSERT( ( ModuleMapIterator != Modules.end() ), "QMXStdLib", "PluginManager::UnregisterModule", "00000012", ModuleID );

		for( const auto& Index : ModuleMapIterator->second )
			Index.PluginStopFunction();

		Modules.erase( ModuleMapIterator );
}

void PluginManager::AutoLoad( const Path& Target )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "PluginManager::AutoLoad", 0000 );

	// Create local variables.

		bool FoundPlugins = false;
		Path LoadTarget = Target;
		Path IndexTarget;

	// Load all plugins at specified path.

		if( boost::filesystem::is_symlink( LoadTarget ) )
			FileSystem::MakeCanonical( LoadTarget );

		QMX_ASSERT( boost::filesystem::is_directory( LoadTarget ), "QMXStdLib", "PluginManager::AutoLoad", "00000013", Target );

		for( DirectoryIterator Index( LoadTarget ); Index != DIRECTORY_END; Index++ )
		{
			IndexTarget = Index->path();

			if( boost::filesystem::is_symlink( IndexTarget ) )
				FileSystem::MakeCanonical( IndexTarget );

			if( boost::filesystem::is_regular_file( IndexTarget ) && ( IndexTarget.extension() == DYNLIB_EXTENSION ) )
			{
				if( !FoundPlugins )
					FoundPlugins = true;

				LoadImp( IndexTarget );
			}
		}

		QMX_ASSERT( FoundPlugins, "QMXStdLib", "PluginManager::AutoLoad", "00000014", Target );
}

void PluginManager::Load( const Path& Target )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "PluginManager::Load", 0000 );

	// Load specified target.

		LoadImp( Target );
}

void PluginManager::Unload( const string& ModuleID, const string& PluginID )
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "PluginManager::Unload", 0000 );

	// Create local variables.

		auto ModuleMapIterator = Modules.find( ModuleID );
		bool IsDone = false;
		size_t Index = Null;

	// Unload specified plugin, if it exists.

		QMX_ASSERT( ( ModuleMapIterator != Modules.end() ), "QMXStdLib", "PluginManager::Unload", "0000001A", ModuleID << ", " << PluginID );

		while( !IsDone && ( Index < ModuleMapIterator->second.size() ) )
		{
			if( ModuleMapIterator->second[ Index ].PluginInstance->GetID() == PluginID )
			{
				ModuleMapIterator->second[ Index ].PluginStopFunction();
				ModuleMapIterator->second.erase( ( ModuleMapIterator->second.begin() + Index ) );
				IsDone = true;
			}

			Index++;
		}

		QMX_ASSERT( IsDone, "QMXStdLib", "PluginManager::Unload", "0000001B", ModuleID << ", " << PluginID );
}

void PluginManager::GetPluginList( PluginManager::PluginMap& Target, const string& ModuleID ) const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "PluginManager::GetPluginList", 0000 );

	// Create local variables.

		auto ModuleMapIterator = Modules.find( ModuleID );

	// Construct a map of currently loaded plugins and their versions for the specified module, if it exists.

		QMX_ASSERT( ( ModuleMapIterator != Modules.end() ), "QMXStdLib", "PluginManager::GetPluginList", "0000001C", ModuleID );

		for( const auto& Index : ModuleMapIterator->second )
			Target[ Index.PluginInstance->GetID() ] = Index.PluginInstance->GetVersion();
}

void PluginManager::GetPluginMeta( StringMap& Target, const string& ModuleID, const string& PluginID ) const
{
	// Obtain locks.

		SCOPED_READ_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "PluginManager::GetPluginMeta", 0000 );

	// Create local variables.

		auto ModuleMapIterator = Modules.find( ModuleID );
		bool IsDone = false;
		size_t Index = Null;

	// Retrieve the specified plugin's meta data from the specified module, if it exists.

		QMX_ASSERT( ( ModuleMapIterator != Modules.end() ), "QMXStdLib", "PluginManager::GetPluginMeta", "0000001D", ModuleID << ", " << PluginID );

		while( !IsDone && ( Index < ModuleMapIterator->second.size() ) )
		{
			if( ModuleMapIterator->second[ Index ].PluginInstance->GetID() == PluginID )
			{
				ModuleMapIterator->second[ Index ].PluginInstance->GetMeta( Target );
				IsDone = true;
			}

			Index++;
		}

		QMX_ASSERT( IsDone, "QMXStdLib", "PluginManager::GetPluginMeta", "0000001E", ModuleID << ", " << PluginID );
}

void PluginManager::Install( Plugin* Instance ) const
{
	// Install specified plugin.

		Instance->Install();

		if( SystemInitialized )
			Instance->Initialize();
}

void PluginManager::Uninstall( Plugin* Instance ) const
{
	// Uninstall specified plugin.

		if( SystemInitialized )
			Instance->Shutdown();

		Instance->Uninstall();
}

void PluginManager::Initialize()
{
	// Obtain locks.

		SCOPED_WRITE_LOCK;

	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "PluginManager::Initialize", 0000 );

	// Initialize all installed plugins.

		QMX_ASSERT( !SystemInitialized, "QMXStdLib", "PluginManager::Initialize", "0000001F", "" );

		for( const auto& ModuleIndex : Modules )
		{
			for( const auto& PluginIndex : ModuleIndex.second )
				PluginIndex.PluginInstance->Initialize();
		}

		SystemInitialized = true;
}

PluginManager::PointerType PluginManager::Create()
{
	// Create local variables.

		PointerType Result( new PluginManager() );

	// Initialize new instance.

		Result->Allocate();

	// Return result to calling routine.

		return Result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods for the 'PluginManager' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PluginManager::PluginManager()
{
	// Initialize fields.

		SystemInitialized = false;
}

void PluginManager::DeallocateImp()
{
	// Perform necessary cleanup.

		for( const auto& ModuleIndex : Modules )
		{
			for( const auto& PluginIndex : ModuleIndex.second )
				PluginIndex.PluginStopFunction();
		}

		Modules.clear();
		SystemInitialized = false;
}

void PluginManager::LoadImp( const Path& Target )
{
	// Create scoped stack traces.

		SCOPED_STACK_TRACE( "PluginManager::LoadImp", 0000 );

	// Create local variables.

		ModuleMap::iterator ModuleMapIterator;
		PluginData TargetData;

	// Load specified plugin, if not already loaded.

		for( const auto& ModuleIndex : Modules )
		{
			for( const auto& PluginIndex : ModuleIndex.second )
				QMX_ASSERT( !boost::filesystem::equivalent( PluginIndex.DynLibInstance->GetPath(), Target ),
				            "QMXStdLib",
				            "PluginManager::LoadImp",
				            "00000015",
				            Target );
		}

		TargetData.DynLibInstance = DynamicLibrary::Create();
		TargetData.DynLibInstance->Load( Target );
		TargetData.PluginGetModuleFunction = reinterpret_cast< PluginGetModulePointer >( TargetData.DynLibInstance->GetSymbol( "PluginGetModule" ) );
		QMX_ASSERT( TargetData.PluginGetModuleFunction, "QMXStdLib", "PluginManager::LoadImp", "00000016", Target );
		TargetData.PluginStartFunction = reinterpret_cast< PluginStartPointer >( TargetData.DynLibInstance->GetSymbol( "PluginStart" ) );
		QMX_ASSERT( TargetData.PluginStartFunction, "QMXStdLib", "PluginManager::LoadImp", "00000017", Target );
		TargetData.PluginStopFunction = reinterpret_cast< PluginStopPointer >( TargetData.DynLibInstance->GetSymbol( "PluginStop" ) );
		QMX_ASSERT( TargetData.PluginStopFunction, "QMXStdLib", "PluginManager::LoadImp", "00000018", Target );
		ModuleMapIterator = Modules.find( TargetData.PluginGetModuleFunction() );
		QMX_ASSERT( ( ModuleMapIterator != Modules.end() ),
		            "QMXStdLib",
		            "PluginManager::LoadImp",
		            "00000019",
		            Target << ", " << TargetData.PluginGetModuleFunction() );
		TargetData.PluginStartFunction( &TargetData.PluginInstance );
		ModuleMapIterator->second.push_back( TargetData );
}

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'PluginManager.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

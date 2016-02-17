////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PluginManager.hpp
// Robert M. Baker | Created : 15APR12 | Last Modified : 28JAN16 by Robert M. Baker
// Version : 1.0.0
// This is a header file for 'QMXStdLib'; it defines the interface for a plugin manager class.
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
  * @date    Last Modified : 28JAN16 by Robert M. Baker
  * @version 1.0.0
  *
  * @brief This header file defines the interface for a plugin manager class.
  *
  * @section Description
  *
  * This header file defines the interface for a plugin manager class.
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

#ifndef __QMX_QMXSTDLIB_PLUGINMANAGER_HPP_
#define __QMX_QMXSTDLIB_PLUGINMANAGER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "Object.hpp"
#include "FileSystem.hpp"
#include "DynamicLibrary.hpp"
#include "Utility.hpp"
#include "Mixins/Singleton.hpp"
#include "Mixins/Plugin.hpp"
#include "RAII/ScopedStackTrace.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define PLUGIN_MANAGER   QMXStdLib::PluginManager::GetSingleton()
#define PLUGIN_MANAGER_P QMXStdLib::PluginManager::GetSingletonPointer()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'PluginManager' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class PluginManager PluginManager.hpp "include/PluginManager.hpp"
  *
  * @brief This class defines plugin management algorithms.
  *
  * These algorithms are useful when it is necessary to handle dynamically-loaded plugins.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Yes
  */

class PluginManager : public Object< PluginManager >, public Singleton< PluginManager >
{
public:

	// Public Type Definitions

		typedef std::unordered_map< std::string, QMXStdLib::Utility::VersionData > PluginMap;

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		virtual ~PluginManager();

	// Public Methods

		/**
		  * @brief This method registers a module with the plugin manager.
		  *
		  * A module would be a discrete unit of algorithims with a specific function, such as an audio or graphics rendering module.
		  *
		  * @param ModuleID
		  * 	This is the ID with which to register with the plugin manager.
		  *
		  * @exception QMXException
		  * 	If the specified module could not be registered because it already exists.
		  */

		void RegisterModule( const std::string& ModuleID );

		/**
		  * @brief This method unregisters a previously registered module from the plugin manager.
		  *
		  * If a module has any loaded plugins at the time of being unregistered, they will all be automatically unloaded.
		  *
		  * @param ModuleID
		  * 	This is the ID with which to unregister from the plugin manager.
		  *
		  * @exception QMXException
		  * 	If the specified module could not be unregistered because it did not exist.<br>
		  * 	If an error occurs while unloading any plugins.
		  */

		void UnregisterModule( const std::string& ModuleID );

		/**
		  * @brief This method loads all plugins at the specified path.
		  *
		  * This method will load all files with a dynamic library extension (which depends on the target platform) but will not recurse into subdirectories.
		  *
		  * @param Target
		  * 	This is the directory path to use when loading plugins.
		  *
		  * @exception QMXException
		  * 	If no plugins could be loaded because the specified path was not a directory.<br>
		  * 	If no plugins were found at the specified path.<br>
		  * 	If the specified plugin was already loaded.<br>
		  * 	If the specified plugin did not have a 'PluginGetModule' function.<br>
		  * 	If the specified plugin did not have a 'PluginStart' function.<br>
		  * 	If the specified plugin did not have a 'PluginStop' function.<br>
		  * 	If the specified plugin could not be loaded because its module was not registered.<br>
		  * 	If an error occurs while creating the dynamic library instance.<br>
		  * 	If an error occurs while loading the dynamic library target.<br>
		  * 	If an error occurs while starting the plugin.
		  */

		void AutoLoad( const Path& Target );

		/**
		  * @brief This method loads the specified plugin.
		  *
		  * This method will call the plugin dynamic library's 'PluginStart' function.
		  *
		  * @param Target
		  * 	This is the plugin dynamic library path to use when loading.
		  *
		  * @exception QMXException
		  * 	If the specified plugin was already loaded.<br>
		  * 	If the specified plugin did not have a 'PluginGetModule' function.<br>
		  * 	If the specified plugin did not have a 'PluginStart' function.<br>
		  * 	If the specified plugin did not have a 'PluginStop' function.<br>
		  * 	If the specified plugin could not be loaded because its module was not registered.<br>
		  * 	If an error occurs while creating the dynamic library instance.<br>
		  * 	If an error occurs while loading the dynamic library target.<br>
		  * 	If an error occurs while starting the plugin.
		  */

		void Load( const Path& Target );

		/**
		  * @brief This method unloads the specified plugin from the specified module, if it exists.
		  *
		  * This method will call the plugin dynamic library's 'PluginStop' function.
		  *
		  * @param ModuleID
		  * 	This is the module ID to use when unloading.
		  *
		  * @param PluginID
		  * 	This is the plugin ID to use when unloading.
		  *
		  * @exception QMXException
		  * 	If the specified plugin could not be unloaded because its module did not exist.<br>
		  * 	If the specified plugin could not be unloaded because it was not loaded.<br>
		  * 	If an error occurs while stopping the plugin.
		  */

		void Unload( const std::string& ModuleID, const std::string& PluginID );

		/**
		  * @brief This method constructs a map of currently loaded plugins and their versions for the specified module.
		  *
		  * The map key will be the plugin ID, and the map value will be the plugin version.
		  *
		  * @param Target
		  * 	This is a 'PluginMap' reference which will receive the constructed map.
		  *
		  * @param ModuleID
		  * 	This is the module ID from which to construct the map.
		  *
		  * @exception QMXException
		  * 	If a plugin list could not be constructed because the specified module did not exist.
		  */

		void GetPluginList( PluginMap& Target, const std::string& ModuleID ) const;

		/**
		  * @brief This method retrieves the specified plugin's meta data from the specified module.
		  *
		  * The meta data is arbitrary key-value pairs whose meaning is determined by the application
		  *
		  * @param Target
		  * 	This is a 'StringMap' reference which will receive the meta data.
		  *
		  * @param ModuleID
		  * 	This is the module ID to use when retrieving the meta data.
		  *
		  * @param PluginID
		  * 	This is the plugin ID to use when retrieving the meta data.
		  *
		  * @exception QMXException
		  * 	If the specified plugin's meta data could not be retrieved because its module did not exist.<br>
		  * 	If the specified plugin's meta data could not be retrieved because it did not exist.
		  */

		void GetPluginMeta( StringMap& Target, const std::string& ModuleID, const std::string& PluginID ) const;

		/**
		  * @brief This method installs the specified plugin.
		  *
		  * This method will be called automatically by a loading plugin.  If the plugin manager has been initialized (signifying that the system is initialized),
		  * then this method will also initialize the plugin.
		  *
		  * @param Instance
		  * 	This is the plugin pointer to use for installation.
		  *
		  * @exception QMXException
		  * 	If an error occurs during plugin installation.
		  */

		void Install( Plugin* Instance ) const;

		/**
		  * @brief This method uninstalls the specified plugin.
		  *
		  * This method will always be called automatically by an unloading plugin.  If the plugin manager has been initialized (signifying that the system is
		  * initialized), then this method will also shutdown the plugin.
		  *
		  * @param Instance
		  * 	This is the plugin pointer to use for uninstallation.
		  *
		  * @exception QMXException
		  * 	If an error occurs during plugin uninstallation.
		  */

		void Uninstall( Plugin* Instance ) const;

		/**
		  * @brief This method initializes all installed plugins.
		  *
		  * @exception QMXException
		  * 	If attempted to initialize plugin manager, but it was already initialized.<br>
		  * 	If an error occurs during plugin initialization.
		  */

		void Initialize();

		/**
		  * @brief This method creates an instance of this class.
		  *
		  * @return
		  * 	A pointer to the newly created instance.
		  */

		static PointerType Create();

private:

	// Private Data Types

		/**
		  * @brief This structure stores information about a loaded plugin.
		  */

		struct PluginData
		{
		public:

			// Public Fields

				/**
				  * @brief This is the dynamic library instance pointer.
				  */

				DynamicLibrary::PointerType DynLibInstance;

				/**
				  * @brief This is the plugin object pointer.
				  */

				Plugin* PluginInstance;

				/**
				  * @brief This is the pointer to the plugin's module aquisition function.
				  */

				std::string (*PluginGetModuleFunction)();

				/**
				  * @brief This is the pointer to the plugin's start function.
				  */

				void (*PluginStartFunction)( Plugin** );

				/**
				  * @brief This is the pointer to the plugin's stop function.
				  */

				void (*PluginStopFunction)();
		};

	// Private Type Definitions

		typedef std::vector< PluginData > PluginVector;
		typedef std::unordered_map< std::string, PluginVector > ModuleMap;
		typedef std::string (*PluginGetModulePointer)();
		typedef void (*PluginStartPointer)( Plugin** );
		typedef void (*PluginStopPointer)();

	// Private Constructors

		/**
		  * @brief This is the default constructor, which is made private to prevent direct instantiation.
		  */

		PluginManager();

	// Private Methods

		/**
		  * @brief This is the overridden implementation for the 'Deallocate' method.
		  *
		  * This method will unload all currently installed plugins.
		  *
		  * @exception QMXException
		  * 	If an error occurs while unloading any plugins.
		  */

		void DeallocateImp();

		/**
		  * @brief This method loads the specified plugin.
		  *
		  * This method will call the plugin dynamic library's 'PluginStart' function.
		  *
		  * @param Target
		  * 	This is the plugin dynamic library path to use when loading.
		  *
		  * @exception QMXException
		  * 	If the specified plugin was already loaded.<br>
		  * 	If the specified plugin did not have a 'PluginGetModule' function.<br>
		  * 	If the specified plugin did not have a 'PluginStart' function.<br>
		  * 	If the specified plugin did not have a 'PluginStop' function.<br>
		  * 	If the specified plugin could not be loaded because its module was not registered.<br>
		  * 	If an error occurs while creating the dynamic library instance.<br>
		  * 	If an error occurs while loading the dynamic library target.<br>
		  * 	If an error occurs while starting the plugin.
		  */

		void LoadImp( const Path& Target );

	// Private Fields

		/**
		  * @brief This is the boolean flag which determines if the system has been initialized or not.
		  */

		bool SystemInitialized;

		/**
		  * @brief This is the map of currently registered modules and their loaded plugins.
		  */

		ModuleMap Modules;
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_PLUGINMANAGER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'PluginManager.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

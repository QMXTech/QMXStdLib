////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plugin.hpp
// Robert M. Baker | Created : 14APR12 | Last Modified : 21FEB16 by Robert M. Baker
// Version : 1.1.2
// This is a header file for 'QMXStdLib'; it defines the interface for a mixin class to a plugin.
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
  * @date    Created : 14APR12
  * @date    Last Modified : 21FEB16 by Robert M. Baker
  * @version 1.1.2
  *
  * @brief This header file defines the interface for a mixin class to a plugin.
  *
  * @section Description
  *
  * This header file defines the interface for a mixin class to a plugin.
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

#ifndef __QMX_QMXSTDLIB_PLUGIN_HPP_
#define __QMX_QMXSTDLIB_PLUGIN_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../Base.hpp"
#include "../Utility.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'Plugin' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class Plugin Plugin.hpp "include/Plugin.hpp"
  *
  * @brief This class defines a mixin interface for a generic plugin.
  *
  * This is useful when there is a need to create a class which will serve as a plugin.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Conditionally ( The sub-class must implement '*Imp' in a thread-safe manner. )
  */

class Plugin
{
public:

	// Public Constructors

		/**
		  * @brief This is the default constructor.
		  */

		Plugin()
		{
			// Do nothing.
		}

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		virtual ~Plugin()
		{
			// Do nothing.
		}

	// Public Methods

		/**
		  * @brief This method retrieves the unique plugin ID.
		  *
		  * @return
		  * 	A string containing the unique plugin ID.
		  */

		std::string GetID() const
		{
			// Return unique plugin ID to calling routine.

				return GetIDImp();
		}

		/**
		  * @brief This method retrieves the plugin description.
		  *
		  * @return
		  * 	A 'VersionData' instance containing the version data for the plugin.
		  */

		QMXStdLib::Utility::VersionData GetVersion() const
		{
			// Return plugin version to calling routine.

				return GetVersionImp();
		}

		/**
		  * @brief This method retrieves the plugin meta data.
		  *
		  * @param Target
		  * 	This is a string map into which the plugin meta data will be inserted.
		  */

		void GetMeta( StringMap& Target ) const
		{
			// Get plugin meta data.

				GetMetaImp( Target );
		}

		/**
		  * @brief This method installs the plugin, but does not perform any actions which are dependent on a fully-initialized system.
		  *
		  * @exception QMXException
		  * 	If an error occurs during installation.
		  */

		void Install()
		{
			// Install the plugin.

				InstallImp();
		}

		/**
		  * @brief This method uninstalls the plugin, but does not perform any actions which are dependent on a fully-initialized system.
		  *
		  * @exception QMXException
		  * 	If an error occurs during uninstallation.
		  */

		void Uninstall()
		{
			// Uninstall the plugin.

				UninstallImp();
		}

		/**
		  * @brief This method initializes the plugin.
		  *
		  * @exception QMXException
		  * 	If an error occurs during initialization.
		  */

		void Initialize()
		{
			// Initialize the plugin.

				InitializeImp();
		}

		/**
		  * @brief This method shuts down the plugin.
		  *
		  * @exception QMXException
		  * 	If an error occurs during shutdown.
		  */

		void Shutdown()
		{
			// Shutdown the plugin.

				ShutdownImp();
		}

private:

	// Private Methods

		/**
		  * @brief This is the overridable implementation for the 'GetID' method.
		  *
		  * @return
		  * 	A string containing the unique plugin ID.
		  */

		virtual std::string GetIDImp() const = PURE_VIRTUAL;

		/**
		  * @brief This is the overridable implementation for the 'GetVersion' method.
		  *
		  * @return
		  * 	A 'VersionData' instance containing the version data for the plugin.
		  */

		virtual QMXStdLib::Utility::VersionData GetVersionImp() const = PURE_VIRTUAL;

		/**
		  * @brief This is the overridable implementation for the 'GetMeta' method.
		  *
		  * @param Target
		  * 	This is a string map into which the plugin meta data will be inserted.
		  */

		virtual void GetMetaImp( StringMap& Target ) const = PURE_VIRTUAL;

		/**
		  * @brief This is the overridable implementation for the 'Install' method.
		  *
		  * @exception QMXException
		  * 	If an error occurs during installation.
		  */

		virtual void InstallImp() = PURE_VIRTUAL;

		/**
		  * @brief This is the overridable implementation for the 'Uninstall' method.
		  *
		  * @exception QMXException
		  * 	If an error occurs during uninstallation.
		  */

		virtual void UninstallImp() = PURE_VIRTUAL;

		/**
		  * @brief This is the overridable implementation for the 'Initialize' method.
		  *
		  * @exception QMXException
		  * 	If an error occurs during initialization.
		  */

		virtual void InitializeImp() = PURE_VIRTUAL;

		/**
		  * @brief This is the overridable implementation for the 'Shutdown' method.
		  *
		  * @exception QMXException
		  * 	If an error occurs during shutdown.
		  */

		virtual void ShutdownImp() = PURE_VIRTUAL;
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_PLUGIN_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'Plugin.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

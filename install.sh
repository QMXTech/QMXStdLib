#! /bin/bash
################################################################################################################################################################
# install.sh
# Robert M. Baker | Created : 10DEC11 | Last Modified : 14FEB16 by Robert M. Baker
# Version : 1.0.0
# This is a bash script for installing/uninstalling 'QMXStdLib'.
################################################################################################################################################################
# Copyright (C) 2011-2016 QuantuMatriX Software, LLP.
#
# This file is part of 'QMXStdLib'.
#
# 'QMXStdLib' is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option) any later version.
#
# 'QMXStdLib' is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License along with 'QMXStdLib'.  If not, see <http://www.gnu.org/licenses/>.
################################################################################################################################################################

################################################################################################################################################################
# Constants
################################################################################################################################################################

DEF_ABI_VERSION="1"
DEF_BUILD_VERSION="1.0.0"
DEF_TARGET="qmxstdlib"

LIN_DEF_HEADERS_PATH="/usr/local/include"
LIN_DEF_LIBS_PATH="/usr/local/lib"
LIN_DEF_DOCS_PATH="/usr/local/share/doc"

MAC_DEF_HEADERS_PATH=""
MAC_DEF_LIBS_PATH=""
MAC_DEF_DOCS_PATH=""

WIN_DEF_HEADERS_PATH=""
WIN_DEF_LIBS_PATH=""
WIN_DEF_DOCS_PATH=""

################################################################################################################################################################
# Variables
################################################################################################################################################################

Platform=${1}
Mode=${2}
HeadersPath=${3}
LibsPath=${4}
DocsPath=${5}
ABIVersion=""
BuildVersion=""
Target=""

################################################################################################################################################################
# Functions
################################################################################################################################################################

DoAbort()
{
	# Display appropriate abort message.

		if [[ ${2} > 0 ]]; then
			echo -e "install.sh: ${FG_RED}${1}${RESET}"
		else
			echo -e "install.sh: ${1}"
		fi

		echo -e "Usage: install.sh PLATFORM MODE=0 [HEADERS_PATH] [LIBS_PATH] [DOCS_PATH] [ABI_VERSION] [BUILD_VERSION] [TARGET]"
		echo -e "   or: install.sh PLATFORM MODE=1 [HEADERS_PATH] [LIBS_PATH] [DOCS_PATH] [BUILD_VERSION] [TARGET]"
		echo -e "Example: install.sh lin 0 /usr/local/include /usr/local/lib /usr/local/share/doc foo 1 1.0.0"
		echo -e "Example: install.sh lin 1 /usr/local/include /usr/local/lib /usr/local/share/doc foo 1.0.0"
		echo -e
		echo -e "   -h, --help        Display this help text and exit."
		echo -e
		echo -e "   'PLATFORM' must be one of: 'lin' (GNU Linux), 'mac' (Apple Mac OS X), or 'win' (Microsoft Windows)"
		echo -e "   'MODE' must be one of: 0 (Install) or 1 (Uninstall)"
		echo -e
		echo -e "   All parameters after 'MODE' have a default value.  An empty string can be supplied in the case one desires to have default values for some"
		echo -e "   parameters, while still being able to specify custom values for others.  For example:"
		echo -e
		echo -e "      install.sh lin 0 \"\" \"\" /foo/bar/doc"
		echo -e
		echo -e "   Will use defaults for 'HEADERS_PATH' and 'LIBS_PATH', override 'DOCS_PATH', and then use defaults for the remaining parameters."

	# Exit script with specified abort code.

		exit ${2}
}

DoInstallLin()
{
	# Create headers path, if it does not exist.

		if [[ ! -e ${HeadersPath} ]]; then mkdir -p ${HeadersPath}; fi

	# Copy headers from source tree to target path.

		cp -rf ./include/* ${HeadersPath}

	# Repair permissions on all files and directories at headers path.

		find ${HeadersPath} -type d -exec chmod 755 {} \;
		find ${HeadersPath} -type f -exec chmod 644 {} \;

	# Create libraries path, if it does not exist.

		if [[ ! -e ${LibsPath} ]]; then mkdir -p ${LibsPath}; fi

	# Remove old library files with same ABI version, if any exist.

		if ls ${LibsPath}/lib${Target}*.so.${ABIVersion}.* &> /dev/null; then rm -f ${LibsPath}/lib${Target}*.so.${ABIVersion}.*; fi

	# Copy new library files from source tree to target path.

		cp -fP ./build/lib${Target}*.so* ${LibsPath}

	# Repair permissions on new library files.

		chmod 644 ${LibsPath}/lib${Target}*.so.${ABIVersion}.*

	# Rebuild library cache.

		ldconfig

	# Create documentation path, if it does not exist.

		if [[ ! -e ${DocsPath}/html ]]; then mkdir -p ${DocsPath}/html; fi

	# Create Doxygen documentation.

		doxygen qmxstdlib.dox &> /dev/null

	# Copy documentation from source tree to target path.

		cp -f ./doc/* ${DocsPath}
		cp -f ./build/doc/html/*.css ${DocsPath}/html
		cp -f ./build/doc/html/*.html ${DocsPath}/html
		cp -f ./build/doc/html/*.png ${DocsPath}/html
		cp -rf ./build/doc/html/search ${DocsPath}/html

	# Repair permissions on all files and directories at documentation path.

		find ${DocsPath} -type d -exec chmod 755 {} \;
		find ${DocsPath} -type f -exec chmod 644 {} \;
}

DoUninstallLin()
{
	# Perform uninstallation on a GNU Linux platform.

		rm -rf ${HeadersPath}
		rm -f ${LibsPath}/lib${Target}*
		rm -rf ${DocsPath}
}

DoInstallMac()
{
	# Perform installation on an Apple Mac OS X platform.

		echo -e "Stub: Perform Apple Mac OS X install."
}

DoUninstallMac()
{
	# Perform uninstallation on an Apple Mac OS X platform.

		echo -e "Stub: Perform Apple Mac OS X uninstall."
}

DoInstallWin()
{
	# Perform installation on a Microsoft Windows platform.

		echo -e "Stub: Perform Microsoft Windows install."
}

DoUninstallWin()
{
	# Perform uninstallation on a Microsoft Windows platform.

		echo -e "Stub: Perform Microsoft Windows uninstall."
}

################################################################################################################################################################
# Arguments Check
################################################################################################################################################################

if [[ ${#} == 0 ]]; then
	DoAbort "No arguments specified!" 1
elif [[ ( ${1} == "-h" ) || ( ${1} == "--help" ) ]]; then
	DoAbort "Display help text and exit." 0
elif [[ ${#} < 2 ]]; then
	DoAbort "Incorrect number of arguments specified!" 2
elif [[ ( ${Platform} != "lin" ) && ( ${Platform} != "mac" ) && ( ${Platform} != "win" ) ]]; then
	DoAbort "Unsupported platform ( '${Platform}' ) specified!" 3
elif [[ ( ${Platform} == "lin" ) && ( $( whoami ) != "root" ) ]]; then
	DoAbort "This script must be executed with root privileges in GNU Linux!" 4
elif [[ ( ${Mode} < 0 ) || ( ${Mode} > 1 ) ]]; then
	DoAbort "Unknown mode ( '${Mode}' ) specified!" 5
fi

################################################################################################################################################################
# Script Body
################################################################################################################################################################

# Install or uninstall based on the specified platform and mode.

if [[ ${Mode} == 0 ]]; then
	ABIVersion=${6}
	BuildVersion=${7}
	Target=${8}
	if [[ -z ${ABIVersion} ]]; then ABIVersion=${DEF_ABI_VERSION}; fi
	if [[ -z ${BuildVersion} ]]; then BuildVersion=${DEF_BUILD_VERSION}; fi
	if [[ -z ${Target} ]]; then Target=${DEF_TARGET}; fi

	if [[ ${Platform} == "lin" ]]; then
		if [[ -z ${HeadersPath} ]]; then HeadersPath=${LIN_DEF_HEADERS_PATH}; fi
		if [[ -z ${LibsPath} ]]; then LibsPath=${LIN_DEF_LIBS_PATH}; fi
		if [[ -z ${DocsPath} ]]; then DocsPath=${LIN_DEF_DOCS_PATH}; fi
		HeadersPath="${HeadersPath}/${Target}"
		DocsPath="${DocsPath}/${Target}.${BuildVersion}"
		DoInstallLin
	elif [[ ${Platform} == "mac" ]]; then
		if [[ -z ${HeadersPath} ]]; then HeadersPath=${MAC_DEF_HEADERS_PATH}; fi
		if [[ -z ${LibsPath} ]]; then LibsPath=${MAC_DEF_LIBS_PATH}; fi
		if [[ -z ${DocsPath} ]]; then DocsPath=${MAC_DEF_DOCS_PATH}; fi
		HeadersPath="${HeadersPath}/${Target}"
		DocsPath="${DocsPath}/${Target}.${BuildVersion}"
		DoInstallMac
	else
		if [[ -z ${HeadersPath} ]]; then HeadersPath=${WIN_DEF_HEADERS_PATH}; fi
		if [[ -z ${LibsPath} ]]; then LibsPath=${WIN_DEF_LIBS_PATH}; fi
		if [[ -z ${DocsPath} ]]; then DocsPath=${WIN_DEF_DOCS_PATH}; fi
		HeadersPath="${HeadersPath}/${Target}"
		DocsPath="${DocsPath}/${Target}.${BuildVersion}"
		DoInstallWin
	fi
else
	BuildVersion=${6}
	Target=${7}
	if [[ -z ${BuildVersion} ]]; then BuildVersion=${DEF_BUILD_VERSION}; fi
	if [[ -z ${Target} ]]; then Target=${DEF_TARGET}; fi

	if [[ ${Platform} == "lin" ]]; then
		if [[ -z ${HeadersPath} ]]; then HeadersPath=${LIN_DEF_HEADERS_PATH}; fi
		if [[ -z ${LibsPath} ]]; then LibsPath=${LIN_DEF_LIBS_PATH}; fi
		if [[ -z ${DocsPath} ]]; then DocsPath=${LIN_DEF_DOCS_PATH}; fi
		HeadersPath="${HeadersPath}/${Target}"
		DocsPath="${DocsPath}/${Target}.${BuildVersion}"
		DoUninstallLin
	elif [[ ${Platform} == "mac" ]]; then
		if [[ -z ${HeadersPath} ]]; then HeadersPath=${MAC_DEF_HEADERS_PATH}; fi
		if [[ -z ${LibsPath} ]]; then LibsPath=${MAC_DEF_LIBS_PATH}; fi
		if [[ -z ${DocsPath} ]]; then DocsPath=${MAC_DEF_DOCS_PATH}; fi
		HeadersPath="${HeadersPath}/${Target}"
		DocsPath="${DocsPath}/${Target}.${BuildVersion}"
		DoUninstallMac
	else
		if [[ -z ${HeadersPath} ]]; then HeadersPath=${WIN_DEF_HEADERS_PATH}; fi
		if [[ -z ${LibsPath} ]]; then LibsPath=${WIN_DEF_LIBS_PATH}; fi
		if [[ -z ${DocsPath} ]]; then DocsPath=${WIN_DEF_DOCS_PATH}; fi
		HeadersPath="${HeadersPath}/${Target}"
		DocsPath="${DocsPath}/${Target}.${BuildVersion}"
		DoUninstallWin
	fi
fi

################################################################################################################################################################
# End of 'install.sh'
################################################################################################################################################################

#! /bin/bash
################################################################################################################################################################
# install.sh
# Robert M. Baker | Created : 15FEB16 | Last Modified : 18FEB16 by Robert M. Baker
# Version : 1.0.0
# This is a bash script for setup/cleanup of the test directory for 'QMXStdLibTest'.
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
# Variables
################################################################################################################################################################

Platform=${1}
Mode=${2}

################################################################################################################################################################
# Functions
################################################################################################################################################################

DoAbort()
{
	# Display appropriate abort message.

		if [[ ${2} > 0 ]]; then
			echo -e "setup.sh: ${FG_RED}${1}${RESET}"
		else
			echo -e "setup.sh: ${1}"
		fi

		echo -e "Usage: setup.sh PLATFORM MODE"
		echo -e "Example: install.sh lin 0"
		echo -e "Example: install.sh lin 1"
		echo -e
		echo -e "   -h, --help        Display this help text and exit."
		echo -e
		echo -e "   'PLATFORM' must be one of: 'lin' (GNU Linux) or 'mac' (Apple Mac OS X)"
		echo -e "   'MODE' must be one of: 0 (Setup) or 1 (Cleanup)"

	# Exit script with specified abort code.

		exit ${2}
}

DoSetupLin()
{
	# Perform setup on a GNU Linux platform.

		mkdir EmptyTestDirectory
		mkdir -p NonEmptyTestDirectory/NonEmptyTestSubdirectory
		mkdir -p TestPlugins/debug
		mkdir -p TestPlugins/release
		touch EmptyTestFile.txt
		echo "This is a non-empty test file." > NonEmptyTestFile.txt
		cp NonEmptyTestFile.txt NonEmptyTestDirectory
		cp NonEmptyTestFile.txt NonEmptyTestDirectory/NonEmptyTestSubdirectory
		ln EmptyTestFile.txt TestFileHardlink
		ln -s NonEmptyTestDirectory TestDirectorySymlink
		ln -s NonEmptyTestFile.txt TestFileSymlink
		printf "alpha = FooBar\nbit-mask = 1337\n" > Test.cfg
}

DoCleanupLin()
{
	# Perform cleanup on a GNU Linux platform.

		rmdir EmptyTestDirectory
		rm -rf NonEmptyTestDirectory
		rm -rf TestPlugins
		rm EmptyTestFile.txt
		rm NonEmptyTestFile.txt
		rm TestFileHardlink
		rm TestDirectorySymlink
		rm TestFileSymlink
		rm Test.cfg
}

DoSetupMac()
{
	# Perform setup on an Apple Mac OS X platform.

		echo -e "Stub: Perform Apple Mac OS X setup."
}

DoCleanupMac()
{
	# Perform cleanup on an Apple Mac OS X platform.

		echo -e "Stub: Perform Apple Mac OS X cleanup."
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
elif [[ ( ${Platform} != "lin" ) && ( ${Platform} != "mac" ) ]]; then
	DoAbort "Unsupported platform ( '${Platform}' ) specified!" 3
elif [[ ( ${Mode} < 0 ) || ( ${Mode} > 1 ) ]]; then
	DoAbort "Unknown mode ( '${Mode}' ) specified!" 4
fi

################################################################################################################################################################
# Script Body
################################################################################################################################################################

# Setup or cleanup based on the specified platform and mode.

if [[ ${Mode} == 0 ]]; then
	if [[ ${Platform} == "lin" ]]; then
		DoSetupLin
	elif [[ ${Platform} == "mac" ]]; then
		DoSetupMac
	fi
else
	if [[ ${Platform} == "lin" ]]; then
		DoCleanupLin
	elif [[ ${Platform} == "mac" ]]; then
		DoCleanupMac
	fi
fi

################################################################################################################################################################
# End of 'install.sh'
################################################################################################################################################################

#! /bin/bash
################################################################################################################################################################
# update-version.sh
# Robert M. Baker | Created : 18FEB16 | Last Modified : 22FEB16 by Robert M. Baker
# Version : 1.1.2
# This script updates the project version number in all files.
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

NEW_VERSION=${1}

################################################################################################################################################################
# Functions
################################################################################################################################################################

DoAbort()
{
	# Display appropriate abort message.

		if [[ ${2} > 0 ]]; then
			echo -e "update-version.sh: ${FG_RED}${1}${RESET}"
		else
			echo -e "update-version.sh: ${1}"
		fi

		echo -e "Usage: update-version.sh NEW_VERSION"
		echo -e
		echo -e "   -h, --help        Display this help text and exit."
		echo -e
		echo -e "   'NEW_VERSION' should be of the form 'VERSION_MAJOR.VERSION_MINOR.VERSION_PATCH'."

	# Exit script with specified abort code.

		exit ${2}
}

################################################################################################################################################################
# Arguments Check
################################################################################################################################################################

if [[ ${#} == 0 ]]; then
	DoAbort "No arguments specified!" 1
elif [[ ${#} > 1 ]]; then
	DoAbort "Too many arguments specified!" 2
elif [[ ( ${1} == "-h" ) || ( ${1} == "--help" ) ]]; then
	DoAbort "Display help text and exit." 0
fi

################################################################################################################################################################
# Script Body
################################################################################################################################################################

# Replace all occurrences of the current version with the new version.

Files=( $( grep -Rl "Version : [0-9]\+[.][0-9]\+[.][0-9]\+" )
        $( grep -Rl "VERSION [0-9]\+[.][0-9]\+[.][0-9]\+" )
        $( grep -Rl "@version [0-9]\+[.][0-9]\+[.][0-9]\+" )
        $( grep -Rl "V[0-9]\+[.][0-9]\+[.][0-9]\+" ) )
Files=( $( echo ${Files[@]} | tr ' ' '\n' | sort -u | tr '\n' ' ' ) )

for Index in ${Files[@]}; do
	cat ${Index} | sed "s/Version : [0-9]\+[.][0-9]\+[.][0-9]\+/Version : ${NEW_VERSION}/" \
	             | sed "s/VERSION [0-9]\+[.][0-9]\+[.][0-9]\+/VERSION ${NEW_VERSION}/" \
	             | sed "s/@version [0-9]\+[.][0-9]\+[.][0-9]\+/@version ${NEW_VERSION}/" \
	             | sed "s/V[0-9]\+[.][0-9]\+[.][0-9]\+/V${NEW_VERSION}/" > ${Index}.new
	touch -r ${Index} ${Index}.new
	mv ${Index}.new ${Index}
done

################################################################################################################################################################
# End of 'update-version.sh'
################################################################################################################################################################

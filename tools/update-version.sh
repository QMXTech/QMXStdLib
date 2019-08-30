#! /bin/bash
################################################################################################################################################################
# update-version.sh
# Robert M. Baker | Created : 22JUL18 | Last Modified : 26AUG19 by Robert M. Baker
# Version : 2.0.0
# This script updates the project version number in all files.
################################################################################################################################################################
# Copyright (C) 2011-2019 QuantuMatriX Software, a QuantuMatriX Technologies Cooperative Partnership
#
# This file is part of 'QMXStdLib'.
#
# 'QMXStdLib' is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option) any later version.
#
# 'QMXStdLib' is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License along with 'QMXStdLib'.  If not, see <http://www.gnu.org/licenses/>.
################################################################################################################################################################

################################################################################################################################################################
# Variables
################################################################################################################################################################

options=
newVersion=
files=

################################################################################################################################################################
# Constants
################################################################################################################################################################

NAME="update-version.sh"
VERSION="1.0.0"
YEARS="2011-2019"
COMPANY="QuantuMatriX Software, a QuantuMatriX Technologies Cooperative Partnership"
AUTHOR="Robert M. Baker"

COLOR_ERROR=${FG_I_RED}
COLOR_INFO=${FG_I_GREEN}
COLOR_TEXT=${FG_I_WHITE}

OPTIONS_SHORT="hv"
OPTIONS_LONG="help,version"
MIN_ARGS=1

################################################################################################################################################################
# Functions
################################################################################################################################################################

doAbort()
{
	# Display specified abort message.

		if [[ ${2} > 0 ]]; then
			echo -e "${COLOR_ERROR}Error: ${1}${RESET}"
		else
			echo -e "${COLOR_INFO}Info: ${1}${RESET}"
		fi

		echo -e

	# Exit script with specified code.

		exit ${2}
}

doHelp()
{
	# Display help.

		echo -e "${COLOR_INFO}Usage: ${NAME} [OPTION]... <NEW_VERSION>"
		echo -e "Updates the project version number in all files."
		echo -e
		echo -e "  -h, --help           : Display this help and exit."
		echo -e "  -v, --version        : Output version information and exit."
		echo -e
		echo -e "'NEW_VERSION' should be of the form 'VERSION_MAJOR.VERSION_MINOR.VERSION_PATCH'."
		echo -e "${RESET}"

	# Exit script.

		exit 0
}

doVersion()
{
	# Display version information.

		echo -e "${COLOR_INFO}${NAME} V${VERSION}"
		echo -e "Copyright (C) ${YEARS} ${COMPANY}"
		echo -e "License LGPLv3+: GNU LGPL version 3 or later <https://www.gnu.org/licenses/gpl.html>."
		echo -e "This is free software: you are free to change and redistribute it."
		echo -e "There is NO WARRANTY, to the extent permitted by law."
		echo -e
		echo -e "Written by ${AUTHOR}"
		echo -e ${RESET}

	# Exit script with specified abort code.

		exit 0
}

################################################################################################################################################################
# Arguments Check
################################################################################################################################################################

options=$(getopt -o ${OPTIONS_SHORT} -l ${OPTIONS_LONG} -q -- "$@")
eval set -- "${options}"

while true; do
	case "${1}" in
		'-h'|'--help')
			doHelp
		;;
		'-v'|'--version')
			doVersion
		;;
		'--')
			shift 1
			break
		;;
		*)
			doAbort "Unhandled exception!" 1
		;;
	esac
done

if [[ ${#} -lt ${MIN_ARGS} ]]; then
	doAbort "Too few arguments specified!" 2
fi

newVersion=${1}

################################################################################################################################################################
# Script Body
################################################################################################################################################################

# Replace all occurrences of the current version with the new version.

files=(
	$( grep -Rl "Version : [0-9]\+[.][0-9]\+[.][0-9]\+" )
	$( grep -Rl "VERSION [0-9]\+[.][0-9]\+[.][0-9]\+" )
	$( grep -Rl "@version [0-9]\+[.][0-9]\+[.][0-9]\+" )
	$( grep -Rl "V[0-9]\+[.][0-9]\+[.][0-9]\+" )
)

files=( $( echo ${files[@]} | tr ' ' '\n' | sort -u | tr '\n' ' ' ) )

for file in ${files[@]}; do
	cat ${file} | sed "s/Version : [0-9]\+[.][0-9]\+[.][0-9]\+/Version : ${newVersion}/" \
	            | sed "s/VERSION [0-9]\+[.][0-9]\+[.][0-9]\+/VERSION ${newVersion}/" \
	            | sed "s/@version [0-9]\+[.][0-9]\+[.][0-9]\+/@version ${newVersion}/" \
	            | sed "s/V[0-9]\+[.][0-9]\+[.][0-9]\+/V${newVersion}/" > ${file}.new

	touch -r ${file} ${file}.new
	mv ${file}.new ${file}
done

################################################################################################################################################################
# End of 'update-version.sh'
################################################################################################################################################################

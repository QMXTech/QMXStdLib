# QMXStdLib

## Synopsis

> QuantuMatriX Software Standard Library - V2.3.0
> Copyright (C) 2011-2019 QuantuMatriX Software, a QuantuMatriX Technologies Cooperative Partnership
>
> This library is meant to offer an array of general-purpose data structures and algorithms for a multitude of uses.  Each structure must be examined for its specific usefulness to be determined.  Please see the API documentation for more details, or visit the QMXStdLib website at 'https://git.qmx-software.com/open-source/qmxstdlib/'.
>
> 'QMXStdLib' is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

## Dependencies

> ### GNU Linux and Apple macOS
>
>> #### Compiler
>> * Clang >= 3.9 or GCC >= 7.0
>>
>> #### Documentation
>> * Doxygen >= 1.6
>>
>> #### Libraries
>> * Boost >= 1.69
>> * GTest >= 1.6 (optional)
>>
>> #### Tools
>> * CMake >= 3.0
>
> ### Microsoft Windows
>
>> #### Compiler
>> * MSYS2 + Clang >= 3.9 or MSYS2 + MinGW with GCC >= 7.0
>>
>> #### Documentation
>> * Doxygen >= 1.6
>>
>> #### Libraries
>> * Boost >= 1.69
>> * GTest >= 1.6 (optional)
>>
>> #### Tools
>> * CMake >= 3.0

## Building

> To build using CMake, use the following steps:
>
> * Navigate to the project's root directory, and create a new directory called 'build'.
> * Enter the 'build' directory and run the following command (replacing '[GENERATOR]' with the name of the desired CMake generator; note that only Clang and GCC-based compilers are currently supported):
>
>> cmake -G "[GENERATOR]" ..
>
> * After the project files are fully generated, build in the usual manner.  The following targets are supported:
>
>> * all (default; includes 'debug' and 'release')
>> * debug
>> * relwithdebinfo
>> * release
>> * minsizerel
>> * doc (builds Doxygen documentation)
>> * tests (includes 'tests_debug' and 'tests_release' )
>> * tests_debug
>> * tests_relwithdebinfo
>> * tests_release
>> * tests_minsizerel
>> * install (only targets actually built will be installed; unit tests are never installed)
>> * uninstall

## Installing and Uninstalling

> To install on any platform, use the 'install' target of the generated project files.  To uninstall on any platform, use the 'uninstall' target of the generated project files.  Note that on a GNU Linux platform, you will need to run 'ldconfig' after the installation process; otherwise, the system will not be able to locate the new libraries.

## CMake Package

> This project provides a CMake package which can be used with the 'find_package' command.  Once found, the following variables are set:
>
>> * QMXStdLib_VERSION (the current library version)
>> * QMXStdLib_LIB_DEBUG (the debug build of the library)
>> * QMXStdLib_LIB_RELEASE (the release build of the library)
>> * QMXStdLib_INCLUDE_PATH (the library headers path)
>> * QMXStdLib_LIB_PATH (the library path)

## Contacts and Support

> * Site: 'https://git.qmx-software.com/open-source/qmxstdlib/'
> * Forums: 'https://forums.qmx-software.com/qmxstdlib/' (Currently Unavailable)
> * Bug Tracker: 'https://git.qmx-software.com/open-source/qmxstdlib/issues'
> * Email: 'support@qmx-software.com'

## Event Messages

> | Event Index | Event Message                                                                             |
> |-------------|-------------------------------------------------------------------------------------------|
> | 00000000    | The object instance was already initialized!                                              |
> | 00000001    | The object instance was not initialized!                                                  |
> | 00000002    | The specified file was not a dynamic library!                                             |
> | 00000003    | The specified dynamic library could not be loaded!                                        |
> | 00000004    | The symbol could not be retrieved because the dynamic library was not loaded!             |
> | 00000005    | The symbol could not be retrieved!                                                        |
> | 00000006    | The dynamic library could not be unloaded because it was not loaded!                      |
> | 00000007    | The dynamic library could not be unloaded!                                                |
> | 00000008    | A malformed symbol was found in the path!                                                 |
> | 00000009    | A non-existent symbol was found in the path!                                              |
> | 0000000A    | The specified path could not be converted into a canonical path!                          |
> | 0000000B    | The specified path's symlink contents could not be retrieved!                             |
> | 0000000C    | The specified hardlink/symlink could not be created due to an invalid source target!      |
> | 0000000D    | The specified hardlink/symlink could not be created using the specified arguments!        |
> | 0000000E    | The copy operation could not be performed due to an invalid source target!                |
> | 0000000F    | The copy operation could not be completed!                                                |
> | 00000010    | The base was set to none, but the string format pointer was null!                         |
> | 00000011    | The specified config file could not be opened for reading!                                |
> | 00000012    | The specified config file could not be opened for writing!                                |
> | 00000013    | The current thread's ID was not set!                                                      |
> | 00000014    | The current thread's ID was an empty string!                                              |
> | 00000015    | The current thread was already added to the tracer!                                       |
> | 00000016    | The current thread was not added to the tracer!                                           |
> | 00000017    | The specified group could not be created because it already exists!                       |
> | 00000018    | The specified group could not be destroyed because it did not exist!                      |
> | 00000019    | The specified group could not be destroyed because it was not empty!                      |
> | 0000001A    | The thread barrier size could not be set because the specified group did not exist!       |
> | 0000001B    | The specified thread could not be destroyed because its group did not exist!              |
> | 0000001C    | The specified thread could not be destroyed because it did not exist!                     |
> | 0000001D    | The thread barrier could not be called because the specified group did not exist!         |
> | 0000001E    | The thread barrier could not be called because the specified group did not exist!         |
> | 0000001F    | The specified thread could not be joined because its group did not exist!                 |
> | 00000020    | The specified thread could not be joined because it did not exist!                        |
> | 00000021    | The threads could not be joined because the specified group did not exist!                |
> | 00000022    | The specified thread could not be interrupted because its group did not exist!            |
> | 00000023    | The specified thread could not be interrupted because it did not exist!                   |
> | 00000024    | The threads could not be interrupted because the specified group did not exist!           |
> | 00000025    | The specified thread could not be created because its group did not exist!                |
> | 00000026    | The specified thread could not be created because it already exists!                      |

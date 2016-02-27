# QMXStdLib

## Synopsis

> QuantuMatriX Software Standard Library - V1.1.0
> Copyright (C) 2011-2016 QuantuMatriX Software, LLP.
>
> This library is meant to offer an array of general-purpose data structures and algorithms for a multitude of uses.  Each structure must be examined for its specific usefulness to be determined.  Please see the API documentation for more details, or visit the QMX Software website at 'https://software.qmxtech.com/'.
>
> 'QMXStdLib' is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

## Dependencies

> ### Linux and Mac OS X
>
>> #### Compiler
>> * Clang >= 3.7.1 or GCC >= 5.3.0
>>
>> #### Documentation
>> * Doxygen >= 1.8.11
>>
>> #### Libraries
>> * Boost >= 1.60.0
>> * GTest >= 1.7.0 (optional)
>>
>> #### Tools
>> * CMake >= 3.4.3
>
> ### Windows
>
>> #### Compiler
>> * TDM-GCC >= 5.1.0
>>
>> #### Documentation
>> * Doxygen >= 1.8.11
>>
>> #### Libraries
>> * Boost >= 1.60.0
>> * GTest >= 1.7.0 (optional)
>>
>> #### Tools
>> * CMake >= 3.4.3

## Building

> The source release for QMXStdLib may be downloaded from the website link listed under 'Contacts and Support'.
>
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
>> * tests_debug
>> * tests_relwithdebinfo
>> * tests_release
>> * tests_minsizerel
>> * install (only targets actually built will be installed; unit tests are never installed)
>> * uninstall

## Installing and Uninstalling

> To install on any platform, use the 'install' target of the generated project files.  To uninstall on any platform, use the 'uninstall' target of the generated project files.  Note that on a GNU Linux platform, you will need to run 'ldconfig' after the installation process; otherwise, the system will not be able to locate the new libraries.

## Contacts and Support

> * Site: 'https://software.qmxtech.com/qmxstdlib/'
> * Forums: 'https://forums.qmxtech.com/qmxstdlib/'
> * Bug Tracker: 'https://bugs.qmxtech.com/qmxstdlib/'
> * Email: 'support@qmxtech.com'

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
> | 00000011    | The specified module could not be registered because it already exists!                   |
> | 00000012    | The specified module could not be unregistered because it did not exist!                  |
> | 00000013    | No plugins could be loaded because the specified path was not a directory!                |
> | 00000014    | No plugins were found at the specified path!                                              |
> | 00000015    | The specified plugin was already loaded!                                                  |
> | 00000016    | The specified plugin did not have a 'PluginGetModule' function!                           |
> | 00000017    | The specified plugin did not have a 'PluginStart' function!                               |
> | 00000018    | The specified plugin did not have a 'PluginStop' function!                                |
> | 00000019    | The specified plugin could not be loaded because its module was not registered!           |
> | 0000001A    | The specified plugin could not be unloaded because its module did not exist!              |
> | 0000001B    | The specified plugin could not be unloaded because it was not loaded!                     |
> | 0000001C    | A plugin list could not be constructed because the specified module did not exist!        |
> | 0000001D    | The specified plugin's meta data could not be retrieved because its module did not exist! |
> | 0000001E    | The specified plugin's meta data could not be retrieved because it did not exist!         |
> | 0000001F    | Attempted to initialize plugin manager, but it was already initialized!                   |
> | 00000020    | The specified config file could not be opened for reading!                                |
> | 00000021    | The specified config file could not be opened for writing!                                |
> | 00000022    | The current thread's ID was not set!                                                      |
> | 00000023    | The current thread's ID was an empty string!                                              |
> | 00000024    | The current thread was already added to the tracer!                                       |
> | 00000025    | The current thread was not added to the tracer!                                           |
> | 00000026    | The specified group could not be created because it already exists!                       |
> | 00000027    | The specified group could not be destroyed because it did not exist!                      |
> | 00000028    | The specified group could not be destroyed because it was not empty!                      |
> | 00000029    | The thread barrier size could not be set because the specified group did not exist!       |
> | 0000002A    | The specified thread could not be destroyed because its group did not exist!              |
> | 0000002B    | The specified thread could not be destroyed because it did not exist!                     |
> | 0000002C    | The thread barrier could not be called because the specified group did not exist!         |
> | 0000002D    | The specified thread could not be joined because its group did not exist!                 |
> | 0000002E    | The specified thread could not be joined because it did not exist!                        |
> | 0000002F    | The threads could not be joined because the specified group did not exist!                |
> | 00000030    | The specified thread could not be interrupted because its group did not exist!            |
> | 00000031    | The specified thread could not be interrupted because it did not exist!                   |
> | 00000032    | The threads could not be interrupted because the specified group did not exist!           |
> | 00000033    | The specified thread could not be created because its group did not exist!                |
> | 00000034    | The specified thread could not be created because it already exists!                      |

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FileSystemTest.cpp
// Robert M. Baker | Created : 12MAR12 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.2
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::FileSystem' functions.
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../include/FileSystemTest.hpp"

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::FileSystem' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( FileSystemTest, ParseWorks )
{
	// Create local variables.

		string DelimiterLeft( 1, FILESYSTEM_SYMBOL_DELIMITER_LEFT );
		string DelimiterRight( 1, FILESYSTEM_SYMBOL_DELIMITER_RIGHT );
		Path TestPathsBad[] = { ( DelimiterLeft + "QMX_TEST_HOME/directory/file.ext" ),
		                        ( DelimiterRight + "QMX_TEST_HOME" + DelimiterLeft + "/directory/file.ext" ),
		                        ( "QMX_TEST_HOME" + DelimiterRight + "/directory/file.ext" ),
		                        ( DelimiterLeft + "NON_EXISTENT_VAR" + DelimiterRight + "/directory/file.ext" ) };
		Path TestPathsGood[] = { ( DelimiterLeft + "QMX_TEST_HOME" + DelimiterRight + "/" + DelimiterLeft + "QMX_TEST_ALPHA" + DelimiterRight + "/file.ext" ),
		                         ( DelimiterLeft + "QMX_TEST_HOME" + DelimiterRight + "/" + DelimiterLeft + "QMX_TEST_BETA" + DelimiterRight + "/file.ext" ),
		                         ( DelimiterLeft + "QMX_TEST_HOME" + DelimiterRight + "/" + DelimiterLeft + "QMX_TEST_GAMMA" + DelimiterRight + "/file.ext" ),
		                         ( DelimiterLeft + "QMX_TEST_HOME" + DelimiterRight + "/" + DelimiterLeft + "QMX_TEST_DELTA" + DelimiterRight + "/file.ext" ) };
		Path ExpectedResults[] = { "/home/jdoe/foo/file.ext",
		                           "/home/jdoe/bar/file.ext",
		                           "/home/jdoe/baz/file.ext",
		                           "/home/jdoe/xyzzy/file.ext" };

	// Set test environment variables.

		setenv( "QMX_TEST_HOME", "/home/jdoe", False );
		setenv( "QMX_TEST_ALPHA", "foo", False );
		setenv( "QMX_TEST_BETA", "bar", False );
		setenv( "QMX_TEST_GAMMA", "baz", False );
		setenv( "QMX_TEST_DELTA", "xyzzy", False );

	// Perform unit test for 'Parse' function.

		for( size_t Index = 0; Index < ARRAY_SIZE( TestPathsBad ); Index++ )
		{
			ASSERT_THROW( FileSystem::Parse( TestPathsBad[ Index ] ), QMXException );
		}

		for( size_t Index = 0; Index < ARRAY_SIZE( TestPathsGood ); Index++ )
		{
			FileSystem::Parse( TestPathsGood[ Index ] );
			ASSERT_EQ( ExpectedResults[ Index ].string(), TestPathsGood[ Index ].string() );
		}

	// Clear test environment variables.

		unsetenv( "QMX_TEST_HOME" );
		unsetenv( "QMX_TEST_ALPHA" );
		unsetenv( "QMX_TEST_BETA" );
		unsetenv( "QMX_TEST_GAMMA" );
		unsetenv( "QMX_TEST_DELTA" );
}

TEST( FileSystemTest, MakeCanonicalWorks )
{
	// Create local variables.

		Path InitialPath = boost::filesystem::current_path();
		Path TestPathsBad[] = { "NonExistent" };
		Path TestPathsGood[] = { ".",
		                         "TestFileHardlink",
		                         "TestDirectorySymlink",
		                         "TestFileSymlink" };
		Path ExpectedResults[] = { ".",
		                           "TestFileHardlink",
		                           "NonEmptyTestDirectory",
		                           "NonEmptyTestFile.txt" };

	// Change current working directory to 'BASE_PATH'.

		boost::filesystem::current_path( BASE_PATH );

	// Perform unit test for 'MakeCanonical' function.

		for( size_t Index = 0; Index < ARRAY_SIZE( TestPathsBad ); Index++ )
		{
			ASSERT_THROW( FileSystem::MakeCanonical( TestPathsBad[ Index ] ), QMXException );
		}

		for( size_t Index = 0; Index < ARRAY_SIZE( TestPathsGood ); Index++ )
		{
			ASSERT_EQ( boost::filesystem::canonical( ExpectedResults[ Index ] ).make_preferred().string(),
			           FileSystem::MakeCanonical( TestPathsGood[ Index ] ).string() );
		}

	// Restore original working directory.

		boost::filesystem::current_path( InitialPath );
}

TEST( FileSystemTest, ReadSymlinkWorks )
{
	// Create local variables.

		Path InitialPath = boost::filesystem::current_path();
		Path TestPathsBad[] = { "NonExistent",
		                        "NonEmptyTestDirectory",
		                        "NonEmptyTestFile.txt" };
		Path TestPathsGood[] = { "TestDirectorySymlink",
		                         "TestFileSymlink" };
		Path ExpectedResults[] = { "NonEmptyTestDirectory",
		                           "NonEmptyTestFile.txt" };

	// Change current working directory to 'BASE_PATH'.

		boost::filesystem::current_path( BASE_PATH );

	// Perform unit test for 'ReadSymlink' function.

		for( size_t Index = 0; Index < ARRAY_SIZE( TestPathsBad ); Index++ )
		{
			ASSERT_THROW( FileSystem::ReadSymlink( TestPathsBad[ Index ] ), QMXException );
		}

		for( size_t Index = 0; Index < ARRAY_SIZE( TestPathsGood ); Index++ )
		{
			if( !IS_WINDOWS )
			{
				ASSERT_EQ( ExpectedResults[ Index ].string(), FileSystem::ReadSymlink( TestPathsGood[ Index ] ).string() );
			}
			else
			{
				ASSERT_EQ( boost::filesystem::canonical( ExpectedResults[ Index ] ).make_preferred().string(),
				           FileSystem::ReadSymlink( TestPathsGood[ Index ] ).string() );
			}
		}

	// Restore original working directory.

		boost::filesystem::current_path( InitialPath );
}

TEST( FileSystemTest, CreateLinkSymlinkWorks )
{
	// Create local variables.

		Path InitialPath = boost::filesystem::current_path();
		Path TestPathsSourceBad[] = { "NonEmptyTestFile.txt" };
		Path TestPathsLinkBad[] = { "TestFileSymlink" };
		Path TestPathsSourceGood[] = { "NonEmptyTestDirectory",
		                               "NonEmptyTestFile.txt",
		                               "TestFileHardlink",
		                               "TestDirectorySymlink",
		                               "TestFileSymlink" };
		Path TestPathsLinkGood[] = { "TestSymlinkDirectory1",
		                             "TestSymlinkFile1",
		                             "TestSymlinkFile2",
		                             "TestSymlinkDirectory2",
		                             "TestSymlinkFile3" };

	// Change current working directory to 'BASE_PATH'.

		boost::filesystem::current_path( BASE_PATH );

	// Perform unit test for 'CreateLink' function using symlinks.

		for( size_t Index = 0; Index < ARRAY_SIZE( TestPathsSourceBad ); Index++ )
		{
			ASSERT_THROW( FileSystem::CreateLink( TestPathsSourceBad[ Index ], TestPathsLinkBad[ Index ] ), QMXException );
		}

		for( size_t Index = 0; Index < ARRAY_SIZE( TestPathsSourceGood ); Index++ )
		{
			FileSystem::CreateLink( TestPathsSourceGood[ Index ], TestPathsLinkGood[ Index ] );
			boost::filesystem::remove( TestPathsLinkGood[ Index ] );
		}

	// Restore original working directory.

		boost::filesystem::current_path( InitialPath );
}

TEST( FileSystemTest, CreateLinkHardlinkWorks )
{
	// Create local variables.

		Path InitialPath = boost::filesystem::current_path();
		Path TestPathsSourceBad[] = { "EmptyTestDirectory",
		                              TEST_OTHER,
		                              "TestFileSymlink",
		                              "EmptyTestFile.txt" };
		Path TestPathsLinkBad[] = { "TestHardlinkDirectory1",
		                            "TestHardlinkOther1",
		                            "TestHardlinkSymlink1",
                                  "TestFileHardlink" };
		Path TestPathsSourceGood[] = { "NonEmptyTestFile.txt",
		                               "TestFileHardlink" };
		Path TestPathsLinkGood[] = { "TestHardlinkFile1",
		                             "TestHardlinkFile2" };

	// Change current working directory to 'BASE_PATH'.

		boost::filesystem::current_path( BASE_PATH );

	// Perform unit test for 'CreateLink' function using hardlinks.

		for( size_t Index = 0; Index < ARRAY_SIZE( TestPathsSourceBad ); Index++ )
		{
			ASSERT_THROW( FileSystem::CreateLink( TestPathsSourceBad[ Index ], TestPathsLinkBad[ Index ], true ), QMXException );
		}

		for( size_t Index = 0; Index < ARRAY_SIZE( TestPathsSourceGood ); Index++ )
		{
			FileSystem::CreateLink( TestPathsSourceGood[ Index ], TestPathsLinkGood[ Index ], true );
			boost::filesystem::remove( TestPathsLinkGood[ Index ] );
		}

	// Restore original working directory.

		boost::filesystem::current_path( InitialPath );
}

TEST( FileSystemTest, CopyRecursiveWorks )
{
	// Create local variables.

		Path InitialPath = boost::filesystem::current_path();
		Path SourcePathsBad[] = { TEST_OTHER,
		                          "NonEmptyTestDirectory",
										  "NonEmptyTestFile.txt",
										  "TestFileHardlink",
										  "TestDirectorySymlink",
										  "TestFileSymlink" };
		Path DestinationPathsBad[] = { "TestOtherCopy",
		                               "EmptyTestDirectory",
												 "EmptyTestFile.txt",
												 "TestFileSymlink",
												 "EmptyTestDirectory",
												 "TestFileHardlink" };
		Path SourcePathsGood[] = { "NonEmptyTestDirectory",
		                           "NonEmptyTestFile.txt",
		                           "TestFileHardlink",
		                           "TestDirectorySymlink",
		                           "TestFileSymlink" };
		Path DestinationPathsGood[] = { "NonEmptyTestDirectoryCopy",
		                                "NonEmptyTestFileCopy.txt",
		                                "TestFileHardlinkCopy",
		                                "TestDirectorySymlinkCopy",
		                                "TestFileSymlinkCopy" };

	// Change current working directory to 'BASE_PATH'.

		boost::filesystem::current_path( BASE_PATH );

	// Perform unit test for 'Copy' function using recursion.

		for( size_t Index = 0; Index < ARRAY_SIZE( SourcePathsBad ); Index++ )
		{
			ASSERT_THROW( FileSystem::Copy( SourcePathsBad[ Index ], DestinationPathsBad[ Index ], true, FileSystem::FailIfExists ), QMXException );
		}

		for( size_t Index = 0; Index < ARRAY_SIZE( SourcePathsGood ); Index++ )
		{
			FileSystem::Copy( SourcePathsGood[ Index ], DestinationPathsGood[ Index ] );
			FileSystem::Copy( SourcePathsGood[ Index ], DestinationPathsGood[ Index ] );
			FileSystem::Copy( SourcePathsGood[ Index ], DestinationPathsGood[ Index ], true, FileSystem::OverwriteIfExists );
			boost::filesystem::remove_all( DestinationPathsGood[ Index ] );
		}

	// Restore original working directory.

		boost::filesystem::current_path( InitialPath );
}

TEST( FileSystemTest, CopyNonRecursiveWorks )
{
	// Create local variables.

		Path InitialPath = boost::filesystem::current_path();
		Path SourcePathsBad[] = { TEST_OTHER,
		                          "NonEmptyTestDirectory",
										  "NonEmptyTestFile.txt",
										  "TestFileHardlink",
										  "TestDirectorySymlink",
										  "TestFileSymlink" };
		Path DestinationPathsBad[] = { "TestOtherCopy",
		                               "EmptyTestDirectory",
												 "EmptyTestFile.txt",
												 "TestFileSymlink",
												 "EmptyTestDirectory",
												 "TestFileHardlink" };
		Path SourcePathsGood[] = { "NonEmptyTestDirectory",
		                           "NonEmptyTestFile.txt",
		                           "TestFileHardlink",
		                           "TestDirectorySymlink",
		                           "TestFileSymlink" };
		Path DestinationPathsGood[] = { "NonEmptyTestDirectoryCopy",
		                                "NonEmptyTestFileCopy.txt",
		                                "TestFileHardlinkCopy",
		                                "TestDirectorySymlinkCopy",
		                                "TestFileSymlinkCopy" };

	// Change current working directory to 'BASE_PATH'.

		boost::filesystem::current_path( BASE_PATH );

	// Perform unit test for 'Copy' function without recursion.

		for( size_t Index = 0; Index < ARRAY_SIZE( SourcePathsBad ); Index++ )
		{
			ASSERT_THROW( FileSystem::Copy( SourcePathsBad[ Index ], DestinationPathsBad[ Index ], false, FileSystem::FailIfExists ), QMXException );
		}

		for( size_t Index = 0; Index < ARRAY_SIZE( SourcePathsGood ); Index++ )
		{
			FileSystem::Copy( SourcePathsGood[ Index ], DestinationPathsGood[ Index ], false );
			FileSystem::Copy( SourcePathsGood[ Index ], DestinationPathsGood[ Index ], false );
			FileSystem::Copy( SourcePathsGood[ Index ], DestinationPathsGood[ Index ], false, FileSystem::OverwriteIfExists );
			boost::filesystem::remove( DestinationPathsGood[ Index ] );
		}

	// Restore original working directory.

		boost::filesystem::current_path( InitialPath );
}

TEST( FileSystemTest, RunCommandWorks )
{
	// Perform unit test for 'RunCommand' function.

		if( FileSystem::RunCommand() )
		{
			if( !IS_WINDOWS )
			{
				ASSERT_TRUE( FileSystem::RunCommand( "ls > /dev/null 2>&1" ) );
			}
			else
			{
				ASSERT_TRUE( FileSystem::RunCommand( "dir > nul 2>&1" ) );
			}
		}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'FileSystemTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FileSystemTest.cpp
// Robert M. Baker | Created : 12MAR12 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.0.0
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'QMXStdLib::FileSystem' functions.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2011-2019 QuantuMatriX Software, a QuantuMatriX Technologies Cooperative Partnership
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

		string delimiterLeft( 1, FILESYSTEM_SYMBOL_DELIMITER_LEFT );
		string delimiterRight( 1, FILESYSTEM_SYMBOL_DELIMITER_RIGHT );

		Path testPathsBad[] = {
			( delimiterLeft + "QMX_TEST_HOME/directory/file.ext" ),
			( delimiterRight + "QMX_TEST_HOME" + delimiterLeft + "/directory/file.ext" ),
			( "QMX_TEST_HOME" + delimiterRight + "/directory/file.ext" ),
			( delimiterLeft + "NON_EXISTENT_VAR" + delimiterRight + "/directory/file.ext" )
		};

		Path testPathsGood[] = {
			( delimiterLeft + "QMX_TEST_HOME" + delimiterRight + "/" + delimiterLeft + "QMX_TEST_ALPHA" + delimiterRight + "/file.ext" ),
			( delimiterLeft + "QMX_TEST_HOME" + delimiterRight + "/" + delimiterLeft + "QMX_TEST_BETA" + delimiterRight + "/file.ext" ),
			( delimiterLeft + "QMX_TEST_HOME" + delimiterRight + "/" + delimiterLeft + "QMX_TEST_GAMMA" + delimiterRight + "/file.ext" ),
			( delimiterLeft + "QMX_TEST_HOME" + delimiterRight + "/" + delimiterLeft + "QMX_TEST_DELTA" + delimiterRight + "/file.ext" )
		};

		Path expectedResults[] = {
			"/home/jdoe/foo/file.ext",
			"/home/jdoe/bar/file.ext",
			"/home/jdoe/baz/file.ext",
			"/home/jdoe/xyzzy/file.ext"
		};

	// Set test environment variables.

		setenv( "QMX_TEST_HOME", "/home/jdoe", FALSE );
		setenv( "QMX_TEST_ALPHA", "foo", FALSE );
		setenv( "QMX_TEST_BETA", "bar", FALSE );
		setenv( "QMX_TEST_GAMMA", "baz", FALSE );
		setenv( "QMX_TEST_DELTA", "xyzzy", FALSE );

	// Perform unit test for 'parse' function.

		for( size_t index = 0; index < ARRAY_SIZE( testPathsBad ); index++ )
		{
			ASSERT_THROW( FileSystem::parse( testPathsBad[ index ] ), QMXException );
		}

		for( size_t index = 0; index < ARRAY_SIZE( testPathsGood ); index++ )
		{
			FileSystem::parse( testPathsGood[ index ] );
			ASSERT_EQ( expectedResults[ index ].string(), testPathsGood[ index ].string() );
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

		ScopedPathChange testPath( BASE_PATH );

		Path testPathsBad[] = {
			"NonExistent"
		};

		Path testPathsGood[] = {
			".",
			"TestFileHardlink",
			"TestDirectorySymlink",
			"TestFileSymlink"
		};

		Path expectedResults[] = {
			".",
			"TestFileHardlink",
			"NonEmptyTestDirectory",
			"NonEmptyTestFile.txt"
		};

	// Perform unit test for 'makeCanonical' function.

		for( size_t index = 0; index < ARRAY_SIZE( testPathsBad ); index++ )
		{
			ASSERT_THROW( FileSystem::makeCanonical( testPathsBad[ index ] ), QMXException );
		}

		for( size_t index = 0; index < ARRAY_SIZE( testPathsGood ); index++ )
		{
			ASSERT_EQ(
				boost::filesystem::canonical( expectedResults[ index ] ).make_preferred().string(),
			   FileSystem::makeCanonical( testPathsGood[ index ] ).string()
			);
		}
}

TEST( FileSystemTest, ReadSymlinkWorks )
{
	// Create local variables.

		ScopedPathChange testPath( BASE_PATH );

		Path testPathsBad[] = {
			"NonExistent",
			"NonEmptyTestDirectory",
			"NonEmptyTestFile.txt"
		};

		Path testPathsGood[] = {
			"TestDirectorySymlink",
		   "TestFileSymlink"
		};

		Path expectedResults[] = {
			"NonEmptyTestDirectory",
		   "NonEmptyTestFile.txt"
		};

	// Perform unit test for 'readSymlink' function.

		for( size_t index = 0; index < ARRAY_SIZE( testPathsBad ); index++ )
		{
			ASSERT_THROW( FileSystem::readSymlink( testPathsBad[ index ] ), QMXException );
		}

		for( size_t index = 0; index < ARRAY_SIZE( testPathsGood ); index++ )
		{
			if( !IS_WINDOWS )
			{
				ASSERT_EQ( expectedResults[ index ].string(), FileSystem::readSymlink( testPathsGood[ index ] ).string() );
			}
			else
			{
				ASSERT_EQ(
					boost::filesystem::canonical( expectedResults[ index ] ).make_preferred().string(),
				   FileSystem::readSymlink( testPathsGood[ index ] ).string()
				);
			}
		}
}

TEST( FileSystemTest, CreateLinkSymlinkWorks )
{
	// Create local variables.

		ScopedPathChange testPath( BASE_PATH );

		Path testPathsSourceBad[] = {
			"NonEmptyTestFile.txt"
		};

		Path testPathsLinkBad[] = {
			"TestFileSymlink"
		};

		Path testPathsSourceGood[] = {
			"NonEmptyTestDirectory",
		   "TestFileHardlink",
		   "NonEmptyTestFile.txt",
		   "TestDirectorySymlink",
		   "TestFileSymlink"
		};

		Path testPathsLinkGood[] = {
			"TestSymlinkDirectory1",
		   "TestSymlinkFile1",
		   "TestSymlinkFile2",
		   "TestSymlinkDirectory2",
		   "TestSymlinkFile3"
		};

	// Perform unit test for 'createLink' function using symlinks.

		for( size_t index = 0; index < ARRAY_SIZE( testPathsSourceBad ); index++ )
		{
			ASSERT_THROW( FileSystem::createLink( testPathsSourceBad[ index ], testPathsLinkBad[ index ] ), QMXException );
		}

		for( size_t index = 0; index < ARRAY_SIZE( testPathsSourceGood ); index++ )
		{
			FileSystem::createLink( testPathsSourceGood[ index ], testPathsLinkGood[ index ] );
			boost::filesystem::remove( testPathsLinkGood[ index ] );
		}
}

TEST( FileSystemTest, CreateLinkHardlinkWorks )
{
	// Create local variables.

		ScopedPathChange testPath( BASE_PATH );

		Path testPathsSourceBad[] = {
			"EmptyTestDirectory",
		   TEST_OTHER,
		   "EmptyTestFile.txt"
		};

		Path testPathsLinkBad[] = {
			"TestHardlinkDirectory1",
		   "TestHardlinkOther1",
		   "TestFileHardlink"
		};

		Path testPathsSourceGood[] = {
			"NonEmptyTestFile.txt",
		   "TestFileHardlink"
		};

		Path testPathsLinkGood[] = {
			"TestHardlinkFile1",
		   "TestHardlinkFile2"
		};

	// Perform unit test for 'createLink' function using hardlinks.

		for( size_t index = 0; index < ARRAY_SIZE( testPathsSourceBad ); index++ )
		{
			ASSERT_THROW( FileSystem::createLink( testPathsSourceBad[ index ], testPathsLinkBad[ index ], true ), QMXException );
		}

		for( size_t index = 0; index < ARRAY_SIZE( testPathsSourceGood ); index++ )
		{
			FileSystem::createLink( testPathsSourceGood[ index ], testPathsLinkGood[ index ], true );
			boost::filesystem::remove( testPathsLinkGood[ index ] );
		}
}

TEST( FileSystemTest, CopyRecursiveWorks )
{
	// Create local variables.

		ScopedPathChange testPath( BASE_PATH );

		Path sourcePathsBad[] = {
			TEST_OTHER,
		   "NonEmptyTestDirectory",
			"NonEmptyTestFile.txt",
			"TestFileHardlink",
			"TestDirectorySymlink",
			"TestFileSymlink"
		};

		Path destinationPathsBad[] = {
			"TestOtherCopy",
		   "EmptyTestDirectory",
			"EmptyTestFile.txt",
			"TestFileSymlink",
			"EmptyTestDirectory",
			"TestFileHardlink"
		};

		Path sourcePathsGood[] = {
			"NonEmptyTestDirectory",
		   "NonEmptyTestFile.txt",
		   "TestFileHardlink",
		   "TestDirectorySymlink",
		   "TestFileSymlink"
		};

		Path destinationPathsGood[] = {
			"NonEmptyTestDirectoryCopy",
		   "NonEmptyTestFileCopy.txt",
		   "TestFileHardlinkCopy",
		   "TestDirectorySymlinkCopy",
		   "TestFileSymlinkCopy"
		};

	// Perform unit test for 'copy' function using recursion.

		for( size_t index = 0; index < ARRAY_SIZE( sourcePathsBad ); index++ )
		{
			ASSERT_THROW( FileSystem::copy( sourcePathsBad[ index ], destinationPathsBad[ index ], true, FileSystem::FAIL_IF_EXISTS ), QMXException );
		}

		for( size_t index = 0; index < ARRAY_SIZE( sourcePathsGood ); index++ )
		{
			FileSystem::copy( sourcePathsGood[ index ], destinationPathsGood[ index ] );
			FileSystem::copy( sourcePathsGood[ index ], destinationPathsGood[ index ] );
			FileSystem::copy( sourcePathsGood[ index ], destinationPathsGood[ index ], true, FileSystem::OVERWRITE_IF_EXISTS );
			boost::filesystem::remove_all( destinationPathsGood[ index ] );
		}
}

TEST( FileSystemTest, CopyNonRecursiveWorks )
{
	// Create local variables.

		ScopedPathChange testPath( BASE_PATH );

		Path sourcePathsBad[] = {
			TEST_OTHER,
		   "NonEmptyTestDirectory",
			"NonEmptyTestFile.txt",
			"TestFileHardlink",
			"TestDirectorySymlink",
			"TestFileSymlink"
		};

		Path destinationPathsBad[] = {
			"TestOtherCopy",
		   "EmptyTestDirectory",
			"EmptyTestFile.txt",
			"TestFileSymlink",
			"EmptyTestDirectory",
			"TestFileHardlink"
		};

		Path sourcePathsGood[] = {
			"NonEmptyTestDirectory",
		   "NonEmptyTestFile.txt",
		   "TestFileHardlink",
		   "TestDirectorySymlink",
		   "TestFileSymlink"
		};

		Path destinationPathsGood[] = {
			"NonEmptyTestDirectoryCopy",
			"NonEmptyTestFileCopy.txt",
			"TestFileHardlinkCopy",
			"TestDirectorySymlinkCopy",
			"TestFileSymlinkCopy"
		};

	// Perform unit test for 'copy' function without recursion.

		for( size_t index = 0; index < ARRAY_SIZE( sourcePathsBad ); index++ )
		{
			ASSERT_THROW( FileSystem::copy( sourcePathsBad[ index ], destinationPathsBad[ index ], false, FileSystem::FAIL_IF_EXISTS ), QMXException );
		}

		for( size_t index = 0; index < ARRAY_SIZE( sourcePathsGood ); index++ )
		{
			FileSystem::copy( sourcePathsGood[ index ], destinationPathsGood[ index ], false );
			FileSystem::copy( sourcePathsGood[ index ], destinationPathsGood[ index ], false );
			FileSystem::copy( sourcePathsGood[ index ], destinationPathsGood[ index ], false, FileSystem::OVERWRITE_IF_EXISTS );
			boost::filesystem::remove( destinationPathsGood[ index ] );
		}
}

TEST( FileSystemTest, RunCommandWorks )
{
	// Perform unit test for 'runCommand' function.

		if( FileSystem::runCommand() )
		{
			if( !IS_WINDOWS )
			{
				ASSERT_TRUE( FileSystem::runCommand( "ls > /dev/null 2>&1" ) );
			}
			else
			{
				ASSERT_TRUE( FileSystem::runCommand( "dir > nul 2>&1" ) );
			}
		}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'FileSystemTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

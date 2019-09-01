////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ThreadManagerTest.cpp
// Robert M. Baker | Created : 26FEB16 | Last Modified : 31AUG19 by Robert M. Baker
// Version : 2.1.1
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'ThreadManager' class.
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

#include "../include/ThreadManagerTest.hpp"

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'ThreadManagerTest' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ThreadManagerTest
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'Variableindex' Enumeration
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum Variableindex : size_t
{
	ENTER_COUNT,
	WAIT_COUNT,
	EXIT_COUNT
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'Variables' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Variables
{
public:

	// Public Type Definitions

		typedef shared_ptr< Variables > InstancePtr;

	// Public Constructors

		Variables()
		{
			// Initialize fields.

				enterCountVar = UNSET;
				waitCountVar = UNSET;
				exitCountVar = UNSET;
		}

	// Destructor

		virtual ~Variables()
		{
			// Do nothing.
		}

	// Public Methods

		void incCount( const Variableindex index )
		{
			// Obtain locks.

				SCOPED_WRITE_LOCK;

			// Increment variable based on specified index.

				switch( index )
				{
					case ENTER_COUNT:
					{
						enterCountVar++;

						break;
					}

					case WAIT_COUNT:
					{
						waitCountVar++;

						break;
					}

					case EXIT_COUNT:
					{
						exitCountVar++;

						break;
					}
				}
		}

		size_t getCount( const Variableindex index ) const
		{
			// Obtain locks.

				SCOPED_READ_LOCK;

			// Create local variables.

				size_t result = UNSET;

			// Get variable value based on specified index.

				switch( index )
				{
					case ENTER_COUNT:
					{
						result = enterCountVar;

						break;
					}

					case WAIT_COUNT:
					{
						result = waitCountVar; 
						break;
					}

					case EXIT_COUNT:
					{
						result = exitCountVar; 
						break;
					}
				}

			// Return result to calling routine.

				return result;
		}

private:

	// Private Fields

		mutable SharedMutexPair localMutex;
		size_t enterCountVar;
		size_t waitCountVar;
		size_t exitCountVar;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Definitions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void threadMainA( const string& groupID, bool doWait, Variables::InstancePtr vars )
{
	// Execute main code.

		vars->incCount( ENTER_COUNT );

		// Wait Scope
		{
			// Create scope variables.

				DisableInterruption diInstance;

			// Wait if 'doWait' is 'true'.

				if( doWait )
				{
					THREAD_MANAGER.wait( groupID );
					vars->incCount( WAIT_COUNT );
				}
		}

		try
		{
			while( true )
				THREAD_MANAGER.interruptionPoint();
		}
		catch( const ThreadInterrupted& except )
		{
			vars->incCount( EXIT_COUNT );
		}
}

void threadMainB( const string& groupID, bool doWait, Variables::InstancePtr vars )
{
	// Create local variables.

		bool isDone = false;

	// Execute main code.

		vars->incCount( ENTER_COUNT );

		// Wait Scope
		{
			// Create scope variables.

				DisableInterruption diInstance;

			// Wait if 'doWait' is 'true'.

				if( doWait )
				{
					THREAD_MANAGER.wait( groupID );
					vars->incCount( WAIT_COUNT );
				}
		}

		while( !isDone )
		{
			try
			{
				if( THREAD_MANAGER.interruptionRequested() )
				{
					vars->incCount( EXIT_COUNT );
					isDone = true;
				}
			}
			catch( const ThreadInterrupted& except )
			{
				// Do nothing.
			}
		}
}

void threadMainC( const string& groupID, bool doWait, Variables::InstancePtr vars )
{
	// Create local variables.

		DisableInterruption diInstance;
		bool isDone = false;

	// Execute main code.

		vars->incCount( ENTER_COUNT );

		// Wait Scope
		{
			// Create scope variables.

				DisableInterruption diInstance;

			// Wait if 'doWait' is 'true'.

				if( doWait )
				{
					THREAD_MANAGER.wait( groupID );
					vars->incCount( WAIT_COUNT );
				}
		}

		while( !isDone )
		{
			THREAD_MANAGER.interruptionPoint();

			if( THREAD_MANAGER.interruptionRequested() )
			{
				vars->incCount( EXIT_COUNT );
				isDone = true;
			}
		}
}

} // 'ThreadManagerTest' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'ThreadManagerTest' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'QMXStdLib::ThreadManager' Test Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST( ThreadManagerTest, CreateGroupWorks )
{
	// Create local variables.

		ThreadManager::InstancePtr instance = ThreadManager::create();

	// Perform unit test for 'createGroup' method.

		THREAD_MANAGER.createGroup( "TestGroupA" );
		THREAD_MANAGER.createGroup( "TestGroupB" );
		THREAD_MANAGER.createGroup( "TestGroupC" );
		ASSERT_THROW( THREAD_MANAGER.createGroup( "TestGroupA" ), QMXException );
		ASSERT_THROW( THREAD_MANAGER.createGroup( "TestGroupB" ), QMXException );
		ASSERT_THROW( THREAD_MANAGER.createGroup( "TestGroupC" ), QMXException );
}

TEST( ThreadManagerTest, GetGroupIDsWorks )
{
	// Create local variables.

		string expectedResults[] = {
			"TestGroupA",
		   "TestGroupB",
		   "TestGroupC"
		};

		ThreadManager::InstancePtr instance = ThreadManager::create();
		StringVector groupIDs;

	// Perform unit test for 'getgroupIDs' method.

		THREAD_MANAGER.createGroup( "TestGroupA" );
		THREAD_MANAGER.createGroup( "TestGroupB" );
		THREAD_MANAGER.createGroup( "TestGroupC" );
		THREAD_MANAGER.getGroupIDs( groupIDs );
		sort( groupIDs.begin(), groupIDs.end() );

		for( size_t index = 0; index < ARRAY_SIZE( expectedResults ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], groupIDs[ index ] );
		}
}

TEST( ThreadManagerTest, setBarrierSizeWorks )
{
	// Create local variables.

		ThreadManager::InstancePtr instance = ThreadManager::create();

	// Perform unit test for 'setBarrierSize' method.

		ASSERT_THROW( THREAD_MANAGER.setBarrierSize( "TestGroup", 5 ), QMXException );
		THREAD_MANAGER.createGroup( "TestGroup" );
		THREAD_MANAGER.setBarrierSize( "TestGroup", 5 );
}

TEST( ThreadManagerTest, CreateThreadWorks )
{
	// Create local variables.

		ThreadManager::InstancePtr instance = ThreadManager::create();
		ThreadManagerTest::Variables::InstancePtr vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'createThread' method.

		ASSERT_THROW( THREAD_MANAGER.createThread( "TestGroup", "TestThreadA", ThreadManagerTest::threadMainA, "TestGroup", false, vars ), QMXException );
		THREAD_MANAGER.createGroup( "TestGroup" );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadA", ThreadManagerTest::threadMainA, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadB", ThreadManagerTest::threadMainB, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadC", ThreadManagerTest::threadMainC, "TestGroup", false, vars );
		ASSERT_THROW( THREAD_MANAGER.createThread( "TestGroup", "TestThreadA", ThreadManagerTest::threadMainA, "TestGroup", false, vars ), QMXException );
		ASSERT_THROW( THREAD_MANAGER.createThread( "TestGroup", "TestThreadB", ThreadManagerTest::threadMainB, "TestGroup", false, vars ), QMXException );
		ASSERT_THROW( THREAD_MANAGER.createThread( "TestGroup", "TestThreadC", ThreadManagerTest::threadMainC, "TestGroup", false, vars ), QMXException );
		boost::this_thread::sleep_for( DELAY );
		ASSERT_EQ( 3, vars->getCount( ThreadManagerTest::ENTER_COUNT ) );
}

TEST( ThreadManagerTest, GetThreadIDsWorks )
{
	// Create local variables.

		string expectedResults[] = {
			"TestThreadA",
		   "TestThreadB",
		   "TestThreadC"
		};

		ThreadManager::InstancePtr instance = ThreadManager::create();
		ThreadManagerTest::Variables::InstancePtr vars = make_shared< ThreadManagerTest::Variables >();
		StringVector threadIDs;

	// Perform unit test for 'getThreadIDs' method.

		ASSERT_THROW( THREAD_MANAGER.getThreadIDs( "NonExistent", threadIDs ), QMXException );
		THREAD_MANAGER.createGroup( "TestGroup" );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadA", ThreadManagerTest::threadMainA, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadB", ThreadManagerTest::threadMainB, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadC", ThreadManagerTest::threadMainC, "TestGroup", false, vars );
		THREAD_MANAGER.getThreadIDs( "TestGroup", threadIDs );
		sort( threadIDs.begin(), threadIDs.end() );

		for( size_t index = 0; index < ARRAY_SIZE( expectedResults ); index++ )
		{
			ASSERT_EQ( expectedResults[ index ], threadIDs[ index ] );
		}
}

TEST( ThreadManagerTest, JoinWorks )
{
	// Create local variables.

		ThreadManager::InstancePtr instance = ThreadManager::create();
		ThreadManagerTest::Variables::InstancePtr vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'join' method.

		ASSERT_THROW( THREAD_MANAGER.join( "TestGroup", "TestThreadA" ), QMXException );
		THREAD_MANAGER.createGroup( "TestGroup" );
		ASSERT_THROW( THREAD_MANAGER.join( "TestGroup", "TestThreadA" ), QMXException );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadA", ThreadManagerTest::threadMainA, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadB", ThreadManagerTest::threadMainB, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadC", ThreadManagerTest::threadMainC, "TestGroup", false, vars );
		THREAD_MANAGER.interruptAll( "TestGroup" );
		THREAD_MANAGER.join( "TestGroup", "TestThreadA" );
		THREAD_MANAGER.join( "TestGroup", "TestThreadB" );
		THREAD_MANAGER.join( "TestGroup", "TestThreadC" );
		ASSERT_EQ( 3, vars->getCount( ThreadManagerTest::EXIT_COUNT ) );
}

TEST( ThreadManagerTest, TryJoinWorks )
{
	// Create local variables.

		ThreadManager::InstancePtr instance = ThreadManager::create();
		ThreadManagerTest::Variables::InstancePtr vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'tryJoin' method.

		ASSERT_THROW( THREAD_MANAGER.tryJoin( "TestGroup", "TestThreadA", Seconds( 1 ) ), QMXException );
		THREAD_MANAGER.createGroup( "TestGroup" );
		ASSERT_THROW( THREAD_MANAGER.tryJoin( "TestGroup", "TestThreadA", Seconds( 1 ) ), QMXException );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadA", ThreadManagerTest::threadMainA, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadB", ThreadManagerTest::threadMainB, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadC", ThreadManagerTest::threadMainC, "TestGroup", false, vars );
		ASSERT_FALSE( THREAD_MANAGER.tryJoin( "TestGroup", "TestThreadA", Seconds( 1 ) ) );
		ASSERT_FALSE( THREAD_MANAGER.tryJoin( "TestGroup", "TestThreadB", Seconds( 1 ) ) );
		ASSERT_FALSE( THREAD_MANAGER.tryJoin( "TestGroup", "TestThreadC", Seconds( 1 ) ) );
		THREAD_MANAGER.interruptAll( "TestGroup" );
		ASSERT_TRUE( THREAD_MANAGER.tryJoin( "TestGroup", "TestThreadA", Seconds( 1 ) ) );
		ASSERT_TRUE( THREAD_MANAGER.tryJoin( "TestGroup", "TestThreadB", Seconds( 1 ) ) );
		ASSERT_TRUE( THREAD_MANAGER.tryJoin( "TestGroup", "TestThreadC", Seconds( 1 ) ) );
		ASSERT_EQ( 3, vars->getCount( ThreadManagerTest::EXIT_COUNT ) );
}

TEST( ThreadManagerTest, JoinAllWorks )
{
	// Create local variables.

		ThreadManager::InstancePtr instance = ThreadManager::create();
		ThreadManagerTest::Variables::InstancePtr vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'joinAll' method.

		ASSERT_THROW( THREAD_MANAGER.joinAll( "TestGroup" ), QMXException );
		THREAD_MANAGER.createGroup( "TestGroup" );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadA", ThreadManagerTest::threadMainA, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadB", ThreadManagerTest::threadMainB, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadC", ThreadManagerTest::threadMainC, "TestGroup", false, vars );
		THREAD_MANAGER.interruptAll( "TestGroup" );
		THREAD_MANAGER.joinAll( "TestGroup" );
		ASSERT_EQ( 3, vars->getCount( ThreadManagerTest::EXIT_COUNT ) );
}

TEST( ThreadManagerTest, TryJoinAllWorks )
{
	// Create local variables.

		ThreadManager::InstancePtr instance = ThreadManager::create();
		ThreadManagerTest::Variables::InstancePtr vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'tryJoinAll' method.

		ASSERT_THROW( THREAD_MANAGER.tryJoinAll( "TestGroup", Seconds( 1 ) ), QMXException );
		THREAD_MANAGER.createGroup( "TestGroup" );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadA", ThreadManagerTest::threadMainA, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadB", ThreadManagerTest::threadMainB, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadC", ThreadManagerTest::threadMainC, "TestGroup", false, vars );
		ASSERT_FALSE( THREAD_MANAGER.tryJoinAll( "TestGroup", Seconds( 1 ) ) );
		THREAD_MANAGER.interruptAll( "TestGroup" );
		ASSERT_TRUE( THREAD_MANAGER.tryJoinAll( "TestGroup", Seconds( 1 ) ) );
		ASSERT_EQ( 3, vars->getCount( ThreadManagerTest::EXIT_COUNT ) );
}

TEST( ThreadManagerTest, InterruptWorks )
{
	// Create local variables.

		ThreadManager::InstancePtr instance = ThreadManager::create();
		ThreadManagerTest::Variables::InstancePtr vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'interrupt' method.

		ASSERT_THROW( THREAD_MANAGER.interrupt( "TestGroup", "TestThreadA" ), QMXException );
		THREAD_MANAGER.createGroup( "TestGroup" );
		ASSERT_THROW( THREAD_MANAGER.interrupt( "TestGroup", "TestThreadA" ), QMXException );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadA", ThreadManagerTest::threadMainA, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadB", ThreadManagerTest::threadMainB, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadC", ThreadManagerTest::threadMainC, "TestGroup", false, vars );
		THREAD_MANAGER.interrupt( "TestGroup", "TestThreadA" );
		THREAD_MANAGER.interrupt( "TestGroup", "TestThreadB" );
		THREAD_MANAGER.interrupt( "TestGroup", "TestThreadC" );
		ASSERT_TRUE( THREAD_MANAGER.tryJoinAll( "TestGroup", Seconds( 5 ) ) );
		ASSERT_EQ( 3, vars->getCount( ThreadManagerTest::EXIT_COUNT ) );
}

TEST( ThreadManagerTest, InterruptAllWorks )
{
	// Create local variables.

		ThreadManager::InstancePtr instance = ThreadManager::create();
		ThreadManagerTest::Variables::InstancePtr vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'interruptAll' method.

		ASSERT_THROW( THREAD_MANAGER.interruptAll( "TestGroup" ), QMXException );
		THREAD_MANAGER.createGroup( "TestGroup" );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadA", ThreadManagerTest::threadMainA, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadB", ThreadManagerTest::threadMainB, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadC", ThreadManagerTest::threadMainC, "TestGroup", false, vars );
		THREAD_MANAGER.interruptAll( "TestGroup" );
		ASSERT_TRUE( THREAD_MANAGER.tryJoinAll( "TestGroup", Seconds( 5 ) ) );
		ASSERT_EQ( 3, vars->getCount( ThreadManagerTest::EXIT_COUNT ) );
}

TEST( ThreadManagerTest, WaitWorks )
{
	// Create local variables.

		ThreadManager::InstancePtr instance = ThreadManager::create();
		ThreadManagerTest::Variables::InstancePtr vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'wait' method.

		ASSERT_THROW( THREAD_MANAGER.wait( "TestGroup" ), QMXException );
		THREAD_MANAGER.createGroup( "TestGroup" );
		THREAD_MANAGER.setBarrierSize( "TestGroup", 3 );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadA", ThreadManagerTest::threadMainA, "TestGroup", true, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadB", ThreadManagerTest::threadMainB, "TestGroup", true, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadC", ThreadManagerTest::threadMainC, "TestGroup", true, vars );
		THREAD_MANAGER.interruptAll( "TestGroup" );
		ASSERT_TRUE( THREAD_MANAGER.tryJoinAll( "TestGroup", Seconds( 5 ) ) );
		ASSERT_EQ( 3, vars->getCount( ThreadManagerTest::WAIT_COUNT ) );
}

TEST( ThreadManagerTest, DestroyThreadWorks )
{
	// Create local variables.

		ThreadManager::InstancePtr instance = ThreadManager::create();
		ThreadManagerTest::Variables::InstancePtr vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'destroyThread' method.

		ASSERT_THROW( THREAD_MANAGER.destroyThread( "TestGroup", "TestThreadA" ), QMXException );
		THREAD_MANAGER.createGroup( "TestGroup" );
		ASSERT_THROW( THREAD_MANAGER.destroyThread( "TestGroup", "TestThreadA" ), QMXException );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadA", ThreadManagerTest::threadMainA, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadB", ThreadManagerTest::threadMainB, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadC", ThreadManagerTest::threadMainC, "TestGroup", false, vars );
		THREAD_MANAGER.destroyThread( "TestGroup", "TestThreadA", false );
		THREAD_MANAGER.destroyThread( "TestGroup", "TestThreadB", false );
		THREAD_MANAGER.destroyThread( "TestGroup", "TestThreadC", false );
		boost::this_thread::sleep_for( DELAY );
		ASSERT_EQ( 0, vars->getCount( ThreadManagerTest::EXIT_COUNT ) );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadA", ThreadManagerTest::threadMainA, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadB", ThreadManagerTest::threadMainB, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadC", ThreadManagerTest::threadMainC, "TestGroup", false, vars );
		THREAD_MANAGER.destroyThread( "TestGroup", "TestThreadA" );
		THREAD_MANAGER.destroyThread( "TestGroup", "TestThreadB" );
		THREAD_MANAGER.destroyThread( "TestGroup", "TestThreadC" );
		boost::this_thread::sleep_for( DELAY );
		ASSERT_EQ( 3, vars->getCount( ThreadManagerTest::EXIT_COUNT ) );
}

TEST( ThreadManagerTest, DestroyGroupWorks )
{
	// Create local variables.

		ThreadManager::InstancePtr instance = ThreadManager::create();
		ThreadManagerTest::Variables::InstancePtr vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'destroyGroup' method.

		ASSERT_THROW( THREAD_MANAGER.destroyGroup( "TestGroup" ), QMXException );
		THREAD_MANAGER.createGroup( "TestGroup" );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadA", ThreadManagerTest::threadMainA, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadB", ThreadManagerTest::threadMainB, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadC", ThreadManagerTest::threadMainC, "TestGroup", false, vars );
		ASSERT_THROW( THREAD_MANAGER.destroyGroup( "TestGroup" ), QMXException );
		THREAD_MANAGER.destroyGroup( "TestGroup", true, false );
		boost::this_thread::sleep_for( DELAY );
		ASSERT_EQ( 0, vars->getCount( ThreadManagerTest::EXIT_COUNT ) );
		THREAD_MANAGER.createGroup( "TestGroup" );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadA", ThreadManagerTest::threadMainA, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadB", ThreadManagerTest::threadMainB, "TestGroup", false, vars );
		THREAD_MANAGER.createThread( "TestGroup", "TestThreadC", ThreadManagerTest::threadMainC, "TestGroup", false, vars );
		THREAD_MANAGER.destroyGroup( "TestGroup", true );
		boost::this_thread::sleep_for( DELAY );
		ASSERT_EQ( 3, vars->getCount( ThreadManagerTest::EXIT_COUNT ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ThreadManagerTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

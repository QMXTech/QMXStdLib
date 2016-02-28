////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ThreadManagerTest.cpp
// Robert M. Baker | Created : 26FEB16 | Last Modified : 27FEB16 by Robert M. Baker
// Version : 1.1.0
// This is a source file for 'QMXStdLibTest'; it defines a set of unit tests for the 'ThreadManager' class.
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

#include "../include/ThreadManagerTest.hpp"

using namespace std;
using namespace QMXStdLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'ThreadManagerTest' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ThreadManagerTest
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'VariableIndex' Enumeration
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum VariableIndex : size_t
{
	EnterCount,
	WaitCount,
	ExitCount
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'Variables' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Variables
{
public:

	// Public Type Definitions

		typedef shared_ptr< Variables > PointerType;

	// Public Constructors

		Variables()
		{
			// Initialize fields.

				EnterCountVar = Null;
				WaitCountVar = Null;
				ExitCountVar = Null;
		}

	// Destructor

		virtual ~Variables()
		{
			// Do nothing.
		}

	// Public Methods

		void IncCount( const VariableIndex Index )
		{
			// Obtain locks.

				SCOPED_WRITE_LOCK;

			// Increment variable based on specified index.

				switch( Index )
				{
					case EnterCount: { EnterCountVar++;  break; }
					case WaitCount: { WaitCountVar++;  break; }
					case ExitCount: { ExitCountVar++;  break; }
				}
		}

		size_t GetCount( const VariableIndex Index ) const
		{
			// Obtain locks.

				SCOPED_READ_LOCK;

			// Create local variables.

				size_t Result = Null;

			// Get variable value based on specified index.

				switch( Index )
				{
					case EnterCount: { Result = EnterCountVar;  break; }
					case WaitCount: { Result = WaitCountVar;  break; }
					case ExitCount: { Result = ExitCountVar;  break; }
				}

			// Return result to calling routine.

				return Result;
		}

private:

	// Private Fields

		mutable SharedMutex LocalMutex;
		size_t EnterCountVar;
		size_t WaitCountVar;
		size_t ExitCountVar;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Definitions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ThreadMainA( const string& GroupID, bool DoWait, Variables::PointerType Vars )
{
	// Execute main code.

		Vars->IncCount( EnterCount );

		// Wait Scope
		{
			// Create scope variables.

				DisableInterruption DIInstance;

			// Wait if 'DoWait' is 'true'.

				if( DoWait )
				{
					THREAD_MANAGER.Wait( GroupID );
					Vars->IncCount( WaitCount );
				}
		}

		try
		{
			while( true )
				THREAD_MANAGER.InterruptionPoint();
		}
		catch( const ThreadInterrupted& TargetException )
		{
			Vars->IncCount( ExitCount );
		}
}

void ThreadMainB( const string& GroupID, bool DoWait, Variables::PointerType Vars )
{
	// Create local variables.

		bool IsDone = false;

	// Execute main code.

		Vars->IncCount( EnterCount );

		// Wait Scope
		{
			// Create scope variables.

				DisableInterruption DIInstance;

			// Wait if 'DoWait' is 'true'.

				if( DoWait )
				{
					THREAD_MANAGER.Wait( GroupID );
					Vars->IncCount( WaitCount );
				}
		}

		while( !IsDone )
		{
			try
			{
				if( THREAD_MANAGER.InterruptionRequested() )
				{
					Vars->IncCount( ExitCount );
					IsDone = true;
				}
			}
			catch( const ThreadInterrupted& TargetException )
			{
				// Do nothing.
			}
		}
}

void ThreadMainC( const string& GroupID, bool DoWait, Variables::PointerType Vars )
{
	// Create local variables.

		DisableInterruption DIInstance;
		bool IsDone = false;

	// Execute main code.

		Vars->IncCount( EnterCount );

		// Wait Scope
		{
			// Create scope variables.

				DisableInterruption DIInstance;

			// Wait if 'DoWait' is 'true'.

				if( DoWait )
				{
					THREAD_MANAGER.Wait( GroupID );
					Vars->IncCount( WaitCount );
				}
		}

		while( !IsDone )
		{
			THREAD_MANAGER.InterruptionPoint();

			if( THREAD_MANAGER.InterruptionRequested() )
			{
				Vars->IncCount( ExitCount );
				IsDone = true;
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

		ThreadManager::PointerType Instance = ThreadManager::Create();

	// Perform unit test for 'CreateGroup' method.

		THREAD_MANAGER.CreateGroup( "TestGroupA" );
		THREAD_MANAGER.CreateGroup( "TestGroupB" );
		THREAD_MANAGER.CreateGroup( "TestGroupC" );
		ASSERT_THROW( THREAD_MANAGER.CreateGroup( "TestGroupA" ), QMXException );
		ASSERT_THROW( THREAD_MANAGER.CreateGroup( "TestGroupB" ), QMXException );
		ASSERT_THROW( THREAD_MANAGER.CreateGroup( "TestGroupC" ), QMXException );
}

TEST( ThreadManagerTest, SetBarrierSizeWorks )
{
	// Create local variables.

		ThreadManager::PointerType Instance = ThreadManager::Create();

	// Perform unit test for 'SetBarrierSize' method.

		ASSERT_THROW( THREAD_MANAGER.SetBarrierSize( "TestGroup", 5 ), QMXException );
		THREAD_MANAGER.CreateGroup( "TestGroup" );
		THREAD_MANAGER.SetBarrierSize( "TestGroup", 5 );
}

TEST( ThreadManagerTest, CreateThreadWorks )
{
	// Create local variables.

		ThreadManager::PointerType Instance = ThreadManager::Create();
		ThreadManagerTest::Variables::PointerType Vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'CreateThread' method.

		ASSERT_THROW( THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadA", ThreadManagerTest::ThreadMainA, "TestGroup", false, Vars ), QMXException );
		THREAD_MANAGER.CreateGroup( "TestGroup" );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadA", ThreadManagerTest::ThreadMainA, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadB", ThreadManagerTest::ThreadMainB, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadC", ThreadManagerTest::ThreadMainC, "TestGroup", false, Vars );
		ASSERT_THROW( THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadA", ThreadManagerTest::ThreadMainA, "TestGroup", false, Vars ), QMXException );
		ASSERT_THROW( THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadB", ThreadManagerTest::ThreadMainB, "TestGroup", false, Vars ), QMXException );
		ASSERT_THROW( THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadC", ThreadManagerTest::ThreadMainC, "TestGroup", false, Vars ), QMXException );
		boost::this_thread::sleep_for( DELAY );
		ASSERT_EQ( 3, Vars->GetCount( ThreadManagerTest::EnterCount ) );
}

TEST( ThreadManagerTest, JoinWorks )
{
	// Create local variables.

		ThreadManager::PointerType Instance = ThreadManager::Create();
		ThreadManagerTest::Variables::PointerType Vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'Join' method.

		ASSERT_THROW( THREAD_MANAGER.Join( "TestGroup", "TestThreadA" ), QMXException );
		THREAD_MANAGER.CreateGroup( "TestGroup" );
		ASSERT_THROW( THREAD_MANAGER.Join( "TestGroup", "TestThreadA" ), QMXException );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadA", ThreadManagerTest::ThreadMainA, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadB", ThreadManagerTest::ThreadMainB, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadC", ThreadManagerTest::ThreadMainC, "TestGroup", false, Vars );
		THREAD_MANAGER.InterruptAll( "TestGroup" );
		THREAD_MANAGER.Join( "TestGroup", "TestThreadA" );
		THREAD_MANAGER.Join( "TestGroup", "TestThreadB" );
		THREAD_MANAGER.Join( "TestGroup", "TestThreadC" );
		ASSERT_EQ( 3, Vars->GetCount( ThreadManagerTest::ExitCount ) );
}

TEST( ThreadManagerTest, TryJoinWorks )
{
	// Create local variables.

		ThreadManager::PointerType Instance = ThreadManager::Create();
		ThreadManagerTest::Variables::PointerType Vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'TryJoin' method.

		ASSERT_THROW( THREAD_MANAGER.TryJoin( "TestGroup", "TestThreadA", Seconds( 1 ) ), QMXException );
		THREAD_MANAGER.CreateGroup( "TestGroup" );
		ASSERT_THROW( THREAD_MANAGER.TryJoin( "TestGroup", "TestThreadA", Seconds( 1 ) ), QMXException );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadA", ThreadManagerTest::ThreadMainA, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadB", ThreadManagerTest::ThreadMainB, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadC", ThreadManagerTest::ThreadMainC, "TestGroup", false, Vars );
		ASSERT_FALSE( THREAD_MANAGER.TryJoin( "TestGroup", "TestThreadA", Seconds( 1 ) ) );
		ASSERT_FALSE( THREAD_MANAGER.TryJoin( "TestGroup", "TestThreadB", Seconds( 1 ) ) );
		ASSERT_FALSE( THREAD_MANAGER.TryJoin( "TestGroup", "TestThreadC", Seconds( 1 ) ) );
		THREAD_MANAGER.InterruptAll( "TestGroup" );
		ASSERT_TRUE( THREAD_MANAGER.TryJoin( "TestGroup", "TestThreadA", Seconds( 1 ) ) );
		ASSERT_TRUE( THREAD_MANAGER.TryJoin( "TestGroup", "TestThreadB", Seconds( 1 ) ) );
		ASSERT_TRUE( THREAD_MANAGER.TryJoin( "TestGroup", "TestThreadC", Seconds( 1 ) ) );
		ASSERT_EQ( 3, Vars->GetCount( ThreadManagerTest::ExitCount ) );
}

TEST( ThreadManagerTest, JoinAllWorks )
{
	// Create local variables.

		ThreadManager::PointerType Instance = ThreadManager::Create();
		ThreadManagerTest::Variables::PointerType Vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'JoinAll' method.

		ASSERT_THROW( THREAD_MANAGER.JoinAll( "TestGroup" ), QMXException );
		THREAD_MANAGER.CreateGroup( "TestGroup" );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadA", ThreadManagerTest::ThreadMainA, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadB", ThreadManagerTest::ThreadMainB, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadC", ThreadManagerTest::ThreadMainC, "TestGroup", false, Vars );
		THREAD_MANAGER.InterruptAll( "TestGroup" );
		THREAD_MANAGER.JoinAll( "TestGroup" );
		ASSERT_EQ( 3, Vars->GetCount( ThreadManagerTest::ExitCount ) );
}

TEST( ThreadManagerTest, TryJoinAllWorks )
{
	// Create local variables.

		ThreadManager::PointerType Instance = ThreadManager::Create();
		ThreadManagerTest::Variables::PointerType Vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'TryJoinAll' method.

		ASSERT_THROW( THREAD_MANAGER.TryJoinAll( "TestGroup", Seconds( 1 ) ), QMXException );
		THREAD_MANAGER.CreateGroup( "TestGroup" );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadA", ThreadManagerTest::ThreadMainA, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadB", ThreadManagerTest::ThreadMainB, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadC", ThreadManagerTest::ThreadMainC, "TestGroup", false, Vars );
		ASSERT_FALSE( THREAD_MANAGER.TryJoinAll( "TestGroup", Seconds( 1 ) ) );
		THREAD_MANAGER.InterruptAll( "TestGroup" );
		ASSERT_TRUE( THREAD_MANAGER.TryJoinAll( "TestGroup", Seconds( 1 ) ) );
		ASSERT_EQ( 3, Vars->GetCount( ThreadManagerTest::ExitCount ) );
}

TEST( ThreadManagerTest, InterruptWorks )
{
	// Create local variables.

		ThreadManager::PointerType Instance = ThreadManager::Create();
		ThreadManagerTest::Variables::PointerType Vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'Interrupt' method.

		ASSERT_THROW( THREAD_MANAGER.Interrupt( "TestGroup", "TestThreadA" ), QMXException );
		THREAD_MANAGER.CreateGroup( "TestGroup" );
		ASSERT_THROW( THREAD_MANAGER.Interrupt( "TestGroup", "TestThreadA" ), QMXException );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadA", ThreadManagerTest::ThreadMainA, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadB", ThreadManagerTest::ThreadMainB, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadC", ThreadManagerTest::ThreadMainC, "TestGroup", false, Vars );
		THREAD_MANAGER.Interrupt( "TestGroup", "TestThreadA" );
		THREAD_MANAGER.Interrupt( "TestGroup", "TestThreadB" );
		THREAD_MANAGER.Interrupt( "TestGroup", "TestThreadC" );
		ASSERT_TRUE( THREAD_MANAGER.TryJoinAll( "TestGroup", Seconds( 5 ) ) );
		ASSERT_EQ( 3, Vars->GetCount( ThreadManagerTest::ExitCount ) );
}

TEST( ThreadManagerTest, InterruptAllWorks )
{
	// Create local variables.

		ThreadManager::PointerType Instance = ThreadManager::Create();
		ThreadManagerTest::Variables::PointerType Vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'InterruptAll' method.

		ASSERT_THROW( THREAD_MANAGER.InterruptAll( "TestGroup" ), QMXException );
		THREAD_MANAGER.CreateGroup( "TestGroup" );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadA", ThreadManagerTest::ThreadMainA, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadB", ThreadManagerTest::ThreadMainB, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadC", ThreadManagerTest::ThreadMainC, "TestGroup", false, Vars );
		THREAD_MANAGER.InterruptAll( "TestGroup" );
		ASSERT_TRUE( THREAD_MANAGER.TryJoinAll( "TestGroup", Seconds( 5 ) ) );
		ASSERT_EQ( 3, Vars->GetCount( ThreadManagerTest::ExitCount ) );
}

TEST( ThreadManagerTest, WaitWorks )
{
	// Create local variables.

		ThreadManager::PointerType Instance = ThreadManager::Create();
		ThreadManagerTest::Variables::PointerType Vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'Wait' method.

		ASSERT_THROW( THREAD_MANAGER.Wait( "TestGroup" ), QMXException );
		THREAD_MANAGER.CreateGroup( "TestGroup" );
		THREAD_MANAGER.SetBarrierSize( "TestGroup", 3 );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadA", ThreadManagerTest::ThreadMainA, "TestGroup", true, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadB", ThreadManagerTest::ThreadMainB, "TestGroup", true, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadC", ThreadManagerTest::ThreadMainC, "TestGroup", true, Vars );
		THREAD_MANAGER.InterruptAll( "TestGroup" );
		ASSERT_TRUE( THREAD_MANAGER.TryJoinAll( "TestGroup", Seconds( 5 ) ) );
		ASSERT_EQ( 3, Vars->GetCount( ThreadManagerTest::WaitCount ) );
}

TEST( ThreadManagerTest, DestroyThreadWorks )
{
	// Create local variables.

		ThreadManager::PointerType Instance = ThreadManager::Create();
		ThreadManagerTest::Variables::PointerType Vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'DestroyThread' method.

		ASSERT_THROW( THREAD_MANAGER.DestroyThread( "TestGroup", "TestThreadA" ), QMXException );
		THREAD_MANAGER.CreateGroup( "TestGroup" );
		ASSERT_THROW( THREAD_MANAGER.DestroyThread( "TestGroup", "TestThreadA" ), QMXException );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadA", ThreadManagerTest::ThreadMainA, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadB", ThreadManagerTest::ThreadMainB, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadC", ThreadManagerTest::ThreadMainC, "TestGroup", false, Vars );
		THREAD_MANAGER.DestroyThread( "TestGroup", "TestThreadA", false );
		THREAD_MANAGER.DestroyThread( "TestGroup", "TestThreadB", false );
		THREAD_MANAGER.DestroyThread( "TestGroup", "TestThreadC", false );
		boost::this_thread::sleep_for( DELAY );
		ASSERT_EQ( 0, Vars->GetCount( ThreadManagerTest::ExitCount ) );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadA", ThreadManagerTest::ThreadMainA, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadB", ThreadManagerTest::ThreadMainB, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadC", ThreadManagerTest::ThreadMainC, "TestGroup", false, Vars );
		THREAD_MANAGER.DestroyThread( "TestGroup", "TestThreadA" );
		THREAD_MANAGER.DestroyThread( "TestGroup", "TestThreadB" );
		THREAD_MANAGER.DestroyThread( "TestGroup", "TestThreadC" );
		boost::this_thread::sleep_for( DELAY );
		ASSERT_EQ( 3, Vars->GetCount( ThreadManagerTest::ExitCount ) );
}

TEST( ThreadManagerTest, DestroyGroupWorks )
{
	// Create local variables.

		ThreadManager::PointerType Instance = ThreadManager::Create();
		ThreadManagerTest::Variables::PointerType Vars = make_shared< ThreadManagerTest::Variables >();

	// Perform unit test for 'DestroyGroup' method.

		ASSERT_THROW( THREAD_MANAGER.DestroyGroup( "TestGroup" ), QMXException );
		THREAD_MANAGER.CreateGroup( "TestGroup" );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadA", ThreadManagerTest::ThreadMainA, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadB", ThreadManagerTest::ThreadMainB, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadC", ThreadManagerTest::ThreadMainC, "TestGroup", false, Vars );
		ASSERT_THROW( THREAD_MANAGER.DestroyGroup( "TestGroup" ), QMXException );
		THREAD_MANAGER.DestroyGroup( "TestGroup", true, false );
		boost::this_thread::sleep_for( DELAY );
		ASSERT_EQ( 0, Vars->GetCount( ThreadManagerTest::ExitCount ) );
		THREAD_MANAGER.CreateGroup( "TestGroup" );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadA", ThreadManagerTest::ThreadMainA, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadB", ThreadManagerTest::ThreadMainB, "TestGroup", false, Vars );
		THREAD_MANAGER.CreateThread( "TestGroup", "TestThreadC", ThreadManagerTest::ThreadMainC, "TestGroup", false, Vars );
		THREAD_MANAGER.DestroyGroup( "TestGroup", true );
		boost::this_thread::sleep_for( DELAY );
		ASSERT_EQ( 3, Vars->GetCount( ThreadManagerTest::ExitCount ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'ThreadManagerTest.cpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

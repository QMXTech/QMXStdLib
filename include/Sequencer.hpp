////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sequencer.hpp
// Robert M. Baker | Created : 29FEB12 | Last Modified : 28FEB16 by Robert M. Baker
// Version : 1.1.2
// This is a header file for 'QMXStdLib'; it defines the interface for a numeric sequencer class.
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

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 29FEB12
  * @date    Last Modified : 28FEB16 by Robert M. Baker
  * @version 1.1.2
  *
  * @brief This header file defines the interface for a numeric sequencer class.
  *
  * @section Description
  *
  * This header file defines the interface for a numeric sequencer class.
  *
  * @section License
  *
  * Copyright (C) 2011-2016 QuantuMatriX Software, LLP.
  *
  * This file is part of 'QMXStdLib'.
  *
  * 'QMXStdLib' is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free
  * Software Foundation, either version 3 of the License, or (at your option) any later version.
  *
  * 'QMXStdLib' is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  * A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public License along with 'QMXStdLib'.  If not, see <http://www.gnu.org/licenses/>.
  */

#ifndef __QMX_QMXSTDLIB_SEQUENCER_HPP_
#define __QMX_QMXSTDLIB_SEQUENCER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Base.hpp"
#include "Object.hpp"
#include "RAII/ScopedStackTrace.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'SequencerProperties' Structure
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief This structure holds the public properties for the 'Sequencer' class.
  */

template< typename NType > struct SequencerProperties
{
public:

	// Public Fields

		/**
		  * @brief This is the flag which determines if the sequencer will loop upon reaching the end of the sequence.
		  */

		bool IsLooped;

		/**
		  * @brief This is the current sequencer mode.
		  */

		int SequenceMode;

		/**
		  * @brief This is the minimum value of the sequencer.
		  */

		NType Minimum;

		/**
		  * @brief This is the maximum value of the sequencer.
		  */

		NType Maximum;

		/**
		  * @brief This is the amount to step the sequencer each time it is incremented or decremented.
		  */

		NType Step;

		/**
		  * @brief This is the current value of the sequencer.
		  */

		NType Value;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'Sequencer' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class Sequencer Sequencer.hpp "include/Sequencer.hpp"
  *
  * @brief This class defines numeric sequencing algorithms.
  *
  * These algorithms are useful when is necessary to control such things as animation logic.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Yes
  */

template< typename NType > class Sequencer : public Object< Sequencer< NType >, SequencerProperties< NType > >
{
	// Friend Classes

		friend class Object< Sequencer< NType >, SequencerProperties< NType > >;

public:

	// Public Data Types

		/**
		  * @brief This enumeration defines all valid sequencer modes.
		  */

		enum Mode
		{
			Linear,
			Oscillate
		};

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		virtual ~Sequencer()
		{
			// Perform necessary cleanup.

				if( this->Initialized )
					this->Deallocate();
		}

	// Public Overloaded Operators

		/**
		  * @brief This is the overloaded post-increment operator, which will step the sequencer forward.
		  *
		  * If the 'SequenceMode' property is set to an out-of-range value, this operation will have no effect.
		  */

		void operator++( int )
		{
			// Obtain locks.

				SCOPED_WRITE_LOCK;

			// Create local variables.

				SequencerProperties< NType >* PP = &(this->Properties);

			// Perform post-increment operator logic.

				switch( PP->SequenceMode )
				{
					case Linear:
					{
						if( PP->Value < PP->Maximum )
							PP->Value += PP->Step;
						else if( PP->IsLooped && ( PP->Value == PP->Maximum ) )
							PP->Value = PP->Minimum;

						if( PP->Value > PP->Maximum )
							PP->Value = PP->Maximum;

						break;
					}

					case Oscillate:
					{
						if( !OscillationFlag )
						{
							if( PP->Value < PP->Maximum )
								PP->Value += PP->Step;
							else if( PP->Value == PP->Maximum )
							{
								PP->Value -= PP->Step;
								OscillationFlag = true;
							}

							if( PP->Value > PP->Maximum )
								PP->Value = PP->Maximum;
						}
						else
						{
							if( PP->Value > PP->Minimum )
								PP->Value -= PP->Step;
							else if( PP->IsLooped && ( PP->Value == PP->Minimum ) )
							{
								PP->Value += PP->Step;
								OscillationFlag = false;
							}

							if( PP->Value < PP->Minimum )
								PP->Value = PP->Minimum;
						}

						break;
					}

					default:
					{
						// Do nothing.
					}
				}
		}

		/**
		  * @brief This is the overloaded post-decrement operator, which will step the sequencer backward.
		  *
		  * If the 'SequenceMode' property is set to an out-of-range value, this operation will have no effect.
		  */

		void operator--( int )
		{
			// Obtain locks.

				SCOPED_WRITE_LOCK;

			// Create local variables.

				SequencerProperties< NType >* PP = &(this->Properties);

			// Perform post-decrement operator logic.

				switch( PP->SequenceMode )
				{
					case Linear:
					{
						if( PP->Value > PP->Minimum )
							PP->Value -= PP->Step;
						else if( PP->IsLooped && ( PP->Value == PP->Minimum ) )
							PP->Value = PP->Maximum;

						if( PP->Value < PP->Minimum )
							PP->Value = PP->Minimum;

						break;
					}

					case Oscillate:
					{
						if( !OscillationFlag )
						{
							if( PP->Value > PP->Minimum )
								PP->Value -= PP->Step;
							else if( PP->Value == PP->Minimum )
							{
								PP->Value += PP->Step;
								OscillationFlag = true;
							}

							if( PP->Value < PP->Minimum )
								PP->Value = PP->Minimum;
						}
						else
						{
							if( PP->Value < PP->Maximum )
								PP->Value += PP->Step;
							else if( PP->IsLooped && ( PP->Value == PP->Maximum ) )
							{
								PP->Value -= PP->Step;
								OscillationFlag = false;
							}

							if( PP->Value > PP->Maximum )
								PP->Value = PP->Maximum;
						}

						break;
					}

					default:
					{
						// Do nothing.
					}
				}
		}

		/**
		  * @brief This method gets the current sequencer value.
		  *
		  * @return
		  * 	The current sequencer value.
		  */

		NType GetValue() const
		{
			// Obtain locks.

				SCOPED_READ_LOCK;

			// Return current sequencer value to calling routine.

				return this->Properties.Value;
		}

private:

	// Private Fields

		/**
		  * @brief This is a state flag used by the ocillation algorithms.
		  */

		bool OscillationFlag;

	// Private Constructors

		/**
		  * @brief This is the default constructor, which is made private to prevent direct instantiation.
		  */

		Sequencer()
		{
			// Initialize fields.

				ZERO_MEMORY( &(this->Properties), sizeof( SequencerProperties< NType > ) );
				OscillationFlag = false;
		}

	// Private Methods

		/**
		  * @brief This is the overridden implementation for the 'operator=' method.
		  *
		  * @param Instance
		  * 	This is the 'Object' pointer with which to set 'this'.
		  */

		void OperatorAssignImp( const Object< Sequencer< NType >, SequencerProperties< NType > >* Instance )
		{
			// Create local variables.

				const Sequencer* DInstance = dynamic_cast< const Sequencer* >( Instance );

			// Assign specified object to 'this'.

				OscillationFlag = DInstance->OscillationFlag;
		}

		/**
		  * @brief This is the overridden implementation for the 'Clone' method.
		  *
		  * @return
		  * 	A pointer to a copy of this object.
		  */

		CLONE_IMP_T( Sequencer< NType > )
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_SEQUENCER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'Sequencer.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

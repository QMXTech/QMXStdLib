////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sequencer.hpp
// Robert M. Baker | Created : 29FEB12 | Last Modified : 29AUG19 by Robert M. Baker
// Version : 2.1.1
// This is a header file for 'QMXStdLib'; it defines the interface for a numeric sequencer class.
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

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 29FEB12
  * @date    Last Modified : 29AUG19 by Robert M. Baker
  * @version 2.1.1
  *
  * @brief This header file defines the interface for a numeric sequencer class.
  *
  * @section SequencerH0000 Description
  *
  * This header file defines the interface for a numeric sequencer class.
  *
  * @section SequencerH0001 License
  *
  * Copyright (C) 2011-2019 QuantuMatriX Software, a QuantuMatriX Technologies Cooperative Partnership
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
#include "RAII/ScopedLock.hpp"
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

		bool isLooped;

		/**
		  * @brief This is the current sequencer mode.
		  */

		int sequenceMode;

		/**
		  * @brief This is the minimum value of the sequencer.
		  */

		NType minimum;

		/**
		  * @brief This is the maximum value of the sequencer.
		  */

		NType maximum;

		/**
		  * @brief This is the amount to step the sequencer each time it is incremented or decremented.
		  */

		NType step;

		/**
		  * @brief This is the current value of the sequencer.
		  */

		NType value;
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
			LINEAR,
			OSCILLATE
		};

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		~Sequencer()
		{
			try
			{
				// Perform necessary cleanup.

					if( this->initialized )
						this->deallocate();
			}
			catch( const std::exception& except )
			{
				// Do nothing.
			}
		}

	// Public Methods

		/**
		  * @brief This method gets the current sequencer value.
		  *
		  * @return
		  * 	The current sequencer value.
		  */

		NType getValue() const
		{
			// Obtain locks.

				SCOPED_READ_LOCK;

			// Return current sequencer value to calling routine.

				return this->properties.value;
		}

	// Public Overloaded Operators

		/**
		  * @brief This is the overloaded post-increment operator, which will step the sequencer forward.
		  *
		  * If the 'sequenceMode' property is set to an out-of-range value, this operation will have no effect.
		  */

		void operator++( int )
		{
			// Obtain locks.

				SCOPED_WRITE_LOCK;

			// Create local variables.

				SequencerProperties< NType >* PP = &this->properties;

			// Perform post-increment operator logic.

				switch( PP->sequenceMode )
				{
					case LINEAR:
					{
						if( PP->value < PP->maximum )
							PP->value += PP->step;
						else if( PP->isLooped && ( PP->value == PP->maximum ) )
							PP->value = PP->minimum;

						if( PP->value > PP->maximum )
							PP->value = PP->maximum;

						break;
					}

					case OSCILLATE:
					{
						if( !oscillationFlag )
						{
							if( PP->value < PP->maximum )
								PP->value += PP->step;
							else if( PP->value == PP->maximum )
							{
								PP->value -= PP->step;
								oscillationFlag = true;
							}

							if( PP->value > PP->maximum )
								PP->value = PP->maximum;
						}
						else
						{
							if( PP->value > PP->minimum )
								PP->value -= PP->step;
							else if( PP->isLooped && ( PP->value == PP->minimum ) )
							{
								PP->value += PP->step;
								oscillationFlag = false;
							}

							if( PP->value < PP->minimum )
								PP->value = PP->minimum;
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

				SequencerProperties< NType >* PP = &this->properties;

			// Perform post-decrement operator logic.

				switch( PP->sequenceMode )
				{
					case LINEAR:
					{
						if( PP->value > PP->minimum )
							PP->value -= PP->step;
						else if( PP->isLooped && ( PP->value == PP->minimum ) )
							PP->value = PP->maximum;

						if( PP->value < PP->minimum )
							PP->value = PP->minimum;

						break;
					}

					case OSCILLATE:
					{
						if( !oscillationFlag )
						{
							if( PP->value > PP->minimum )
								PP->value -= PP->step;
							else if( PP->value == PP->minimum )
							{
								PP->value += PP->step;
								oscillationFlag = true;
							}

							if( PP->value < PP->minimum )
								PP->value = PP->minimum;
						}
						else
						{
							if( PP->value < PP->maximum )
								PP->value += PP->step;
							else if( PP->isLooped && ( PP->value == PP->maximum ) )
							{
								PP->value -= PP->step;
								oscillationFlag = false;
							}

							if( PP->value > PP->maximum )
								PP->value = PP->maximum;
						}

						break;
					}

					default:
					{
						// Do nothing.
					}
				}
		}

private:

	// Private Fields

		/**
		  * @brief This is a state flag used by the ocillation algorithms.
		  */

		bool oscillationFlag;

	// Private Constructors

		/**
		  * @brief This is the default constructor, which is made private to prevent direct instantiation.
		  */

		Sequencer()
		{
			// Initialize fields.

				ZERO_MEMORY( &this->properties, sizeof( SequencerProperties< NType > ) );
				oscillationFlag = false;
		}

	// Private Methods

		/**
		  * @brief This is the overridden implementation for the 'Clone' method.
		  *
		  * @param target
		  * 	This is the object pointer to use when setting.
		  */

		void cloneImp( typename Sequencer< NType >::InstancePtr& target ) const
		{
			// Assign data of 'this' to specified object.

				target->oscillationFlag = oscillationFlag;
		}
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_SEQUENCER_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'Sequencer.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Stringizable.hpp
// Robert M. Baker | Created : 04MAR12 | Last Modified : 27AUG19 by Robert M. Baker
// Version : 2.0.0
// This is a header file for 'QMXStdLib'; it defines the interface for a mixin class to allow for string representation of an object.
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
  * @date    Created : 04MAR12
  * @date    Last Modified : 27AUG19 by Robert M. Baker
  * @version 2.0.0
  *
  * @brief This header file defines the interface for a mixin class to allow for string representation of an object.
  *
  * @section StringizableH0000 Description
  *
  * This header file defines the interface for a mixin class to allow for string representation of an object.
  *
  * @section StringizableH0001 License
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

#ifndef __QMX_QMXSTDLIB_STRINGIZABLE_HPP_
#define __QMX_QMXSTDLIB_STRINGIZABLE_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../Base.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'Stringizable' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class Stringizable Stringizable.hpp "include/Mixins/Stringizable.hpp"
  *
  * @brief This class defines a mixin interface to allow acquisition of a string representation of an object.
  *
  * This is useful when it would be convenient to acquire string representations of objects, such as for debugging purposes.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Conditionally (The sub-class must implement '*Imp' in a thread-safe manner.)
  */

class Stringizable
{
public:

	// Public Data Types

		/**
		  * @brief This enumeration is used by the to-string algorithm to determine numeric base.
		  */

		enum NumericBase
		{
			NONE,
			BINARY,
			OCTAL,
			DECIMAL,
			HEXIDECIMAL
		};

		/**
		  * @brief This structure defines options used by the to-string algorithm.
		  */

		struct StringFormat
		{
		public:

			// Public Fields

				/**
				  * @brief This is the flag to determine if prefixes should be used for binary, octal, or hexidecimal values.
				  */

				bool usePrefix;

				/**
				  * @brief This is the flag to determine case of any letters appearing in the conversion.
				  */

				bool useUpperCase;

				/**
				  * @brief This is the flag to determine if boolean values will yield 'yes/no' instead of 'true/false'.
				  */

				bool useYesNo;

				/**
				  * @brief This is the flag to determine if character values are treated as integers.
				  */

				bool charsAsInts;

				/**
				  * @brief This is the fill character to use for padding if needed.
				  */

				char filler;

				/**
				  * @brief This is the minimum width to use when converting the numerical value.
				  */

				int32_t width;

				/**
				  * @brief This is the floating point precision to use when converting the numerical value.
				  */

				int32_t precision;

				/**
				  * @brief This is the numerical base to use for the conversion.
				  */

				NumericBase base;
		};

	// Public Constructors

		/**
		  * @brief This is the default constructor.
		  */

		Stringizable()
		{
			// Do nothing.
		}

	// Destructor

		/**
		  * @brief This is the destructor.
		  */

		virtual ~Stringizable()
		{
			// Do nothing.
		}

	// Public Methods

		/**
		  * @brief This method constructs a string representation of this object.
		  *
		  * @return
		  * 	A string representing this object.
		  */

		std::string toString() const
		{
			// Return a string representation of this object to calling routine.

				return toStringImp();
		}

		/**
		  * @brief This method sets the specified string format struct to the default settings for the specified numeric base.
		  *
		  * 	If the numeric base is set to 'NONE', then it will default to decimal.
		  *
		  * @param target
		  * 	This is the string format struct to set to the default settings.
		  *
		  * @param base
		  * 	This is the numeric base that determines the default settings; if it is given an out-of-range value, it will be set to decimal.
		  */

		static void setStringFormat( StringFormat& target, NumericBase base = DECIMAL )
		{
			// Set the specified string format struct to the default settings for the specified numeric base.

				switch( base )
				{
					case BINARY:
					{
						target = { true, false, false, true, '0', 0, 0 };

						break;
					}

					case OCTAL:
					{
						target = { true, false, false, false, '0', 0, 0 };

						break;
					}

					case NONE:
					case DECIMAL:
					{
						target = { false, false, false, false, '0', 0, 5 };

						break;
					}

					case HEXIDECIMAL:
					{
						target = { true, true, false, false, '0', 16, 0 };

						break;
					}
				}

				target.base = base;
		}

private:

	// Private Methods

		/**
		  * @brief This is the overridable implementation for the 'toString' method.
		  *
		  * @return
		  * 	A string representing this object.
		  */

		virtual std::string toStringImp() const = PURE_VIRTUAL;
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_STRINGIZABLE_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'Stringizable.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
